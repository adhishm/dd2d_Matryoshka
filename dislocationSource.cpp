/**
 * @file dislocationSource.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 02/05/2013
 * @brief Definition of the member functions of the DislocationSource class.
 * @details This file defines the member functions of the DislocationSource class representing a source of dislocations in the simulation. This class inherits from the Defect class. This object is basically the representation of a Frank-Read source emitting dislocation dipoles.
 */

#include "dislocationSource.h"

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
DislocationSource::DislocationSource ()
{
  this->setPosition ( 0.0, 0.0, 0.0 );
  this->setBurgers ( Vector3d ( DEFAULT_BURGERS_0, DEFAULT_BURGERS_1, DEFAULT_BURGERS_2 ) );
  this->setLineVector ( Vector3d ( DEFAULT_LINEVECTOR_0, DEFAULT_LINEVECTOR_1, DEFAULT_LINEVECTOR_2) );
  this->bmag = DEFAULT_BURGERS_MAGNITUDE;
  this->tauCritical = DEFAULT_TAU_CRITICAL;
  this->nIterations = DEFAULT_NITERATIONS;
}

/**
 * @brief Constructor that explicitly specifies all parameters.
 * @details All parameters: Burgers vector, line vector, position, are specified.
 * @param burgers Burgers vector.
 * @param line Line vector.
 * @param position Position of the dislocation.
 * @param bm Magnitude of the Burgers vector in metres.
 * @param tau Critical shear stress value.
 * @param nIter Number of iterations of experiencing critical stress before a dipole is emitted.
 */
DislocationSource::DislocationSource (Vector3d burgers, Vector3d line, Vector3d position, double bm, double tau, int nIter)
{
  this->bvec   = burgers;
  this->lvec   = line;
  this->pos    = position;
  this->bmag   = bm;
  this->tauCritical = tau;
  this->nIterations = nIter;
}

/**
 * @brief Sets the Burgers vector of the dislocation.
 * @param burgers Bergers vector of the dislocation.
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
