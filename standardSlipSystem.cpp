/**
 * @file standardSlipSystem.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 07/06/2013
 * @brief Definition of the member functions of the StandardSlipSystem class.
 * @details This file defines the member functions of the StandardSlipSystem class representing a slip system in the simulation. This class will basically be used to store the various possible slip systems corresponding different crystal structures.
 */

#include "standardSlipSystem.h"

// Constructors
/**
 * @brief Constructor for creating the standard slip system with all the possible normals and directions, depending on the crystal structure provided.
 * @details This contructor builds an instance of the class with all valid conbinations of the slip plane normal and slip direction.
 * @param c Enumerated type representing the crystal structure. 0=FCC. 1=BCC.
 */
StandardSlipSystem::StandardSlipSystem (CrystalStructure c)
{
  switch (c)
    {
    case CrystalStructure::CRYSTAL_STRUCTURE_FCC:
      this->createFCCSlipSystems ();
      break;
      
    case CrystalStructure::CRYSTAL_STRUCTURE_BCC:
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
  Vector3d d (1.0. 1.0. 1.0);  // Slip direction

  this->createSlipSystems (n, d);
}

/**
 * @brief Creates the possible slip systems using the normal and slip directions provided.
 * @param n Slip plane normal vector.
 * @param d Slip direction.
 */
void StandardSlipSystem::createSlipSystems (Vector3d n, Vector3d d)
{
  std::vector<Vector3d> normals    = n.permute ();
  std::vector<Vector3d> directions = d.permute ();

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
