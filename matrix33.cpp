#include "matrix33.h"

// Constructors
/**
 * Default constructor.
 */
Matrix33::Matrix33 ()
{
  int i, j;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  this->x[i][j] = 0.0;
	}
    }
}

/**
 * Constructor with the values provided in a 3x3 matrix.
 * @param a Pointer to the two-dimensional 3x3 array.
 */
Matrix33::Matrix33 (double** a)
{
  int i, j;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  this->x[i][j] = a[i][j];
	}
    }
}

/**
 * Constructor to create the matrix from the dyadic product of a vector with itself.
 * @param a The vector whose dyadic product results in the matrix.
 */
Matrix33::Matrix33 (Vector3d a)
{
  int i, j;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  this->x[i][j] = a.x[i] * a.x[j];
	}
    }
}

/**
 * Constructor with the vectors, the product of which will result in the matrix.
 * @param a First vector.
 * @param b Second vector.
 */
Matrix33::Matrix33 (Vector3d a, Vector3d b)
{
  int i, j;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  this->x[i][j] = a.x[i] * b.x[j];
	}
    }
}

// Functions
/**
 * Function to set the value of an element indicated by its position.
 * @param row Row index of the element.
 * @param column Column index of the element.
 * @param value Value that the element is to be set to.
 */
void Matrix33::setValue (int row, int column, double value)
{
  if (row>=0 && row<3)
    {
      if (column>=0 && column<3)
	{
	  this->x[row][column] = value;
	}
    }
}

/**
 * Returns the value of the element located by the row and column indices provided.
 * @param row Row index of the element.
 * @param column Column index of the element.
 */
double Matrix33::getValue (int row, int column)
{
  if (row>=0 && row<3)
    {
      if (column>=0 && column<3)
	{
	  return (this->x[row][column]);
	}
    }
  
  return (0.0);
}

/**
 * Returns the adjugate matrix of the present matrix.
 * @return The adjugate matrix of the present matrix.
 */
Matrix33 Matrix33::adjugate ()
{
  Matrix33 adj;
  
  adj.x[0][0] = (this->x[1][1]*this->x[2][2]) - (this->x[1][2]*this->x[2][1]);
  adj.x[0][1] = (this->x[1][2]*this->x[2][0]) - (this->x[1][0]*this->x[2][2]);
  adj.x[0][2] = (this->x[1][0]*this->x[2][1]) - (this->x[1][1]*this->x[2][0]);
  
  adj.x[1][0] = (this->x[2][1]*this->x[0][2]) - (this->x[0][1]*this->x[2][2]);
  adj.x[1][1] = (this->x[2][2]*this->x[0][0]) - (this->x[2][0]*this->x[0][2]);
  adj.x[1][2] = (this->x[2][0]*this->x[0][1]) - (this->x[2][1]*this->x[0][0]);
  
  adj.x[2][0] = (this->x[0][1]*this->x[1][2]) - (this->x[0][2]*this->x[1][1]);
  adj.x[2][1] = (this->x[0][2]*this->x[1][0]) - (this->x[0][0]*this->x[1][2]);
  adj.x[2][2] = (this->x[0][0]*this->x[1][1]) - (this->x[1][0]*this->x[0][1]);

  return (adj);
}
   
// Operators
// Addition
/**
 * Operator for addition of two matrices.
 * Adds the current matrix to the provided matrix and returns a third matrix with the result.
 */
Matrix33 Matrix33::operator+ (const Matrix33& p) const
{
  int i, j;
  Matrix33 r;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  r.x[i][j] = this->x[i][j] + p.x[i][j];
	}
    }
  
  return (r);
}

/**
 * Operator for reflexive addition of two matrices.
 * Adds the current matrix to the provided matrix and populates the current matrix elements with the result.
 */
void Matrix33::operator+= (const Matrix33& p)
{
  int i, j;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  this->x[i][j] += p.x[i][j];
	}
    }
}

// Subtraction
/**
 * Operator for the subtraction of two matrices.
 * Subtracts the given matrix from the current matrix and returns the result in a new matrix.
 */
Matrix33 Matrix33::operator- (const Matrix33& p) const
{
  int i, j;
  Matrix33 r;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  r.x[i][j] = this->x[i][j] - p.x[i][j];
	}
    }
  
  return (r);
}

/**
 * Operator for reflexive subtraction of two matrices.
 * Subtracts the given matrix from the current matrix and populates the current matrix with the result.
 */
void Matrix33::operator-= (const Matrix33& p)
{
  int i, j;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  this->x[i][j] -= p.x[i][j];
	}
    }
}

// Multiplication
/**
 * Operator for scaling the matrix by a scalar.
 * Scales the current matrix by the scalar provided and returns the result in a third matrix.
 */
Matrix33 Matrix33::operator* (const double& p) const
{
  int i, j;
  Matrix33 r;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  r.x[i][j] = this->x[i][j] * p;
	}
    }
  
  return (r);
}

/**
 * Operator for reflexive scaling of the matrix by a scalar.
 * Scales the current matrix by the scalar provided and populates the current matrix elements with the result.
 */
void Matrix33::operator*= (const double& p)
{
  int i, j;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  this->x[i][j] *= p;
	}
    }
}

/**
 * Operator for the multiplication of two matrices.
 * Multiplies the current matrix with another 3x3 matrix and returns the result in a new matrix.
 */
Matrix33 Matrix33::operator* (const Matrix33& p) const
{
  int i, j, k;
  Matrix33 r;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  r.x[i][j] = 0.0;
	  for (k=0; k<3; k++)
	    {
	      r.x[i][j] += this->x[i][k] * p.x[k][j];
	    }
	}
    }
  
  return (r);
}
  
/**
 * Operator for reflexive multiplication of two matrices.
 * Multiplies the current matrix with another 3x3 matrix and populates the elements of the current matrix with the result.
 */
void Matrix33::operator*= (const Matrix33& p)
{
  Matrix33* r = new Matrix33;
  
  *r = (*this) * p;
  *this = *r;
  
  delete(r);
  r = NULL;
}
  
/**
 * Returns in a vector the result of the multiplication of the current matrix with the provided vector.
 */
Vector3d Matrix33::operator* (const Vector3d& v) const
{
  Vector3d r(0.0, 0.0, 0.0);
  int i, j;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  r[i] += this->x[i][j] * v.x[j];
	}
    }
  
  return (r);
}

// Matrix operations
/**
 * Returns in a new matrix the transpose of the current matrix.
 */
Matrix33 Matrix33::operator^ () const
{
  Matrix33 r;
  int i, j;
  
  for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
	{
	  r.x[i][j] = this->x[j][i];
	}
    }
  
  return (r);
}
  
/**
 * Returns the determinant of the current matrix.
 */
double Matrix33::operator~ () const
{
  double d = 0.0;
  
  d += this.x[0][0] * ( (this->x[1][1]*this->x[2][2]) - (this->x[2][1]*this->x[1][2]) );
  d += this.x[0][1] * ( (this->x[1][2]*this->x[2][0]) - (this->x[1][0]*this->x[2][2]) );
  d += this.x[0][2] * ( (this->x[1][0]*this->x[2][1]) - (this->x[2][0]*this->x[1][1]) );
  
  return (d);
}

/**
 * Returns in a new matrix the inverse of the current matrix.
 * If the current matrix is non-invertible, a zero matrix is returned.
 */
Matrix33 Matrix33::operator! () const
{
  Matrix33 r;	// Result matrix
  
  double determinant = ~(*this);
  
  if (determinant == 0.0)
    {
      // The matrix is non-invertible
      return (r);	// Zero matrix
    }
  
  // If we are still here, the matrix is invertible
  
  //  Transpose
  Matrix33 tr = ^(*this);
  
  // Find Adjugate matrix
  Matrix33 adj = tr.adjugate();
  
  // Calculate the inverse by dividing the adjugate matrix by the determinant
  r = adj * (1.0/determinant);
  
  return (r);
}
