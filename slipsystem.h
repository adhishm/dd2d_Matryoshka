/**
 * @file slipsystem.h
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

#ifndef SLIPSYSTEM_H
#define SLIPSYSTEM_H

#include "slipPlane.h"
#include "standardSlipSystem.h"

#ifndef SLIPSYSTEM_DEFAULT_NUMBERPLANES
/**
  * @brief The default number of slip planes in the slip system
  */
#define SLIPSYSTEM_DEFAULT_NUMBERPLANES 1
#endif

/**
 * @brief The SlipSystem class representing a slip system in the simulation.
 * @details In the simulation, a slip system is considered to be a collection of slip planes, all parallel to each other. The slip system is characterized by a slip plane normal and a slip direction, both represented in the crystal co-ordinate system, ie, the frame of reference of a grain.
 */
class SlipSystem
{
protected:
    /**
     * @brief Vector container with pointers to slip planes that make up this slip system.
     */
    std::vector<SlipPlane*> slipPlanes;
    /**
     * @brief The slip system's local co-ordinate system.
     */
    CoordinateSystem coordinateSystem;
    /**
     * @brief The normal to the slip planes making up this slip system, expressed in the crystal (grain) co-ordinate system.
     */
    Vector3d slipPlaneNormal;
    /**
     * @brief The direction of the slip plane, normal to the slip plane normal, expressed in the crystal (grain) co-ordinate system.
     */
    Vector3d slipPlaneDirection;
    /**
     * @brief Position of the origin of the slip system.
     */
    Vector3d position;

public:
    /**
     * @brief Default constructor for the class SlipSystem.
     */
    SlipSystem();

    /**
     * @brief Constructor for the class SlipSystem, mentioning details of the slip system.
     * @param pos Position of the origin of the slip system, expressed in the base co-ordinate system.
     * @param normal The normal to the slip planes that are present in this slip system, expressed in the base co-ordinate system.
     * @param direction The direction of the slip plane, expressed in the crystal (grain) co-ordinate system.
     * @param base Pointer to the base co-ordinate system.
     * @param s The vector container with pointers to the slip planes that are part of the slip system.
     */
    SlipSystem(Vector3d pos, Vector3d normal, Vector3d direction, CoordinateSystem *base, std::vector<SlipPlane*> s);

    // Assignment functions
    /**
     * @brief Set the position of the origin of the slip system.
     * @param pos The position vector of the origin, in the base co-ordinate system.
     */
    void setPosition (Vector3d pos);
    /**
     * @brief Set the co-ordinate systems for all the slip planes.
     */
    void setSlipPlaneCoordinateSystems ();
    /**
     * @brief Set the normal vector for the slip system.
     * @param normal The normal vector of the slip system, in the base co-ordinate system.
     */
    void setNormal (Vector3d normal);
    /**
     * @brief Set the direction of the slip planes in the slip system.
     * @param direction The direction vector for the slip planes in the slip system.
     */
    void setDirection (Vector3d direction);
    /**
     * @brief Set the base co-ordinate system for the slip system.
     * @param base Pointer to the base co-ordinate system.
     */
    void setBaseCoordinateSystem (CoordinateSystem *base);
    /**
     * @brief Create the slip system's co-ordinate system.
     * @param base Pointer to the base co-ordinate system.
     */
    void createCoordinateSystem (CoordinateSystem *base);

    // Access functions
    /**
     * @brief Gets the co-ordinate system of the slip system.
     * @return Pointer to the co-ordinate system of the slip system.
     */
    CoordinateSystem* getCoordinateSystem ();
    /**
     * @brief Get the position vector of the origin of the slip system.
     * @return The position vector of the origin of the slip system.
     */
    Vector3d getPosition () const;
    /**
     * @brief Get the normal to all slip planes in the slip system.
     * @return Normal to the slip system.
     */
    Vector3d getNormal () const;
    /**
     * @brief Get the direction of all slip planes in the slip system.
     * @return The direction of slip planes in the slip system.
     */
    Vector3d getDirection () const;
    /**
     * @brief Get the vector container with pointers to all slip planes.
     * @return Vector container with pointers to all slip planes.
     */
    std::vector<SlipPlane*> getSlipPlanes ();
    /**
     * @brief Get the pointer to a specific slip plane, indicated by the argument. If the argument is greater than the size, a NULL pointer is returned.
     * @param i Index of the slip plane the pointer to which is required.
     * @return Pointer to the slip plane indicated by the argument. If the argument is greater than the size of the vector, a NULL pointer is returned.
     */
    SlipPlane* getSlipPlane (int i);
};

#endif // SLIPSYSTEM_H
