/**
 * @file defect.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 16/04/2013
 * @section BRIEF
 * Definition of the Defect class.
 * @section DETAILS
 * This file defines the Defect class representing an defect in the simulation. This is simply a generic description class with virtual functions. Later classes like dislocations, precipitates, boundaries etc will inherit from this class.
 */

#ifndef DEFECT_H
#define DEFECT_H

#include "vector3d.h"
#include "matrix33.h"

/**
 * Class Defect.
 * Defines the Defect class representing an defect in the simulation. This is simply a generic description class with virtual functions.
 * Later classes like dislocations, precipitates, boundaries etc will inherit from this class.
 */
class Defect
{
 protected:
  /**
   * Position of the defect in 2D space.
   */
  Vector3d pos;
    
 public:
  // Constructors
  /**
   * Default constructor.
   * Creates the object with position (0.0, 0.0, 0.0).
   */
  Defect ();
  /**
   * Constructor specifying the position.
   * @param x X-coordinate of the defect.
   * @param y Y-coordinate of the defect
   */
  Defect (double x, double y, double z);
  /**
   * Constructor specifying the position.
   * @param p Pointer to the array containing the coordinates of the defect.
   */
  Defect (double* p);
  
  // Assignment functions
  /**
   * Sets the position of the defect as the values in the array pointed to by the argument.
   * @param a Pointer to the array containing the coordinates of the defect.
   */
  void setPosition (double* a);
  /**
   * Sets the position of the defect as the coordinates provided as arguments.
   * @param x X-coordinate of the defect.
   * @param y Y-coordinate of the defect.
   * @param z Z-coordinate of the defect.
   */
  void setPosition (double x, double y, double z);
  /**
   * Sets the X-coordinate of the defect.
   * @param x X-coordinate of the defect.
   */
  void setX (double x);
  /**
   * Sets the Y-coordinate of the defect.
   * @param y Y-coordinate of the defect.
   */
  void setY (double y);
  /**
   * Sets the Z-coordinate of the defect.
   * @param z Z-coordinate of the defect.
   */
  void setZ (double z);
    
  // Access Functions
  /**
   * Returns in an array the position.
   */
  double* getPosition ();
  /**
   * Returns in the array provided in the argument the position of the defect. The array must be pre-allocated.
   * @param a Pointer to the location where the defect coordinates are to be populated.
   */
  void getPosition (double* a);
  /**
   * Returns the X-coordinate of the defect.
   * @return X-coordinate of the defect.
   */
  double getX ();
  /**
   * Returns the Y-coordinate of the defect.
   * @return Y-coordinate of the defect.
   */
  double getY ();
  /**
   * Returns the Z-coordinate of the defect.
   * @return Z-coordinate of the defect.
   */
  double getZ ();
    
  // Virtual functions
  /**
   * Returns the value of the stress field of the given defect at the position given by the argument.
   * @param p Position vector of the the point where the stress field is to be calculated.
   * @return Stress field value at the position p.
   */
  virtual Matrix33 stressField (Vector3d p)
  {
    // This virtual function returns a zero matrix.
    // Inheriting classes will have functions implementing this in their own way
    // They will override this behaviour.
    Matrix33 r;
    return (r);
  }
};

#endif
