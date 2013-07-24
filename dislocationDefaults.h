/**
 * @file dislocationDefaults.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 26/04/2013
 * @brief Definition of certain default values for members of the Dislocation class.
 * @details This file defines some default values for members of the Dislocation class representing a dislocation in the simulation.
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


#ifndef DISLOCATIONDEFAULTS_H
#define DISLOCATIONDEFAULTS_H

/**
 * @brief Default value of the position vector x-coordinate.
 */
#define DEFAULT_POSITION_0 0.0
/**
 * @brief Default value of the position vector y-coordinate.
 */
#define DEFAULT_POSITION_1 0.0
/**
 * @brief Default value of the position vector z-coordinate.
 */
#define DEFAULT_POSITION_2 0.0

/**
 * @brief Default value of the magnitude of the Burgers vector.
 */
#define DEFAULT_BURGERS_MAGNITUDE 5.0e-09

/**
 * @brief Default value of the Burgers vector x-coordinate.
 */
#define DEFAULT_BURGERS_0 1.0
/**
 * @brief Default value of the Burgers vector y-coordinate.
 */
#define DEFAULT_BURGERS_1 1.0
/**
 * @brief Default value of the Burgers vector z-coordinate.
 */
#define DEFAULT_BURGERS_2 0.0

/**
 * @brief Default value of the line vector x-coordinate.
 */
#define DEFAULT_LINEVECTOR_0 1.0
/**
 * @brief Default value of the line vector y-coordinate.
 */
#define DEFAULT_LINEVECTOR_1 -1.0
/**
 * @brief Default value of the line vector z-coordinate.
 */
#define DEFAULT_LINEVECTOR_2 -2.0

#endif
