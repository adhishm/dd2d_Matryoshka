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
Grain::Grain()
{
}

/**
 * @brief Constructor for the class Grain specifying the centroid and the crystallographic orientation.
 * @param centroid Position vector of the grain's centroid.
 * @param phi Pointer to the array containing the grain's crystallographic orientation.
 */
Grain::Grain(Vector3d centroid, double* phi)
{
    this->coordinateSystem = CoordinateSystem(phi, centroid);
}

/**
 * @brief Constructor for the class Grain, specifying all details.
 * @details All details are provided to the constructor.  For the moment only one slip system is active per grain, so only one normal and only one slip direction are given. This may be modified in the future when multiple slip will be handled.
 * @param phi Pointer to the array containing the three Euler angles representing the grain orientation.
 * @param points An STL vector container with the position vectors, in the base (polycrystal) co-ordinate system, of the points that make up the grain boundary. These points must be given in a fixed sequence, either clockwise or anti-clockwise.
 * @param slipSystemNormal Miller indices, in the crystallographic frame (grain co-ordinate system), of the slip system normal.
 * @param slipDirection Miller indices, in the crystallographic frame (grain co-ordinate system), of the slip direction.
 */
Grain::Grain(double* phi, std::vector<Vector3d> points, Vector3d slipSystemNormal, Vector3d slipDirection)
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
    Vector3d slipPlaneTrace = viewPlaneNormal ^ slipSystemNormal;

    // Get the grain boundary points in the local co-ordinate system
    this->gbPoints_base = points;
    this->gbPoints_local = this->coordinateSystem.vector_BaseToLocal(points);


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
