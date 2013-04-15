/**
 *@file vector3d.h
 *@author Adhish Majumdar
 *@version 0.0
 *@date 15/04/2013
 *@brief Definition of the Vector3d class.
 *@details This file defines the Vector3d class representing a single 3-dimensional vector in the simulation.
 */

#ifndef VECTOR3D_H
#define VECTOR3D_H

/**
 * Vector3d class representing a single 3-dimensional vector in the simulation.
 */
class Vector3d
{
 protected:
  /**
   * The elements if the vector.
   */
  double x[3];
 public:
  // Constructors
  /**
   * Default constructor.
   */
  Vector3d ();
  /**
   * Constructor with values provided in an array.
   * @param a Pointer to the array containing the elements of the vector
   */
  Vector3d (double* a);
  /**
   * Constructor with values provided explicitly.
   * @param a1 Value of the first element of the vector.
   * @param a2 Value of the second element of the vector.
   * @param a3 Value of the third element of the vector.
   */
  Vector3d (double a1, double a2, double a3);

  // Access functions
  /**
   * Function to set the value of an element of the vector.
   * @param index Index of the element whose value is to be set.
   * @param value Value that is to be given to the element.
   */
  void setValue (int index, double value);
  /**
   * Function to set the value of the entire vector using an array.
   * @param a Pointer ot the array containing the values of the elements of the vector.
   */
  void setVector (double* a);
  /**
   * Function to get the value of an element of the vector.
   * @param index Index of the element whose value is to be got.
   */
  double getValue (int index);
  /**
   * Function to get the values of the elements of the vector in an array.
   */
  double* getVector ();
  /**
   * Computes the sum of the elements of the vector.
   */
  double sum ();

  // Operators
  // Addition
  /**
   * Operator for addition of two vectors.
   * Adds the current vector to the provided vector and returns a third vector with the result.
   */
  Vector3d operator+ (const Vector3d&) const;
  /**
   * Operator for reflexive addition of two vectors.
   * Adds the current vector to the provided vector and populates the current vector elements with the result.
   */
  void operator+= (const Vector3d&);
  // Subtraction
  /**
   * Operator for the subtraction of two vectors.
   * Subtracts the given vector from the current vector and returns the result in a new vector.
   */
  Vector3d operator- (const Vector3d&) const;
  /**
   * Operator for reflexive subtraction of two vectors.
   * Subtracts the given vector from the current vector and populates the current vector with the result.
   */
  void operator-= (const Vector3d&);
  // Multiplication
  /**
   * Operator for scaling the vector by a scalar.
   * Scales the current vector by the scalar provided and returns the result in a third vector.
   */
  Vector3d operator* (const double&) const;
  /**
   * Operator for reflexive scaling of the vector by a scalar.
   * Scales the current vector by the scalar provided and populates the current vector elements with the result.
   */
  void operator*= (const double&);
  /**
   * Operator for the scalar product of two vectors.
   */
  double operator* (const Vector3d&) const;
  /**
   * Operator for the vector product of two vectors.
   * Evaluates the vector product of the current vector with the provided vector and returns the result in a third vector.
   */
  Vector3d operator^ (const Vector3d&) const;
  /**
   * Operator for reflexive vector product of two vectors.
   * Evaluates the vector product of the current vector and the one provided, and populates the result in the current vector.
   */
  void operator^= (const Vector3d&);
};

#endif
