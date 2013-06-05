/**
 * @file rotationMatrix.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 25/04/2013
 * @brief Definition of the RotationMatrix class.
 * @details This file defines the RotationMatrix class for carrying out 3D rotations and axes transformations.
 */

#ifndef	ROTATIONMATRIX_H
#define ROTATIONMATRIX_H

#include "matrix33.h"

/**
 * @brief RotationMatrix class to represent a rotation matrix.
 * @details The member functions of this class create a rotation matrix for carrying out rotations in 3D and transformation of axes.
 */
class RotationMatrix : public Matrix33
{
 protected:
  // 
 public:
  // Constructors
  /**
   * @brief Default constructor
   * @details Initializes the rotation matrix with a unit matrix.
   */
  RotationMatrix ();
  /**
   * @brief Constructor specifying the matrix.
   * @details The rotation matrix is provided as the matrix m.
   * @param m The matrix m which is equal to the rotation matrix.
   */
  RotationMatrix (Matrix33 m);
  /**
   * @brief Defines the rotation matrix based on two co-ordinate systems.
   * @details The rotation matrix is created using the axes of the two co-ordinate systems provided as arguments. The vectors must be normalized to be unit vectors.
   * @param unPrimed Pointer to the array containing the three axes vectors of the unprimed (old) system.
   * @param primed Pointer to the array containing the three axes vectors of the primed (new) system.
   */
  RotationMatrix (Vector3d *unPrimed, Vector3d *primed);
};

#endif
