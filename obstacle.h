/**
 * @file obstacle.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 16/04/2013
 * @brief Definition of the Obstacle class.
 * @details This file defines the Obstacle class representing an obstacle in the simulation. This is simply a generic description class with virtual functions. Later classes like dislocations, precipitates, boundaries etc will inherit from this class.
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "vector3d.h"
#include "matrix33.h"

/**
 * Class Obstacle.
 * Defines the Obstacle class representing an obstacle in the simulation. This is simply a generic description class with virtual functions.
 * Later classes like dislocations, precipitates, boundaries etc will inherit from this class.
 */
class Obstacle
{
 protected:
  /**
   * Position of the obstacle in 2D space.
   */
  Vector3d pos;
    
 public:
  // Constructors
  /**
   * Default constructor.
   * Creates the object with position (0.0, 0.0, 0.0).
   */
  Obstacle ();
  /**
   * Constructor specifying the position.
   * @param x X-coordinate of the obstacle.
   * @param y Y-coordinate of the obstacle
   */
  Obstacle (double x, double y, double z);
  /**
   * Constructor specifying the position.
   * @param p Pointer to the array containing the coordinates of the obstacle.
   */
  Obstacle (double* p);
  
  // Assignment functions
  /**
   * Sets the position of the obstacle as the values in the array pointed to by the argument.
   * @param a Pointer to the array containing the coordinates of the obstacle.
   */
  void setPosition (double* a);
  /**
   * Sets the position of the obstacle as the coordinates provided as arguments.
   * @param x X-coordinate of the obstacle.
   * @param y Y-coordinate of the obstacle.
   * @param z Z-coordinate of the obstacle.
   */
  void setPosition (double x, double y, double z);
  /**
   * Sets the X-coordinate of the obstacle.
   * @param x X-coordinate of the obstacle.
   */
  void setX (double x);
  /**
   * Sets the Y-coordinate of the obstacle.
   * @param y Y-coordinate of the obstacle.
   */
  void setY (double y);
  /**
   * Sets the Z-coordinate of the obstacle.
   * @param z Z-coordinate of the obstacle.
   */
  void setZ (double z);
    
  // Access Functions
  /**
   * Returns in an array the position.
   */
  double* getPosition ();
  /**
   * Returns in the array provided in the argument the position of the obstacle. The array must be pre-allocated.
   * @param a Pointer to the location where the obstacle coordinates are to be populated.
   */
  void getPosition (double* a);
  /**
   * Returns the X-coordinate of the obstacle.
   */
  double getX ();
  /**
   * Returns the Y-coordinate of the obstacle.
   */
  double getY ();
  /**
   * Returns the Z-coordinate of the obstacle.
   */
  double getZ ();
    
  // Virtual functions
  /**
   * Returns the value of the stress field of the given obstacle at the position given by the argument.
   * @param p Position vector of the the point where the stress field is to be calculated.
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
