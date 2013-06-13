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
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "slipPlane.h"
#include "standardSlipPlane.h"
#include "parameter.h"

/**
 * @brief This function manages the simulation for a single slip plane.
 * @details This function is the point of entry into a simulation with a single slip plane.
 */
void simulateSingleSlipPlane ();

/**
 * @brief Reads the slip plane details from the file.
 * @details The details of the slip plane and its dislocations are stored in a file the name of which is provided. This file is read and the information is saved into the instance of the SlipPlane class, the pointer to which is given.
 * @param fileName String containing the name of the file.
 * @param s Pointer to the instance of SlipPlane into which all data is to be stored.
 * @return Flag indicating the success or failure of the operation.
 */
bool readSlipPlane (std::string fileName, SlipPlane *s);

/**
 * @brief Reads 3 values from a string and returns them in a Vector3d.
 * @param s The string that is to be read from.
 * @return Vector3d object containing the 3 values read.
 */
Vector3d readVectorFromLine (std::string s);

/**
 * @brief Reads the data from a line and builds a dislocation from it.
 * @param s The string that is to be read from.
 * @return The dislocation.
 */
Dislocation readDislocationFromLine (std::string s);

/**
 * @brief Reads the data from a line and builds a dislocation source from it.
 * @param s The string that is to be read from.
 * @return The dislocation source.
 */
DislocationSource readDislocationSourceFromLine (std::string s);

#endif
