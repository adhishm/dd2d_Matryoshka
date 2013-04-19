/**
 * @file matrix33.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 15/04/2013
 * @brief Definition of the Matrix33 class.
 * @details This file defines the Matrix33 class representing a 3x3 matrix in the simulation.
 */

#ifndef MATRIX33_H
#define MATRIX33_H

#include "vector3d.h"

/**
 * @brief Matrix33 class representing a 3x3 square matrix.
 *
 * @details This class represents a 3x3 square matrix. The member functions and operators define various operations that may be carried out on the matrix.
 */
class Matrix33
{
 protected:
  /**
   * Array containing the elements of the matrix.
   */
  double x[3][3];
 public:
  // Constructors
  /**
   * Default constructor.
   */
  Matrix33 ();
  /**
   * Constructor with the values provided in a 3x3 matrix.
   * @param a Pointer to the two-dimensional 3x3 array.
   */
  Matrix33 (double** a);
  /**
   * Constructor to create the matrix from the dyadic product of a vector with itself.
   * @param a The vector whose dyadic product results in the matrix.
   */
  Matrix33 (Vector3d a);
  /**
   * Constructor with the vectors, the product of which will result in the matrix.
   * @param a First vector.
   * @param b Second vector.
   */
  Matrix33 (Vector3d a, Vector3d b);
   
  // Functions
  /**
   * Function to set the value of an element indicated by its position.
   * @param row Row index of the element.
   * @param column Column index of the element.
   * @param value Value that the element is to be set to.
   */
  void setValue (int row, int column, double value);
  /**
   * Returns the value of the element located by the row and column indices provided.
   * @param row Row index of the element.
   * @param column Column index of the element.
   */
  double getValue (int row, int column);
   
  // Operators
  // Addition
  /**
   * Operator for addition of two matrices.
   * Adds the current matrix to the provided matrix and returns a third matrix with the result.
   */
  Matrix33 operator+ (const Matrix33&) const;
  /**
   * Operator for reflexive addition of two matrices.
   * Adds the current matrix to the provided matrix and populates the current matrix elements with the result.
   */
  void operator+= (const Matrix33&);
  // Subtraction
  /**
   * Operator for the subtraction of two matrices.
   * Subtracts the given matrix from the current matrix and returns the result in a new matrix.
   */
  Matrix33 operator- (const Matrix33&) const;
  /**
   * Operator for reflexive subtraction of two matrices.
   * Subtracts the given matrix from the current matrix and populates the current matrix with the result.
   */
  void operator-= (const Matrix33&);
  // Multiplication
  /**
   * Operator for scaling the matrix by a scalar.
   * Scales the current matrix by the scalar provided and returns the result in a third matrix.
   */
  Matrix33 operator* (const double&) const;
  /**
   * Operator for reflexive scaling of the matrix by a scalar.
   * Scales the current matrix by the scalar provided and populates the current matrix elements with the result.
   */
  void operator*= (const double&);
  /**
   * Operator for the multiplication of two matrices.
   * Multiplies the current matrix with another 3x3 matrix and returns the result in a new matrix.
   */
  Matrix33 operator* (const Matrix33&) const;
  /**
   * Operator for reflexive multiplication of two matrices.
   * Multiplies the current matrix with another 3x3 matrix and populates the elements of the current matrix with the result.
   */
  void operator*= (const Matrix33&);
  /**
   * Returns in a vector the result of the multiplication of the current matrix with the provided vector.
   */
  Vector3d operator* (const Vector3d&) const;
  
  // Matrix operations
  /**
   * Returns in a new matrix the transpose of the current matrix.
   */
  Matrix33 operator^ () const;
  /**
   * Returns the determinant of the current matrix.
   */
  double operator~ () const;
  /**
   * Returns in a new matrix the inverse of the current matrix.
   * If the current matrix is non-invertible, a zero matrix is returned.
   */
  Matrix33 operator! () const;
};

#endif
