/**
 * @file slipPlane.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 28/05/2013
 * @brief Definition of the SlipPlane class.
 * @details This file defines the SlipPlane class representing a slip plane in the simulation.
 */

#ifndef SLIPPLANE_H
#define SLIPPLANE_H

// STL containers
#include <vector>

// Defects
#include "defect.h"
#include "dislocation.h"
#include "dislocationSource.h"


/**
 * @brief SlipPlane class representing a slip plane in the simulation.
 * @details This is the definition of the class SlipPlane. It represents a slip plane in the simulation. A slip plane is considered to be a collection of defects, such as dislocations and dislocation sources. In these simulations in two dimensions, the slip plane becomes a straight line. Its attributes are: position vectors of the extremities, normal vector (since we are concerned with the cubic system here, the normal vector's indices are the same as those of the plane), and the collection of defects.
 */
class SlipPlane
{
protected:
  /**
   * @brief The extremities of the slip plane.
   * @details The slip plane is represented as a straight line in these two dimensional simulations. The position vectors of the two ends are given here.
   */
  Vector3d extremities[2];
  
  /**
   * @brief The normal vector to the slip plane.
   * @details This is the vector normal to the slip plane. Since we are concerned with the cubic system here, the indices of the normal vector are the same as those of the slip plane.
   */
  Vector3d normalVector;
  
  /**
   * @brief The position vector of the slip plane.
   * @details This position vector is redundant because the combination of the position vectors of the extremities and the normal vector define the slip plane completely. However, this vector, position, is useful to locate the slip plane in a given slip system.
   */
  Vector3d position;
  
  /**
   * @brief STL vector container with dislocations.
   * @details A slip plane may contain several dislocations. These are stored in this vector container dislocations.
   */
  std::vector<Dislocation> dislocations;
  
  /**
   * @brief STL vector container with dislocation sources.
   * @details A slip plane may contain several dislocation sources. These are stored in this vector container dislocationSources.
   */
  std::vector<DislocationSource> dislocationSources;
  
  /**
   * @brief Rotation matrix for co-ordinate system transformations.
   * @details The slip plane's local co-ordinate system is defined as follows: z-axis||NormalVector; x-axis||slipPlane line. The rotation matrix is created using this convention.
   */
  RotationMatrix rotationMatrix;
  
public:
  // Constructors
  /**
   * @brief Default constructor.
   * @details The slip plane is initialized with default parameters.
   */
  SlipPlane ();
  
  /**
   * @brief Constructor that specifies all members explicitly.
   * @details The slip plane is initialized with parameters specified in the arguments.
   * @param ends Pointer to an array of type Vector3d, containing the position vectors of the extremities of the slip plane in consecutive locations.
   * @param normal The normal vector of the slip plane.
   * @param pos The position vector of the slip plane. (This parameter is useful for locating the slip plane within a slip system)
   * @param dislocationList A vector container of type Dislocation containing the dislocations lying on this slip plane.
   * @param dislocationSourceList A vector container of type DislocationSource containing the dislocation sources lying on this slip plane.
   */
  SlipPlane (Vector3d *ends, Vector3d normal, Vector3d pos, std::vector<Dislocation> dislocationList, std::vector<DislocationSource> dislocationSourceList);
  
  // Assignment functions
  /**
   * @brief Set the extremities of the slip plane.
   * @param ends Pointer to an array of type Vector3d, containing the position vectors of the extremities of the slip plane in consecutive locations.
   */
  void setExtremities (Vector3d *ends);
  
  /**
   * @brief Set the normal vector of the slip plane.
   * @param normal The normal vector of the slip plane.
   */
  void setNormal (Vector3d normal);
  
  /**
   * @brief Set the position of the slip plane.
   * @param pos The position vector of the slip plane. (This parameter is useful for locating the slip plane within a slip system)
   */
  void setPosition (Vector3d pos);
  
  /**
   * @brief Set the list of dislocations of the slip plane.
   * @param dislocationList A vector container of type Dislocation containing the dislocations lying on this slip plane.
   */
  void setDislocationList (std::vector<Dislocation> dislocationList);
  
  /**
   * @brief Set the list of dislocation sources on the slip plane.
   * @param dislocationSourceList A vector container of type DislocationSource containing the dislocation sources lying on this slip plane.
   */
  void setDislocationSourceList (std::vector<DislocationSource> dislocationSourceList);
  
  // Access functions
  /**
   * @brief Get the position vector of the extremity whose index is provided as argument.
   * @param i Index of the extremity. Possible values: 0, 1
   * @return Position vector of the extremity indicated by the argument, returned as a variable of type Vector3d.
   */
  Vector3d getExtremity (int i);
  
  /**
   * @brief Get the position vectors of the extremities of the slip plane.
   * @return Pointer to an array containing the position vectors of the two extremities of the slip plane, variables of type Vector3d.
   */
  Vector3d* getExtremities ();
  
  /**
   * @brief Get the normal vector of the slip plane.
   * @return The normal vector of the slip plane, in a variable of type Vector3d.
   */
  Vector3d getNormal ();
  
  /**
   * @brief Get the position vector of the slip plane.
   * @details This function returns the position vector of the slip plane. The position vector is redundant because the slip plane is completely defined by its extremities and the normal vector. Nevertheless, this value can be useful to locate the slip plane within a slip system.
   * @return Position vector of the slip plane, in a variable of type Vector3d.
   */
  Vector3d getPosition ();
  
  /**
   * @brief Get the dislocation on the slip plane indicated by the index provided as argument.
   * @details The slip plane contains several dislocations that are stored in a vector container. This function returns the dislocation in that vector that corresponds to the index provided as argument.
   * @param i Index of the required dislocation in the vector. This value should be greater than or equal to 0 and less than the number of dislocations on the slip plane.
   * @param d Pointer to the memory location where the required dislocation is to be stored. Space in memory must be pre-allocated.
   * @return True if the provided index is greater than or equal to 0 and less than the number of dislocations on the slip plane (the memory location pointed to by d is populated with the Dislocation data). Otherwise, the return value is false.
   */
  bool getDislocation (int i, Dislocation* d);
  
  /**
   * @brief Get the entire vector container which holds the dislocations lying on this slip plane.
   * @return The vector of dislocations lying on this slip plane.
   */
  std::vector<Dislocation> getDislocationList ();
  
  /**
   * @brief Get the dislocation source on the slip plane indicated by the index provided as argument.
   * @details The slip plane contains several dislocation sources that are stored in a vector container. This function returns the dislocation source in that vector that corresponds to the index provided as argument.
   * @param i Index of the required dislocation source in the vector. This value should be greater than or equal to 0 and less than the number of dislocation sources on the slip plane.
   * @param dSource Pointer to the memory location where the required dislocation source is to be stored. Space in memory must be pre-allocated.
   * @return True if the provided index is greater than or equal to 0 and less than the number of dislocation sources on the slip plane (the memory location pointed to by d is populated with the DislocationSource data). Otherwise, the return value is false.
   */
  bool getDislocationSource (int i, DislocationSource* dSource);
  
  /**
   * @brief Get the entire vector container which holds the dislocation sources lying on this slip plane.
   * @return The vector of dislocation sources lying on this slip plane.
   */
  std::vector<DislocationSource> getDislocationSourceList ();  
  
  /**
   * @brief Get the rotation matrix for this slip plane.
   * @return The rotation matrix of this slip plane, in a variable of type RotationMatrix.
   */
  RotationMatrix getRotationMatrix ();
  
  /**
   * @brief Get the axis (expressed in the global co-ordinate system) of the slip plane's local co-ordinate system, as indicated by the argument. (0, 1, 2)=(x, y, z).
   * @param i Index of the axis that is to be returned. (0, 1, 2)=(x, y, z).
   * @return The desired axis of the slip plane's local co-ordinate system, expressed in the global co-ordinate system.
   */
  Vector3d getAxis (int i);
};

#endif
