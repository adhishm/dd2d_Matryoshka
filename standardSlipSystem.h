/**
 * @file standardSlipSystem.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 07/06/2013
 * @brief Definition of the StandardSlipSystem class.
 * @details This file defines the StandardSlipSystem class representing a slip system in the simulation. This class will basically be used to store the various possible slip systems corresponding different crystal structures.
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


#ifndef STANDARDSLIPSYSTEM_H
#define STANDARDSLIPSYSTEM_H

#include <vector>

#include "vector3d.h"
#include "matrix33.h"
#include "tools.h"

/**
 * @brief Definition of the StandardSlipSystem class.
 * @details This class contains the basic components of a slip system: the normal to the slip plane and the slip direction. Instances of this class will be the variables that will provide the slip planes and directions to other slip systems depending on the crystal structure.
 */
class StandardSlipSystem
{
 private:
  /**
   * @brief The normal vectors of the slip planes in this slip system.
   * @details These vectors are the normals to the slip planes. In cubic crystal systems (BCC, FCC), the Miller indices of the slip plane are identical to those of its normal vector. The vectors should be normalized so that they are always unit vectors.
   */
  std::vector<Vector3d> slipPlaneNormalVector;
  
  /**
   * @brief The vectors indicating the slip direction.
   * @details These vectors represent the direction of slip on the plane corresponding to its position in the list of slip planes. These vectors should be normalized so that they are always unit vectors.
   */
  std::vector<Vector3d> slipDirection;

  /**
   * @brief Number of slip systems.
   */
  int nSlipSystems;
  
 public:
  // Defaults
  /**
   * @brief Enumerated data type to define indices for the crystal structure.
   */
  enum class CrystalStructure {
      CRYSTAL_STRUCTURE_FCC = 0,
      CRYSTAL_STRUCTURE_BCC
    };
  // Constructors
  /**
   * @brief Constructor for creating the standard slip system with all the possible normals and directions, depending on the crystal structure provided.
   * @details This contructor builds an instance of the class with all valid conbinations of the slip plane normal and slip direction.
   * @param c Enumerated type representing the crystal structure. 0=FCC. 1=BCC.
   */
  StandardSlipSystem (StandardSlipSystem::CrystalStructure c);

  // Assignment functions
  /**
   * @brief Creates the 12 possible FCC slip systems.
   */  
  void createFCCSlipSystems ();
  
  /**
   * @brief Creates the 48 possible BCC slip systems.
   */
  void createBCCSlipSystems ();

  /**
   * @brief Creates the possible slip systems using the normal and slip directions provided.
   * @param n Slip plane normal vector.
   * @param d Slip direction.
   */
  void createSlipSystems (Vector3d n, Vector3d d);
  
  // Access functions
};

#endif
