/**
 * @file stress.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 22/04/2013
 * @brief Definition of the member functions if the Stress class.
 * @details This file defines the member functions of the Stress class for the stress tensor.
 */

#include "stress.h"

/**
 * @brief Default constructor.
 * @details Initializes the stress tensor with zeros.
 */
Stress::Stress ()
{
  int i, j;

  for (i=0; i<3; i++)
    {
      principalStresses [i] = 0.0;
      shearStresses [i] = 0.0;
    }

  this->populateMatrix ();
}

/**
 * @brief Constructor specifying the principal and shear stresses.
 * @details The principal and shear stresses are provided in the arguments and the symmetrical stress tensor is contstructed using them.
 * @param principal Pointer to the array containing principal stresses.
 * @param shear Pointer to the array containing shear stresses.
 */
Stress::Stress (double *principal, double *shear)
{
  int i;

  for (i=0; i<3; i++)
    {
      this->principalStresses [i] = principal [i];
      this->shearStresses [i] = shear [i];
    }

  this->populateMatrix ();
}

/**
 * @brief Construct the stress tensor from the principal and shear stresses.
 * @details Takes the values in principalStresses and shearStresses and constructs the symmetrical stress matrix.
 */
void Stress::populateMatrix ()
{
  this->x[0][0] = this->principalStresses [0];
  this->x[1][1] = this->principalStresses [1];
  this->x[2][2] = this->principalStresses [2];

  this->x[0][1] = this->x[1][0] = this->shearStresses [0];
  this->x[0][2] = this->x[2][0] = this->shearStresses [1];
  this->x[1][2] = this->x[2][1] = this->shearStresses [2];
}

/**
 * @brief Get the principal stresses.
 * @details Returns a 3-member array with the principal stresses: s11 s22 s33.
 * @return 3-member array with the principal stresses.
 */
double* Stress::getPrincipalStresses ()
{
  double p[3];
  int i;

  for (i=0; i<3; i++)
    {
      p[i] = this->principalStresses[i];
    }

  return (p);
}

/**
 * @brief Get the shear stresses.
 * @details Returns a 3-member array with the shear stresses: s12 s13 s23.
 * @return 3-member array with the shear stresses.
 */
double* Stress::getShearStresses ()
{
  double s[3];
  int i;

  for (i=0; i<3; i++)
    {
      s[i] = this->shearStresses[i];
    }

  return (s);
}

/**
 * @brief Rotate the stress tensor from one coordinate system to another.
 * @details Rotates the present stress matrix from one coordinate system to another using the rotation matrix supplied. The result is returned in a new Stress matrix.
 * @param alpha Rotation matrix.
 * @result Rotated stress tensor.
 */
Stress Stress::rotate (RotationMatrix alpha)
{
  Matrix33 alphaT = ^alpha;  // Transpose
  Stress sNew;

  sNew = alpha * (*this) * alphaT;  // Rotate the stress matrix

  return (sNew);
}
