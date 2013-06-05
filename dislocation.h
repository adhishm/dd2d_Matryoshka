/**
 * @file dislocation.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 04/06/2013
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
   * Burgers vector magnitude: Default value set in the defaults file.
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
   * @param burgers Bergers vector of the dislocation.
   */
  void setBurgers (Vector3d burgers);
  /**
   * @brief Sets the line vector of the dislocation.
   * @param line Line vector of the dislocation.
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
  Vector3d getBurgers () const;
  /**
   * @brief Gets the line vector of the dislocation.
   * @return Line vector in a variable of type Vector3d.
   */
  Vector3d getLineVector () const;
  /**
   * @brief Returns whether the dislocation is mobile or pinned.
   * @return Returns true if the dislocation is mobile, false if pinned.
   */
  bool isMobile () const;
  
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
   * @brief Calculates the stress field due to the dislocation in the local co-ordinate system.
   * @details The stress field due to the dislocation is calculated at the position indicated by the argument. The stress tensor is expressed in the dislocation's local co-ordinate system.
   * @param p Position vector of the point where the stress field is to be calculated. This position vector is calculated in the local co-ordinate system, taking the dislocation as the origin.
   * @param mu Shear modulus in Pascals.
   * @param nu Poisson's ratio.
   * @return Stress tensor, expressed in the dislocation's local co-ordinate system.
   */
  Stress stressFieldLocal (Vector3d p, double mu, double nu) const;
  
  // Force
  /**
   * @brief Calculate the Peach-Koehler force acting on the dislocation due the stress.
   * @details This function calculates the Peach-Koehler force in the dislocation due to the stress (expressed in the global co-ordinate system) provided as argument. The force returned is also in the global co-ordinate system. This function checks if the xy component of the stress tensorm expressed in the dislocation's local co-ordinate system, is greater than tau_crss. If it is, the force is calculated using the Peach-Koehler equation, otherwise, the force on the dislocation is zero.
   * @param sigma The stress tensor, expressed in the global co-ordinate system.
   * @param tau_crss Critical Resolved Shear Stress in Pa.
   * @return The Peach-Koehler force on the dislocation, expressed in the global co-ordinate system.
   */
  Vector3d forcePeachKoehler (Stress sigma, double tau_crss) const;

/**
 * @brief Returns the ideal time increment for the dislocation.
 * @details A dislocation is not allowed to approach another defect beyond a certain distance, specified by the argument minDistance. This function calculates the ideal time increment for this dislocation to not collide with the defect.
 * @param v0 Velocity of the dislocation.
 * @param minDistance Minimum distance of approach to the defect.
 * @param d The defect for which the present dislocation's time increment is to be calculated.
 * @param v1 Velocity of the other defect.
 * @return The ideal time increment for this dislocation.
 */
double idealTimeIncrement (Vector3d v0, double minDistance, Defect d, Vector3d v1);
};

#endif
