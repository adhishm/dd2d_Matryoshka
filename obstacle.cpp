#include "obstacle.h"

// Constructors
/**
 * Default constructor.
 * Creates the object with position (0.0, 0.0, 0.0).
 */
Obstacle::Obstacle ()
{
  for (int i=0; i<3; i++)
  {
    this->pos.setValue(i, 0.0);
  }
}

/**
 * Constructor specifying the position.
 * @param x X-coordinate of the obstacle.
 * @param y Y-coordinate of the obstacle
 */
Obstacle::Obstacle (double x, double y, double z)
{
  this->pos.setValue (0, x);
  this->pos.setValue (1, y);
  this->pos.setValue (2, z);
}

/**
 * Constructor specifying the position.
 * @param p Pointer to the array containing the coordinates of the obstacle.
 */
Obstacle::Obstacle (double* p)
{
  this->pos.setValue (p);
}

    
// Assignment functions
/**
 * Sets the position of the obstacle as the values in the array pointed to by the argument.
 * @param a Pointer to the array containing the coordinates of the obstacle.
 */
void Obstacle::setPosition (double* a)
{
  this->pos.setValue (a);
}

/**
 * Sets the position of the obstacle as the coordinates provided as arguments.
 * @param x X-coordinate of the obstacle.
 * @param y Y-coordinate of the obstacle.
 * @param z Z-coordinate of the obstacle.
 */
void Obstacle::setPosition (double x, double y, double z)
{
  this->pos.setValue (0, x);
  this->pos.setValue (1, y);
  this->pos.setValue (2, z);
}

/**
 * Sets the X-coordinate of the obstacle.
 * @param x X-coordinate of the obstacle.
 */
void setX (double x)
{
  this->pos.setValue (0, x);
}

/**
 * Sets the Y-coordinate of the obstacle.
 * @param y Y-coordinate of the obstacle.
 */
void Obstacle::setY (double y)
{
  this->pos.setValue (1, y);
}

/**
 * Sets the Z-coordinate of the obstacle.
 * @param z Z-coordinate of the obstacle.
 */
void Obstacle::setZ (double z)
{
  this->pos.setValue (2, z);
}

// Access Functions
/**
 * Returns in an array the position.
 */
double* Obstacle::getPosition ()
{
  return (this->pos.getVector ());
}

/**
 * Returns in the array provided in the argument the position of the obstacle. The array must be pre-allocated.
 * @param a Pointer to the location where the obstacle coordinates are to be populated.
 */
void Obstacle::getPosition (double* a)
{
  a = this->pos.getVector ();
}

/**
 * Returns the X-coordinate of the obstacle.
 */
double Obstacle::getX ()
{
  return (this->getValue (0));
}

/**
 * Returns the Y-coordinate of the obstacle.
 */
double Obstacle::getY ()
{
  return (this->pos.getValue (1));
}

/**
 * Returns the Z-coordinate of the obstacle.
 */
double Obstacle::getZ ()
{
  return (this->pos.getValue (2));
}
