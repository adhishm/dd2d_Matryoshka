/**
 * @file slipPlaneDefaults.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 31/05/2013
 * @brief Definition of certain default values for members of the SlipPlane class.
 * @details This file defines some default values for members of the SlipPlane class representing a slip plane in the simulation.
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


#ifndef SLIPPLANEDEFAULTS_H
#define SLIPPLANEDEFAULTS_H

// Default values for dislocations and dislocation sources
#include "dislocationDefaults.h"
#include "dislocationSourceDefaults.h"

/**
 * @brief Default value of the position vector x-coordinate.
 */
#define DEFAULT_SLIPPLANE_POSITION_0 0.0

/**
 * @brief Default value of the position vector y-coordinate.
 */
#define DEFAULT_SLIPPLANE_POSITION_1 0.0

/**
 * @brief Default value of the position vector z-coordinate.
 */
#define DEFAULT_SLIPPLANE_POSITION_2 0.0

/**
 * @brief Default value of the normal vector x-coordinate.
 */
#define DEFAULT_SLIPPLANE_NORMALVECTOR_0 1.0

/**
 * @brief Default value of the normal vector y-coordinate.
 */
#define DEFAULT_SLIPPLANE_NORMALVECTOR_1 1.0

/**
 * @brief Default value of the normal vector z-coordinate.
 */
#define DEFAULT_SLIPPLANE_NORMALVECTOR_2 1.0

/**
 * @brief Default value of the position vector of extremity 1 x-coordinate.
 */
#define DEFAULT_SLIPPLANE_EXTREMITY1_0 5.0e-06

/**
 * @brief Default value of the position vector of extremity 1 y-coordinate.
 */
#define DEFAULT_SLIPPLANE_EXTREMITY1_1 0.0

/**
 * @brief Default value of the position vector of extremity 1 z-coordinate.
 */
#define DEFAULT_SLIPPLANE_EXTREMITY1_2 0.0

/**
 * @brief Default value of the position vector of extremity 2 x-coordinate.
 */
#define DEFAULT_SLIPPLANE_EXTREMITY2_0 0.0

/**
 * @brief Default value of the position vector of extremity 2 y-coordinate.
 */
#define DEFAULT_SLIPPLANE_EXTREMITY2_1 5.0e-6

/**
 * @brief Default value of the position vector of extremity 2 z-coordinate.
 */
#define DEFAULT_SLIPPLANE_EXTREMITY2_2 0.0

/**
 * @brief The mean number of dislocation sources per slip plane.
 * @details This number gives us the average number of dislocation sources per slip plane. It is required in order to generate a population of critical stress values with a Gaussian distribution before knowing the actual number of dislocation sources in the simulation.
 */
#define MEAN_NUM_DISLOCATION_SOURCES_PERSLIPPLANE 20

/**
 * @brief The mean number of slip planes in a slip system.
 * @details This number gives us the average number of slip planes per slip system. It is required in order to generate a population of critical stress values with a Gaussian distribution before knowing the actual number of dislocation sources in the simulation.
 */
#define MEAN_NUM_SLIPPLANES_PER_SLIPSYSTEM 10

#endif
