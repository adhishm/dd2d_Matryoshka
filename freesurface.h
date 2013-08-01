/**
 * @file freesurface.h
 * @author Adhish Majumdar
 * @version 1.1
 * @date 01/08/2013
 * @brief Definition of the FreeSurface class.
 * @details This file defines the FreeSurface class representing a free surface in the simulation. This class inherits Defect.
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

#ifndef FREESURFACE_H
#define FREESURFACE_H

#include "defect.h"
#include "dislocation.h"

/**
 * @brief The FreeSurface class.
 * @details This class represents a free surface in the simulation. It inherits the properties of the Defect class and has specific properties relevant to a free surface.
 */
class FreeSurface : public Defect
{
public:
    /**
     * @brief Default constructor.
     * @details Creates a free surface with origin at (0, 0, 0).
     */
    FreeSurface();

    /**
     * @brief Constructor for a free surface.
     * @param base Pointer to the base co-ordinate system. Default value: NULL.
     * @param p Position of the free surface. Default value: (0, 0, 0).
     */
    FreeSurface (CoordinateSystem *base = NULL, Vector3d p=Vector3d::zeros());

    /**
     * @brief Calculates the image force exerted by the free surface on a given dislocation.
     * @param disl Pointer to the dislocation on which the image force is to be calculated.
     * @param mu Shear modulus in Pa.
     * @param nu Poisson's ratio.
     * @return The vector containing the image force, expressed in the base co-ordinate system.
     */
    Vector3d imageForce (Dislocation* disl, double mu, double nu);
};

#endif // FREESURFACE_H
