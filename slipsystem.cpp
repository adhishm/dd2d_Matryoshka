/**
 * @file slipSystem.cpp
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
    this->slipPlanes (SLIPSYSTEM_DEFAULT_NUMBERPLANES, SlipPlane());
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
    this->coordinateSystem.setOrigin(pos);
    // Set the axes
    Vector3d *axes = new Vector3d[3];
    axes[2] = normal;
    axes[0] = direction;
    axes[1] = axes[2] ^ axes[0];
    this->coordinateSystem.setAxes(axes);
    delete [] axes;
    // Set the base co-ordinate system
    this->coordinateSystem.setBase(base);
    this->coordinateSystem.calculateRotationMatrix();
    // Set the slip planes
    this->slipPlanes = s;
    // Set the slip plane normal
    this->slipPlaneNormal = normal;
    // Set the slip direction
    this->slipPlaneDirection = direction;

    // Refresh the rotation matrices of the slip planes
    this->setSlipPlaneCoordinateSystems();
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

// Access functions
/**
 * @brief Gets the co-ordinate system of the slip system.
 * @return Pointer to the co-ordinate system of the slip system.
 */
CoordinateSystem* SlipSystem::getCoordinateSystem ()
{
    return (&(this->coordinateSystem));
}
