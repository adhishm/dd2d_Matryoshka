/**
 * @file strain.h
 * @author Adhish Majumdar
 * @version 1.1
 * @date 25/06/2013
 * @brief Definition of the Strain class.
 * @details This file defines the Strain class for the strain tensor.
 */

#ifndef STRAIN_H
#define STRAIN_H

#include "matrix33.h"
#include "rotationMatrix.h"

/**
 * @brief Strain class to represent the strain tensor.
 *
 * @details The member functions of this class construct the symmetric strain tensor and operate on it.
 */
class Strain : public Matrix33
{
 protected:
  /**
   * The three principal strains: s11, s22, s33.
   */
  double principalStrains[3];
  /**
   * The three shear strains: s12, s13, s23,
   */
  double shearStrains[3];
 public:
  // Constructors
  /**
   * @brief Default constructor.
   * @details Initializes the strain tensor with zeros.
   */
  Strain ();
  /**
   * @brief Constructor specifying the principal and shear strains.
   * @details The principal and shear strains are provided in the arguments and the symmetrical strain tensor is contstructed using them.
   * @param principal Pointer to the array containing principal strains.
   * @param shear Pointer to the array containing shear strains.
   */
  Strain (double *principal, double *shear);
  /**
   * @brief Constructor specifying the full matrix
   * @details This constructor accepts the full strain matrix as input and extracts the principal and shear strain components.
   * @param m Matrix33 variable containing the full strain tensor.
   */
  Strain (Matrix33 m);

  // Assignment functions
  /**
   * @brief Set the value of the principal strain indicated by the index.
   * @details The principal strains s_xx, s_yy, or s_zz are set by this function by the indices 0, 1, and 2 respectively.
   * @param i Index of the strain whose value is to be set.
   * @param v The value that has to be put.
   */
  void setPrincipalStrain (int i, double v);

  /**
   * @brief Set the value of the shear strain indicated by the index.
   * @details The principal strains s_xy, s_xz, or s_yz are set by this function by the indices 0, 1, and 2 respectively.
   * @param i Index of the strain whose value is to be set.
   * @param v The value that has to be put.
   */
  void setShearStrain (int i, double v);
  /**
   * @brief Construct the strain tensor from the principal and shear strains.
   * @details Takes the values in principalStrains and shearStrains and constructs the symmetrical strain matrix.
   */
  void populateMatrix ();

  // Access functions
  /**
   * @brief Get the principal strains.
   * @details Returns a vector of type Vector3d with the principal strains: s11 s22 s33.
   * @return Vector3d variable with the principal strains.
   */
  Vector3d getPrincipalStrains () const;
  /**
   * @brief Get one component of the principal strain.
   * @details Returns the value of the component of the principal strain indicated by the argument: 0=s11 1=s22 2=s33.
   * @param i The index of the component required.
   * @return The component of the principal strains.
   */
  double getPrincipalStrain (int i) const;
  /**
   * @brief Get the shear strains.
   * @details Returns a vector of type Vector3d with the shear strains: s12 s13 s23.
   * @return Vector3d variable with the shear strains.
   */
  Vector3d getShearStrains () const;
  /**
   * @brief Get one component of the shear strain.
   * @details Returns the value of the component of the shear strain indicated by the argument: 0=s01 1=s12 2=s23.
   * @param i The index of the component required.
   * @return The component of the shear strains.
   */
  double getShearStrain (int i) const;

  // Operators
  /**
   * @brief Operator for addition of two strain tensors.
   * @details Adds two strain tensors together and returns the result in a third tensor.
   * @return The result of the addition of two strain tensors.
   */
  Strain operator+ (const Strain&) const;
  /**
   * @brief Reflexive addition of two strain tensors.
   */
  void operator+= (const Strain&);
  
  // Operations
  /**
   * @brief Rotate the strain tensor from one coordinate system to another.
   * @details Rotates the present strain matrix from one coordinate system to another using the rotation matrix supplied. The result is returned in a new Strain matrix.
   * @param alpha Rotation matrix.
   * @result Rotated strain tensor.
   */
  Strain rotate (RotationMatrix alpha);  
};

#endif
