/**
 * @file stress.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 22/04/2013
 * @brief Definition of the Stress class.
 * @details This file defines the Stress class for the stress tensor.
 */

#ifndef STRESS_H
#define STRESS_H

#include "matrix33.h"

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

  // Assignment functions
  /**
   * @brief Construct the stress tensor from the principal and shear stresses.
   * @details Takes the values in principalStresses and shearStresses and constructs the symmetrical stress matrix.
   */
  void populateMatrix ();

  // Retrieval functions
  /**
   * @brief Get the principal stresses.
   * @details Returns a 3-member array with the principal stresses: s11 s22 s33.
   * @return 3-member array with the principal stresses.
   */
  double* getPrincipalStresses ();
  /**
   * @brief Get the shear stresses.
   * @details Returns a 3-member array with the shear stresses: s12 s13 s23.
   * @return 3-member array with the shear stresses.
   */
  double* getShearStresses ();
  
  // Operations
  /**
   * @brief Rotate the stress tensor from one coordinate system to another.
   * @details Rotates the present stress matrix from one coordinate system to another using the rotation matrix supplied. The result is returned in a new Stress matrix.
   * @param alpha Rotation matrix.
   * @result Rotated stress tensor.
   */
  Stress rotate (Matrix33 alpha);
  
  
};

#endif
