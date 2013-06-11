/**
 * @file slipPlaneDefaults.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 31/05/2013
 * @brief Definition of certain default values for members of the SlipPlane class.
 * @details This file defines some default values for members of the SlipPlane class representing a slip plane in the simulation.
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

#endif
