/**
 * @file dislocation.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 26/04/2013
 * @brief Definition of constructors and member functions of the Dislocation class.
 * @details This file defines the constructors and member functions of the Dislocation class. This class inherits from the Defect class.
 */

#include "dislocation.h"

/**
 * @brief Default constructor.
 * @details Initializes the dislocation with the following default parameters:
 * Position: (0.0, 0.0, 0.0)
 * Burgers vector: Default value set in defaults file.
 * Line vector: Default value set in defaults file.
 * Burgers vector magnitude: Default value set in teh defaults file.
 * Mobile: true.
 */
Dislocation::Dislocation ()
{
  this->setPosition ( 0.0, 0.0, 0.0 );
  this->setBurgers ( Vector3d ( DEFAULT_BURGERS_0, DEFAULT_BURGERS_1, DEFAULT_BURGERS_2 ) );
  this->setLineVector ( Vector3d ( DEFAULT_LINEVECTOR_0, DEFAULT_LINEVECTOR_1, DEFAULT_LINEVECTOR_2) );
  this->bmag = DEFAULT_BURGERS_MAGNITUDE;
  this->mobile = true;
}

/**
 * @brief Constructor that explicitly specifies all parameters.
 * @details All parameters: Burgers vector, line vector, position, are specified.
 * @param burgers Burgers vector.
 * @param line Line vector.
 * @param position Position of the dislocation.
 * @param bm Magnitude of the Burgers vector in metres.
 * @param m Mobility (true/false).
 */
Dislocation::Dislocation (Vector3d burgers, Vector3d line, Vector3d position,  double bm, bool m)
{
  this->bvec   = burgers;
  this->lvec   = line;
  this->pos    = position;
  this->mobile = m;
  this->bmag   = bm;
}

// Assignment functions
/**
 * @brief Sets the Burgers vector of the dislocation.
 */
void Dislocation::setBurgers (Vector3d burgers)
{
  this->bvec = burgers;
}

/**
 * @brief Sets the line vector of the dislocation.
 */
void Dislocation::setLineVector (Vector3d line)
{
  this->lvec = line;
}

/**
 * @brief Sets the dislocation as mobile.
 * @details Sets the flag mobile to true.
 */
void Dislocation::setMobile ()
{
  this->mobile = true;
}

/**
 * @brief Sets the dislocation as pinned.
 * @details Sets the flag mobile to false.
 */
void Dislocation::setPinned ()
{
  this->mobile = false;
}

// Access functions
/**
 * @brief Gets the Burgers vector of the dislocation.
 * @return Burgers vector in a variable of type Vector3d.
 */
Vector3d Dislocation::getBurgers ()
{
  return ( this->bvec );
}

/**
 * @brief Gets the line vector of the dislocation.
 * @return Line vector in a variable of type Vector3d.
 */
Vector3d Dislocation::getLineVector ()
{
  return ( this->lvec );
}

// Rotation matrix
/**
 * @brief Calculate the roation matrix.
 * @details This function calculates the rotation matrix for this dislocation using the global and local co-ordinate systems. The matrix rotationMatrix is for rotation from the old (unprimed, global) to the new (primed, dislocation) system.
 */
void Dislocation::calculateRotationMatrix ()
{
  Vector3d globalSystem[3];	// Global co-ordinate systems
  Vector3d localSystem[3];	// Dislocation co-ordinate system
  
  // Vectors of the global co-ordinate system
  globalSystem[0] = Vector3d (1.0, 0.0, 0.0);
  globalSystem[1] = Vector3d (0.0, 1.0, 0.0);
  globalSystem[2] = Vector3d (0.0, 0.0, 1.0);
  
  // Vectors of the dislocation co-ordinate system
  localSystem[0] = bvec.normalize ();
  localSystem[2] = lvec.normalize ();
  localSystem[1] = (lvec ^ bvec).normalize ();
  
  // Calculate rotation matrix
  this->rotationMatrix = RotationMatrix (globalSystem, localSystem);
}
  
// Stress field
/**
 * @brief Calculates the stress field due to this dislocation at the position given as argument.
 * @details The stress field of the dislocation is calculated at the position indicated by the argument.
 * @param p Position vector of the point where the stress field is to be calculated.
 * @param mu Shear modulus in Pascals.
 * @param nu Poisson's ratio.
 * @return Stress tensor giving the value of the stress field at position p.
 */
Stress Dislocation::stressField (Vector3d p, double mu, double nu)
{
  Stress s;    // Variable for holding the stress tensor
  Vector3d r;  // Vector joining the present dislocation to the point p
  
  r = p - this->pos;
  
  double D = ( mu * this->bm ) / ( 2.0 * PI * ( 1.0 - nu ) );
  
  // Calculate the rotation matrix for transforming vectors and tensors
  // from the local coordinate system of the dislocation to the
}
