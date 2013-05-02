/**
 * @file dislocationSource.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 02/05/2013
 * @brief Definition of the DislocationSource class.
 * @details This file defines the DislocationSource class representing a source of dislocations in the simulation. This class inherits from the Defect class. This object is basically the representation of a Frank-Read source emitting dislocation dipoles.
 */

#ifndef DISLOCATIONSOURCE_H
#define DISLOCATIONSOURCE_H

#include "dislocation.h"
#include "constants.h"

/**
 * @brief DislocationSource class representing a source of dislocations in the simulation.
 * @details This class inherits from the Defect class. This object is basically the representation of a Frank-Read source emitting dislocation dipoles. The properties of this class and the member functions will be declared here.
 */
class DislocationSource : public Defect
{
protected:
  /**
   * @brief Burgers vector of the dislocation.
   */
  Vector3d bvec;
  
  /**
   * @brief Line vector if the dislocation.
   */
  Vector3d lvec;
  
  /**
   * @brief Boolean term indicating mobility.
   * @details For mobile dislocations this term is true and for pinned dislocations it is false.
   */
  bool mobile;
  
  /**
   * @brief Magnitude of the Burgers vector in metres.
   * @details The magnitude of the Burgers vector is useful for several calculations such as stress field around the dislocation.
   */
  double bmag;
  
  /**
   * @brief The rotation matrix for rotating from the global to the local co-ordinate system and vice-versa.
   * @details This is the rotation matrix that represents the relationship between the global and local co-ordinate systems. It is used to convert tensors and vectors between the two systems. The rotation matrix needs to be calculated once and may be refreshed periodically if lattice rotation is implemented. In the absence of lattice rotation, the matrix will remain invariant.
   */
  RotationMatrix rotationMatrix;
  
  /**
   * @brief Critical stress for the emission of a dislocation dipole.
   * @details A dislocation dipole source needs to experience a certain critical level of shear stress for a certain amount of time before it can emit a dipole. This critical stress is given by tauCritical.
   */
  double tauCritical;
  
  /**
   * @brief Number of iterations before a dipole is emitted.
   * @details A dislocation dipole source needs to experience a certain critical level of shear stress for a certain amount of time before it can emit a dipole. The amount of time is represented instead by a number of iterations nIterations.
   */
  double nIterations;
  
public:
  // Constructors
  /**
   * @brief Default constructor.
   * @details Initializes the dislocation with the following default parameters:
   * Position: (0.0, 0.0, 0.0)
   * Burgers vector: Default value set in defaults file.
   * Line vector: Default value set in defaults file.
   * Burgers vector magnitude: Default value set in the defaults file.
   * Tau critical: Default value set in the defaults file.
   * nIterations: Default value set in the defaults file.
   */
  DislocationSource ();
};

#endif
