/**
 * @file dislocationSource.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 05/06/2013
 * @brief Definition of the member functions of the DislocationSource class.
 * @details This file defines the member functions of the DislocationSource class representing a source of dislocations in the simulation. This class inherits from the Defect class. This object is basically the representation of a Frank-Read source emitting dislocation dipoles. When the dislocation source experiences a shear stress greater than a critical value for a certain amount of time (or number of iterations), it emits a dislocation dipole with a length that is a function of the applied stress.
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


#include "dislocationSource.h"

// Constructors
/**
 * @brief Default constructor.
 * @details Initializes the dislocation with the default parameters provided in the files dislocationDefaults.h and dislocationSourceDefaults.h.
 */
DislocationSource::DislocationSource ()
    : Defect ( FRANKREADSOURCE, Vector3d ( DEFAULT_POSITION_0, DEFAULT_POSITION_1, DEFAULT_POSITION_2 ) )
{
  this->setBurgers ( Vector3d ( DEFAULT_BURGERS_0, DEFAULT_BURGERS_1, DEFAULT_BURGERS_2 ) );
  this->setLineVector ( Vector3d ( DEFAULT_LINEVECTOR_0, DEFAULT_LINEVECTOR_1, DEFAULT_LINEVECTOR_2) );
  this->bmag = DEFAULT_BURGERS_MAGNITUDE;
  this->tauCritical = DEFAULT_TAU_CRITICAL;
  this->timeBeforeDipoleEmission = DEFAULT_DIPOLEEMISSIONTIMELIMIT;
  this->countTimeTillDipoleEmission = 0.0;
}

/**
 * @brief Constructor that explicitly specifies all parameters.
 * @details All parameters: Burgers vector, line vector, position, are specified.
 * @param burgers Burgers vector.
 * @param line Line vector.
 * @param position Position of the dislocation.
 * @param bm Magnitude of the Burgers vector in metres.
 * @param tau Critical shear stress value.
 * @param timeTillEmit Amount of time of experiencing critical stress before a dipole is emitted.
 */
DislocationSource::DislocationSource (Vector3d burgers, Vector3d line, Vector3d position, double bm, double tau, double timeTillEmit)
    : Defect ( FRANKREADSOURCE, position )
{
  this->bvec   = burgers;
  this->lvec   = line;
  this->bmag   = bm;
  this->tauCritical = tau;
  this->timeBeforeDipoleEmission = timeTillEmit;
  this->countTimeTillDipoleEmission = 0;
}

// Assignment functions
/**
 * @brief Sets the Burgers vector of the dislocation.
 * @param burgers Burgers vector of the dislocation.
 */
void DislocationSource::setBurgers (Vector3d burgers)
{
  this->bvec = burgers;
}

/**
 * @brief Sets the line vector of the dislocation.
 * @param line Line vector of the dislocation.
 */
void DislocationSource::setLineVector (Vector3d line)
{
  this->lvec = line;
}

/**
 * @brief Set the magnitude of the Burgers vector.
 * @param bm Magnitude of the Burgers vector.
 */
void DislocationSource::setBurgersMagnitude (double bm)
{
  this->bmag = bm;
}

/**
 * @brief Set the critical shear stres for dipole emission.
 * @param tauC Critical shear stress for dipole emission.
 */
void DislocationSource::setTauCritical (double tauC)
{
  this->tauCritical = tauC;
}

/**
 * @brief Set the critical time before a dipole is emitted.
 * @param timeTillEmit Amount of time spent at a high shear stress value before a dislocation dipole is emitted.
 */
void DislocationSource::setTimeTillDipoleEmission (double timeTillEmit)
{
    this->timeBeforeDipoleEmission = timeTillEmit;
}

/**
 * @brief Sets the time counter to zero.
 */
void DislocationSource::resetTimeCounter ()
{
  this->countTimeTillDipoleEmission = 0.0;
}

// Access functions
/**
 * @brief Returns the Burgers vector of the dislocations in the dipole.
 * @return The Burgers vector of the dislocations in the dipole.
 */
Vector3d DislocationSource::getBurgers () const
{
  return (this->bvec);
}

/**
 * @brief Returns the line vector of the dislocations in the dipole.
 * @return The line vector of the dislocations in the dipole.
 */
Vector3d DislocationSource::getLineVector () const
{
  return (this->lvec);
}

/**
 * @brief Returns the magnitude of the Burgers vector.
 * @return The magnitude of the Burgers vector.
 */
double DislocationSource::getBurgersMag () const
{
  return (this->bmag);
}

/**
 * @brief Returns the critical shear stress value for dipole emission.
 * @return The critical shear stress value for dipole emission.
 */
double DislocationSource::getTauCritical () const
{
  return (this->tauCritical);
}

/**
 * @brief Returns the amount of time that the dislocation source must spend experiencing a shear stress greater than the critical value before it can emit a dislocation dipole.
 * @return The amout of time that the dislocation source must spend experiencing a shear stress greater than the critical value before it can emit a dislocation dipole.
 */
double DislocationSource::getTimeTillEmit () const
{
    return ( this->timeBeforeDipoleEmission );
}

/**
 * @brief Get the amount of time spent at higher than critical shear stress.
 * @return Amount of time spent at higher than critical shear stress.
 */
double DislocationSource::getTimeCount () const
{
    return ( this->countTimeTillDipoleEmission );
}

// Operations specific to the class
/**
 * @brief The nucleation length of the dipole.
 * @details When a dislocation source has experienced a shear stress greater than the critical value for a certain amount of time, it emits a dislocation dipole. In three dimensions, this is equivalent to a dislocation loop emitted by a Frank-Read source. The length of the dipole (or diameter of the loop in 3D) is such that the interaction force between the two dislocations (or line tension in 3D) balances out the applied shear stress.
 * @param tau The shear stress experienced by the dislocation source.
 * @param mu Shear modulus of the material, in Pa.
 * @param nu Poisson's ratio.
 * @return The length of the dislocation dipole.
 */
double DislocationSource::dipoleNucleationLength (double tau, double mu, double nu) const
{
  double L = 0.0;

  if (tau >= tauCritical)
  {
    L = (mu * this->bmag) / ( 2.0 * PI * (1.0 - nu) * this->tauCritical );
  }

  return (L);
}

/**
 * @brief Increments the time counter.
 * @param dt The time increment that is to be used to increase the counter.
 */
void DislocationSource::incrementTimeCount (double dt)
{
    this->countTimeTillDipoleEmission += dt;
}

/**
 * @brief Checks if the dislocation source has experienced higher than critical shear stress for long enough to emit a dipole.
 * @details The number of iterations for which the dislocation source must experience a shear stress higher than the critical value is given in the member nIterations. When the counter variable countIterations reaches this value, the source is ready to emit a dipole, so a true value is returned. In other cases, false is returned.
 * @return The boolean result of whether the count of iterations is greater than the limiting number of iterations provided at input.
 */
bool DislocationSource::ifEmitDipole () const
{
  return ( this->countTimeTillDipoleEmission >= this->timeBeforeDipoleEmission );
}
