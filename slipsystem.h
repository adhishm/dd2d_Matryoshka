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
     * @brief The slip direction, expressed in the crystal (grain) co-ordinate system.
     */
    Vector3d slipDirection;
public:
    /**
     * @brief Default constructor for the class SlipSystem.
     */
    SlipSystem();
    /**
     * @brief Constructor for the class SlipSystem creating a standard slip systemfor the crystal structure provided as argument.
     * @details This constructor uses the default values for the kind of standard slip system corresponding to the crystal structure specified as argument. The crystal structures are FCC, BCC.
     * @param c Variable indicating the crystal structure for which a standard slip system is to be created.
     */
    SlipSystem(CrystalStructure c);
    /**
     * @brief Constructor for the class SlipSystem, mentioning details of the slip system.
     * @param pos Position of the origin of the slip system, expressed in the base co-ordinate system.
     * @param normal The normal to the slip planes that are present in this slip system, expressed in the base co-ordinate system.
     * @param direction The slip direction, , expressed in the base co-ordinate system.
     * @param base Pointer to the base co-ordinate system.
     * @param s The vector container with pointers to the slip planes that are part of the slip system.
     */
    SlipSystem(Vector3d pos, Vector3d normal, Vector3d direction, CoordinateSystem *base, std::vector<SlipPlane*> s);
};

#endif // SLIPSYSTEM_H
