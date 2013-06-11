/**
 * @file simulateSingleSlipPlane.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 10/06/2013
 * @brief Defintion various functions to simulate dislocation motion on a single slip plane.
 * @details This file defines various functions to simulate dislocation motion on a single slip plane. It also writes statistics to files which will be treated separately.
 */

#include "simulateSingleSlipPlane.h"

/**
 * @brief This function manages the simulation for a single slip plane.
 * @details This function is the point of entry into a simulation with a single slip plane.
 */
void simulateSingleSlipPlane ()
{
  std::string fName;

  std::cout << "Parameter file name: ";
  std::cin >> fName;
