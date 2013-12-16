/**
 * @file simulatePolycrystal.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 16/12/2013
 * @brief Declaration various functions to simulate dislocation motion within a polycrystal.
 * @details This file declares various functions to simulate dislocation motion within a polycrystal.
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

#ifndef SIMULATEPOLYCRYSTAL_H
#define SIMULATEPOLYCRYSTAL_H

#include <iostream>

#include "polycrystal.h"
#include "readFromFile.h"

/**
 * @brief This function manages the simulation of dislocation motion in a polycrystal. It is the point of entry into the simulation.
 */
void simulateSinglePolycrystal ();

/**
 * @brief This is an overloaded function. This function manages the simulation of dislocation motion in a polycrystal. It is the point of entry into the simulation.
 * @param fileName String containing the name of the parameters file.
 */
void simulateSinglePolycrystal(std::string fileName);

/**
 * @brief This function handles the iterations in the simulation of dislocation motion in a single polycrystal.
 * @param param Pointer to the instance of the Parameter class containing the simulation parameters.
 * @param polycrystal Pointer to the instance of the Polycrystal class containing all data for the polycrystal.
 * @param currentTime The value of the current simulation time.
 */
void polycrystal_iterate (Parameter* param, Polycrystal* polycrystal, double currentTime);

#endif // SIMULATEPOLYCRYSTAL_H
