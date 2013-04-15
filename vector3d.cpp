#include "vector3d.h"

/**
 * Default constructor.
 */
Vector3d ()
{
 this->x[0] = 0.0;
 this->x[1] = 0.0;
 this->x[2] = 0.0;
}
/**
 * Constructor with values provided in an array.
 * @param a Pointer to the array containing the elements of the vector
 */
Vector3d (double* a)
{
  this->x[0] = a[0];
  this->x[1] = a[1];
  this->x[2] = a[2];
}

/**
 * Constructor with values provided explicitly.
 * @param a1 Value of the first element of the vector.
 * @param a2 Value of the second element of the vector.
 * @param a3 Value of the third element of the vector.
 */
Vector3d (double a1, double a2, double a3)
{
  this->x[0] = a1;
  this->x[1] = a2;
  this->x[2] = a3;
}

// Access functions
/**
 * Function to set the value of an element of the vector.
 * @param index Index of the element whose value is to be set.
 * @param value Value that is to be given to the element.
 */
void setValue (int index, double value)
{
  if (index>=0 && index <3)
  {
    this->x[index] = value;
  }
}

/**
 * Function to set the value of the entire vector using an array.
 * @param a Pointer ot the array containing the values of the elements of the vector.
 */
void setVector (double* a)
{
  this->x[0] = a[0];
  this->x[1] = a[1];
  this->x[2] = a[2];
}

/**
 * Function to get the value of an element of the vector.
 * @param index Index of the element whose value is to be got.
 */
double getValue (int index)
{
  if (index>=0 && index<3)
  {
    return (this->x[index]);
  }
  else
  {
    return (0);
  }
}

/**
 * Function to get the values of the elements of the vector in an array.
 */
double* getVector ()
{
  double* a = new double[3];
  
  a[0] = this->x[0];
  a[1] = this->x[1];
  a[2] = this->x[2];
  
  return (a);
}

/**
 * Computes the sum of the elements of the vector.
 */
double sum ()
{
  double s = 0.0;
  int i;
  
  for (i=0; i<3; i++)
  {
    s += this->x[i];
  }
  
  return (s);
}

// Operators
// Addition
/**
 * Operator for addition of two vectors.
 * Adds the current vector to the provided vector and returns a third vector with the result.
 */
Vector3d operator+ (const Vector3d& p) const
{
  Vector3d r (0.0, 0.0, 0.0);
  int i;
  
  for (i=0; i<3; i++)
  {
    r.x[i] = this->x[i] + p.x[i];
  }
  
  return (r);
}

/**
 * Operator for reflexive addition of two vectors.
 * Adds the current vector to the provided vector and populates the current vector elements with the result.
 */
void operator+= (const Vector3d& p)
{
  int i;
  
  for (i=0; i<3; i++)
  {
    this->x[i] += p.x[i];
  }
}

// Subtraction
/**
 * Operator for the subtraction of two vectors.
 * Subtracts the given vector from the current vector and returns the result in a new vector.
 */
Vector3d operator- (const Vector3d& p) const
{
  Vector3d r(0.0, 0.0, 0.0);
  int i;
  
  for (i=0; i<3; i++)
  {
    r.x[i] = this->x[i] - p.x[i];
  }
  
  return (r);
}

/**
 * Operator for reflexive subtraction of two vectors.
 * Subtracts the given vector from the current vector and populates the current vector with the result.
 */
void operator-= (const Vector3d& p)
{
  int i;
  
  for (i=0; i<3; i++)
  {
    this->x[i] -= p.x[i];
  }
}

// Multiplication
/**
 * Operator for scaling the vector by a scalar.
 * Scales the current vector by the scalar provided and returns the result in a third vector.
 */
Vector3d operator* (const double& p) const
{
  Vector3d r(0.0, 0.0, 0.0);
  int i;
  
  for (i=0; i<3; i++)
  {
    r.x[i] = this->x[i] * p;
  }
  
  return (r);
}
   
/**
 * Operator for reflexive scaling of the vector by a scalar.
 * Scales the current vector by the scalar provided and populates the current vector elements with the result.
 */
void operator*= (const double& p)
{
  int i;
  
  for (i=0; i<3; i++)
  {
    this->x[i] *= p;
  }
}

/**
 * Operator for the scalar product of two vectors.
 */
double operator* (const Vector3d& p) const
{
  double s = 0.0;
  int i;
  
  for (i=0; i<3; i++)
  {
    s += this->x[i] * p.x[i];
  }
  
  return (s);
}

/**
 * Operator for the vector product of two vectors.
 * Evaluates the vector product of the current vector with the provided vector and returns the result in a third vector.
 */
Vector3d operator^ (const Vector3d& p) const
{
  Vector3d r(0.0, 0.0, 0.0);
  
  r.x[0] = (this->x[1] * p.x[2]) - (this->x[2] * p.x[1]);
  r.x[1] = (this->x[2] * p.x[0]) - (this->x[0] * p.x[2]);
  r.x[2] = (this->x[0] * p.x[1]) - (this->x[1] * p.x[0]);
  
  return (r);
}

/**
 * Operator for reflexive vector product of two vectors.
 * Evaluates the vector product of the current vector and the one provided, and populates the result in the current vector.
 */
void operator^= (const Vector3d& p)
{
  Vector3d* r = Vector3d(0.0, 0.0, 0.0);
  
  r->x[0] = (this->x[1] * p.x[2]) - (this->x[2] * p.x[1]);
  r->x[1] = (this->x[2] * p.x[0]) - (this->x[0] * p.x[2]);
  r->x[2] = (this->x[0] * p.x[1]) - (this->x[1] * p.x[0]);
  
  *this = *r;
  
  delete (r);
  r = NULL;
}
