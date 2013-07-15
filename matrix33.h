/**
 * @file matrix33.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 04/06/2013
 * @brief Definition of the Matrix33 class.
 * @details This file defines the Matrix33 class representing a 3x3 matrix in the simulation.
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
   * @brief Array containing the elements of the matrix.
   */
    double x[3][3];

public:
    // Constructors
    /**
   * @brief Default constructor.
   * @details Initializes the matrix with all elements equal to 0.0.
   */
    Matrix33 ();
    /**
   * @brief Constructor with the values provided in a 3x3 matrix.
   * @details Populated the mstrix with data present in corresponding elements of the provided 3x3 array.
   * @param a Pointer to the two-dimensional 3x3 array.
   */
    Matrix33 (double** a);
    /**
   * @brief Constructor to create the matrix from the dyadic product of a vector with itself.
   * @details The matrix is created by performing the dyadic product of the provided vector with itself.
   * @param a The vector whose dyadic product results in the matrix.
   */
    Matrix33 (Vector3d a);
    /**
   * @brief Constructor with the vectors, the product of which will result in the matrix.
   * @details The matrix is created from the product the first vector with the second.
   * @param a First vector.
   * @param b Second vector.
   */
    Matrix33 (Vector3d a, Vector3d b);

    // Functions
    /**
   * @brief Function to set the value of an element indicated by its position.
   * @details The element indicated by the arguments row and column is set to the value provided. The values of row and column must correspond to array indices, and thus can be one of 0, 1 and 2. In any other case 0.0 is returned.
   * @param row Row index of the element.
   * @param column Column index of the element.
   * @param value Value that the element is to be set to.
   */
    void setValue (int row, int column, double value);
    /**
   * @brief Returns the value of the element located by the row and column indices provided.
   * @details The value of the element indicated by the arguments row and column is returned. The values of row and column must correspond to array indices, and thus can be one of 0, 1 and 2. In any other case 0.0 is returned.
   * @param row Row index of the element.
   * @param column Column index of the element.
   * @return Value of the element located at the given position.
   */
    double getValue (int row, int column) const;
    /**
   * @brief Returns the adjugate matrix of the present matrix.
   * @details The adjugate matrix of the present matrix is returned. The adjugate matrix is calculated by evaluating the determinant of the cofactor matrix of each element, and then replacing the corresponding element position by the value of the determinant. This operation is useful in calculating the inverse of a matrix.
   * @return The adjugate matrix of the present matrix.
   */
    Matrix33 adjugate () const;
    /**
   * @brief Returns the transpose of the present matrix.
   * @details The transpose of a matrix is another matrix having rows identical to the columns of the present matrix, and vice-versa.
   * @return The transpose of the present matrix.
   */
    Matrix33 transpose () const;

    // Operators
    // Addition
    /**
   * @brief Operator for addition of two matrices.
   * @details Adds the current matrix to the provided matrix and returns a third matrix with the result.
   * @return Matrix containing the sum of the present matrix and the one provided.
   */
    Matrix33 operator+ (const Matrix33&) const;
    /**
   * @brief Operator for reflexive addition of two matrices.
   * @details Adds the current matrix to the provided matrix and populates the current matrix elements with the result.
   */
    void operator+= (const Matrix33&);
    // Subtraction
    /**
   * @brief Operator for the subtraction of two matrices.
   * @details Subtracts the given matrix from the current matrix and returns the result in a new matrix.
   * @return Matrix containing the result of subtracting the provided matrix from the current matrix.
   */
    Matrix33 operator- (const Matrix33&) const;
    /**
   * @brief Operator for reflexive subtraction of two matrices.
   * @details Subtracts the given matrix from the current matrix and populates the current matrix with the result.
   */
    void operator-= (const Matrix33&);
    // Multiplication
    /**
   * @brief Operator for scaling the matrix by a scalar.
   * @details Scales the current matrix by the scalar provided and returns the result in a third matrix.
   * @return Matrix containing the result of scaling the current matrix by the scalar provided as argument.
   */
    Matrix33 operator* (const double&) const;
    /**
   * @brief Operator for reflexive scaling of the matrix by a scalar.
   * @details Scales the current matrix by the scalar provided and populates the current matrix elements with the result.
   */
    void operator*= (const double&);
    /**
   * @brief Operator for the multiplication of two matrices.
   * @details Multiplies the current matrix with another 3x3 matrix and returns the result in a new matrix.
   * @return The result of the multiplication of the current matrix with the one provided as argument.
   */
    Matrix33 operator* (const Matrix33&) const;
    /**
   * @brief Operator for reflexive multiplication of two matrices.
   * @details Multiplies the current matrix with another 3x3 matrix and populates the elements of the current matrix with the result.
   */
    void operator*= (const Matrix33&);
    /**
   * @brief Operator for the multiplication of a matrix with a vector.
   * @details Returns in a vector the result of the multiplication of the current matrix with the provided vector.
   * @return The vector resulting from the multiplication of the current matrix with a vector.
   */
    Vector3d operator* (const Vector3d&) const;

    // Matrix operations
    /**
   * @brief Determinant.
   * @details Calculates the determinant of the current matrix.
   * @return Returns the determinant of the current matrix.
   */
    double operator~ () const;
    /**
   * @brief Inverse
   * @details Returns in a new matrix the inverse of the current matrix. If the current matrix is non-invertible, a zero matrix is returned.
   * @return Matrix with the inverse of the current matrix. If the current matrix is non-invertible, a zero matrix is returned.
   */
    Matrix33 operator! () const;
};

#endif
