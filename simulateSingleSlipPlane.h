/**
 * @file simulateSingleSlipPlane.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 10/06/2013
 * @brief Declaration various functions to simulate dislocation motion on a single slip plane.
 * @details This file declares various functions to simulate dislocation motion on a single slip plane. It also writes statistics to files which will be treated separately.
 */

#ifndef SIMULATESINGLESLIPPLANE_H
#define SIMULATESINGLESLIPPLANE_H

#include <iostream>
#include <vector>
#include <string>

#include "slipPlane.h"
#include "standardSlipPlane.h"

/**
 * @brief This function manages the simulation for a single slip plane.
 * @details This function is the point of entry into a simulation with a single slip plane.
 */
void simulateSingleSlipPlane ();

#endif
