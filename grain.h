/**
 * @file grain.h
 * @author Adhish Majumdar
 * @version 1.3
 * @date 20/11/2013
 * @brief Definition of the Grain class.
 * @details This file defines the Grain class representing an grain/crystal in the simulation. A grain is considered to be a collection of slip systems.
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

#ifndef GRAIN_H
#define GRAIN_H

#include "slipsystem.h"

#ifndef GRAIN_DEFAULTS
#define GRAIN_DEFAULTS

#define DEFAULT_ORIENTATION_PHI1 0.0
#define DEFAULT_ORIENTATION_PHI  0.0
#define DEFAULT_ORIENTATION_PHI2 0.0

#define DEFAULT_CENTROID_X1 0.0
#define DEFAULT_CENTROID_X2 0.0
#define DEFAULT_CENTROID_X3 0.0

#endif

class Grain
{
protected:
    /**
     * @brief STL vector container with pointers to all slip systems that belong to this grain.
     */
    std::vector<SlipSystem*> slipSystems;
    /**
     * @brief The grain's co-ordinate system.
     * @details The origin of the co-ordinate system should tyipcally be the centroid of the grain. The axes depend on the crystallographic orientation with respect to the global (polycrystal) co-ordinate system.
     */
    CoordinateSystem coordinateSystem;
    /**
     * @brief Crystallographic orientation of the grain using the three Euler angles (Bunge's notation).
     * @details Bunge's notation for the three Euler angles gives the angles of rotation about the Z, X and Z axes, in that order.
     */
    double phi[3];
    /**
     * @brief STL vector container with position vectors, expressed in the base co-ordinate system, of points lying on the grain boundary, in sequential order.
     */
    std::vector<Vector3d> gbPoints_base;
    /**
     * @brief STL vector container with position vectors, expressed in the local co-ordinate system, of points lying on the grain boundary, in sequential order.
     */
    std::vector<Vector3d> gbPoints_local;
public:
    // Constructors
    /**
     * @brief Default constructor for the Grain class.
     */
    Grain();
    /**
     * @brief Constructor for the class Grain specifying the centroid and the crystallographic orientation.
     * @param centroid Position vector of the grain's centroid.
     * @param phi Pointer to the array containing the grain's crystallographic orientation.
     */
    Grain(Vector3d centroid, double* phi);
    /**
     * @brief Constructor for the class Grain, specifying all details.
     * @param phi Pointer to the array containing the three Euler angles representing the grain orientation.
     * @param points An STL vector container with the position vectors, in the base (polycrystal) co-ordinate system, of the points that make up the grain boundary. These points must be given in a fixed sequence, either clockwise or anti-clockwise.
     * @param slipSystemNormal Miller indices, in the crystallographic frame (grain co-ordinate system), of the slip system normal.
     * @param slipDirection Miller indices, in the crystallographic frame (grain co-ordinate system), of the slip direction.
     */
    Grain(double* phi, std::vector<Vector3d> points, Vector3d slipSystemNormal, Vector3d slipDirection);

    // Destructor
    /**
     * @brief Destructor for the class Grain.
     */
    virtual ~Grain();
};

#endif // GRAIN_H
