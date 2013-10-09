/**
 * @file simulateSingleSlipPlane.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 10/06/2013
 * @brief Declaration various functions to simulate dislocation motion on a single slip plane.
 * @details This file declares various functions to simulate dislocation motion on a single slip plane. It also writes statistics to files which will be treated separately.
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


#ifndef SIMULATESINGLESLIPPLANE_H
#define SIMULATESINGLESLIPPLANE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "slipPlane.h"
#include "standardSlipSystem.h"
#include "parameter.h"
#include "tools.h"
#include "readFromFile.h"

/**
 * @brief This function manages the simulation for a single slip plane.
 * @details This function is the point of entry into a simulation with a single slip plane.
 */
void simulateSingleSlipPlane ();



/**
 * @brief Carry out the iterations for the simulation of dislocation motion on a single slip plane.
 * @param param Pointer to the instance of the Parameter class containing all simulation parameters.
 * @param slipPlane Pointer to the instance of the SlipPlane class containing the data for the dislocation structure.
 * @param currentTime The value of time at the beginning of the simulation.
 */
void singleSlipPlane_iterate (Parameter *param, SlipPlane *slipPlane, double currentTime);

#endif
