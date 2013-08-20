/**
 * @file vector3d.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 17/07/2013
 * @brief Definition of the Vector3d class.
 * @details This file defines the Vector3d class representing a single 3-dimensional vector in the simulation.
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


#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iterator>

/**
 * @brief Vector3d class representing a single 3-dimensional vector in the simulation.
 *
 * @details This class represents a vector in 3D space. The member functions and operators define various operations on the vector and its interactions with other data types.
 */
class Vector3d
{
protected:
    /**
   * @brief The elements of the vector.
   */
    double x[3];
public:
    // Constructors
    /**
   * @brief Default constructor.
   * @details Initializes the vector with all elements equal to 0.0.
   */
    Vector3d ();
    /**
   * @brief Constructor with values provided in an array.
   * @details Initializes the vector with the values provided in the array.
   * @param a Pointer to the array containing the elements of the vector
   */
    Vector3d (double* a);
    /**
   * @brief Constructor with values provided explicitly.
   * @details Initializes the vector with the three values provided as arguments.
   * @param a1 Value of the first element of the vector.
   * @param a2 Value of the second element of the vector.
   * @param a3 Value of the third element of the vector.
   */
    Vector3d (double a1, double a2, double a3);

    // Destructor
    /**
     * @brief Destructor for the class Vector3d.
     * @details The destructor is declared as virtual in order to avoid conflicts with derived class destructors.
     */
    virtual ~Vector3d ()
    {

    }

    // Assignment functions
    /**
   * @brief Function to set the value of an element of the vector.
   * @details Sets the value of the element indicated by the index argument.
   * @param index Index of the element whose value is to be set.
   * @param value Value that is to be given to the element.
   */
    void setValue (int index, double value);
    /**
   * @brief Function to set the value of the entire vector using an array.
   * @details Sets the values of the elements if the vector to values in the array pointed to by the argument a.
   * @param a Pointer ot the array containing the values of the elements of the vector.
   */
    void setVector (double* a);

    // Access functions
    /**
   * @brief Function to get the value of an element of the vector.
   * @details Returns the value of the element at the position indicated by the argument index.
   * @param index Index of the element whose value is to be got.
   * @return The value of the element of the vector at the position
   */
    double getValue (int index) const;
    /**
   * @brief Function to get the values of the elements of the vector in an array.
   * @details The vector is returned in an array.
   * @return Pointer to the first term of an array containing the elements of the vector.
   */
    double* getVector () const;
    /**
   * @brief Computes the sum of the elements of the vector.
   * @details Sums the elements of the vector and returns the result.
   * @return The sum of the elements of the vector.
   */
    double sum () const;
    /**
   * @brief Computes the magnitude of the vector.
   * @details Computes the magnitude of the vector. Basically the square root of the sum of the squares of the vector elements.
   * @return The magnitude of the vector.
   */
    double magnitude () const;
    /**
   * @brief Returns the vector normalized to be a unit vector.
   * @details This function normalizes a vector by dividing its elements by the magnitude. In case the magnitude is zero, a zero vector is returned.
   * @return Normalized vector.
   */
    Vector3d normalize ();

    // Standard vectors
    /**
     * @brief Creates a 3D vector with zeros.
     * @return 3D vector with zeros.
     */
    static Vector3d zeros ()
    {
        return (Vector3d(0.0, 0.0, 0.0));
    }

    /**
     * @brief Creates a 3D vector with ones.
     * @return 3D vector with ones.
     */
    static Vector3d ones ()
    {
        return (Vector3d(1.0, 1.0, 1.0));
    }

    /**
     * @brief Return a vector with the given index as 1 and the two others as 0.
     * @param i The index to be set as 1.
     * @return The unit vector.
     */
    static Vector3d unitVector (int i)
    {
        switch (i) {
        case 0:
            return (Vector3d(1.0, 0.0, 0.0));
        case 1:
            return (Vector3d(0.0, 1.0, 0.0));
        case 2:
            return (Vector3d(0.0, 0.0, 1.0));
        default:
            return (Vector3d(0.0, 0.0, 0.0));
        }
    }

    /**
     * @brief Creates the standard Cartesian axes [100], [010], [001].
     * @return Pointer to the array containing the three axes.
     */
    static Vector3d* standardAxes ()
    {
        Vector3d *axes = new Vector3d[3];
        for (int i=0; i<3; i++) {
            axes[i] = Vector3d::unitVector(i);
        }
        return(axes);
    }


    // Operators
    // Addition
    /**
   * @brief Operator for addition of two vectors.
   * @details Adds the current vector to the provided vector and returns a third vector with the result.
   * @return Vector containing the sum of the current vector with the one provided as argument.
   */
    Vector3d operator+ (const Vector3d&) const;
    /**
   * @brief Operator for reflexive addition of two vectors.
   * @details Adds the current vector to the provided vector and populates the current vector elements with the result.
   */
    void operator+= (const Vector3d&);
    // Subtraction
    /**
   * @brief Operator for the subtraction of two vectors.
   * @details Subtracts the given vector from the current vector and returns the result in a new vector.
   * @return Vector containing the result of subtracting the vector provided as argument from the current vector.
   */
    Vector3d operator- (const Vector3d&) const;
    /**
   * @brief Operator for reflexive subtraction of two vectors.
   * @details Subtracts the given vector from the current vector and populates the current vector with the result.
   */
    void operator-= (const Vector3d&);
    // Multiplication
    /**
   * @brief Operator for scaling the vector by a scalar.
   * @details Scales the current vector by the scalar provided and returns the result in a third vector.
   * @return Vector containing the result of scaling the current vector by the scala provided as argument.
   */
    Vector3d operator* (const double&) const;
    /**
   * @brief Operator for reflexive scaling of the vector by a scalar.
   * @details Scales the current vector by the scalar provided and populates the current vector elements with the result.
   */
    void operator*= (const double&);
    /**
   * @brief Operator for the scalar product of two vectors.
   * @details Performs the scalar product or dot product of the current vector with the one provided as argument and returns the result.
   * @return Scalar value of the scalar product of dot product of the current vector with the one provided as argument.
   */
    double operator* (const Vector3d&) const;
    /**
   * @brief Operator for the vector product of two vectors.
   * @details Evaluates the vector product of the current vector with the provided vector and returns the result in a third vector.
   * @return Vector containing the result of the vector product of the current vector with the one provided as argument.
   */
    Vector3d operator^ (const Vector3d&) const;
    /**
   * @brief Operator for reflexive vector product of two vectors.
   * @details Evaluates the vector product of the current vector and the one provided, and populates the result in the current vector.
   */
    void operator^= (const Vector3d&);
};

#endif
