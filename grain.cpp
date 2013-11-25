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
