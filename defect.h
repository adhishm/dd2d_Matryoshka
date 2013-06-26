/**
 * @file defect.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 04/06/2013
 * @brief Definition of the Defect class.
 * @details This file defines the Defect class representing an defect in the simulation. This is simply a generic description class with virtual functions. Later classes like dislocations, precipitates, boundaries etc will inherit from this class.
 */

#ifndef DEFECT_H
#define DEFECT_H

#include "stress.h"

/**
 * @brief Class Defect representing a generic defect in a material.
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
  /**
   * @brief Enumerated class indicating the kind of defect that this is.
   */
  enum class DefectType {
      VACANCY = 0,
		INTERSTITIAL,
		DISLOCATION,
		FRANKREADSOURCE,
		GRAINBOUNDARY,
		FREESURFACE
		};
  
  /**
   * @brief Instance of the enumerated class DefectType to indicate the kind of defect that this is.
   */
  DefectType defectType;		
  
// Constructors
  /**
   * @brief Default constructor.
   * @details Creates the object with position (0.0, 0.0, 0.0). The default defect is the Dislocation.
   */
  Defect ();
  /**
   * @brief Constructor specifying the position and type of defect.
   * @details The object is initialized with the position specified by the arguments (x, y, z) and the type of defect.
   * @param d The type of defect.
   * @param x X-coordinate of the defect.
   * @param y Y-coordinate of the defect
   * @param z Z-coordinate of the defect.
   */
  Defect (DefectType d, double x, double y, double z );
  /**
   * @brief Constructor specifying the position and type of defect.
   * @details The object is initialized with the position specified in the array pointed to by the argument, and the type of defect specified.
   * @param d The type of defect.
   * @param p Pointer to the array containing the coordinates of the defect.
   */
  Defect (DefectType d, double* p);
  
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
   * @brief Sets the position of the defect.
   * @details The position of the defect is set to the position vector fiven by the argument a.
   * @param a Position vector of the defect.
   */
  void setPosition (Vector3d a);
  
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

  /**
   * @brief Sets the defect type.
   * @param d The defect type.
   */
  void setDefectType (DefectType d);
    
  // Access Functions
  /**
   * @brief Returns the array position in a pre-allocated array.
   * @details Returns in the array provided in the argument the position of the defect. The array must be pre-allocated.
   * @param a Pointer to the location where the defect coordinates are to be populated.
   */
  void getPosition (double* a) const;

  /**
   * @brief Returns the position vector of the defect.
   * @return The position vector of the defect, in a variable of type Vector3d.
   */
  Vector3d getPosition () const;
  
  /**
   * @brief Returns the X-coordinate of the defect.
   * @return X-coordinate of the defect.
   */
  double getX () const;
  
  /**
   * @brief Returns the Y-coordinate of the defect.
   * @return Y-coordinate of the defect.
   */
  double getY () const;
  
  /**
   * @brief Returns the Z-coordinate of the defect.
   * @return Z-coordinate of the defect.
   */
  double getZ () const;

  /**
   * @brief Returns the the type of defect.
   * @return The defect type in the form of a member of Defect::DefectType.
   */
  Defect::DefectType getDefectType () const;
    
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
