/**
 * @file defect.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 04/06/2013
 * @brief Definition of member functions of the Defect class.
 * @details This file defines the member functions of the Defect class representing a single defect in the simulation.
 */

#include "defect.h"

// Constructors
/**
 * @brief Default constructor.
 * @details Creates the object with position (0.0, 0.0, 0.0). The default defect is the Dislocation.
 */
Defect::Defect ()
{
    this->defectType = DefectType::DISLOCATION;

    for (int i=0; i<3; i++)
    {
        this->pos.setValue(i, 0.0);
    }
}

/**
 * @brief Constructor specifying the position and type of defect.
 * @details The object is initialized with the position specified by the arguments (x, y, z) and the type of defect.
 * @param d The type of defect.h
 * @param x X-coordinate of the defect.
 * @param y Y-coordinate of the defect
 * @param z Z-coordinate of the defect.
 */
Defect::Defect (DefectType d, double x, double y, double z)
{
    this->defectType = d;

    this->pos.setValue (0, x);
    this->pos.setValue (1, y);
    this->pos.setValue (2, z);
}

/**
 * @brief Constructor specifying the position and type of defect.
 * @details The object is initialized with the position specified in the array pointed to by the argument, and the type of defect specified.
 * @param d The type of defect.
 * @param p Pointer to the array containing the coordinates of the defect.
 */
Defect::Defect (DefectType d, double* p)
{
    this->defectType = d;
    for (int i=0; i<3; i++)
    {
        this->pos.setValue (i, p[i]);
    }
}

// Assignment functions
/**
 * @brief Sets the position of the defect.
 * @details The position of the defect is set to the co-ordinates present in the array pointed to by the argument.
 * Sets the position of the defect as the values in the array pointed to by the argument.
 * @param a Pointer to the array containing the coordinates of the defect.
 */
void Defect::setPosition (double* a)
{
  this->pos.setVector (a);
}

/**
 * @brief Sets the position of the defect.
 * @details The position of the defect is set to the co-ordinates specified by the arguments (x, y, z).
 * Sets the position of the defect as the coordinates provided as arguments.
 * @param x X-coordinate of the defect.
 * @param y Y-coordinate of the defect.
 * @param z Z-coordinate of the defect.
 */
void Defect::setPosition (double x, double y, double z)
{
  this->pos.setValue (0, x);
  this->pos.setValue (1, y);
  this->pos.setValue (2, z);
}

/**
 * @brief Sets the position of the defect.
 * @details The position of the defect is set to the position vector fiven by the argument a.
 * @param a Position vector of the defect.
 */
void Defect::setPosition (Vector3d a)
{
  this->pos = a;
}

/**
 * @brief Sets the X-coordinate of the defect.
 * @param x X-coordinate of the defect.
 */
void Defect::setX (double x)
{
  this->pos.setValue (0, x);
}

/**
 * @brief Sets the Y-coordinate of the defect.
 * @param y Y-coordinate of the defect.
 */
void Defect::setY (double y)
{
  this->pos.setValue (1, y);
}

/**
 * @brief Sets the Z-coordinate of the defect.
 * @param z Z-coordinate of the defect.
 */
void Defect::setZ (double z)
{
  this->pos.setValue (2, z);
}

/**
 * @brief Sets the defect type.
 * @param d The defect type.
 */
void Defect::setDefectType (DefectType d)
{
    this->defectType = d;
}

// Access Functions
/**
 * @brief Returns the array position in a pre-allocated array.
 * @details Returns in the array provided in the argument the position of the defect. The array must be pre-allocated.
 * @param a Pointer to the location where the defect coordinates are to be populated.
 */
void Defect::getPosition (double* a) const
{
  a = this->pos.getVector ();
}

/**
 * @brief Returns the position vector of the defect.
 * @return The position vector of the defect, in a variable of type Vector3d.
 */
Vector3d Defect::getPosition () const
{
  return (this->pos);
}

/**
 * @brief Returns the X-coordinate of the defect.
 * @return X-coordinate of the defect.
 */
double Defect::getX () const
{
  return (this->pos.getValue (0));
}

/**
 * @brief Returns the Y-coordinate of the defect.
 * @return Y-coordinate of the defect.
 */
double Defect::getY () const
{
  return (this->pos.getValue (1));
}

/**
 * @brief Returns the Z-coordinate of the defect.
 * @return Z-coordinate of the defect.
 */
double Defect::getZ () const
{
  return (this->pos.getValue (2));
}

/**
 * @brief Returns the the type of defect.
 * @return The defect type in the form of a member of Defect::DefectType.
 */
Defect::DefectType Defect::getDefectType () const
{
    return ( this->defectType );
}
