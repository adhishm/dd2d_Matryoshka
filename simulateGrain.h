/**
 * @file simulateGrain.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 26/11/2013
 * @brief Declaration various functions to simulate dislocation motion within a single grain.
 * @details This file declares various functions to simulate dislocation motion within a single grain.
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

#ifndef SIMULATEGRAIN_H
#define SIMULATEGRAIN_H

#include <iostream>

#include "grain.h"
#include "readFromFile.h"

/**
 * @brief This function manages the simulation of dislocation motion in a single grain. It is the point of entry into the simulation.
 */
void simulateSingleGrain ();

/**
 * @brief This function handles the iterations in the simulation of dislocation motion in a single grain.
 * @param param Pointer to the instance of the Parameter class containing the simulation parameters.
 * @param grain Pointer to the instance of the Grain class containing all data for the grain.
 * @param currentTime The value of the current simulation time.
 */
void grain_iterate (Parameter* param, Grain* grain, double currentTime);

#endif // SIMULATEGRAIN_H
