/**
 * @file simulateSingleSlipSystem.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 10/10/2013
 * @brief Declaration various functions to simulate dislocation motion on a single slip system.
 * @details This file declares various functions to simulate dislocation motion on a single slip system.
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

#ifndef SIMULATESLINGLESLIPSYSTEM_H
#define SIMULATESLINGLESLIPSYSTEM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "slipsystem.h"
#include "parameter.h"
#include "tools.h"

/**
 * @brief This function is the point of entry for simulating a single slip system.
 * @details This function handles the simulation of a single slip system, from reading input files, to calling managing the iterations.
 */
void simulateSingleSlipSystem ();

/**
 * @brief Read the slip system from file.
 * @param fileName Name of the file containing the data of the slip system.
 * @param s Pointer to the instance of the SlipSystem class that will contain the data. Memory for this instance should be pre-allocated.
 * @param currentTime Pointer to the variable holding the present time. Memory for this varibale should be pre-allocated.
 * @param param Pointer to the instance of the Parameter class, containing the parameters for the simulation.
 * @return Boolean flag indicating success or failure of the reading operation.
 */
bool readSlipSystem (std::string fileName, SlipSystem *s, double *currentTime, Parameter *param);

#endif // SIMULATESLINGLESLIPSYSTEM_H
