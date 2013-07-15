/**
 * @file matrix33.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 04/06/2013
 * @brief Definition of the member functions and operators of the Matrix33 class.
 * @details This file defines the member functions and operators of the Matrix33 class representing a 3x3 matrix in the simulation.
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


#include "matrix33.h"

// Constructors
/**
 * @brief Default constructor.
 * @details Initializes the matrix with all elements equal to 0.0.
 */
Matrix33::Matrix33 ()
{
    int i, j;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            this->x[i][j] = 0.0;
        }
    }
}

/**
 * @brief Constructor with the values provided in a 3x3 matrix.
 * @details Populated the mstrix with data present in corresponding elements of the provided 3x3 array.
 * @param a Pointer to the two-dimensional 3x3 array.
 */
Matrix33::Matrix33 (double** a)
{
    int i, j;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            this->x[i][j] = a[i][j];
        }
    }
}

/**
 * @brief Constructor to create the matrix from the dyadic product of a vector with itself.
 * @details The matrix is created by performing the dyadic product of the provided vector with itself.
 * @param a The vector whose dyadic product results in the matrix.
 */
Matrix33::Matrix33 (Vector3d a)
{
    int i, j;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            this->x[i][j] = a.getValue(i) * a.getValue(j);
        }
    }
}

/**
 * @brief Constructor with the vectors, the product of which will result in the matrix.
 * @details The matrix is created from the product the first vector with the second.
 * @param a First vector.
 * @param b Second vector.
 */
Matrix33::Matrix33 (Vector3d a, Vector3d b)
{
    int i, j;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            this->x[i][j] = a.getValue(i) * b.getValue(j);
        }
    }
}

// Functions
/**
 * @brief Function to set the value of an element indicated by its position.
 * @details The element indicated by the arguments row and column is set to the value provided. The values of row and column must correspond to array indices, and thus can be one of 0, 1 and 2. In any other case 0.0 is returned.
 * @param row Row index of the element.
 * @param column Column index of the element.
 * @param value Value that the element is to be set to.
 */
void Matrix33::setValue (int row, int column, double value)
{
    if (row>=0 && row<3)
    {
        if (column>=0 && column<3)
        {
            this->x[row][column] = value;
        }
    }
}

/**
 * @brief Returns the value of the element located by the row and column indices provided.
 * @details The value of the element indicated by the arguments row and column is returned. The values of row and column must correspond to array indices, and thus can be one of 0, 1 and 2. In any other case 0.0 is returned.
 * @param row Row index of the element.
 * @param column Column index of the element.
 * @return Value of the element located at the given position.
 */
double Matrix33::getValue (int row, int column) const
{
    if (row>=0 && row<3)
    {
        if (column>=0 && column<3)
        {
            return (this->x[row][column]);
        }
    }

    return (0.0);
}

/**
 * @brief Returns the adjugate matrix of the present matrix.
 * @details The adjugate matrix of the present matrix is returned. The adjugate matrix is calculated by evaluating the determinant of the cofactor matrix of each element, and then replacing the corresponding element position by the value of the determinant. This operation is useful in calculating the inverse of a matrix.
 * @return The adjugate matrix of the present matrix.
 */
Matrix33 Matrix33::adjugate () const
{
    Matrix33 adj;

    adj.setValue(0, 0, ((this->x[1][1]*this->x[2][2]) - (this->x[1][2]*this->x[2][1])));
    adj.setValue(0, 1, ((this->x[1][2]*this->x[2][0]) - (this->x[1][0]*this->x[2][2])));
    adj.setValue(0, 2, ((this->x[1][0]*this->x[2][1]) - (this->x[1][1]*this->x[2][0])));

    adj.setValue(1, 0, ((this->x[2][1]*this->x[0][2]) - (this->x[0][1]*this->x[2][2])));
    adj.setValue(1, 1, ((this->x[2][2]*this->x[0][0]) - (this->x[2][0]*this->x[0][2])));
    adj.setValue(1, 2, ((this->x[2][0]*this->x[0][1]) - (this->x[2][1]*this->x[0][0])));

    adj.setValue(2, 0, ((this->x[0][1]*this->x[1][2]) - (this->x[0][2]*this->x[1][1])));
    adj.setValue(2, 1, ((this->x[0][2]*this->x[1][0]) - (this->x[0][0]*this->x[1][2])));
    adj.setValue(2, 2, ((this->x[0][0]*this->x[1][1]) - (this->x[1][0]*this->x[0][1])));

    return (adj);
}

/**
 * @brief Returns the transpose of the present matrix.
 * @details The transpose of a matrix is another matrix having rows identical to the columns of the present matrix, and vice-versa.
 * @return The transpose of the present matrix.
   */
Matrix33 Matrix33::transpose () const
{
    Matrix33 tr;
    int i, j;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            tr.setValue (i, j, this->x[j][i]);
        }
    }
    return (tr);
}

// Operators
// Addition
/**
 * @brief Operator for addition of two matrices.
 * @details Adds the current matrix to the provided matrix and returns a third matrix with the result.
 * @return Matrix containing the sum of the present matrix and the one provided.
 */
Matrix33 Matrix33::operator+ (const Matrix33& p) const
{
    int i, j;
    Matrix33 r;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            r.setValue(i, j, (this->x[i][j] + p.getValue(i, j)));
        }
    }

    return (r);
}

/**
 * @brief Operator for reflexive addition of two matrices.
 * @details Adds the current matrix to the provided matrix and populates the current matrix elements with the result.
 */
void Matrix33::operator+= (const Matrix33& p)
{
    int i, j;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            this->x[i][j] += p.getValue(i, j);
        }
    }
}

// Subtraction
/**
 * @brief Operator for the subtraction of two matrices.
 * @details Subtracts the given matrix from the current matrix and returns the result in a new matrix.
 * @return Matrix containing the result of subtracting the provided matrix from the current matrix.
 */
Matrix33 Matrix33::operator- (const Matrix33& p) const
{
    int i, j;
    Matrix33 r;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            r.setValue(i, j, (this->x[i][j] - p.getValue(i, j)));
        }
    }

    return (r);
}

/**
 * @brief Operator for reflexive subtraction of two matrices.
 * @details Subtracts the given matrix from the current matrix and populates the current matrix with the result.
 */
void Matrix33::operator-= (const Matrix33& p)
{
    int i, j;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            this->x[i][j] -= p.getValue(i, j);
        }
    }
}

// Multiplication
/**
 * @brief Operator for scaling the matrix by a scalar.
 * @details Scales the current matrix by the scalar provided and returns the result in a third matrix.
 * @return Matrix containing the result of scaling the current matrix by the scalar provided as argument.
 */
Matrix33 Matrix33::operator* (const double& p) const
{
    int i, j;
    Matrix33 r;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            r.setValue(i, j, (this->x[i][j] * p));
        }
    }

    return (r);
}

/**
 * @brief Operator for reflexive scaling of the matrix by a scalar.
 * @details Scales the current matrix by the scalar provided and populates the current matrix elements with the result.
 */
void Matrix33::operator*= (const double& p)
{
    int i, j;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            this->x[i][j] *= p;
        }
    }
}

/**
 * @brief Operator for the multiplication of two matrices.
 * @details Multiplies the current matrix with another 3x3 matrix and returns the result in a new matrix.
 * @return The result of the multiplication of the current matrix with the one provided as argument.
 */
Matrix33 Matrix33::operator* (const Matrix33& p) const
{
    int i, j, k;
    Matrix33 r;
    double s;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            s = 0.0;
            for (k=0; k<3; k++)
            {
                s += this->x[i][k] * p.getValue(k,j);
            }
            r.setValue (i, j, s);
        }
    }

    return (r);
}

/**
 * @brief Operator for reflexive multiplication of two matrices.
 * @details Multiplies the current matrix with another 3x3 matrix and populates the elements of the current matrix with the result.
 */
void Matrix33::operator*= (const Matrix33& p)
{
    Matrix33* r = new Matrix33;

    *r = (*this) * p;
    *this = *r;

    delete(r);
    r = NULL;
}

/**
 * @brief Operator for the multiplication of a matrix with a vector.
 * @details Returns in a vector the result of the multiplication of the current matrix with the provided vector.
 * @return The vector resulting from the multiplication of the current matrix with a vector.
 */
Vector3d Matrix33::operator* (const Vector3d& v) const
{
    Vector3d r(0.0, 0.0, 0.0);
    double s;
    int i, j;

    for (i=0; i<3; i++)
    {
        s = 0.0;
        for (j=0; j<3; j++)
        {
            s += this->x[i][j] * v.getValue(j);
        }
        r.setValue (i, s);
    }

    return (r);
}

// Matrix operations
/**
 * @brief Determinant.
 * @details Calculates the determinant of the current matrix.
 * @return Returns the determinant of the current matrix.
 */
double Matrix33::operator~ () const
{
    double d = 0.0;

    d += this->x[0][0] * ( (this->x[1][1]*this->x[2][2]) - (this->x[2][1]*this->x[1][2]) );
    d += this->x[0][1] * ( (this->x[1][2]*this->x[2][0]) - (this->x[1][0]*this->x[2][2]) );
    d += this->x[0][2] * ( (this->x[1][0]*this->x[2][1]) - (this->x[2][0]*this->x[1][1]) );

    return (d);
}

/**
 * @brief Inverse
 * @details Returns in a new matrix the inverse of the current matrix. If the current matrix is non-invertible, a zero matrix is returned.
 * @return Matrix with the inverse of the current matrix. If the current matrix is non-invertible, a zero matrix is returned.
 */
Matrix33 Matrix33::operator! () const
{
    Matrix33 r;	// Result matrix

    double determinant = ~(*this);

    if (determinant == 0.0)
    {
        // The matrix is non-invertible
        return (r);	// Zero matrix
    }

    // If we are still here, the matrix is invertible

    //  Transpose
    Matrix33 tr = this->transpose();

    // Find Adjugate matrix
    Matrix33 adj = tr.adjugate();

    // Calculate the inverse by dividing the adjugate matrix by the determinant
    r = adj * (1.0/determinant);

    return (r);
}
