/**
 * @file standardSlipSystem.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 07/06/2013
 * @brief Definition of the StandardSlipSystem class.
 * @details This file defines the StandardSlipSystem class representing a slip system in the simulation. This class will basically be used to store the various possible slip systems corresponding different crystal structures.
 */

#ifndef STANDARDSLIPSYSTEM_H
#define STANDARDSLIPSYSTEM_H

#include <vector>

#include "vector3d.h"
#include "matrix33.h"

// Defaults
/**
 * @brief Enumerated data type to define indices for the crystal structure.
 */
enum class CrystalStructure { CRYSTAL_STRUCTURE_FCC, CRYSTAL_STRUCTURE_BCC };

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
  // Constructors
  /**
   * @brief Constructor for creating the standard slip system with all the possible normals and directions, depending on the crystal structure provided.
   * @details This contructor builds an instance of the class with all valid conbinations of the slip plane normal and slip direction.
   * @param c Enumerated type representing the crystal structure. 0=FCC. 1=BCC.
   */
  StandardSlipSystem (CrystalStructure c);

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
