/**
 * @file strain.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 22/04/2013
 * @brief Definition of the Strain class.
 * @details This file defines the Strain class for the strain tensor.
 */

#ifndef STRAIN_H
#define STRAIN_H

#include "matrix33.h"

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

  // Assignment functions
  /**
   * @brief Construct the strain tensor from the principal and shear strains.
   * @details Takes the values in principalStrains and shearStrains and constructs the symmetrical strain matrix.
   */
  void populateMatrix ();

  // Retrieval functions
  /**
   * @brief Get the principal strains.
   * @details Returns a 3-member array with the principal strains: s11 s22 s33.
   * @return 3-member array with the principal strains.
   */
  double* getPrincipalStrains ();
  /**
   * @brief Get the shear strains.
   * @details Returns a 3-member array with the shear strains: s12 s13 s23.
   * @return 3-member array with the shear strains.
   */
  double* getShearStrains ();
  
  // Operations
  /**
   * @brief Rotate the strain tensor from one coordinate system to another.
   * @details Rotates the present strain matrix from one coordinate system to another using the rotation matrix supplied. The result is returned in a new Strain matrix.
   * @param alpha Rotation matrix.
   * @result Rotated strain tensor.
   */
  Strain rotate (Matrix33 alpha);  
};

#endif
