/**
 * @file defect.h
 * @author Adhish Majumdar
 * @version 1.1
 * @date 03/07/2013
 * @brief Definition of the Defect class.
 * @details This file defines the Defect class representing an defect in the simulation. This is simply a generic description class with virtual functions. Later classes like dislocations, precipitates, boundaries etc will inherit from this class.
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

#ifndef DEFECT_H
#define DEFECT_H

#include "defectType.h"
#include "stress.h"
#include "coordinatesystem.h"

#ifndef DEFAULT_DEFECT_POSITION
#define DEFAULT_DEFECT_POSITION
#define DEFAULT_DEFECT_POSITION_0 0.0
#define DEFAULT_DEFECT_POSITION_1 0.0
#define DEFAULT_DEFECT_POSITION_2 0.0
#endif

/**
 * @brief Class Defect representing a generic defect in a material.
 * @details Defines the Defect class representing an defect in the simulation. This is simply a generic description class with virtual functions.
 * Later classes like dislocations, precipitates, boundaries etc will inherit from this class.
 */
class Defect
{
 protected:
  /**
   * @brief The defect's own co-ordinate system.
   * @details The co-ordinate system contains the vectors and the origin. This gives us the orientation and the position of the defect.
   */
  CoordinateSystem coordinateSystem;
    
public:
  /**
   * @brief Instance of the enumerated class DefectType to indicate the kind of defect that this is.
   */
  DefectType defectType;
  
// Constructors
  /**
   * @brief Default constructor.
   * @details Creates the object with position given by the macros DEFAULT_DEFECT_POSITION_x. The default defect is defined by the macro DEFAULT_DEFECT_TYPE in the file defectType.h.
   */
  Defect ();

  /**
   * @brief Constructor specifying the position and type of defect.
   * @details The object is initialized with the position specified in the array pointed to by the argument, and the type of defect specified.
   * @param d The type of defect.
   * @param p Vector3d prividing the position vector of the defect.
   */
  Defect (DefectType d, Vector3d p);

  /**
   * @brief Constructor specifying type, axes and origin.
   * @param d The type of defect.
   * @param p The position vector of the origin of the defect.
   * @param axes Pointer to the array containing the axes of the defect.
   */
  Defect (DefectType d, Vector3d p, Vector3d* axes);

  /**
   * @brief Constructor specifying type, axes, origin and base co-ordinate system.
   * @param d The type of defect.
   * @param p The position vector of the defect (origin of the local co-ordinate system)
   * @param axes Pointer to the array containing the axes of the defect.
   * @param base Pointer ot the base co-ordinate system.
   */
  Defect (DefectType d, Vector3d p, Vector3d *axes, CoordinateSystem* base);
  
  // Assignment functions
  /**
   * @brief Set the co-ordinate system of the defect.
   * @param axes Pointer to the array containing the three axis vectors.
   * @param origin Position vector of the origin.
   * @param base Pointer to the base co-ordinate system.
   */
  void setCoordinateSystem(Vector3d* axes, Vector3d origin, CoordinateSystem* base);

  /**
   * @brief Sets the position of the defect.
   * @details The position of the defect is set to the co-ordinates present in the array pointed to by the argument.
   * Sets the position of the defect as the values in the array pointed to by the argument.
   * @param a Pointer to the array containing the coordinates of the defect.
   */
  void setPosition (double* a);

  /**
   * @brief Sets the position of the defect.
   * @details The position of the defect is set to the co-ordinates specified by the arguments (x, y, z).
   * Sets the position of the defect as the coordinates provided as arguments.
   * @param x X-coordinate of the defect.
   * @param y Y-coordinate of the defect.
   * @param z Z-coordinate of the defect.
   */
  void setPosition (double x, double y, double z);
  
  /**
   * @brief Sets the position of the defect.
   * @details The position of the defect is set to the position vector fiven by the argument a.
   * @param a Position vector of the defect.
   */
  void setPosition (Vector3d a);

  /**
   * @brief Sets the defect type.
   * @param d The defect type.
   */
  void setDefectType (DefectType d);
    
  // Access Functions
  /**
   * @brief Returns the position vector of the defect.
   * @return The position vector of the defect, in a variable of type Vector3d.
   */
  Vector3d getPosition () const;

  /**
   * @brief Returns the the type of defect.
   * @return The defect type in the form of a member of Defect::DefectType.
   */
  DefectType getDefectType () const;
    
  // Virtual functions
  /**
   * @brief Virtual function for calculating the stress field.
   * @details Returns the value of the stress field of the given defect at the position given by the argument. This is a virtual function and always returns a zero matrix. Classes which inherit this function should have their own implementations of this function to override its behaviour.
   * @param p Position vector of the the point where the stress field is to be calculated.
   * @param mu Shear modulus in Pascals.
   * @param nu Poisson's ratio.
   * @return Stress field value at the position p.
   */
  virtual Stress stressField (Vector3d p, double mu, double nu)
  {
    // This virtual function returns a zero matrix.
    // Inheriting classes will have functions implementing this in their own way
    // They will override this behaviour.
    Stress s;
    return (s);
  }
};

#endif
