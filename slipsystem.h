/**
 * @file slipSystem.h
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
     * @brief The slip direction, expressed in the crystal (grain) co-ordinate system.
     */
    Vector3d slipDirection;
public:
    /**
     * @brief Default constructor for the class SlipSystem.
     */
    SlipSystem();
};

#endif // SLIPSYSTEM_H
