#include "defect.h"

// Constructors
/**
 * Default constructor.
 * Creates the object with position (0.0, 0.0, 0.0).
 */
Defect::Defect ()
{
  for (int i=0; i<3; i++)
    {
      this->pos.setValue(i, 0.0);
    }
}

/**
 * Constructor specifying the position.
 * @param x X-coordinate of the defect.
 * @param y Y-coordinate of the defect
 * @param z Z-coordinate of the defect.
 */
Defect::Defect (double x, double y, double z)
{
  this->pos.setValue (0, x);
  this->pos.setValue (1, y);
  this->pos.setValue (2, z);
}

/**
 * Constructor specifying the position.
 * @param p Pointer to the array containing the coordinates of the defect.
 */
Defect::Defect (double* p)
{
  this->pos.setValue (p);
}

    
// Assignment functions
/**
 * Sets the position of the defect as the values in the array pointed to by the argument.
 * @param a Pointer to the array containing the coordinates of the defect.
 */
void Defect::setPosition (double* a)
{
  this->pos.setValue (a);
}

/**
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
 * Sets the X-coordinate of the defect.
 * @param x X-coordinate of the defect.
 */
void Defect::setX (double x)
{
  this->pos.setValue (0, x);
}

/**
 * Sets the Y-coordinate of the defect.
 * @param y Y-coordinate of the defect.
 */
void Defect::setY (double y)
{
  this->pos.setValue (1, y);
}

/**
 * Sets the Z-coordinate of the defect.
 * @param z Z-coordinate of the defect.
 */
void Defect::setZ (double z)
{
  this->pos.setValue (2, z);
}

// Access Functions
/**
 * Returns in an array the position.
 */
double* Defect::getPosition ()
{
  return (this->pos.getVector ());
}

/**
 * Returns in the array provided in the argument the position of the defect. The array must be pre-allocated.
 * @param a Pointer to the location where the defect coordinates are to be populated.
 */
void Defect::getPosition (double* a)
{
  a = this->pos.getVector ();
}

/**
 * Returns the X-coordinate of the defect.
 */
double Defect::getX ()
{
  return (this->getValue (0));
}

/**
 * Returns the Y-coordinate of the defect.
 */
double Defect::getY ()
{
  return (this->pos.getValue (1));
}

/**
 * Returns the Z-coordinate of the defect.
 */
double Defect::getZ ()
{
  return (this->pos.getValue (2));
}
