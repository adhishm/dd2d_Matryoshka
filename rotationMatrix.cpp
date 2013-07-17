/**
 * @file rotationMatrix.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 25/04/2013
 * @brief Definition of the RotationMatrix class member functions.
 * @details This file defines member functions of the RotationMatrix class for carrying out 3D rotations and axes transformations.
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


#include "rotationMatrix.h"

/**
 * @brief Default constructor
 * @details Initializes the rotation matrix with a unit matrix.
 */
RotationMatrix::RotationMatrix ()
{
    *this = RotationMatrix (Matrix33::unitMatrix());
}

/**
 * @brief Constructor specifying the matrix.
 * @details The rotation matrix is provided as the matrix m.
 * @param m The matrix m which is equal to the rotation matrix.
 */
RotationMatrix::RotationMatrix (Matrix33 m)
{
    int i, j;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            this->setValue (i, j, (m.getValue(i,j)));
        }
    }
}

/**
 * @brief Defines the rotation matrix based on two co-ordinate systems.
 * @details The rotation matrix is created using the axes of the two co-ordinate systems provided as arguments. The vectors must be normalized to be unit vectors.
 * @param unPrimed Pointer to the array containing the three axes vectors of the unprimed (old) system.
 * @param primed Pointer to the array containing the three axes vectors of the primed (new) system.
 */
RotationMatrix::RotationMatrix (Vector3d *unPrimed, Vector3d *primed)
{
    int i, j;

    for ( i=0; i<3; i++ ) {
        for ( j=0; j<3; j++ ) {
            this->setValue ( i, j, primed[i]*unPrimed[j] );
        }
    }
}
