/**
 * @file stress.h
 * @author Adhish Majumdar
 * @version 1.1
 * @date 25/06/2013
 * @brief Definition of the Stress class.
 * @details This file defines the Stress class for the stress tensor.
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


#ifndef STRESS_H
#define STRESS_H

#include "matrix33.h"
#include "rotationMatrix.h"

/**
 * @brief Stress class to represent the stress tensor.
 *
 * @details The member functions of this class construct the symmetric stress tensor and operate on it.
 */
class Stress : public Matrix33
{
 protected:
  /**
   * The three principal stresses: s11, s22, s33.
   */
  double principalStresses[3];
  /**
   * The three shear stresses: s12, s13, s23,
   */
  double shearStresses[3];
 public:
  // Constructors
  /**
   * @brief Default constructor.
   * @details Initializes the stress tensor with zeros.
   */
  Stress ();
  /**
   * @brief Constructor specifying the principal and shear stresses.
   * @details The principal and shear stresses are provided in the arguments and the symmetrical stress tensor is contstructed using them.
   * @param principal Pointer to the array containing principal stresses.
   * @param shear Pointer to the array containing shear stresses.
   */
  Stress (double *principal, double *shear);
  /**
   * @brief Constructor specifying the full matrix
   * @details This constructor accepts the full stress matrix as input and extracts the principal and shear stress components.
   * @param m Matrix33 variable containing the full stress tensor.
   */
  Stress (Matrix33 m);

  // Assignment functions
  /**
   * @brief Set the value of the principal stress indicated by the index.
   * @details The principal stresses s_xx, s_yy, or s_zz are set by this function by the indices 0, 1, and 2 respectively.
   * @param i Index of the stress whose value is to be set.
   * @param v The value that has to be put.
   */
  void setPrincipalStress (int i, double v);

  /**
   * @brief Set the value of the shear stress indicated by the index.
   * @details The principal stresses s_xy, s_xz, or s_yz are set by this function by the indices 0, 1, and 2 respectively.
   * @param i Index of the stress whose value is to be set.
   * @param v The value that has to be put.
   */
  void setShearStress (int i, double v);

  /**
   * @brief Construct the stress tensor from the principal and shear stresses.
   * @details Takes the values in principalStresses and shearStresses and constructs the symmetrical stress matrix.
   */
  void populateMatrix ();

  // Access functions
  /**
   * @brief Get the principal stresses.
   * @details Returns a vector of type Vector3d with the principal stresses: s11 s22 s33.
   * @return Vector3d variable with the principal stresses.
   */
  Vector3d getPrincipalStresses () const;
  /**
   * @brief Get one component of the principal stress.
   * @details Returns the value of the component of the principal stress indicated by the argument: 0=s11 1=s22 2=s33.
   * @param i The index of the component required.
   * @return The component of the principal stresses.
   */
  double getPrincipalStress (int i) const;
  /**
   * @brief Get the shear stresses.
   * @details Returns a vector of type Vector3d with the shear stresses: s12 s13 s23.
   * @return Vector3d variable with the shear stresses.
   */
  Vector3d getShearStresses () const;
  /**
   * @brief Get one component of the shear stress.
   * @details Returns the value of the component of the shear stress indicated by the argument: 0=s01 1=s12 2=s23.
   * @param i The index of the component required.
   * @return The component of the shear stresses.
   */
  double getShearStress (int i) const;

  // Operators
  /**
   * @brief Operator for addition of two stress tensors.
   * @details Adds two stress tensors together and returns the result in a third tensor.
   * @return The result of the addition of two stress tensors.
   */
  Stress operator+ (const Stress&) const;
  /**
   * @brief Reflexive addition of two stress tensors.
   */
  void operator+= (const Stress&);
  
  // Operations
  /**
   * @brief Rotate the stress tensor from one coordinate system to another.
   * @details Rotates the present stress matrix from one coordinate system to another using the rotation matrix supplied. The result is returned in a new Stress matrix.
   * @param alpha Rotation matrix.
   * @result Rotated stress tensor.
   */
  Stress rotate (RotationMatrix alpha);
};

#endif
