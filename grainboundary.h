/**
 * @file grainboundary.h
 * @author Adhish Majumdar
 * @version 1.1
 * @date 30/07/2013
 * @brief Definition of the GrainBoundary class.
 * @details This file defines the GrainBoundary class representing an grain boundary in the simulation. This class inherits Defect.
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

#ifndef GRAINBOUNDARY_H
#define GRAINBOUNDARY_H

#include "defect.h"

/**
 * @brief The GrainBoundary class.
 * @details The GrainBoundary class represents a grain boundary in the simulation. It inherits public and protected attributes of the class Defect. It is typically an extremity of a slip plane.
 */
class GrainBoundary : public Defect
{
protected:
    /**
     * @brief Index pointing to a neighbouring grain.
     */
    int neighbour1;
    /**
     * @brief Index pointing to a neighbouring grain.
     */
    int neighbour2;
public:
    /**
     * @brief Default constructor.
     * @details Creates a default grain boundary with origin at (0, 0, 0) and neighbour indices 0.
     */
    GrainBoundary();

    /**
     * @brief Creates a grain boundary
     * @param base Pointer to the base co-ordinate system. Default value: NULL.
     * @param p Position vector of the origin. Default value: Vector3d::zeros().
     * @param n1 Index of the first neighbour. Default value: 0.
     * @param n2 Index of the second neighbour. Default value: 0.
     */
    GrainBoundary(CoordinateSystem* base = NULL, Vector3d p = Vector3d::zeros(), int n1=0, int n2=0);
};

#endif // GRAINBOUNDARY_H
