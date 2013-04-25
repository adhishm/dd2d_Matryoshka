/**
 * @file strain.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 22/04/2013
 * @brief Definition of the member functions if the Strain class.
 * @details This file defines the member functions of the Strain class for the strain tensor.
 */

#include "strain.h"

/**
 * @brief Default constructor.
 * @details Initializes the strain tensor with zeros.
 */
Strain::Strain ()
{
  int i, j;

  for (i=0; i<3; i++)
    {
      principalStrains [i] = 0.0;
      shearStrains [i] = 0.0;
    }

  this->populateMatrix ();
}

/**
 * @brief Constructor specifying the principal and shear strains.
 * @details The principal and shear strains are provided in the arguments and the symmetrical strain tensor is contstructed using them.
 * @param principal Pointer to the array containing principal strains.
 * @param shear Pointer to the array containing shear strains.
 */
Strain::Strain (double *principal, double *shear)
{
  int i;

  for (i=0; i<3; i++)
    {
      this->principalStrains [i] = principal [i];
      this->shearStrains [i] = shear [i];
    }

  this->populateMatrix ();
}

/**
 * @brief Construct the strain tensor from the principal and shear strains.
 * @details Takes the values in principalStrains and shearStrains and constructs the symmetrical strain matrix.
 */
void Strain::populateMatrix ()
{
  this->x[0][0] = this->principalStrains [0];
  this->x[1][1] = this->principalStrains [1];
  this->x[2][2] = this->principalStrains [2];

  this->x[0][1] = this->x[1][0] = this->shearStrains [0];
  this->x[0][2] = this->x[2][0] = this->shearStrains [1];
  this->x[1][2] = this->x[2][1] = this->shearStrains [2];
}

/**
 * @brief Get the principal strains.
 * @details Returns a 3-member array with the principal strains: s11 s22 s33.
 * @return 3-member array with the principal strains.
 */
double* Strain::getPrincipalStrains ()
{
  double p[3];
  int i;

  for (i=0; i<3; i++)
    {
      p[i] = this->principalStrains[i];
    }

  return (p);
}

/**
 * @brief Get the shear strains.
 * @details Returns a 3-member array with the shear strains: s12 s13 s23.
 * @return 3-member array with the shear strains.
 */
double* Strain::getShearStrains ()
{
  double s[3];
  int i;

  for (i=0; i<3; i++)
    {
      s[i] = this->shearStrains[i];
    }

  return (s);
}

/**
 * @brief Rotate the strain tensor from one coordinate system to another.
 * @details Rotates the present strain matrix from one coordinate system to another using the rotation matrix supplied. The result is returned in a new Strain matrix.
 * @param alpha Rotation matrix.
 * @result Rotated strain tensor.
 */
Strain Strain::rotate (Matrix33 alpha)
{
  Matrix33 alphaT = ^alpha;  // Transpose
  Strain sNew;

  sNew = alpha * (*this) * alphaT;  // Rotate the strain matrix

  return (sNew);
}
