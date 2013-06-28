/**
 * @file standardSlipSystem.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 07/06/2013
 * @brief Definition of the member functions of the StandardSlipSystem class.
 * @details This file defines the member functions of the StandardSlipSystem class representing a slip system in the simulation. This class will basically be used to store the various possible slip systems corresponding different crystal structures.
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


#include "standardSlipSystem.h"

// Constructors
/**
 * @brief Constructor for creating the standard slip system with all the possible normals and directions, depending on the crystal structure provided.
 * @details This contructor builds an instance of the class with all valid conbinations of the slip plane normal and slip direction.
 * @param c Enumerated type representing the crystal structure. 0=FCC. 1=BCC.
 */
StandardSlipSystem::StandardSlipSystem (StandardSlipSystem::CrystalStructure c)
{
  switch (c)
  {
  case StandardSlipSystem::CrystalStructure::CRYSTAL_STRUCTURE_FCC:
      this->createFCCSlipSystems ();
      break;

  case StandardSlipSystem::CrystalStructure::CRYSTAL_STRUCTURE_BCC:
      this->createBCCSlipSystems ();
      break;

  default:
      this->createFCCSlipSystems ();
      break;
  }
}

// Assignment functions
/**
 * @brief Creates the 12 possible FCC slip systems.
 */
void StandardSlipSystem::createFCCSlipSystems ()
{
  Vector3d n (1.0, 1.0, 1.0);  // Normal vector
  Vector3d d (1.0, 1.0, 0.0);  // Slip direction

  this->createSlipSystems (n, d);
}

/**
 * @brief Creates the 48 possible BCC slip systems.
 */
void StandardSlipSystem::createBCCSlipSystems ()
{
  Vector3d n (1.0, 1.0, 0.0);  // Normal vector
  Vector3d d (1.0, 1.0, 1.0);  // Slip direction

  this->createSlipSystems (n, d);
}

/**
 * @brief Creates the possible slip systems using the normal and slip directions provided.
 * @param n Slip plane normal vector.
 * @param d Slip direction.
 */
void StandardSlipSystem::createSlipSystems (Vector3d n, Vector3d d)
{
  std::vector<Vector3d> normals    = permuteVector (n);
  std::vector<Vector3d> directions = permuteVector (d);

  std::vector<Vector3d>::iterator ni; // Iterator for normals
  std::vector<Vector3d>::iterator di; // Iterator for directions

  double dotProduct;

  ni = normals.begin ();

  this->nSlipSystems = 0;

  while (ni != normals.end())
    {
      di = directions.begin();
      while (di != directions.end())
	{
	  dotProduct = (*ni) * (*di);
	  if ( 0.0 == dotProduct)
	    {
	      this->nSlipSystems ++;
	      this->slipPlaneNormalVector.push_back (*ni);
	      this->slipDirection.push_back (*di);
	    }
	  di++;
	}
      ni++;
    }
}
