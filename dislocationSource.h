/**
 * @file dislocationSource.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 05/06/2013
 * @brief Definition of the DislocationSource class.
 * @details This file defines the DislocationSource class representing a source of dislocations in the simulation. This class inherits from the Defect class. This object is basically the representation of a Frank-Read source emitting dislocation dipoles. When the dislocation source experiences a shear stress greater than a critical value for a certain amount of time (or number of iterations), it emits a dislocation dipole with a length that is a function of the applied stress.
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
   * @brief Critical stress for the emission of a dislocation dipole.
   * @details A dislocation dipole source needs to experience a certain critical level of shear stress for a certain amount of time before it can emit a dipole. This critical stress is given by tauCritical.
   */
  double tauCritical;
  
  /**
   * @brief Amount of time before a dipole is emitted.
   * @details A dislocation dipole source needs to experience a certain critical level of shear stress for a certain amount of time before it can emit a dipole. The amount of time is represented this variable.
   */
  double timeBeforeDipoleEmission;
  
  /**
   * @brief Counter variable for the time in number of consecutive iterations the dislocation source has experienced a shear stress greater than its critical value.
   * @details A dislocation source needs to experience a shear stress higher than a critical value, given by tauCritical, for a certain amount of time before it is triggered and it emits a dislocation dipole. This limiting time is given by the variable timeBeforeDipoleEmission, and this variable countTimeTillDipoleEmission is a counter variable. Once this limit is reached, a dipole is emitted and this counter variable is set to zero.
   */
  double countTimeTillDipoleEmission;
  
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
   * @param timeTillEmit Amount of time of experiencing critical stress before a dipole is emitted.
   */
  DislocationSource (Vector3d burgers, Vector3d line, Vector3d position, double bm, double tau, double timeTillEmit);

  // Destructor
  /**
   * @brief Destructor for the class DislocationSource.
   * @details The destructor is declared as virtual in order to avoid conflicts with derived class destructors.
   */
  virtual ~DislocationSource ()
  {

  }
  
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
   * @brief Set the critical time before a dipole is emitted.
   * @param timeTillEmit Amount of time spent at a high shear stress value before a dislocation dipole is emitted.
   */
  void setTimeTillDipoleEmission (double timeTillEmit);
  
  /**
   * @brief Sets the time counter to zero.
   */
  void resetTimeCounter ();
  
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
   * @brief Returns the amount of time that the dislocation source must spend experiencing a shear stress greater than the critical value before it can emit a dislocation dipole.
   * @return The amout of time that the dislocation source must spend experiencing a shear stress greater than the critical value before it can emit a dislocation dipole.
   */
  double getTimeTillEmit () const;
  
  /**
   * @brief Get the amount of time spent at higher than critical shear stress.
   * @return Amount of time spent at higher than critical shear stress.
   */
  double getTimeCount () const;
  
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
   * @brief Increments the time counter.
   * @param dt The time increment that is to be used to increase the counter.
   */
  void incrementTimeCount (double dt);
  
  /**
   * @brief Checks if the dislocation source has experienced higher than critical shear stress for long enough to emit a dipole.
   * @details The number of iterations for which the dislocation source must experience a shear stress higher than the critical value is given in the member nIterations. When the counter variable countIterations reaches this value, the source is ready to emit a dipole, so a true value is returned. In other cases, false is returned.
   * @return The boolean result of whether the count of iterations is greater than the limiting number of iterations provided at input.
   */
  bool ifEmitDipole () const;
};

#endif
