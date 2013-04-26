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
 * Mobile: true.
 */
Dislocation::Dislocation ()
{
    this->setPosition ( 0.0, 0.0, 0.0 );
    this->setBurgers ( Vector3d ( DEFAULT_BURGERS_0, DEFAULT_BURGERS_1, DEFAULT_BURGERS_2 ) );
    this->setLineVector ( Vector3d ( DEFAULT_LINEVECTOR_0, DEFAULT_LINEVECTOR_1, DEFAULT_LINEVECTOR_2) );
    this->mobile = true;
}

/**
 * @brief Constructor that explicitly specifies all parameters.
 * @details All parameters: Burgers vector, line vector, position, are specified.
 * @param burgers Burgers vector.
 * @param line Line vector.
 * @param position Position of the dislocation.
 * @param m Mobility (true/false).
 */
Dislocation::Dislocation (Vector3d burgers, Vector3d line, Vector3d position,  bool m)
{
    this->bvec   = burgers;
    this->lvec   = line;
    this->pos    = position;
    this->mobile = m;
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

