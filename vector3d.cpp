/**
 * @file vector3d.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 04/06/2013
 * @brief Definition of member functions and operators of the Vector3d class.
 * @details This file defines the member functions and operators of the Vector3d class representing a single 3-dimensional vector in the simulation.
 */

#include "vector3d.h"

/**
 * @brief Default constructor.
 * @details Initializes the vector with all elements equal to 0.0.
 */
Vector3d::Vector3d ()
{
  this->x[0] = 0.0;
  this->x[1] = 0.0;
  this->x[2] = 0.0;
}

/**
 * @brief Constructor with values provided in an array.
 * @details Initializes the vector with the values provided in the array.
 * @param a Pointer to the array containing the elements of the vector
 */
Vector3d::Vector3d (double* a)
{
  this->x[0] = a[0];
  this->x[1] = a[1];
  this->x[2] = a[2];
}

/**
 * @brief Constructor with values provided explicitly.
 * @details Initializes the vector with the three values provided as arguments.
 * @param a1 Value of the first element of the vector.
 * @param a2 Value of the second element of the vector.
 * @param a3 Value of the third element of the vector.
 */
Vector3d::Vector3d (double a1, double a2, double a3)
{
  this->x[0] = a1;
  this->x[1] = a2;
  this->x[2] = a3;
}

// Assignment functions
/**
 * @brief Function to set the value of an element of the vector.
 * @details Sets the value of the element indicated by the index argument.
 * @param index Index of the element whose value is to be set.
 * @param value Value that is to be given to the element.
 */
void Vector3d::setValue (int index, double value)
{
  if (index>=0 && index <3)
    {
      this->x[index] = value;
    }
}

/**
 * @brief Function to set the value of the entire vector using an array.
 * @details Sets the values of the elements if the vector to values in the array pointed to by the argument a.
 * @param a Pointer ot the array containing the values of the elements of the vector.
 */
void Vector3d::setVector (double* a)
{
  this->x[0] = a[0];
  this->x[1] = a[1];
  this->x[2] = a[2];
}

// Access functions
/**
 * @brief Function to get the value of an element of the vector.
 * @details Returns the value of the element at the position indicated by the argument index.
 * @param index Index of the element whose value is to be got.
 * @return The value of the element of the vector at the position
 */
double Vector3d::getValue (int index) const
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
 * @brief Function to get the values of the elements of the vector in an array.
 * @details The vector is returned in an array.
 * @return Pointer to the first term of an array containing the elements of the vector.
 */
double* Vector3d::getVector () const
{
  double* a = new double[3];
  
  a[0] = this->x[0];
  a[1] = this->x[1];
  a[2] = this->x[2];
  
  return (a);
}

/**
 * @brief Computes the sum of the elements of the vector.
 * @details Sums the elements of the vector and returns the result.
 * @return The sum of the elements of the vector.
 */
double Vector3d::sum () const
{
  double s = 0.0;
  int i;
  
  for (i=0; i<3; i++)
    {
      s += this->x[i];
    }
  
  return (s);
}

/**
 * @brief Computes the magnitude of the vector.
 * @details Computes the magnitude of the vector. Basically the square root of the sum of the squares of the vector elements.
 * @return The magnitude of the vector.
 */
double Vector3d::magnitude () const
{
  double s = 0.0;
  int i;
  
  for (i=0; i<3; i++)
  {
    s += this->x[i] * this->x[i];
  }
  
  return ( sqrt (s) );
}  

/**
 * @brief Returns the vector normalized to be a unit vector.
 * @details This function normalizes a vector by dividing its elements by the magnitude. In case the magnitude is zero, a zero vector is returned.
 * @return Normalized vector.
 */
Vector3d Vector3d::normalize ()
{
  double m = this->magnitude ();
  
  if (m==0.0)
  {
    return (Vector3d ());
  }
  else
  {
    return ((*this) * (1.0/m));
  }
}
  
// Operators
// Addition
/**
 * @brief Operator for addition of two vectors.
 * @details Adds the current vector to the provided vector and returns a third vector with the result.
 * @return Vector containing the sum of the current vector with the one provided as argument.
 */
Vector3d Vector3d::operator+ (const Vector3d& p) const
{
  Vector3d r (0.0, 0.0, 0.0);
  int i;
  
  for (i=0; i<3; i++)
    {
      r.setValue(i, (this->x[i] + p.getValue(i)));
    }
  
  return (r);
}

/**
 * @brief Operator for reflexive addition of two vectors.
 * @details Adds the current vector to the provided vector and populates the current vector elements with the result.
 */
void Vector3d::operator+= (const Vector3d& p)
{
  int i;
  
  for (i=0; i<3; i++)
    {
      this->x[i] += p.x[i];
    }
}

// Subtraction
/**
 * @brief Operator for the subtraction of two vectors.
 * @details Subtracts the given vector from the current vector and returns the result in a new vector.
 * @return Vector containing the result of subtracting the vector provided as argument from the current vector.
 */
Vector3d Vector3d::operator- (const Vector3d& p) const
{
  Vector3d r(0.0, 0.0, 0.0);
  int i;
  
  for (i=0; i<3; i++)
    {
      r.setValue(i, (this->x[i] - p.getValue(i)));
    }
  
  return (r);
}

/**
 * @brief Operator for reflexive subtraction of two vectors.
 * @details Subtracts the given vector from the current vector and populates the current vector with the result.
 */
void Vector3d::operator-= (const Vector3d& p)
{
  int i;
  
  for (i=0; i<3; i++)
    {
      this->x[i] -= p.getValue(i);
    }
}

// Multiplication
/**
 * @brief Operator for scaling the vector by a scalar.
 * @details Scales the current vector by the scalar provided and returns the result in a third vector.
 * @return Vector containing the result of scaling the current vector by the scala provided as argument.
 */
Vector3d Vector3d::operator* (const double& p) const
{
  Vector3d r(0.0, 0.0, 0.0);
  int i;
  
  for (i=0; i<3; i++)
    {
      r.setValue(i, (this->x[i] * p));
    }
  
  return (r);
}
   
/**
 * @brief Operator for reflexive scaling of the vector by a scalar.
 * @details Scales the current vector by the scalar provided and populates the current vector elements with the result.
 */
void Vector3d::operator*= (const double& p)
{
  int i;
  
  for (i=0; i<3; i++)
    {
      this->x[i] *= p;
    }
}

/**
 * @brief Operator for the scalar product of two vectors.
 * @details Performs the scalar product or dot product of the current vector with the one provided as argument and returns the result.
 * @return Scalar value of the scalar product of dot product of the current vector with the one provided as argument.
 */
double Vector3d::operator* (const Vector3d& p) const
{
  double s = 0.0;
  int i;
  
  for (i=0; i<3; i++)
    {
      s += this->x[i] * p.getValue(i);
    }
  
  return (s);
}

/**
 * @brief Operator for the vector product of two vectors.
 * @details Evaluates the vector product of the current vector with the provided vector and returns the result in a third vector.
 * @return Vector containing the result of the vector product of the current vector with the one provided as argument.
 */
Vector3d Vector3d::operator^ (const Vector3d& p) const
{
  Vector3d r(0.0, 0.0, 0.0);
  
  r.setValue(0, ((this->x[1] * p.getValue(2)) - (this->x[2] * p.getValue(1))));
  r.setValue(1, ((this->x[2] * p.getValue(0)) - (this->x[0] * p.getValue(2))));
  r.setValue(2, ((this->x[0] * p.getValue(1)) - (this->x[1] * p.getValue(0))));
  
  return (r);
}

/**
 * @brief Operator for reflexive vector product of two vectors.
 * @details Evaluates the vector product of the current vector and the one provided, and populates the result in the current vector.
 */
void Vector3d::operator^= (const Vector3d& p)
{
  Vector3d* r = new Vector3d(0.0, 0.0, 0.0);

  *r = (*this)^p;
  *this = *r;
  delete (r);
  r = NULL;
}
