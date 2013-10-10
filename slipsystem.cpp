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
