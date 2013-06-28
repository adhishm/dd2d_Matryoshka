/**
 * @file dislocation.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 04/06/2013
 * @brief Definition of constructors and member functions of the Dislocation class.
 * @details This file defines the constructors and member functions of the Dislocation class. This class inherits from the Defect class.
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
    : Defect ( DISLOCATION, Vector3d ( DEFAULT_POSITION_0, DEFAULT_POSITION_1, DEFAULT_POSITION_2 ) )
{
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
    : Defect ( DISLOCATION, position )
{
  this->bvec   = burgers;
  this->lvec   = line;
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
 * @brief Sets the magnitude of the Burgers vector of the dislocation.
 * @param b Magnitude of the Burgers vector of the dislocation.
 */
void Dislocation::setBurgersMagnitude (double b)
{
    this->bmag = b;
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

/**
 * @brief Sets the total stress value in the class and the vector keeping track of stresses in each iteration.
 * @param s Stress.
 */
void Dislocation::setTotalStress (Stress s)
{
  this->totalStress = s;
  this->totalStresses.push_back (s);
}

/**
 * @brief Sets the total force in the class and the vector keeping track of forces in each iteration.
 * @param f Force.
 */
void Dislocation::setTotalForce (Vector3d f)
{
  this->force = f;
  this->forces.push_back (f);
}

/**
 * @brief Sets the total velocity in the class and the vector keeping track of velocities in each iteration.
 * @param v Velocity.
 */
void Dislocation::setVelocity (Vector3d v)
{
  this->velocity = v;
  this->velocities.push_back (v);
}

// Access functions
/**
 * @brief Gets the Burgers vector of the dislocation.
 * @return Burgers vector in a variable of type Vector3d.
 */
Vector3d Dislocation::getBurgers () const
{
  return ( this->bvec );
}

/**
 * @brief Gets the magnitude of the Burgers vector of the dislocation.
 * @return Magnitude of the Burgers vector.
 */
double Dislocation::getBurgersMagnitude () const
{
    return ( this->bmag );
}

/**
 * @brief Gets the line vector of the dislocation.
 * @return Line vector in a variable of type Vector3d.
 */
Vector3d Dislocation::getLineVector () const
{
  return ( this->lvec );
}

/**
 * @brief Returns whether the dislocation is mobile or pinned.
 * @return Returns true if the dislocation is mobile, false if pinned.
 */
bool Dislocation::isMobile () const
{
  return (this->mobile);
}

/**
 * @brief Gets the total stress in the current iteration.
 * @return Total stress in the current iteration.
 */
Stress Dislocation::getTotalStress () const
{
  return (this->totalStress);
}

/**
 * @brief Gets the total force on the dislocation in the current iteration.
 * @return Total force on the dislocation in the current iteration.
 */
Vector3d Dislocation::getTotalForce () const
{
  return (this->force);
}

/**
 * @brief The velocity of the dislocation in the current iteration.
 * @return Velocity of the dislocation in the current iteration.
 */
Vector3d Dislocation::getVelocity () const
{
  return (this->velocity);
}

/**
 * @brief Returns the total stress at the iteration i.
 * @details The total stress at the iteration i is returned. If an invalid value of i is provided, a zero stress tensor is returned.
 * @param i Iteration number for which the total stress is to be returned.
 * @return Total stress at iteration i.
 */
Stress Dislocation::getTotalStressAtIteration (int i) const
{
  if (i < this->totalStresses.size())
    {
      // If the iteration number provided is valid
      return (this->totalStresses[i]);
    }
  else
    {
      // Invalid iteration number - return zeros
      return (Stress());
    }
}

/**
 * @brief Returns the total force at the iteration i.
 * @details The total force at the iteration i is returned. If an invalid value of i is provided, a zero force vector is returned.
 * @param i Iteration number for which the total force is to be returned.
 * @return Total force at iteration i.
 */
Vector3d Dislocation::getTotalForceAtIteration (int i) const
{
  if (i < this->forces.size())
    {
      // If the iteration number provided is valid
      return (this->forces[i]);
    }
  else
    {
      // Invalid iteration number - return zeros
      return (Vector3d());
    }
}

/**
 * @brief Returns the total velocity at the iteration i.
 * @details The total velocity at the iteration i is returned. If an invalid value of i is provided, a zero velocity vector is returned.
 * @param i Iteration number for which the total velocity is to be returned.
 * @return Total velocity at iteration i.
 */
Vector3d Dislocation::getVelocityAtIteration (int i) const
{
  if (i < this->velocities.size())
    {
      // If the iteration number provided is valid
      return (this->velocities[i]);
    }
  else
    {
      // Invalid iteration number - return zeros
      return (Vector3d());
    }
}

// Rotation matrix
/**
 * @brief Calculate the roation matrix.
 * @details This function calculates the rotation matrix for this dislocation using the global and local co-ordinate systems. The matrix rotationMatrix is for rotation from the old (unprimed, global) to the new (primed, dislocation) system.
 */
void Dislocation::calculateRotationMatrix ()
{
  Vector3d *globalSystem = new Vector3d[3];	// Global co-ordinate systems
  Vector3d *localSystem  = new Vector3d[3];	// Dislocation co-ordinate system

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

  // Release memory
  delete (globalSystem);  globalSystem = NULL;
  delete (localSystem);   localSystem  = NULL;
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
  //Stress sGlobal = (this->rotationMatrix) * sLocal * (this->rotationMatrix.transpose());
  Stress sGlobal = sLocal.rotate (this->rotationMatrix);

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
Stress Dislocation::stressFieldLocal (Vector3d p, double mu, double nu) const
{
  double D = ( mu * this->bmag ) / ( 2.0 * PI * ( 1.0 - nu ) );	// Constant for all components of the stress tensor

  double x, y, denominator;	// Terms that appear repeatedly in the stress tensor

  x = p.getValue (0);
  y = p.getValue (1);
  denominator = pow ( ((x*x) + (y*y)), 2);

  double principalStresses[3], shearStresses[3];

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
Vector3d Dislocation::forcePeachKoehler (Stress sigma, double tau_crss) const
{
  // Stress in the local co-ordinate system
  Stress sigmaLocal = sigma.rotate(this->rotationMatrix);
  Vector3d force;

  // Check for CRSS condition
  if (fabs(sigmaLocal.getValue(0,1)) >= tau_crss)
    {
      force = sigma * ((this->bvec)^(this->lvec));
    }

  return (force);
}

/**
 * @brief Returns the ideal time increment for the dislocation.
 * @details A dislocation is not allowed to approach another defect beyond a certain distance, specified by the argument minDistance. This function calculates the ideal time increment for this dislocation to not collide with the defect.
 * @param minDistance Minimum distance of approach to the defect.
 * @param d The defect for which the present dislocation's time increment is to be calculated.
 * @param v1 Velocity of the other defect.
 * @return The ideal time increment for this dislocation.
 */
double Dislocation::idealTimeIncrement (double minDistance, Defect d, Vector3d v1)
{
  Vector3d v0 = this->velocity;
  double norm_v0 = v0.magnitude();
  if (norm_v0 == 0.0)
    {
      // This dislocation is not moving
      return (1000.0);
    }

  // Positions
  Vector3d p0 = this->getPosition();
  Vector3d p1 = d.getPosition();
  Vector3d p01 = p1 - p0;
  double norm_p01 = p01.magnitude();

  if (norm_p01 <= 0.0)
    {
      // The dislocation is lying on top of the obstacle - so it should not move
      return (0.0);
    }
  else
    {
      // Find out if the dislocation is approaching the defect or not

      // Velocities
      Vector3d v01 = v1 - v0;
      double norm_v01 = v01.magnitude();
      double dotProduct = v01 * p01;
      double cosine = dotProduct/(norm_v01 * norm_p01);
      if (cosine < 0.0)
	{
	  if (norm_p01 <= minDistance)
	    {
	      return (0.0);
	    }
	  else
	    {
	      // The dislocation is approaching the other defect
	      return ( (norm_p01 - minDistance)/norm_v01 );
	    }
	}
      else
	{
	  // They are diverging
	  // So any time increment will do
	  return (1000.0);
	}
    }
}
