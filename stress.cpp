/**
 * @file stress.cpp
 * @author Adhish Majumdar
 * @version 1.1
 * @date 01/07/2013
 * @brief Definition of the member functions of the Stress class.
 * @details This file defines the member functions of the Stress class for the stress tensor.
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


#include "stress.h"

/**
 * @brief Default constructor.
 * @details Initializes the stress tensor with zeros.
 */
Stress::Stress ()
{
  int i;

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
 * @brief Constructor specifying the full matrix
 * @details This constructor accepts the full stress matrix as input and extracts the principal and shear stress components.
 * @param m Matrix33 variable containing the full stress tensor.
 */
Stress::Stress (Matrix33 m)
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
      this->principalStresses [0] = m.getValue(0,0);
      this->principalStresses [1] = m.getValue(1,1);
      this->principalStresses [2] = m.getValue(2,2);

      this->shearStresses [0] = m.getValue(0,1);
      this->shearStresses [1] = m.getValue(0,2);
      this->shearStresses [2] = m.getValue(1,2);
    }
  else
    {
      // The matrix is asymmetrical
      // A zero matrix will be returned
      for (i=0; i<3; i++)
	{
	  this->principalStresses[i] = 0.0;
	  this->shearStresses[i] = 0.0;
	}
    }

  this->populateMatrix ();
}

/**
 * @brief Set the value of the principal stress indicated by the index.
 * @details The principal stresses s_xx, s_yy, or s_zz are set by this function by the indices 0, 1, and 2 respectively.
 * @param i Index of the stress whose value is to be set.
 * @param v The value that has to be put.
   */
void Stress::setPrincipalStress (int i, double v)
{
  if (i>=0 && i<=2)
    {
      this->principalStresses[i] = v;
    }
}

/**
 * @brief Set the value of the shear stress indicated by the index.
 * @details The principal stresses s_xy, s_xz, or s_yz are set by this function by the indices 0, 1, and 2 respectively.
 * @param i Index of the stress whose value is to be set.
 * @param v The value that has to be put.
 */
void Stress::setShearStress (int i, double v)
{
  if (i>=0 && i<=2)
    {
      this->shearStresses[i] = v;
    }
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
 * @details Returns a vector of type Vector3d with the principal stresses: s11 s22 s33.
 * @return Vector3d variable with the principal stresses.
 */
Vector3d Stress::getPrincipalStresses () const
{
  return ( Vector3d (this->principalStresses [0],
		     this->principalStresses [1],
		     this->principalStresses [2] ) );
}

/**
 * @brief Get one component of the principal stress.
 * @details Returns the value of the component of the principal stress indicated by the argument: 0=s11 1=s22 2=s33.
 * @param i The index of the component required.
   * @return The component of the principal stresses.
   */
double Stress::getPrincipalStress (int i) const
{
  if (i>=0 && i<=2)
    {
      return (this->principalStresses[i]);
    }
  else
    {
      return (0.0);
    }
}
  
/**
 * @brief Get the shear stresses.
 * @details Returns a vector of type Vector3d with the shear stresses: s12 s13 s23.
 * @return Vector3d variable with the shear stresses.
 */
Vector3d Stress::getShearStresses () const
{
  return ( Vector3d (this->shearStresses [0],
		     this->shearStresses [1],
		     this->shearStresses [2] ) );
}

/**
 * @brief Get one component of the shear stress.
 * @details Returns the value of the component of the shear stress indicated by the argument: 0=s01 1=s12 2=s23.
 * @param i The index of the component required.
   * @return The component of the shear stresses.
   */
double Stress::getShearStress (int i) const
{
  if (i>=0 && i<=2)
    {
      return (this->shearStresses[i]);
    }
  else
    {
      return (0.0);
    }
}

/**
 * @brief Operator for addition of two stress tensors.
 * @details Adds two stress tensors together and returns the result in a third tensor.
 * @return The result of the addition of two stress tensors.
 */
Stress Stress::operator+ (const Stress& p) const
{
  Stress s;
  int i;

  for (i=0; i<3; i++)
    {
      s.setPrincipalStress (i, this->getPrincipalStress(i) + p.getPrincipalStress(i));
      s.setShearStress (i, this->getShearStress(i) + p.getShearStress(i));
    }

  s.populateMatrix ();
  return (s);
}

/**
 * @brief Reflexive addition of two stress tensors.
 */
void Stress::operator+= (const Stress& p)
{
  int i;
  
  for (i=0; i<3; i++)
    {
      this->setPrincipalStress (i, this->getPrincipalStress(i) + p.getPrincipalStress(i));
      this->setShearStress (i, this->getShearStress(i) + p.getShearStress(i));
    }

  this->populateMatrix ();
}

/**
 * @brief Rotate the stress tensor from one coordinate system to another.
 * @details Rotates the present stress matrix from one coordinate system to another using the rotation matrix supplied. The result is returned in a new Stress matrix.
 * @param alpha Rotation matrix.
 * @result Rotated stress tensor.
 */
Stress Stress::rotate (RotationMatrix alpha)
{
  // Transpose
  RotationMatrix alphaT (alpha.transpose());

  // Rotate the stress matrix
  Matrix33 m = alpha * ((*this) * alphaT);
  double *principalStress = new double[3];
  double *shearStress = new double[3];
  int i;

  for (i=0; i<3; i++)
    {
      principalStress[i] = m.getValue(i,i);
    }
  shearStress[0] = m.getValue(0,1);
  shearStress[1] = m.getValue(0,2);
  shearStress[2] = m.getValue(1,2);
  Stress sNew = Stress (principalStress, shearStress);

  delete (principalStress); principalStress = NULL;
  delete (shearStress);     shearStress = NULL;

  return (sNew);
}
