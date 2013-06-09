/**
 * @file tools.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 09/06/2013
 * @brief Declaration various tools.
 * @details This file declares various tools that may come in handy.
 */

#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <iterator>

#include "vector3d.h"

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
std::vector<Vector3d> permuteVector_abc (Vector3d v, int index);

/**
 * @brief Permutations of the given vector by only changing signs of the elements.
 * @details This function permutes the vector by only changing the signs but not the positions the elements. For example, if the vector is [a b c], the permutations will contain [a b c], [-a b c], [a -b c], [a b -c].
 * @param v The vector that has to be permuted.
 * @return An STL vector container with the permuted vectors.
 */
std::vector<Vector3d> permuteVector_signs (Vector3d v);

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

#endif
