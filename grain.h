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

/**
 * @brief The Grain class represents a grain in the simulation. A grain is seen as a collection of slip systems. The extremities of the slip planes of the grains define the grain boundaries.
 */
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
     * @brief Constructor for the class Grain, specifying all details.
     * @details All details are provided to the constructor.  For the moment only one slip system is active per grain, so only one normal and only one slip direction are given. This may be modified in the future when multiple slip will be handled.
     * @param phi Pointer to the array containing the three Euler angles representing the grain orientation.
     * @param points An STL vector container with the position vectors, in the base (polycrystal) co-ordinate system, of the points that make up the grain boundary. These points must be given in a fixed sequence, either clockwise or anti-clockwise.
     * @param slipSystemNormal Miller indices, in the crystallographic frame (grain co-ordinate system), of the slip system normal.
     * @param slipPlanePositions STL vector containing the positions of slip planes on the slip system normal.
     * @param dislocations Pointer to an array of vector containers with dislocations for the slip planes.
     * @param dislocationSources Pointer to an array of vector containers with dislocation sources for the slip planes.
     */
    Grain(double* phi, std::vector<Vector3d> points, Vector3d slipSystemNormal, std::vector<double> slipPlanePositions, std::vector<Dislocation*> *dislocations, std::vector<DislocationSource*> *dislocationSources);

    // Destructor
    /**
     * @brief Destructor for the class Grain.
     */
    virtual ~Grain();

    // Assignment functions
    /**
     * @brief Set the crystallographic orientation of the grain.
     * @param p Pointer to an array containing the three Euler angles.
     */
    void setOrientation (double *p);

    /**
     * @brief Overloaded function to set crystallographic orientation of the grain.
     * @param p Vector3d variable containing the three Euler angles.
     */
    void setOrientation (Vector3d p);

    /**
     * @brief Set the points that make up the grain boundary.
     * @param gbPoints Vector container with the grain boundary points expressed in the base co-ordinate system.
     */
    void setGBPoints (std::vector<Vector3d> gbPoints);

    /**
     * @brief Calculate the coordinateSystem of the grain.
     */
    void calculateCoordinateSystem ();

    /**
     * @brief Calculate the grain boundary point locations in the local CoordinateSystem.
     */
    void calculateGBPointsLocal ();

    /**
     * @brief Set the Base CoordinateSystem.
     * @param base Pointer ot the base co-ordinate system.
     */
    void setBaseCoordinateSystem (CoordinateSystem* base);

    /**
     * @brief Insert a new slip system into the grain.
     * @param s Pointer to the slip system (instance of class SlipSystem).
     */
    void insertSlipSystem (SlipSystem* s);

    // Clear functions
    /**
     * @brief Clear out all the slip systems of the grain.
     */
    void clearSlipSystems ();

    // Access functions
    /**
     * @brief Get the crystallographic orientation of the grain.
     * @param p Pointer to the array of type double with 3 available pre-allocated memory locations.
     */
    void getOrientation(double* p) const;

    /**
     * @brief Get the grain boundary points expressed in the grain's local co-ordinate system.
     * @return Vector container with teh position vectors of the grain boundary points expressed in the local co-ordinate system.
     */
    std::vector<Vector3d> getGBPoints_local () const;

    /**
     * @brief Get the grain boundary points expressed in the base co-ordinate system.
     * @return Vector container with teh position vectors of the grain boundary points expressed in the base co-ordinate system.
     */
    std::vector<Vector3d> getGBPoints_base () const;

    /**
     * @brief Get a pointer to the Grain CoordinateSystem.
     * @return Pointer to the Grain co-ordinate system.
     */
    CoordinateSystem* getCoordinateSystem ();
};

#endif // GRAIN_H
