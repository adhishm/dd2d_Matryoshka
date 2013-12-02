/**
 * @file constants.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 18/07/2013
 * @brief Definition of constants used in the program.
 * @details This file defines the values of various constants used in the program.
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

#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @brief The irrational number pi.
 */
#define PI 3.141592654

/**
 * @brief The constant to convert from degrees to radians.
 */
#define DEG2RAD (PI/180.0)

/**
 * @brief The constant to convert from radians to degrees.
 */
#define RAD2DEG (180.0/PI)

/**
 * @brief The square root of 2.
 */
#define SQRT2 1.414213562

/**
 * @brief The square root of 3.
 */
#define SQRT3 1.732050808

/**
 * @brief The square root of 5.
 */
#define SQRT5 2.236067978

/**
  * @brief Tolerance value for very small numbers.
  **/
#define SMALL_NUMBER 1.0e-06

/**
  * @brief A large number.
  **/
#define LARGE_NUMBER 1.0e+03

#endif
