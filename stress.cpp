#include "stress.h"

/**
 * Default constructor.
 *
 * Fills the stress tensor with zeros.
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
 * Constructor specifying the principal and shear stresses.
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
 * Takes the values in principalStresses and shearStresses and constructs the stress matrix.
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
 * Returns a 3-member array with the principal stresses.
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
 * Returns a 3-member array with the shear stresses.
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
 * Rotates the present stress matrix using the rotation matrix supplied and returns the result.
 * @param alpha Rotation matrix.
 * @result Rotated stress tensor.
 */
Stress Stress::rotate (Matrix33 alpha)
{
  Matrix33 alphaT = ^alpha;  // Transpose
  Stress sNew;
  
  sNew = alpha * (*this) * alphaT;  // Rotate the stress matrix
  
  return (sNew);
}
