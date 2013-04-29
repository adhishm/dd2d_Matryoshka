/**
 * @file dislocation.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 29/04/2013
 * @brief Definition of the Dislocation class.
 * @details This file defines the Dislocation class representing a dislocation in the simulation. This class inherits from the Defect class.
 */

#ifndef DISLOCATION_H
#define DISLOCATION_H

#include "defect.h"
#include "dislocationDefaults.h"
#include "constants.h"

/**
 * @brief Dislocation class representing a dislocation in the simulation.
 * @details The Dislocation class represents a dislocation in the simulation. The class inherits from the Defect class. A dislocation has several properties like a Burgers vector, line vector, etc. which will all be declared here.
 */
class Dislocation : public Defect
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
  
public:
  // Constructors
  /**
   * @brief Default constructor.
   * @details Initializes the dislocation with the following default parameters:
   * Position: (0.0, 0.0, 0.0)
   * Burgers vector: Default value set in defaults file.
   * Line vector: Default value set in defaults file.
   * Burgers vector magnitude: Default value set in teh defaults file.
   * Mobile: true.
   */
  Dislocation ();
  /**
   * @brief Constructor that explicitly specifies all parameters.
   * @details All parameters: Burgers vector, line vector, position, are specified.
   * @param burgers Burgers vector.
   * @param line Line vector.
   * @param position Position of the dislocation.
   * @param bm Magnitude of the Burgers vector in metres.
   * @param m Mobility (true/false).
   */
  Dislocation (Vector3d burgers, Vector3d line, Vector3d position, double bm, bool m);
  
  // Assignment functions
  /**
   * @brief Sets the Burgers vector of the dislocation.
   */
  void setBurgers (Vector3d burgers);
  /**
   * @brief Sets the line vector of the dislocation.
   */
  void setLineVector (Vector3d line);
  /**
   * @brief Sets the dislocation as mobile.
   * @details Sets the flag mobile to true.
   */
  void setMobile ();
  /**
   * @brief Sets the dislocation as pinned.
   * @details Sets the flag mobile to false.
   */
  void setPinned ();
  
  // Access functions
  /**
   * @brief Gets the Burgers vector of the dislocation.
   * @return Burgers vector in a variable of type Vector3d.
   */
  Vector3d getBurgers ();
  /**
   * @brief Gets the line vector of the dislocation.
   * @return Line vector in a variable of type Vector3d.
   */
  Vector3d getLineVector ();
  
  // Rotation matrix
  /**
   * @brief Calculate the roation matrix.
   * @details This function calculates the rotation matrix for this dislocation using the global and local co-ordinate systems. The matrix rotationMatrix is for rotation from the old (unprimed, global) to the new (primed, dislocation) system.
   */
  void calculateRotationMatrix ();
  
  // Stress field
  /**
   * @brief Calculates the stress field due to this dislocation at the position given as argument.
   * @details The stress field of the dislocation is calculated at the position indicated by the argument.
   * @param p Position vector of the point where the stress field is to be calculated.
   * @param mu Shear modulus in Pascals.
   * @param nu Poisson's ratio.
   * @return Stress tensor, expressed in the global co-ordinate system, giving the value of the stress field at position p.
   */
  Stress stressField (Vector3d p, double mu, double nu);
  
  /**
   * @brief Calculates the stress field doe to the dislocation in the local co-ordinate system.
   * @details The stress field due to the dislocation is calculated at the position indicated by the argument. The stress tensor is expressed in the dislocation's local co-ordinate system.
   * @param p Position vector of the point where the stress field is to be calculated. This position vector is calculated in the local co-ordinate system, taking the dislocation as the origin.
   * @param mu Shear modulus in Pascals.
   * @param nu Poisson's ratio.
   * @return Stress tensor, expressed in the dislocation's local co-ordinate system.
   */
  Stress stressFieldLocal (Vector3d p, double mu, double nu);
  
};

#endif
