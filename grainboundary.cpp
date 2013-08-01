/**
 * @file grainboundary.cpp
 * @author Adhish Majumdar
 * @version 1.1
 * @date 30/07/2013
 * @brief Definition of member functions of the GrainBoundary class.
 * @details This file defines member functions of the GrainBoundary class representing an grain boundary in the simulation. This class inherits Defect.
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

#include "grainboundary.h"

/**
 * @brief Default constructor.
 * @details Creates a default grain boundary with origin at (0, 0, 0) and neighbour indices 0.
 */
GrainBoundary::GrainBoundary()
    : Defect(GRAINBOUNDARY, Vector3d::zeros())
{
    this->neighbour1 = 0;
    this->neighbour2 = 0;
}

/**
 * @brief Creates a grain boundary
 * @param base Pointer to the base co-ordinate system. Default value: NULL.
 * @param p Position vector of the origin. Default value: Vector3d::zeros().
 * @param n1 Index of the first neighbour. Default value: 0.
 * @param n2 Index of the second neighbour. Default value: 0.
 */
GrainBoundary::GrainBoundary(CoordinateSystem* base, Vector3d p, int n1, int n2)
    : Defect (GRAINBOUNDARY, p, Vector3d::standardAxes())
{
    this->neighbour1 = n1;
    this->neighbour2 = n2;
}
