/**
 * @file strain.cpp
 * @author Adhish Majumdar
 * @version 1.1
 * @date 25/06/2013
 * @brief Definition of the member functions if the Strain class.
 * @details This file defines the member functions of the Strain class for the strain tensor.
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
 * @brief Set the value of the principal strain indicated by the index.
 * @details The principal strains s_xx, s_yy, or s_zz are set by this function by the indices 0, 1, and 2 respectively.
 * @param i Index of the strain whose value is to be set.
 * @param v The value that has to be put.
   */
void Strain::setPrincipalStrain (int i, double v)
{
  if (i>=0 && i<=2)
    {
      this->principalStrains[i] = v;
    }
}

/**
 * @brief Set the value of the shear strain indicated by the index.
 * @details The principal strains s_xy, s_xz, or s_yz are set by this function by the indices 0, 1, and 2 respectively.
 * @param i Index of the strain whose value is to be set.
 * @param v The value that has to be put.
 */
void Strain::setShearStrain (int i, double v)
{
  if (i>=0 && i<=2)
    {
      this->shearStrains[i] = v;
    }
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
 * @brief Get one component of the principal strain.
 * @details Returns the value of the component of the principal strain indicated by the argument: 0=s11 1=s22 2=s33.
 * @param i The index of the component required.
   * @return The component of the principal strains.
   */
double Strain::getPrincipalStrain (int i) const
{
  if (i>=0 && i<=2)
    {
      return (this->principalStrains[i]);
    }
  else
    {
      return (0.0);
    }
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
 * @brief Get one component of the shear strain.
 * @details Returns the value of the component of the shear strain indicated by the argument: 0=s01 1=s12 2=s23.
 * @param i The index of the component required.
   * @return The component of the shear strains.
   */
double Strain::getShearStrain (int i) const
{
  if (i>=0 && i<=2)
    {
      return (this->shearStrains[i]);
    }
  else
    {
      return (0.0);
    }
}

/**
 * @brief Operator for addition of two strain tensors.
 * @details Adds two strain tensors together and returns the result in a third tensor.
 * @return The result of the addition of two strain tensors.
 */
Strain Strain::operator+ (const Strain& p) const
{
  Strain s;
  int i;

  for (i=0; i<3; i++)
    {
      s.setPrincipalStrain (i, this->getPrincipalStrain(i) + p.getPrincipalStrain(i));
      s.setShearStrain (i, this->getShearStrain(i) + p.getShearStrain(i));
    }

  s.populateMatrix ();
  return (s);
}

/**
 * @brief Reflexive addition of two strain tensors.
 */
void Strain::operator+= (const Strain& p)
{
  int i;
  
  for (i=0; i<3; i++)
    {
      this->setPrincipalStrain (i, this->getPrincipalStrain(i) + p.getPrincipalStrain(i));
      this->setShearStrain (i, this->getShearStrain(i) + p.getShearStrain(i));
    }

  this->populateMatrix ();
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
  Matrix33 m = alpha * ((*this) * alphaT);
  double *principalStrain = new double[3];
  double *shearStrain = new double[3];
  int i;

  for (i=0; i<3; i++)
    {
      principalStrain[i] = m.getValue(i,i);
    }
  shearStrain[0] = m.getValue(0,1);
  shearStrain[1] = m.getValue(0,2);
  shearStrain[2] = m.getValue(1,2);
  Strain sNew = Strain (principalStrain, shearStrain);

  delete (principalStrain); principalStrain = NULL;
  delete (shearStrain);     shearStrain = NULL;

  return (sNew);
}
