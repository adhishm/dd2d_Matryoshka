/**
 * @file rotationMatrix.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 25/04/2013
 * @brief Definition of the RotationMatrix class member functions.
 * @details This file defines member functions of the RotationMatrix class for carrying out 3D rotations and axes transformations.
 */

#include "rotationMatrix.h"

/**
 * @brief Default constructor
 * @details Initializes the rotation matrix with a unit matrix.
 */
RotationMatrix::RotationMatrix ()
{
    int i,  j;

    for ( i=0; i<3; i++ ) {
        for ( j=0; i<3; j++ ) {
            if ( i==j ) {
                this->setValue ( i, j, 1.0 );
            }
            else {
                this->setValue ( i, j, 0.0 );
            }
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
