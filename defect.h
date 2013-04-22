/**
 * @file defect.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 22/04/2013
 * @brief Definition of the Defect class.
 * @details This file defines the Defect class representing an defect in the simulation. This is simply a generic description class with virtual functions. Later classes like dislocations, precipitates, boundaries etc will inherit from this class.
 */

#ifndef DEFECT_H
#define DEFECT_H

#include "vector3d.h"
#include "matrix33.h"
#include "stress.h"

/**
 * @brief Class Defect representing a generic defect in a material.
 *
 * @details Defines the Defect class representing an defect in the simulation. This is simply a generic description class with virtual functions.
 * Later classes like dislocations, precipitates, boundaries etc will inherit from this class.
 */
class Defect
{
 protected:
  /**
   * @brief Position vector of the defect in 2D space.
   */
  Vector3d pos;
    
 public:
  // Constructors
  /**
   * @brief Default constructor.
   * @details Creates the object with position (0.0, 0.0, 0.0).
   */
  Defect ();
  /**
   * @brief Constructor specifying the position.
   * @details The object is initialized with the position specified by the arguments (x, y, z).
   * @param x X-coordinate of the defect.
   * @param y Y-coordinate of the defect
   * @param z Z-coordinate of the defect.
   */
  Defect (double x, double y, double z);
  /**
   * @brief Constructor specifying the position.
   * @details The object is initialized with the position specified in the array pointed to by the argument.
   * @param p Pointer to the array containing the coordinates of the defect.
   */
  Defect (double* p);
  
  // Assignment functions
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
   * @brief Sets the X-coordinate of the defect.
   * @param x X-coordinate of the defect.
   */
  void setX (double x);
  /**
   * @brief Sets the Y-coordinate of the defect.
   * @param y Y-coordinate of the defect.
   */
  void setY (double y);
  /**
   * @brief Sets the Z-coordinate of the defect.
   * @param z Z-coordinate of the defect.
   */
  void setZ (double z);
    
  // Access Functions
  /**
   * @brief Returns in an array the position.
   * @details The position of the defect is saved in an array and a pointer to its first term is returned.
   * @return Pointer to the first term of the array containing the position of the defect.
   */
  double* getPosition ();
  /**
   * @brief Returns the array position in a pre-allocated array.
   * @details Returns in the array provided in the argument the position of the defect. The array must be pre-allocated.
   * @param a Pointer to the location where the defect coordinates are to be populated.
   */
  void getPosition (double* a);
  /**
   * @brief Returns the X-coordinate of the defect.
   * @return X-coordinate of the defect.
   */
  double getX ();
  /**
   * @brief Returns the Y-coordinate of the defect.
   * @return Y-coordinate of the defect.
   */
  double getY ();
  /**
   * @brief Returns the Z-coordinate of the defect.
   * @return Z-coordinate of the defect.
   */
  double getZ ();
    
  // Virtual functions
  /**
   * @brief Virtual function for calculating the stress field.
   * @details Returns the value of the stress field of the given defect at the position given by the argument. This is a virtual function and always returns a zero matrix. Classes which inherit this function should have their own implementations of this function to override its behaviour.
   * @param p Position vector of the the point where the stress field is to be calculated.
   * @return Stress field value at the position p.
   */
  virtual Stress stressField (Vector3d p)
  {
    // This virtual function returns a zero matrix.
    // Inheriting classes will have functions implementing this in their own way
    // They will override this behaviour.
    Stress s;
    return (s);
  }
};

#endif
