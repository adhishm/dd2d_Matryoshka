/**
 * @file tools.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 10/09/2013
 * @brief Declaration various tools.
 * @details This file declares various tools that may come in handy.
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


#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>

#include <vector>
#include <iterator>
#include <string>
#include <sstream>

// GNU Scientific Library files
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "vector3d.h"
#include "constants.h"
#include "matrix33.h"
#include "stress.h"
#include "strain.h"

/**
 * @brief Creates all possible permutations of vectors having the same elements.
 * @details This function returns a vector container with all possible permutations of the present vector. This is useful in creating a list of equivalent vectors when the Miller indices of one are provided. For example, if the current vector is [1 1 0], the return vector container would contain the vectors [1 1 0], [1 0 1], [0 1 1], [-1 1 0], etc.
 * @param v The Vector3d variable that has to be permuted.
 * @return STL vector container with Vector3d variables created from permutations of the present vector elements.
 */
std::vector<Vector3d> permuteVector (Vector3d v);

/**
 * @brief The vector is permuted keeping the index position constant.
 * @details This function permutes the given vector v keeping the element from the index position first. For example, if the vector is [a b c], and the index is 0, the permutations will contain [a b c], [-a b c], [a -b c], [a b -c], [a c b], [-a c b], [a -c b], [a c -b]. The permutations with sign changes are carried out by the function std::vector<Vector3d> permuteVector_signs (Vector3d v).
 * @param v The vector that has to be permuted.
 * @param index The index of the element of the vector v that must remain in position.
 * @return An STL vector container with the list of the permuted vectors keeping the indicated element in its original position.
 */
std::vector<Vector3d> permuteVector_byIndex (Vector3d v, int index);

/**
 * @brief Permutations of the given vector by only changing signs of the elements.
 * @details This function permutes the vector by only changing the signs but not the positions the elements. For example, if the vector is [a b c], the permutations will contain [a b c], [-a b c], [a -b c], [a b -c].
 * @param v The vector that has to be permuted.
 * @return An STL vector container with the permuted vectors.
 */
std::vector<Vector3d> permuteVector_bySign (Vector3d v);

/**
 * @brief Concatenates two STL vectors containing elements of type Vector3d.
 * @param v1 First vector.
 * @param v2 Secone vector.
 * @return Concatenated vector.
 */
std::vector<Vector3d> concatenateVectors (std::vector<Vector3d> v1, std::vector<Vector3d> v2);

/**
 * @brief Eliminates the duplicate vectors from the given STL vector.
 * @details This function eliminates duplicate vectors from the STL vector provided as argument and returns the result. The argument negatives is a flag to indicate if the negative of a vector is to be considered as its duplicate or not.
 * @param v The vector from which duplicates are to be removed.
 * @param negatives Flag to indicate if the negative of a vector should be considered as its duplicate or not.
 * @return The vector without duplicates.
 */
std::vector<Vector3d> eliminateDuplicatesFromVector (std::vector<Vector3d> v, bool negatives);

/**
 * @brief Checks if the input line is to be ignored or not.
 * @details A line in an input file may be empty or may be a comment. In these cases it should be ignored. This function tests if the given line is empty or begins with the character that indicates that it is a comment (default is #).
 * @param line The line that is to be tested.
 * @param comment The character that indicates a comment, default value is #.
 * @return A boolean flag saying if the line should be ignored or not.
 */
bool ignoreLine (std::string line, char comment = '#');

/**
 * @brief Displays the message on screen.
 * @param message An std""string containing the message to be displayed.
 */
void displayMessage (std::string message);

/**
 * @brief Converts an integer to an std::string.
 * @details This function uses ostringstream to convert an integer to a string.
 * @param i The integer to be converted to a string.
 * @return The integer converted to a string.
 */
std::string intToString (int i);

/**
 * @brief Converts an double to an std::string.
 * @details This function uses ostringstream to convert an double to a string.
 * @param i The double to be converted to a string.
 * @return The double converted to a string.
 */
std::string doubleToString (double i);

/**
 * @brief SGN function to return the sign of a number.
 * @param v The value whose sign is to be found.
 * @return The sign of the value (-1, 0, 1).
 */
template <typename T> int sgn(T v)
{
    return ( (T(0) < v) - (v < T(0)) );
}

/**
 * @brief Function to get a vector container filled with a Gaussian distribution of doubles with the given mean and standard deviation.
 * @param n Number of doubles required.
 * @param mean The mean value of the Gaussian distribution.
 * @param stdev The standard deviation of the Gaussian distribution.
 * @return Vector container with the doubles in a Gaussian distribution with the required mean and standard deviation.
 */
std::vector<double> rng_Gaussian (int n, double mean, double stdev);

/**
 * @brief Finds the arithmetic mean of values given as a vector. The addition operator must be defined, as well as the division by a scalar.
 * @param p STL vector container with the values whose mean is to be found.
 * @return The mean of the values provided in p.
 */
template <typename T> T mean (std::vector<T> p)
{
    T m;
    int n = p.size();
    if (n != 0) {
        for (int i=0; i<n; i++) {
            m += p.at(i);
        }
        m *= (1.0/n);
    }
    return (m);
}

/**
 * @brief Function to check for the intersection between a line parallel to the vector V, passing through the point R, with the line joining P and Q.
 * @details Description of the method: The intersection point S is given by the parametric forms of the line equations. For the line passing through R and parallel to V, S = R + uV, - infinity < u < + infinity. For the line passing through P and Q, S = P + t(Q-P), 0 <= t <= 1. Therefore we need to solve the equations R + uV = P + t(Q-P), for t and u. Since all the vector quantities are known, the equation may be simplified to uV = A + tB, where A = P-R, B = Q-P. Performing a cross product with V on both sides, we have 0 = (AxV) + t(BxV). If the solutions for t from all three possible pairs of equations are the same, it proves the coplanarity of the points P, Q, R and the vector V. If t is bounded between 0 and 1, then the intersection lies between P and Q, else it is outside. If it is bounded, we calculate the position S = P + tB.
 * @param R Position vector of the point through which the line passes.
 * @param V Vector to which the line is parallel.
 * @param P Position vector of the first point.
 * @param Q Position vector of the second point.
 * @param S Pointer to the Vector3d instance that will contain the intersection point, if there is one. The memory must be pre-allocated.
 * @return Boolean flag indicating if the lines intersect (true) or not (false).
 */
bool intersection (Vector3d R, Vector3d V, Vector3d P, Vector3d Q, Vector3d* S);

#endif
