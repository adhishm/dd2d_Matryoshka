/**
 * @file readFromFile.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 10/10/2013
 * @brief Declaration various functions to read data from files.
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

#ifndef READFROMFILE_H
#define READFROMFILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "grain.h"
#include "slipsystem.h"
#include "slipPlane.h"
#include "dislocation.h"
#include "dislocationSource.h"
#include "defect.h"

#include "parameter.h"
#include "tools.h"

/**
 * @brief Reads the slip plane details from the file.
 * @details The details of the slip plane and its dislocations are stored in a file the name of which is provided. This file is read and the information is saved into the instance of the SlipPlane class, the pointer to which is given.
 * @param fileName String containing the name of the file.
 * @param s Pointer to the instance of SlipPlane into which all data is to be stored.
 * @param currentTime Pointer to the variable storing the initial time.
 * @param param Pointer to the Parameter class object containing the simulation parameters.
 * @return Flag indicating the success or failure of the operation.
 */
bool readSlipPlane (std::string fileName, SlipPlane *s, double *currentTime, Parameter *param);

/**
 * @brief Read the slip system from file.
 * @param fileName Name of the file containing the data of the slip system.
 * @param s Pointer to the instance of the SlipSystem class that will contain the data. Memory for this instance should be pre-allocated.
 * @param currentTime Pointer to the variable holding the present time. Memory for this varibale should be pre-allocated.
 * @param param Pointer to the instance of the Parameter class, containing the parameters for the simulation.
 * @return Boolean flag indicating success or failure of the reading operation.
 */
bool readSlipSystem (std::string fileName, SlipSystem *s, double *currentTime, Parameter *param);

/**
 * @brief Read the grain from file.
 * @param fileName Name of the file containing the data of the grain.
 * @param g Pointer to the instance of the Grain class that will contain the data. Memory for this instance should be pre-allocated.
 * @param currentTime Pointer to the variable holding the present time. Memory for this varibale should be pre-allocated.
 * @param param Pointer to the instance of the Parameter class, containing the parameters for the simulation.
 * @return Boolean flag indicating success or failure of the reading operation.
 */
bool readGrain (std::string fileName, Grain *g, double *currentTime, Parameter *param);

/**
 * @brief Reads 3 values from a string and returns them in a Vector3d.
 * @param s The string that is to be read from.
 * @return Vector3d object containing the 3 values read.
 */
Vector3d readVectorFromLine (std::string s);

/**
 * @brief Read integers from a line.
 * @param s The string containing the line.
 * @param n Pointer to the integer in which we will store the number of integers read from the line.
 * @return Pointer to the memory location where the integers are stored.
 */
int* readIntegersFromLine (std::string s, int* n);

/**
 * @brief Reads the data from a line and builds a dislocation from it.
 * @param s The string that is to be read from.
 * @return Pointer to the dislocation.
 */
Dislocation* readDislocationFromLine (std::string s);

/**
 * @brief Reads the data from a line and builds a dislocation source from it.
 * @param s The string that is to be read from.
 * @return Pointer to the dislocation source.
 */
DislocationSource* readDislocationSourceFromLine (std::string s);

#endif // READFROMFILE_H
