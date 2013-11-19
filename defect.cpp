/**
 * @file defect.cpp
 * @author Adhish Majumdar
 * @version 1.1
 * @date 03/07/2013
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
 * @details Creates the object with position given by the macros DEFAULT_DEFECT_POSITION_x. The default defect is defined by the macro DEFAULT_DEFECT_TYPE in the file defectType.h.
 */
Defect::Defect ()
{
    this->defectType = DEFAULT_DEFECT_TYPE;

    this->coordinateSystem.setDefaultVectors();
    this->coordinateSystem.setOrigin(Vector3d(DEFAULT_DEFECT_POSITION_0,
                                              DEFAULT_DEFECT_POSITION_1,
                                              DEFAULT_DEFECT_POSITION_2));
    this->coordinateSystem.setBase(NULL);

    this->setUniqueID();
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

    this->coordinateSystem.setOrigin(p);

    this->setUniqueID();
}

/**
 * @brief Constructor specifying type, axes and origin.
 * @param d The type of defect.
 * @param p The position vector of the origin of the defect.
 * @param axes Pointer to the array containing the axes of the defect.
 */
Defect::Defect (DefectType d, Vector3d p, Vector3d* axes)
{
    this->defectType = d;

    this->coordinateSystem.setAxes(axes);
    this->coordinateSystem.setOrigin(p);

    this->setUniqueID();
    this->setParametersUniquesList();
}

/**
 * @brief Constructor specifying type, axes, origin and base co-ordinate system.
 * @param d The type of defect.
 * @param p The position vector of the defect (origin of the local co-ordinate system)
 * @param axes Pointer to the array containing the axes of the defect.
 * @param base Pointer ot the base co-ordinate system.
 */
Defect::Defect (DefectType d, Vector3d p, Vector3d *axes, CoordinateSystem* base)
{
    this->defectType = d;
    this->setCoordinateSystem(axes, p, base);
}

// Assignment functions
/**
 * @brief Set the unique id for this defect.
 */
void Defect::setUniqueID ()
{
    UniqueID* uid_instance = UniqueID::getInstance();
    this->uniqueID = uid_instance->newIndex(this->defectType);
}

/**
 * @brief Set the co-ordinate system of the defect.
 * @param axes Pointer to the array containing the three axis vectors.
 * @param origin Position vector of the origin.
 * @param base Pointer to the base co-ordinate system.
 */
void Defect::setCoordinateSystem (Vector3d* axes, Vector3d origin, CoordinateSystem* base)
{
    this->coordinateSystem.setAxes(axes);
    this->coordinateSystem.setOrigin(origin);
    this->coordinateSystem.setBase(base);
    this->coordinateSystem.calculateRotationMatrix();
}

/**
 * @brief Set the base pointer of the defect's co-ordinate system.
 * @param base Pointer to the base co-ordinate system.
 */
void Defect::setBaseCoordinateSystem(CoordinateSystem *base)
{
    this->coordinateSystem.setBase(base);
}

/**
 * @brief Calculate the Rotation Matrix of the defect's co-ordinate system for conversions between the defect and base co-ordinate systems.
 * @details The rotation matrix of the defect's co-ordinate system is calculated. This function should be called every time there is a modification in the co-ordinate system, or a change of base.
 */
void Defect::calculateRotationMatrix()
{
    this->coordinateSystem.calculateRotationMatrix();
}

/**
 * @brief Sets the position of the defect.
 * @details The position of the defect is set to the co-ordinates present in the array pointed to by the argument.
 * Sets the position of the defect as the values in the array pointed to by the argument.
 * @param a Pointer to the array containing the coordinates of the defect.
 */
void Defect::setPosition (double* a)
{
    this->coordinateSystem.setOrigin(Vector3d(a));
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
    this->coordinateSystem.setOrigin(Vector3d(x,y,z));
}

/**
 * @brief Sets the position of the defect.
 * @details The position of the defect is set to the position vector fiven by the argument a.
 * @param a Position vector of the defect.
 */
void Defect::setPosition (Vector3d a)
{
    this->coordinateSystem.setOrigin(a);
}

/**
 * @brief Sets the defect type.
 * @param d The defect type.
 */
void Defect::setDefectType (DefectType d)
{
    this->defectType = d;
}

/**
 * @brief Sets the total stress value in the class and the vector keeping track of stresses in each iteration.
 * @param s Stress.
 */
void Defect::setTotalStress (Stress s)
{
    this->totalStress = s;
    this->totalStresses.push_back (s);
}

// Access Functions
/**
 * @brief Returns the position vector of the defect.
 * @return The position vector of the defect, in a variable of type Vector3d.
 */
Vector3d Defect::getPosition () const
{
    return (this->coordinateSystem.getOrigin());
}

/**
 * @brief Returns the the type of defect.
 * @return The defect type in the form of a member of Defect::DefectType.
 */
DefectType Defect::getDefectType () const
{
    return ( this->defectType );
}

/**
 * @brief Returns a pointer to the co-ordinate system of the defect.
 * @return Pointer to the co-ordinate system of the defect.
 */
CoordinateSystem* Defect::getCoordinateSystem ()
{
    return (&(this->coordinateSystem));
}

/**
 * @brief Gets the total stress in the current iteration.
 * @return Total stress in the current iteration.
 */
Stress Defect::getTotalStress () const
{
    return (this->totalStress);
}

/**
 * @brief Returns the total stress at the iteration i.
 * @details The total stress at the iteration i is returned. If an invalid value of i is provided, a zero stress tensor is returned.
 * @param i Iteration number for which the total stress is to be returned.
 * @return Total stress at iteration i.
 */
Stress Defect::getTotalStressAtIteration (int i) const
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
 * @brief Get the defect's uniqueID
 * @return The defect's uniqueID.
 */
long int Defect::getUniqueID () const
{
    return (this->uniqueID);
}
