/**
 * @file grain.cpp
 * @author Adhish Majumdar
 * @version 1.3
 * @date 20/11/2013
 * @brief Definition of the Grain class member functions.
 * @details This file defines member functions of the Grain class representing an grain/crystal in the simulation. A grain is considered to be a collection of slip systems.
 */

/*
    DD2D-Matryoshka approach.
    A set of classes defining the behaviour of crystalline defects,
    with the final goal of carrying out dislocation dynamics simulations
    in two dimensions.
    Copyright (C) 2013  Adhish Majumdar
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/ 

#include "grain.h"

/**
 * @brief Default constructor for the Grain class.
 */
Grain::Grain ()
{
    Vector3d centroid (DEFAULT_CENTROID_X1, DEFAULT_CENTROID_X2, DEFAULT_CENTROID_X3);
    double phi[3];

    phi[0] = DEFAULT_ORIENTATION_PHI1;
    phi[1] = DEFAULT_ORIENTATION_PHI;
    phi[2] = DEFAULT_ORIENTATION_PHI2;

    this->coordinateSystem = CoordinateSystem(phi, centroid);
}

/**
 * @brief Constructor for the class Grain, specifying all details.
 * @details All details are provided to the constructor.  For the moment only one slip system is active per grain, so only one normal and only one slip direction are given. This may be modified in the future when multiple slip will be handled.
 * @param phi Pointer to the array containing the three Euler angles representing the grain orientation.
 * @param points An STL vector container with the position vectors, in the base (polycrystal) co-ordinate system, of the points that make up the grain boundary. These points must be given in a fixed sequence, either clockwise or anti-clockwise.
 * @param slipSystemNormal Miller indices, in the crystallographic frame (grain co-ordinate system), of the slip system normal.
 * @param slipPlanePositions STL vector containing the positions of slip planes on the slip system normal.
 * @param dislocations Pointer to an array of vector containers with dislocations for the slip planes.
 * @param dislocationSources Pointer to an array of vector containers with dislocation sources for the slip planes.
 */
Grain::Grain(double* phi, std::vector<Vector3d> points, Vector3d slipSystemNormal, std::vector<double> slipPlanePositions, std::vector<Dislocation*> *dislocations, std::vector<DislocationSource*> *dislocationSources)
{
    Vector3d centroid = mean (points);

    this->coordinateSystem = CoordinateSystem(phi, centroid);

    /**
     * @brief viewPlaneNormal This is the polycrystal Z-axis, expressed in the local co-ordinate system.
     */
    Vector3d viewPlaneNormal = this->coordinateSystem.vector_BaseToLocal_noTranslate(Vector3d::unitVector(2));

    /**
     * @brief slipPlaneTrace The trace of the slip plane on the view plane.
     * @details The trace of the slip plane on the view plane is required in order to calculate the extremities of the slip planes, which in turn will define the boundaries of the grain.
     */
    Vector3d slipPlaneTrace = (viewPlaneNormal ^ slipSystemNormal).normalize();

    /**
     * @brief slipNormalTrace The trace of the slip system normal on the view plane.
     * @details The trace of the slip system normal is the projection of the slip system normal on to the view plane. It is perpendicular to both the slip splane trace and the view plane normal.
     */
    Vector3d slipNormalTrace = (viewPlaneNormal ^ slipPlaneTrace).normalize();

    // Get the grain boundary points in the local co-ordinate system
    this->gbPoints_base = points;
    this->gbPoints_local = this->coordinateSystem.vector_BaseToLocal(points);

    // Create the slip system
    SlipSystem* s = new SlipSystem;
    s->setPosition(centroid);
    s->setNormal(slipSystemNormal);
    s->setDirection(slipPlaneTrace);
    s->createCoordinateSystem(this->getCoordinateSystem());
    this->slipSystems.clear();
    this->slipSystems.push_back(s);
    s->clearSlipPlanes();

    // Go through slip plane positions
    std::vector<double>::iterator slipPlanePositions_it;
    std::vector<Vector3d>::iterator gbPoints_it;
    Vector3d P, Q, R;   // Vectors for detecting intersections with the grain boundary
    Vector3d R_slipSystem;  // Slip Plane position in the Slip System frame of reference
    Vector3d* S = new Vector3d[2];
    Vector3d* S_slipSystem = new Vector3d[2];
    SlipPlane* slipPlane;
    int nIntersections;
    int nSlipPlane = 0;
    for (slipPlanePositions_it=slipPlanePositions.begin(); slipPlanePositions_it!=slipPlanePositions.end(); slipPlanePositions_it++) {
        // Point through which the slip plane vector will pass
        R = slipNormalTrace * (*slipPlanePositions_it);
        nIntersections = 0;
        for (gbPoints_it = this->gbPoints_local.begin(); gbPoints_it!=this->gbPoints_local.end()-1; gbPoints_it++) {
            P = *gbPoints_it;
            Q = *(gbPoints_it+1);
            if (intersection(R, slipPlaneTrace, P, Q, (S+nIntersections))) {
                nIntersections++;
            }
            if (nIntersections==2) {
                break;
            }
        }
        R_slipSystem = (s->getCoordinateSystem())->vector_BaseToLocal(R);
        S_slipSystem[0] = (s->getCoordinateSystem())->vector_BaseToLocal(S[0]);
        S_slipSystem[1] = (s->getCoordinateSystem())->vector_BaseToLocal(S[1]);
        slipPlane = new SlipPlane(S_slipSystem, R_slipSystem, s->getCoordinateSystem(), dislocations[nSlipPlane], dislocationSources[nSlipPlane]);
        nSlipPlane++;
        s->insertSlipPlane(slipPlane);
    }

    // Delete the position vectors allocated
    delete[] (S);
    delete[] (S_slipSystem);
}

// Destructor
/**
 * @brief Destructor for the class Grain.
 */
Grain::~Grain()
{
    std::vector<SlipSystem*>::iterator s_it;
    SlipSystem* s;

    // Delete individual slip systems
    for (s_it=this->slipSystems.begin(); s_it!=this->slipSystems.end(); s_it++) {
        s = *s_it;
        delete (s);
        s = NULL;
        *s_it = NULL;
    }

    // Clear the vector of pointers
    this->slipSystems.clear();
}

// Assignment functions
/**
 * @brief Set the crystallographic orientation of the grain.
 * @param p Pointer to an array containing the three Euler angles.
 */
void Grain::setOrientation (double *p)
{
    this->phi[0] = p[0];
    this->phi[1] = p[1];
    this->phi[2] = p[2];
}

/**
 * @brief Overloaded function to set crystallographic orientation of the grain.
 * @param p Vector3d variable containing the three Euler angles.
 */
void Grain::setOrientation (Vector3d p)
{
    this->phi[0] = p.getValue(0);
    this->phi[1] = p.getValue(1);
    this->phi[2] = p.getValue(2);
}

/**
 * @brief Set the points that make up the grain boundary.
 * @param gbPoints Vector container with the grain boundary points expressed in the base co-ordinate system.
 */
void Grain::setGBPoints (std::vector<Vector3d> gbPoints)
{
    this->gbPoints_base = gbPoints;
}

/**
 * @brief Calculate the coordinateSystem of the grain.
 */
void Grain::calculateCoordinateSystem ()
{
    Vector3d centroid = mean (this->gbPoints_base);
    this->coordinateSystem = CoordinateSystem(this->phi, centroid);
}

/**
 * @brief Set the Base CoordinateSystem.
 * @param base Pointer ot the base co-ordinate system.
 */
void Grain::setBaseCoordinateSystem (CoordinateSystem* base)
{
    this->coordinateSystem.setBase(base);
}

/**
 * @brief Calculate the grain boundary point locations in the local CoordinateSystem.
 */
void Grain::calculateGBPointsLocal ()
{
    this->gbPoints_local = this->coordinateSystem.vector_BaseToLocal(this->gbPoints_base);
}

/**
 * @brief Insert a new slip system into the grain.
 * @param s Pointer to the slip system (instance of class SlipSystem).
 */
void Grain::insertSlipSystem (SlipSystem* s)
{
    this->slipSystems.push_back(s);
}

// Stress functions
/**
 * @brief Calculate the externally applied stress in the grain co-ordinate system
 * @param s Stress applied externally, expressed in the base co-ordinate system.
 */
void Grain::calculateGrainAppliedStress (Stress s)
{
    this->appliedStress_base = s;
    this->appliedStress_local = this->coordinateSystem.stress_BaseToLocal(s);
}

/**
 * @brief Calculate the applied stress on all the slip systems.
 */
void Grain::calculateSlipSystemAppliedStress()
{
    std::vector<SlipSystem*>::iterator sit;
    SlipSystem* s;

    for (sit=this->slipSystems.begin(); sit!=this->slipSystems.end(); sit++) {
        s = *sit;
        s->calculateSlipSystemAppliedStress(this->appliedStress_local);
        s->calculateSlipPlaneAppliedStress();
    }
}

/**
 * @brief Calculate the total stresses experienced by all defects on all the slip planes.
 * @param mu Shear modulus of the material (Pa).
 * @param nu Poisson's ratio.
 */
void Grain::calculateAllStresses (double mu, double nu)
{
    std::vector<SlipSystem*>::iterator sourceSlipSystem_it;
    std::vector<SlipSystem*>::iterator destinationSlipSystem_it;

    SlipSystem* sourceSlipSystem;
    SlipSystem* destinationSlipSystem;

    std::vector<Defect*> defects;
    std::vector<Defect*>::iterator defects_it;
    Defect* defect;

    std::vector<Vector3d> defectPositions;
    std::vector<Vector3d>::iterator defectPositions_it;

    Stress totalStress;
    Stress totalStress_slipSystem;
    Stress totalStress_slipPlane;
    Stress totalStress_defect;

    for (destinationSlipSystem_it=this->slipSystems.begin(); destinationSlipSystem_it!=this->slipSystems.end(); destinationSlipSystem_it++) {
        destinationSlipSystem = *destinationSlipSystem_it;
        // Get all the defects and their position vectors
        defects = destinationSlipSystem->getDefects();
        defectPositions = destinationSlipSystem->getAllDefectPositions_base();
        for (defectPositions_it=defectPositions.begin(), defects_it=defects.begin();
             defectPositions_it!=defectPositions.end();
             defectPositions_it++, defects_it++) {
            // Set the total stress to the grain's local applied stress
            totalStress = this->appliedStress_local;
            defect = *defects_it;
            for (sourceSlipSystem_it=this->slipSystems.begin(); sourceSlipSystem_it!=this->slipSystems.end(); sourceSlipSystem_it++) {
                sourceSlipSystem = *sourceSlipSystem_it;
                totalStress += sourceSlipSystem->slipSystemStressField(*defectPositions_it, mu, nu);
            }
            // The total stress is in the grain co-ordinate system
            defect = *defects_it;
            totalStress_slipSystem = destinationSlipSystem->getCoordinateSystem()->stress_BaseToLocal(totalStress);
            totalStress_slipPlane  = defect->getCoordinateSystem()->getBase()->stress_BaseToLocal(totalStress_slipSystem);
            totalStress_defect     = defect->getCoordinateSystem()->stress_BaseToLocal(totalStress_slipPlane);
            defect->setTotalStress(totalStress_defect);
        }
    }
}

/**
 * @brief Calculate the Peach-Koehler force on all dislocations and their resulting velocities.
 * @param B The drag coefficient.
 */
void Grain::calculateDislocationVelocities (double B)
{
    std::vector<SlipSystem*>::iterator s_it;
    SlipSystem* s;

    for (s_it=this->slipSystems.begin(); s_it!=this->slipSystems.end(); s_it++) {
        s = *s_it;
        s->calculateSlipPlaneDislocationForcesVelocities(B);
    }
}

/**
 * @brief The total stress field due to all defects in the grain at the position p.
 * @param p Position vector, in the base co-ordinate system, of the point at which the stress field is to be calculated.
 * @param mu Shear modulus (Pa).
 * @param nu Poisson's ratio.
 * @return Stress field, in the base co-ordinate system, due to all defects in this grain.
 */
Stress Grain::grainStressField (Vector3d p, double mu, double nu)
{
    std::vector<SlipSystem*>::iterator s_it;
    SlipSystem* ss;
    Stress s;

    Vector3d p_local = this->coordinateSystem.vector_BaseToLocal(p);

    for (s_it=this->slipSystems.begin(); s_it!=this->slipSystems.end(); s_it++) {
        ss = *s_it;
        s += ss->slipSystemStressField(p_local, mu, nu);
    }

    return (this->coordinateSystem.stress_LocalToBase(s));
}

// Time increments
/**
 * @brief Set the time increments for all slip systems.
 * @param dt The value of the time increment.
 */
void Grain::setSlipSystemTimeIncrements (double dt)
{
    std::vector<SlipSystem*>::iterator s_it;
    SlipSystem* s;

    for (s_it=this->slipSystems.begin(); s_it!=this->slipSystems.end(); s_it++) {
        s = *s_it;
        s->setTimeIncrement(dt);
    }
}

/**
 * @brief Calculates the ideal time increments of all the slip planes in all the slip systems in the grain.
 * @param minDistance The minimum distance allowed between adjacent defects.
 * @param minDt The smallest time step allowed.
 * @return STL vector container with the time increments for each slip plane.
 */
std::vector<double> Grain::calculateTimeIncrement (double minDistance, double minDt)
{
    std::vector<double> timeIncrements;
    std::vector<double> slipSystemTimeIncrements;

    std::vector<SlipSystem*>::iterator s_it;
    SlipSystem* s;

    timeIncrements.clear();
    for (s_it=this->slipSystems.begin(); s_it!=this->slipSystems.end(); s_it++) {
        s = *s_it;
        slipSystemTimeIncrements = s->calculateTimeIncrement(minDistance, minDt);
        timeIncrements.insert(timeIncrements.end(), slipSystemTimeIncrements.begin(), slipSystemTimeIncrements.end());
        slipSystemTimeIncrements.clear();
    }

    return (timeIncrements);
}

// Displacement
/**
 * @brief Displace all the dislocations.
 * @param minDistance The minimum distance allowed between two defects.
 * @param dt The value of the time increment.
 * @param mu Shear modulus (Pa).
 * @param nu Poisson's ratio.
 */
void Grain::moveAllDislocations (double minDistance, double dt, double mu, double nu)
{
    std::vector<SlipSystem*>::iterator s_it;
    SlipSystem* s;

    for (s_it=this->slipSystems.begin(); s_it!=this->slipSystems.end(); s_it++) {
        s = *s_it;
        s->moveSlipPlaneDislocations(minDistance, dt, mu, nu);
    }
}

// Dislocation sources
/**
 * @brief Check all the dislocation sources in the grain for dislocation dipole emissions.
 * @param dt The time increment in this iteration.
 * @param mu Shear modulus (Pa).
 * @param nu Poisson's ratio.
 * @param minDistance The limiting distance of approach between two defects.
 */
void Grain::checkDislocationSources (double dt, double mu, double nu, double minDistance)
{
    std::vector<SlipSystem*>::iterator s_it;
    SlipSystem* s;

    for (s_it=this->slipSystems.begin(); s_it!=this->slipSystems.end(); s_it++) {
        s = *s_it;
        s->checkSlipPlaneDislocationSources(dt, mu, nu, minDistance);
    }
}

// Local reactions
/**
 * @brief Check the local reactions between defects within the grain.
 * @param reactionRadius The limiting distance between to defects for which a local reaction can take place.
 */
void Grain::checkGrainLocalReactions (double reactionRadius)
{
    std::vector<SlipSystem*>::iterator s_it;
    SlipSystem* s;

    for (s_it=this->slipSystems.begin(); s_it!=this->slipSystems.end(); s_it++) {
        s = *s_it;
        s->checkSlipPlaneLocalReactions(reactionRadius);
    }
}

// Clear functions
/**
 * @brief Clear out all the slip systems of the grain.
 */
void Grain::clearSlipSystems ()
{
    this->slipSystems.clear();
}

// Access functions
/**
 * @brief Get the crystallographic orientation of the grain.
 * @param p Pointer to the array of type double with 3 available pre-allocated memory locations.
 */
void Grain::getOrientation(double* p) const
{
    p[0] = this->phi[0];
    p[1] = this->phi[1];
    p[2] = this->phi[2];
}

/**
 * @brief Get the grain boundary points expressed in the grain's local co-ordinate system.
 * @return Vector container with teh position vectors of the grain boundary points expressed in the local co-ordinate system.
 */
std::vector<Vector3d> Grain::getGBPoints_local () const
{
    return (this->gbPoints_local);
}

/**
 * @brief Get the grain boundary points expressed in the base co-ordinate system.
 * @return Vector container with teh position vectors of the grain boundary points expressed in the base co-ordinate system.
 */
std::vector<Vector3d> Grain::getGBPoints_base () const
{
    return (this->gbPoints_base);
}

/**
 * @brief Get a pointer to the Grain CoordinateSystem.
 * @return Pointer to the Grain co-ordinate system.
 */
CoordinateSystem* Grain::getCoordinateSystem ()
{
    return (&(this->coordinateSystem));
}

/**
 * @brief Get the positions of all the defects in this grain, expressed in the base co-ordinate system.
 * @return Vector container with the positions of all the defects in this grain, expressed in the base co-ordinate system.
 */
std::vector<Vector3d> Grain::getAllDefectPositions_base()
{
    return (this->coordinateSystem.vector_LocalToBase(this->getAllDefectPositions_local()));
}

/**
 * @brief Get the positions of all the defects in this grain, expressed in the local co-ordinate system.
 * @return Vector container with the positions of all the defects in this grain, expressed in the local co-ordinate system.
 */
std::vector<Vector3d> Grain::getAllDefectPositions_local()
{
    std::vector<Vector3d> defectPositions;
    std::vector<Vector3d> slipSystemDefects;

    std::vector<SlipSystem*>::iterator s_it;
    SlipSystem* s;

    defectPositions.clear();
    for (s_it=this->slipSystems.begin(); s_it!=this->slipSystems.end(); s_it++) {
        s = *s_it;
        slipSystemDefects = s->getAllDefectPositions_base();
        defectPositions.insert(defectPositions.end(), slipSystemDefects.begin(), slipSystemDefects.end());
    }

    return (defectPositions);
}
