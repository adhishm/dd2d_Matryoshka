/**
 * @file dislocationSource.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 05/06/2013
 * @brief Definition of the DislocationSource class.
 * @details This file defines the DislocationSource class representing a source of dislocations in the simulation. This class inherits from the Defect class. This object is basically the representation of a Frank-Read source emitting dislocation dipoles. When the dislocation source experiences a shear stress greater than a critical value for a certain amount of time (or number of iterations), it emits a dislocation dipole with a length that is a function of the applied stress.
 */

#ifndef DISLOCATIONSOURCE_H
#define DISLOCATIONSOURCE_H

#include "dislocation.h"
#include "constants.h"
#include "dislocationDefaults.h"
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
  
  /**
   * @brief Counter variable for the number of consecutive iterations the dislocation source has experienced a shear stress greater than its critical value.
   * @details A dislocation source needs to experience a shear stress higher than a critical value, given by tauCritical, for a certain amount of time before it is triggered and it emits a dislocation dipole. This limiting number of iterations is given by the variable nIterations, and this variable countIterations is a counter variable. Once this limit is reached, a dipole is emitted and this counter variable is set to zero.
   */
  int countIterations;
  
public:
  // Constructors
  /**
   * @brief Default constructor.
   * @details Initializes the dislocation with the default parameters provided in the files dislocationDefaults.h and dislocationSourceDefaults.h.
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
   * @brief Set the magnitude of the Burgers vector.
   * @param bm Magnitude of the Burgers vector.
   */
  void setBurgersMagnitude (double bm);
  
  /**
   * @brief Set the critical shear stres for dipole emission.
   * @param tauC Critical shear stress for dipole emission.
   */
  void setTauCritical (double tauC);
  
  /**
   * @brief Set the number of iterations before a dipole is emitted.
   * @param nIter Number of iterations spent at a high shear stress value before a dislocation dipole is emitted.
   */
  void setNumIterations (int nIter);
  
  /**
   * @brief Sets the iteration counter to zero.
   */
  void resetIterationCounter ();
  
  // Access functions
  /**
   * @brief Returns the Burgers vector of the dislocations in the dipole.
   * @return The Burgers vector of the dislocations in the dipole.
   */
  Vector3d getBurgers () const;
  
  /**
   * @brief Returns the line vector of the dislocations in the dipole.
   * @return The line vector of the dislocations in the dipole.
   */
  Vector3d getLineVector () const;
  
  /**
   * @brief Returns the magnitude of the Burgers vector.
   * @return The magnitude of the Burgers vector.
   */
  double getBurgersMag () const;
  
  /**
   * @brief Returns the critical shear stress value for dipole emission.
   * @return The critical shear stress value for dipole emission.
   */
  double getTauCritical () const;
  
  /**
   * @brief Returns the number if iterations that the dislocation source must spend experiencing a shear stress greater than the critical value before it can emit a dislocation dipole.
   * @return The number if iterations that the dislocation source must spend experiencing a shear stress greater than the critical value before it can emit a dislocation dipole.
   */
  int getNumIterations () const;
  
  /**
   * @brief Get the count of the iterations spent at higher than critical shear stress.
   * @return Number of iterations spent at higher than critical shear stress.
   */
  int getIterationCount () const;
  
  // Operations specific to the class
  /**
   * @brief The nucleation length of the dipole.
   * @details When a dislocation source has experienced a shear stress greater than the critical value for a certain amount of time, it emits a dislocation dipole. In three dimensions, this is equivalent to a dislocation loop emitted by a Frank-Read source. The length of the dipole (or diameter of the loop in 3D) is such that the interaction force between the two dislocations (or line tension in 3D) balances out the applied shear stress.
   * @param tau The shear stress experienced by the dislocation source.
   * @param mu Shear modulus of the material, in Pa.
   * @param nu Poisson's ratio.
   * @return The length of the dislocation dipole.
   */
  double dipoleNucleationLength (double tau, double mu, double nu) const;
  
  /**
   * @brief Increments the variable countIterations by 1.
   */
  void incrementIterationCount ();
  
  /**
   * @brief Checks if the dislocation source has experienced higher than critical shear stress for long enough to emit a dipole.
   * @details The number of iterations for which the dislocation source must experience a shear stress higher than the critical value is given in the member nIterations. When the counter variable countIterations reaches this value, the source is ready to emit a dipole, so a true value is returned. In other cases, false is returned.
   * @return The boolean result of whether the count of iterations is greater than the limiting number of iterations provided at input.
   */
  bool ifEmitDipole () const;
};

#endif
