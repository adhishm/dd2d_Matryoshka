/**
 * @file defect.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 04/06/2013
 * @brief Definition of member functions of the Defect class.
 * @details This file defines the member functions of the Defect class representing a single defect in the simulation.
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


#include "defect.h"

// Constructors
/**
 * @brief Default constructor.
 * @details Creates the object with position (0.0, 0.0, 0.0). The default defect is defined by the macro DEFAULT_DEFECT_TYPE in the file defectType.h.
 */
Defect::Defect ()
{
    this->defectType = DEFAULT_DEFECT_TYPE;

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

/**
 * @brief Constructor specifying the position and type of defect.
 * @details The object is initialized with the position specified in the array pointed to by the argument, and the type of defect specified.
 * @param d The type of defect.
   * @param p Vector3d prividing the position vector of the defect.
   */
Defect::Defect (DefectType d, Vector3d p)
{
    this->defectType = d;
    this->setPosition ( p );
}

// Assignment functions

/**
 * @brief Set the co-ordinate system of the defect.
 * @param axes Pointer to the array containing the three axis vectors.
 * @param origin Position vector of the origin.
 * @param base Pointer to the base co-ordinate system.
 */
virtual void Defect::setCoordinateSystem(Vector3d* axes, Vector3d origin, CoordinateSystem* base)
{
    this->coordinateSystem.setAxes(axes);
    this->coordinateSystem.setOrigin(origin);
    this->coordinateSystem.setBase(base);
}

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
DefectType Defect::getDefectType () const
{
    return ( this->defectType );
}
