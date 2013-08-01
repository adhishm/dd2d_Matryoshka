/**
 * @file freesurface.cpp
 * @author Adhish Majumdar
 * @version 1.1
 * @date 01/08/2013
 * @brief Definition of member functions of the FreeSurface class.
 * @details This file defines the member functions of the FreeSurface class representing a free surface in the simulation. This class inherits Defect.
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

#include "freesurface.h"

/**
 * @brief Default constructor.
 * @details Creates a free surface with origin at (0, 0, 0).
 */
FreeSurface::FreeSurface()
    : Defect (FREESURFACE,Vector3d::zeros())
{
    // Nothing to do here
}

/**
 * @brief Constructor for a free surface.
 * @param base Pointer to the base co-ordinate system. Default value: NULL.
 * @param p Position of the free surface. Default value: (0, 0, 0).
 */
FreeSurface::FreeSurface (CoordinateSystem *base = NULL, Vector3d p=Vector3d::zeros())
    : Defect (FREESURFACE, p, Vector3d::standardAxes(), base)
{
    // Nothing to do here
}

/**
 * @brief Calculates the image force exerted by the free surface on a given dislocation.
 * @details The image force exerted by the free surface on a dislocation is calculated by creating an image dislocation as if it were on the same slip plane, and then calculating the Peach-Koehler force on the present dislocation due to this image dislocation.
 * @param disl Pointer to the dislocation on which the image force is to be calculated.
 * @param mu Shear modulus in Pa.
 * @param nu Poisson's ratio.
 * @return The vector containing the image force, expressed in the base co-ordinate system.
 */
Vector3d FreeSurface::imageForce (Dislocation* disl, double mu, double nu)
{
    // Calculate the position and Burgers vector of the image
    Vector3d position = this->getPosition() + this->getPosition() - disl->getPosition();
    Vector3d burgers_disl  = disl->getBurgers();
    Vector3d burgers_image = burgers_disl * (-1.0);

    // Create an immobile image dislocation
    Dislocation* imageDislocation = new Dislocation(burgers_image,disl->getLineVector(),
                                                    position,this->getCoordinateSystem(),
                                                    disl->getBurgersMagnitude(),false);
    // Stress field of the image dislocation at the present dislocation position
    Stress s = imageDislocation->stressField(disl->getPosition(),mu,nu);
    // The resulting Peach-Koehler force
    Vector3d force = disl->forcePeachKoehler(s);

    // Clear memory
    delete (imageDislocation);
    imageDislocation = NULL;

    return (force);
}
