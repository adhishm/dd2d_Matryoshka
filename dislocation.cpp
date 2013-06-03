/**
 * @file dislocation.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 31/05/2013
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
  this->calculateRotationMatrix ();
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
  this->calculateRotationMatrix ();
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
 * @return Stress tensor, expressed in the global co-ordinate system, giving the value of the stress field at position p.
 */
Stress Dislocation::stressField (Vector3d p, double mu, double nu)
{
  double principalStresses[3];
  double shearStresses[3];
  Vector3d r;  // Vector joining the present dislocation to the point p
  
  r = p - this->pos;	// Still in global coordinate system
  Vector3d rLocal = this->rotationMatrix * r;	// Rotated to local co-ordinate system
  
  // Calculate the stress field in the local co-ordinate system
  Stress sLocal = this->stressFieldLocal (rLocal, mu, nu);
  
  // Calculate the stress field in the global co-ordinate system
  Stress sGlobal = (this->rotationMatrix) * sLocal * (^(this->rotationMatrix));
  
  return (sGlobal);
}

/**
 * @brief Calculates the stress field due to the dislocation in the local co-ordinate system.
 * @details The stress field due to the dislocation is calculated at the position indicated by the argument. The stress tensor is expressed in the dislocation's local co-ordinate system.
 * @param p Position vector of the point where the stress field is to be calculated. This position vector is calculated in the local co-ordinate system, taking the dislocation as the origin.
 * @param mu Shear modulus in Pascals.
 * @param nu Poisson's ratio.
 * @return Stress tensor, expressed in the dislocation's local co-ordinate system.
 */
Stress Dislocation::stressFieldLocal (Vector3d p, double mu, double nu)
{
  double D = ( mu * this->bm ) / ( 2.0 * PI * ( 1.0 - nu ) );	// Constant for all components of the stress tensor
  
  double x, y, denominator;	// Terms that appear repeatedly in the stress tensor
  
  x = p.getValue (0);
  y = p.getValue (1);
  denominator = pow ( ((x*x) + (y*y)), 2);
  
  principalStresses[0] = -1.0 * D * y * ( (3.0*x*x) + (y*y) ) / denominator;
  principalStresses[1] = D * y * ( (x*x) - (y*y) ) / denominator;
  principalStresses[2] = nu * ( principalStresses[0] + principalStresses[1] );
  
  shearStresses[0] = D * x * ( (x*x) - (y*y) ) / denominator;
  shearStresses[1] = 0.0;
  shearStresses[2] = 0.0;
  
  return (Stress(principalStresses, shearStresses));
}

// Force
/**
 * @brief Calculate the Peach-Koehler force acting on the dislocation due the stress.
 * @details This function calculates the Peach-Koehler force in the dislocation due to the stress (expressed in the global co-ordinate system) provided as argument. The force returned is also in the global co-ordinate system. This function checks if the xy component of the stress tensorm expressed in the dislocation's local co-ordinate system, is greater than tau_crss. If it is, the force is calculated using the Peach-Koehler equation, otherwise, the force on the dislocation is zero.
 * @param sigma The stress tensor, expressed in the global co-ordinate system.
 * @param tau_crss Critical Resolved Shear Stress in Pa.
 * @return The Peach-Koehler force on the dislocation, expressed in the global co-ordinate system.
 */
Vector3d Dislocation::forcePeachKoehler (Stress sigma, double tau_crss)
{
  // Stress in the local co-ordinate system
  Stress sigmaLocal = (this->rotationMatrix) * (sigma) * (this->rotationMatrix)^;
  Vector3d force;

  // Check for CRSS condition
  if (sigmaLocal.getValue(0,1) >= tau_crss)
    { 
      Vector3d force = sigma * ((this->bvec)^(this->lvec));
    }

  return (force);
}
