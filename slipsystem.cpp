/**
 * @file slipsystem.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 02/10/2013
 * @brief Definition of the SlipSystem class.
 * @details This file defines the Slipsystem class representing a slip system in the simulation. A slip system is considered to be a set of slip planes, all parallel to each other. The attributes of a slip system are the slip plane normal and the slip direction, both expressed in the frame of reference of the grain.
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

#include "slipsystem.h"

/**
 * @brief Default constructor for the class SlipSystem.
 */
SlipSystem::SlipSystem()
{
    this->slipPlanes = std::vector<SlipPlane*> (SLIPSYSTEM_DEFAULT_NUMBERPLANES, new SlipPlane);
    this->slipPlaneNormal = Vector3d(DEFAULT_SLIPPLANE_NORMALVECTOR_0,
                                     DEFAULT_SLIPPLANE_NORMALVECTOR_1,
                                     DEFAULT_SLIPPLANE_NORMALVECTOR_2);
}

/**
 * @brief Constructor for the class SlipSystem, mentioning details of the slip system.
 * @param pos Position of the origin of the slip system, expressed in the base co-ordinate system.
 * @param normal The normal to the slip planes that are present in this slip system, expressed in the base co-ordinate system.
 * @param direction The direction of the slip plane, expressed in the crystal (grain) co-ordinate system.
 * @param base Pointer to the base co-ordinate system.
 * @param s The vector container with pointers to the slip planes that are part of the slip system.
 */
SlipSystem::SlipSystem(Vector3d pos, Vector3d normal, Vector3d direction, CoordinateSystem *base, std::vector<SlipPlane*> s)
{
    // Set the origin
    this->position = pos;
    // Set the slip plane normal
    this->slipPlaneNormal = normal;
    // Set the slip direction
    this->slipPlaneDirection = direction;
    // Create the co-ordinate system
    this->createCoordinateSystem(base);
    // Set the slip planes
    this->slipPlanes = s;

    // Refresh the rotation matrices of the slip planes
    this->setSlipPlaneCoordinateSystems();
}

// Destructor
/**
 * @brief Destructor for the class SlipSystem.
 */
SlipSystem::~SlipSystem ()
{
    std::vector<SlipPlane*>::iterator sp_it;
    SlipPlane* sp;

    for (sp_it=this->slipPlanes.begin(); sp_it!=this->slipPlanes.end(); sp_it++) {
        sp = *sp_it;
        delete (sp);
        sp = NULL;
    }

    this->slipPlanes.clear();
}

// Assignment functions
/**
 * @brief Set the position of the origin of the slip system.
 * @param pos The position vector of the origin, in the base co-ordinate system.
 */
void SlipSystem::setPosition (Vector3d pos)
{
    this->position = pos;
}

/**
 * @brief Set the co-ordinate systems for all the slip planes.
 */
void SlipSystem::setSlipPlaneCoordinateSystems ()
{
    std::vector<SlipPlane*>::iterator sit;
    SlipPlane *s;

    for (sit=this->slipPlanes.begin(); sit!=this->slipPlanes.end(); sit++) {
        s = *sit;
        s->setBaseCoordinateSystem(this->getCoordinateSystem());
        s->calculateRotationMatrix();
    }
}

/**
 * @brief Set the normal vector for the slip system.
 * @param normal The normal vector of the slip system, in the base co-ordinate system.
 */
void SlipSystem::setNormal (Vector3d normal)
{
    this->slipPlaneNormal = normal;
}

/**
 * @brief Set the direction of the slip planes in the slip system.
 * @param direction The direction vector for the slip planes in the slip system.
 */
void SlipSystem::setDirection (Vector3d direction)
{
    this->slipPlaneDirection = direction;
}

/**
 * @brief Set the base co-ordinate system for the slip system.
 * @param base Pointer to the base co-ordinate system.
 */
void SlipSystem::setBaseCoordinateSystem (CoordinateSystem *base)
{
    this->coordinateSystem.setBase(base);
}

/**
 * @brief Create the slip system's co-ordinate system.
 * @param base Pointer to the base co-ordinate system.
 */
void SlipSystem::createCoordinateSystem (CoordinateSystem *base)
{
    // Set the origin
    this->coordinateSystem.setOrigin(this->position);
    // Set the axes
    Vector3d *axes = new Vector3d[3];
    axes[2] = this->slipPlaneNormal;
    axes[0] = this->slipPlaneDirection;
    axes[1] = axes[2] ^ axes[0];
    this->coordinateSystem.setAxes(axes);
    delete [] axes;
    // Set the base co-ordinate system
    this->coordinateSystem.setBase(base);
    this->coordinateSystem.calculateRotationMatrix();
}

/**
 * @brief Insert a slip plane into the the list of slip planes.
 * @param s Pointer to the slip plane that is to be inserted.
 */
void SlipSystem::insertSlipPlane (SlipPlane *s)
{
    this->slipPlanes.push_back(s);
}

/**
 * @brief Insert a  list of slip planes.
 * @param sList STL vector container with pointers to slip planes.
 */
void SlipSystem::insertSlipPlaneList (std::vector<SlipPlane*> sList)
{
    this->slipPlanes.insert(this->slipPlanes.end(),
                            sList.begin(),
                            sList.end());
}

/**
 * @brief Set the time increment for the slip system
 * @param t The value of the time increment.
 */
void SlipSystem::setTimeIncrement (double t)
{
    this->dt = t;
}

// Access functions
/**
 * @brief Gets the co-ordinate system of the slip system.
 * @return Pointer to the co-ordinate system of the slip system.
 */
CoordinateSystem* SlipSystem::getCoordinateSystem ()
{
    return (&(this->coordinateSystem));
}

/**
 * @brief Get the position vector of the origin of the slip system.
 * @return The position vector of the origin of the slip system.
 */
Vector3d SlipSystem::getPosition () const
{
    return (this->position);
}
/**
 * @brief Get the normal to all slip planes in the slip system.
 * @return Normal to the slip system.
 */
Vector3d SlipSystem::getNormal () const
{
    return (this->slipPlaneNormal);
}

/**
 * @brief Get the direction of all slip planes in the slip system.
 * @return The direction of slip planes in the slip system.
 */
Vector3d SlipSystem::getDirection () const
{
    return (this->slipPlaneDirection);
}

/**
 * @brief Get the vector container with pointers to all slip planes.
 * @return Vector container with pointers to all slip planes.
 */
std::vector<SlipPlane*> SlipSystem::getSlipPlanes ()
{
    return (this->slipPlanes);
}

/**
 * @brief Get the pointer to a specific slip plane, indicated by the argument. If the argument is greater than the size, a NULL pointer is returned.
 * @param i Index of the slip plane the pointer to which is required.
 * @return Pointer to the slip plane indicated by the argument. If the argument is greater than the size of the vector, a NULL pointer is returned.
 */
SlipPlane* SlipSystem::getSlipPlane (int i)
{
    SlipPlane *s;

    if (i>=0 && i<this->slipPlanes.size()) {
        s = this->slipPlanes.at(i);
    }
    else {
        s = NULL;
    }

    return (s);
}

/**
 * @brief Get the applied stress in the slip system's local co-ordinate system.
 * @return The applied stress in the slip system's local co-ordinate system.
 */
Stress SlipSystem::getAppliedStress_local () const
{
    return (this->appliedStress_local);
}

/**
 * @brief Get the applied stress in the slip system's base co-ordinate system.
 * @return The applied stress in the slip system's base co-ordinate system.
 */
Stress SlipSystem::getAppliedStress_base () const
{
    return (this->appliedStress_base);
}

/**
 * @brief Get the slip system time increment.
 * @return The slip system time increment.
 */
double SlipSystem::getTimeIncrement () const
{
    return (this->dt);
}

/**
 * @brief Get the time increments of all the slip planes.
 * @return STL vector container with the time increments of all the slip planes.
 */
std::vector<double> SlipSystem::getSlipPlaneTimeIncrements ()
{
    std::vector<double> timeIncrements (this->slipPlanes.size(), 0.0);
    std::vector<double>::iterator timeIncrements_it;
    std::vector<SlipPlane*>::iterator slipPlanes_it;
    SlipPlane *s;

    timeIncrements_it = timeIncrements.begin();
    slipPlanes_it = this->slipPlanes.begin();

    while (timeIncrements_it != timeIncrements.end()) {
        s = *slipPlanes_it;
        *timeIncrements_it = s->getTimeIncrement();
        timeIncrements_it++;
        slipPlanes_it++;
    }
    return (timeIncrements);
}

/**
 * @brief Return the position of all the defects, expressed in the slip system co-ordinate system.
 * @return Vector container with the positions of all defects expressed in the slip system co-ordinate system.
 */
std::vector<Vector3d> SlipSystem::getAllDefectPositions_local ()
{
    std::vector<Vector3d> defectPositions;
    std::vector<Vector3d> slipPlaneDefects;

    std::vector<SlipPlane*>::iterator s_it;
    SlipPlane* s;

    defectPositions.clear();
    for (s_it=this->slipPlanes.begin(); s_it!=this->slipPlanes.end(); s_it++) {
        s = *s_it;
        slipPlaneDefects = s->getAllDefectPositions_base();
        defectPositions.insert(defectPositions.end(), slipPlaneDefects.begin(), slipPlaneDefects.end());
    }

    return (defectPositions);
}

/**
 * @brief Return the position of all the defects, expressed in the base co-ordinate system.
 * @return Vector container with the positions of all defects expressed in the base co-ordinate system.
 */
std::vector<Vector3d> SlipSystem::getAllDefectPositions_base ()
{
    return (this->coordinateSystem.vector_LocalToBase(this->getAllDefectPositions_local()));
}

// Sort functions
/**
 * @brief Sort the slip planes in ascending order based on their positions.
 */
void SlipSystem::sortSlipPlanes ()
{
    std::sort (this->slipPlanes.begin(), this->slipPlanes.end(), SlipPlane::compareSlipPlanePositions);
}

// Clean up functions
/**
 * @brief Clear the vector containing SlipPlanes.
 */
void SlipSystem::clearSlipPlanes ()
{
    this->slipPlanes.clear();
}

// Stresses
/**
 * @brief Calculate the applied stress, in the slip system co-ordinate system.
 * @param appliedStress
 */
void SlipSystem::calculateSlipSystemAppliedStress (Stress appliedStress)
{
    this->appliedStress_base = appliedStress;
    this->appliedStress_local = this->coordinateSystem.stress_BaseToLocal(appliedStress);
}

/**
 * @brief Calculate the applied stress on the slip planes, in their respective co-ordinate systems.
 */
void SlipSystem::calculateSlipPlaneAppliedStress ()
{
    std::vector<SlipPlane*>::iterator sit;
    SlipPlane* s;

    for (sit=this->slipPlanes.begin(); sit!=this->slipPlanes.end(); sit++) {
        s = *sit;
        s->calculateSlipPlaneAppliedStress(this->appliedStress_local);
    }
}

/**
 * @brief Calculate the total stresses experienced by all defects on all the slip planes.
 * @param mu Shear modulus of the material (Pa).
 * @param nu Poisson's ratio.
 */
void SlipSystem::calculateAllStresses (double mu, double nu)
{
    std::vector<SlipPlane *>::iterator source_slipPlane_it;
    std::vector<SlipPlane *>::iterator destination_slipPlane_it;

    SlipPlane *destination_slipPlane;
    SlipPlane *source_slipPlane;

    Stress totalStress;
    Stress totalStress_slipPlane;
    Stress totalStress_defect;

    std::vector<Vector3d> defectPositions;
    std::vector<Vector3d>::iterator defectPositions_it;

    std::vector<Defect *> defects;
    std::vector<Defect *>::iterator defects_it;
    Defect *defect;

    for (destination_slipPlane_it=this->slipPlanes.begin(); destination_slipPlane_it!=this->slipPlanes.end(); destination_slipPlane_it++) {
        destination_slipPlane = *destination_slipPlane_it;
        totalStress = this->appliedStress_local;
        // Get all defects and their position vectors
        defects = destination_slipPlane->getDefectList();
        defectPositions = destination_slipPlane->getAllDefectPositions_base();
        for (defectPositions_it=defectPositions.begin(), defects_it=defects.begin();
             defectPositions_it!=defectPositions.end();
             defectPositions_it++, defects_it++) {
            for (source_slipPlane_it=this->slipPlanes.begin(); source_slipPlane_it!=this->slipPlanes.end(); source_slipPlane_it++) {
                source_slipPlane = *source_slipPlane_it;
                // Add the source slip plane's stress field to the total stress field at this position
                totalStress += source_slipPlane->slipPlaneStressField(*defectPositions_it, mu, nu);
            }
            // The stress is in the slip system co-ordinate system
            // It should be converted to the slip plane co-ordinate system
            // and then to the defect co-ordinate system
            defect = *defects_it;
            totalStress_slipPlane = destination_slipPlane->getCoordinateSystem()->stress_BaseToLocal(totalStress);
            totalStress_defect = defect->getCoordinateSystem()->stress_BaseToLocal(totalStress_slipPlane);
            defect->setTotalStress(totalStress_defect);
        }
    }
}

/**
 * @brief Calculate the forces on all the dislocations on all the slip planes.
 * @param B The drag coefficient for the dislocations.
 */
void SlipSystem::calculateSlipPlaneDislocationForcesVelocities (double B)
{
    std::vector<SlipPlane*>::iterator slipPlanes_it;
    SlipPlane *s;

    for (slipPlanes_it=this->slipPlanes.begin(); slipPlanes_it!=this->slipPlanes.end(); slipPlanes_it++) {
        s = *slipPlanes_it;
        s->calculateDislocationForces();
        s->calculateDislocationVelocities(B);
    }
}

// Time increment
/**
 * @brief Calculates the ideal time increments of all the slip planes in the slip system.
 * @param minDistance The minimum distance allowed between adjacent defects.
 * @param minDt The smallest time step allowed.
 * @return STL vector container with the time increments for each slip plane.
 */
std::vector<double> SlipSystem::calculateTimeIncrement (double minDistance, double minDt)
{
    std::vector<SlipPlane*>::iterator slipPlanes_it;
    SlipPlane *s;
    std::vector<double> timeIncrements (this->slipPlanes.size(), 0.0);
    std::vector<double>::iterator timeIncrements_it;

    for (slipPlanes_it=this->slipPlanes.begin(), timeIncrements_it=timeIncrements.begin();
         slipPlanes_it!=this->slipPlanes.end();
         slipPlanes_it++, timeIncrements_it++) {
        s = *slipPlanes_it;
        s->calculateTimeIncrement(minDistance, minDt);
        *timeIncrements_it = s->getTimeIncrement();
    }

    return (timeIncrements);
}

// Move dislocations on all slip planes
/**
 * @brief This function moves all the dislocations on all slip planes belonging to the slip system.
 * @details The function uses a constant time increment, and uses the function SlipPlane::moveDislocationsToLocalEquilibrium to bring dislocations to an equilibrium position (if this position is not too far away).
 * @param minDistance The minimum allowed distance between two defects.
 * @param dtGlobal The global time increment.
 * @param mu Shear modulus (Pa).
 * @param nu Poisson's ratio.
 */
void SlipSystem::moveSlipPlaneDislocations (double minDistance, double dtGlobal, double mu, double nu)
{
    std::vector<SlipPlane*>::iterator slipPlanes_it;
    SlipPlane *s;

    for (slipPlanes_it=this->slipPlanes.begin(); slipPlanes_it!=this->slipPlanes.end(); slipPlanes_it++) {
        s = *slipPlanes_it;
        s->moveDislocationsToLocalEquilibrium(minDistance, dtGlobal, mu, nu);
    }
}

// Check dislocation sources
/**
 * @brief Check the dislocation sources lying on all the slip planes for dipole emissions.
 * @param timeIncrement The time increment for the current iteration.
 * @param mu Shear modulus (Pa).
 * @param nu Poisson's ratio.
 * @param limitingDistance Minimum distance allowed between two defects.
 */
void SlipSystem::checkSlipPlaneDislocationSources (double timeIncrement, double mu, double nu, double limitingDistance)
{
    std::vector<SlipPlane*>::iterator slipPlanes_it;
    SlipPlane *s;

    for (slipPlanes_it=this->slipPlanes.begin(); slipPlanes_it!=this->slipPlanes.end(); slipPlanes_it++) {
        s = *slipPlanes_it;
        s->checkDislocationSources(timeIncrement, mu, nu, limitingDistance);
    }
}

// Local reactions
/**
 * @brief Check for local reactions on all the slip planes.
 * @param reactionRadius The limiting distance between to defects for which a local reaction can take place.
 */
void SlipSystem::checkSlipPlaneLocalReactions (double reactionRadius)
{
    std::vector<SlipPlane*>::iterator slipPlanes_it;
    SlipPlane *s;

    for (slipPlanes_it=this->slipPlanes.begin(); slipPlanes_it!=this->slipPlanes.end(); slipPlanes_it++) {
        s = *slipPlanes_it;
        s->checkLocalReactions(reactionRadius);
    }
}

