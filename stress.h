/**
 * @file stress.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 19/04/2013
 * @brief Definition of the Stress class.
 * @details This file defines the Stress class for the stress tensor.
 */

#ifndef STRESS_H
#define STRESS_H

#include "matrix33.h"

/**
 * Stress class to represent the stress tensor.
 *
 * The member functions of this class construct the symmetric stress tensor and operate on it.
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
};

#endif
