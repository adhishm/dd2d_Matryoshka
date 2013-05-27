/**
 * @file dislocationSource.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 27/05/2013
 * @brief Definition of the DislocationSource class.
 * @details This file defines the DislocationSource class representing a source of dislocations in the simulation. This class inherits from the Defect class. This object is basically the representation of a Frank-Read source emitting dislocation dipoles. When the dislocation source experiences a shear stress greater than a critical value for a certain amount of time (or number of iterations), it emits a dislocation dipole with a length that is a function of the applied stress.
 */

#ifndef DISLOCATIONSOURCE_H
#define DISLOCATIONSOURCE_H

#include "dislocation.h"
#include "constants.h"
#include "dislocationSourceDefaults.h"

/**
 * @brief DislocationSource class representing a source of dislocations in the simulation.
 * @details This class inherits from the Defect class. This object is basically the representation of a Frank-Read source emitting dislocation dipoles. When the dislocation source experiences a shear stress greater than a critical value for a certain amount of time (or number of iterations), it emits a dislocation dipole with a length that is a function of the applied stress. The properties of this class and the member functions will be declared here.
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
  int nIterations;
  
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
  
  /**
   * @brief Constructor that explicitly specifies all parameters.
   * @details All parameters: Burgers vector, line vector, position, are specified.
   * @param burgers Burgers vector.
   * @param line Line vector.
   * @param position Position of the dislocation source.
   * @param bm Magnitude of the Burgers vector in metres.
   * @param tau Critical shear stress value.
   * @param nIter Number of iterations of experiencing critical stress before a dipole is emitted.
   */
  DislocationSource (Vector3d burgers, Vector3d line, Vector3d position, double bm, double tau, int nIter);
  
  // Assignment functions
  /**
   * @brief Sets the Burgers vector of the dislocation.
   * @param burgers Burgers vector of the dislocation.
   */
  void setBurgers (Vector3d burgers);
  
  /**
   * @brief Sets the line vector of the dislocation.
   * @param line Line vector of the dislocation.
   */
  void setLineVector (Vector3d line);
  
  /**
   * @brief Sets the position of the dislocation source.
   * @param position The position vector giving the position of the dislocation source.
   */
  void setPosition (Vector3d position);
  
  // Access functions
  /**
   * @brief Returns the Burgers vector of the dislocations in the dipole.
   * @return The Burgers vector of the dislocations in the dipole.
   */
  Vector3d getBurgers ();
  
  /**
   * @brief Returns the line vector of the dislocations in the dipole.
   * @return The line vector of the dislocations in the dipole.
   */
  Vector3d getLineVector ();
  
  /**
   * @brief Returns the position vector of the dislocation source.
   * @return The position vector of the dislocation source.
   */
  Vector3d getPosition ();
  
  /**
   * @brief Returns the magnitude of the Burgers vector.
   * @return The magnitude of the Burgers vector.
   */
  double getBurgersMag ();
  
  /**
   * @brief Returns the critical shear stress value for dipole emission.
   * @return The critical shear stress value for dipole emission.
   */
  double getTauCritical ();
  
  // Operations specific to the class
  /**
   * @brief The nucleation length of the dipole.
   * @details When a dislocation source has experienced a shear stress greater than the critical value for a certain amount of time, it emits a dislocation dipole. In three dimensions, this is equivalent to a dislocation loop emitted by a Frank-Read source. The length of the dipole (or diameter of the loop in 3D) is such that the interaction force between the two dislocations (or line tension in 3D) balances out the applied shear stress.
   * @param tau The shear stress experienced by the dislocation source.
   * @param mu Shear modulus of the material, in Pa.
   * @param nu Poisson's ratio.
   * @return The length of the dislocation dipole.
   */
  double dipoleNucleationLength (double tau, double mu, double nu);
  
};

#endif
