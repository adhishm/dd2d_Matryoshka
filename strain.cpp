/**
 * @file strain.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 05/06/2013
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
 * @brief Constructor specifying the full matrix
 * @details This constructor accepts the full strain matrix as input and extracts the principal and shear strain components.
 * @param m Matrix33 variable containing the full strain tensor.
 */
Strain::Strain (Matrix33 m)
{
  int i, j;
  bool symmetry = true;

  // Verify symmetry
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  if (m.getValue(i,j) != m.getValue(j,i))
	    {
	      symmetry = false;
	      break;
	    }
	}
    }

  if (symmetry)
    {
      // The matrix is symmetrical
      this->principalStrains [0] = m.getValue(0,0);
      this->principalStrains [1] = m.getValue(1,1);
      this->principalStrains [2] = m.getValue(2,2);

      this->shearStrains [0] = m.getValue(0,1);
      this->shearStrains [1] = m.getValue(0,2);
      this->shearStrains [2] = m.getValue(1,2);
    }
  else
    {
      // The matrix is asymmetrical
      // A zero matrix will be returned
      for (i=0; i<3; i++)
	{
	  this->principalStrains[i] = 0.0;
	  this->shearStrains[i] = 0.0;
	}
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
 * @details Returns a vector of type Vector3d with the principal strains: s11 s22 s33.
 * @return Vector3d variable with the principal strains.
 */
Vector3d Strain::getPrincipalStrains () const
{
  return ( Vector3d (this->principalStrains [0],
		     this->principalStrains [1],
		     this->principalStrains [2] ) );
}

/**
 * @brief Get the shear strains.
 * @details Returns a vector of type Vector3d with the shear strains: s12 s13 s23.
 * @return Vector3d variable with the shear strains.
 */
Vector3d Strain::getShearStrains () const
{
  return ( Vector3d (this->shearStrains [0],
		     this->shearStrains [1],
		     this->shearStrains [2] ) );
}

/**
 * @brief Rotate the strain tensor from one coordinate system to another.
 * @details Rotates the present strain matrix from one coordinate system to another using the rotation matrix supplied. The result is returned in a new Strain matrix.
 * @param alpha Rotation matrix.
 * @result Rotated strain tensor.
 */
Strain Strain::rotate (RotationMatrix alpha)
{
  // Transpose
  RotationMatrix alphaT (alpha.transpose());

  // Rotate the strain matrix
  Strain sNew = Strain (alpha * (*this) * alphaT);

  return (sNew);
}
