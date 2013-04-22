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
   * Default constructor.
   *
   * Fills the stress tensor with zeros.
   */
  Stress ();
  /**
   * Constructor specifying the principal and shear stresses.
   * @param principal Pointer to the array containing principal stresses.
   * @param shear Pointer to the array containing shear stresses.
   */
  Stress (double *principal, double *shear);

  // Assignment functions
  /**
   * Takes the values in principalStresses and shearStresses and constructs the stress matrix.
   */
  void populateMatrix ();

  // Retrieval functions
  /**
   * Returns a 3-member array with the principal stresses.
   * @return 3-member array with the principal stresses.
   */
  double* getPrincipalStresses ();
  /**
   * Returns a 3-member array with the shear stresses.
   * @return 3-member array with the shear stresses.
   */
  double* getShearStresses ();
  
  // Operations
  /**
   * Rotates the present stress matrix using the rotation matrix supplied and returns the result.
   * @param alpha Rotation matrix.
   * @result Rotated stress tensor.
   */
  Stress rotate (Matrix33 alpha);
  
  
};

#endif
