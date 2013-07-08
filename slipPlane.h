/**
 * @file slipPlane.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 18/06/2013
 * @brief Definition of the SlipPlane class.
 * @details This file defines the SlipPlane class representing a slip plane in the simulation.
 */

/*
    DD2D-Matryoshka approach.
    A set of classes defining the behaviour of crystalline defects,
    with the final goal of carrying out dislocation dynamics simulations
    in two dimensions.
    Copyright (C) 2013  Adhish Majumdar

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef SLIPPLANE_H
#define SLIPPLANE_H

// Standard library
#include <fstream>
#include <string>

// Algorithms
#include <algorithm>

// STL containers
#include <vector>
#include <iterator>

// Default values
#include "slipPlaneDefaults.h"

// Parameters
#include "parameter.h"

// Co-ordinate system
#include "coordinatesystem.h"

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
  Defect extremities[2];
  
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
   * @brief STL vector container for defects.
   * @details A slip plane contains simply a list of defects, which may be dislocations, or other defects. Pointers are used so that when virtual functions are called, they are point to the appropriate implementation.
   */
  std::vector<Defect*> defects;

  /**
   * @brief STL vector container for dislocations.
   * @details This vector container holds pointers to all the dislocations on the slip plane.
   */
  std::vector<Dislocation*> dislocations;

  /**
   * @brief STL vector container for dislocation sources.
   * @details This vector container holds pointers to all the dislocation sources on the slip plane.
   */
  std::vector<DislocationSource*> dislocationSources;

  /**
   * @brief Time increment for the slip plane.
   * @details A time increment is calculated for each slip plane based on the distances traveled by the dislocations.
   */
  double dt;

  /**
   * @brief The slip plane's own co-ordinate system.
   */
  CoordinateSystem coordinateSystem;
  
public:
  // Constructors
  /**
   * @brief Default constructor.
   * @details The slip plane is initialized with default parameters specified in the file slipPlaneDefaults.h.
   */
  SlipPlane ();
  
  /**
   * @brief Constructor that specifies all members explicitly.
   * @details The slip plane is initialized with parameters specified in the arguments.
   * @param ends Pointer to an array of type Vector3d, containing the position vectors of the extremities of the slip plane in consecutive locations.
   * @param normal The normal vector of the slip plane.
   * @param pos The position vector of the slip plane. (This parameter is useful for locating the slip plane within a slip system)
   * @param base Pointer to the co-ordinate system of the base.
   * @param dislocationList A vector container of type Dislocation* containing the dislocations lying on this slip plane.
   * @param dislocationSourceList A vector container of type DislocationSource* containing the dislocation sources lying on this slip plane.
   */
  SlipPlane (Vector3d *ends, Vector3d normal, Vector3d pos, CoordinateSystem* base, std::vector<Dislocation*> dislocationList, std::vector<DislocationSource*> dislocationSourceList);
  
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
   * @brief Creates the co-ordinate system using information from the extremities, position, normal etc. The base co-ordinate system must be provided.
   * @details The co-ordinate system of the slip plane is as follows: X-axis=line joining the extremities; Z-axis=Normal vector; Y-axis=cross(Z,X).
   * @param base Pointer to the base co-ordinate system.
   */
  void createCoordinateSystem(CoordinateSystem* base);

  /**
   * @brief Insert a list of dislocations into the slip plane's defect list
   * @param dList The list of pointers to dislocations.
   */
  void insertDislocationList (std::vector<Dislocation*> dList);

  /**
   * @brief Inserted the provided dislocation into the slip plane's dislocation list.
   * @param d The dislocation that is to be inserted into the silp plane's dislocation list.
   */
  void insertDislocation (Dislocation* d);
    
  /**
   * @brief Insert a list of dislocation sources on the slip plane.
   * @param dislocationSourceList A vector container of type DislocationSource* containing pointers the dislocation sources lying on this slip plane.
   */
  void insertDislocationSourceList (std::vector<DislocationSource*> dislocationSourceList);

  /**
   * @brief Inserted the provided dislocation source into the slip plane's dislocation source list.
   * @param d The dislocation source that is to be inserted into the silp plane's dislocation source list.
   */
  void insertDislocationSource (DislocationSource* d);
  
  // Access functions
  /**
   * @brief Get the position vector of the extremity whose index is provided as argument.
   * @param i Index of the extremity. Possible values: 0, 1
   * @return Position vector of the extremity indicated by the argument, returned as a variable of type Vector3d.
   */
  Vector3d getExtremity (int i) const;
  
  /**
   * @brief Get the normal vector of the slip plane.
   * @return The normal vector of the slip plane, in a variable of type Vector3d.
   */
  Vector3d getNormal () const;
  
  /**
   * @brief Get the position vector of the slip plane.
   * @details This function returns the position vector of the slip plane. The position vector is redundant because the slip plane is completely defined by its extremities and the normal vector. Nevertheless, this value can be useful to locate the slip plane within a slip system.
   * @return Position vector of the slip plane, in a variable of type Vector3d.
   */
  Vector3d getPosition () const;

  /**
   * @brief Gets a pointer to the co-ordinate system.
   * @details The pointer to the co-ordinate system is useful for entities (defects) that lie on the slip plane.
   * @return Pointer to the instance of CoordinateSystem that is a member of this class.
   */
  CoordinateSystem* getCoordinateSystem();
  
  /**
   * @brief Get the dislocation on the slip plane indicated by the index provided as argument.
   * @details The slip plane contains several dislocations that are stored in a vector container. This function returns the dislocation in that vector that corresponds to the index provided as argument.
   * @param i Index of the required dislocation in the vector. This value should be greater than or equal to 0 and less than the number of dislocations on the slip plane.
   * @param d Pointer to the memory location where the required dislocation is to be stored. Space in memory must be pre-allocated.
   * @return True if the provided index is greater than or equal to 0 and less than the number of dislocations on the slip plane (the memory location pointed to by d is populated with the Dislocation data). Otherwise, the return value is false.
   */
  bool getDislocation (int i, Dislocation* d) const;
  
  /**
   * @brief Get the entire vector container which holds the dislocations lying on this slip plane.
   * @return The vector of dislocations lying on this slip plane.
   */
  std::vector<Dislocation*> getDislocationList ();

  /**
   * @brief Get the number of dislocations.
   * @return The number of dislocations on the slip plane.
   */
  int getNumDislocations () const;
  
  /**
   * @brief Get the dislocation source on the slip plane indicated by the index provided as argument.
   * @details The slip plane contains several dislocation sources that are stored in a vector container. This function returns the dislocation source in that vector that corresponds to the index provided as argument.
   * @param i Index of the required dislocation source in the vector. This value should be greater than or equal to 0 and less than the number of dislocation sources on the slip plane.
   * @param dSource Pointer to the memory location where the required dislocation source is to be stored. Space in memory must be pre-allocated.
   * @return True if the provided index is greater than or equal to 0 and less than the number of dislocation sources on the slip plane (the memory location pointed to by d is populated with the DislocationSource data). Otherwise, the return value is false.
   */
  bool getDislocationSource (int i, DislocationSource* dSource) const;

  /**
   * @brief Get the number of dislocation sources.
   * @return The number of dislocation sources on the slip plane.
   */
  int getNumDislocationSources () const;
  
  /**
   * @brief Get the entire vector container which holds the dislocation sources lying on this slip plane.
   * @return The vector of dislocation sources lying on this slip plane.
   */
  std::vector<DislocationSource *> getDislocationSourceList() const;
  
  /**
   * @brief Get the rotation matrix for this slip plane.
   * @return The rotation matrix of this slip plane, in a variable of type RotationMatrix.
   */
  RotationMatrix getRotationMatrix () const;

  /**
   * @brief Get the time increment for this slip plane in the current iteration.
   * @return The time increment for the slip plane in the current iteration.
   */
  double getTimeIncrement () const;
  
  /**
   * @brief Get the axis (expressed in the global co-ordinate system) of the slip plane's local co-ordinate system, as indicated by the argument. (0, 1, 2)=(x, y, z).
   * @param i Index of the axis that is to be returned. (0, 1, 2)=(x, y, z).
   * @return The desired axis of the slip plane's local co-ordinate system, expressed in the global co-ordinate system. In case of invalid argument, a zero vector is returned.
   */
  Vector3d getAxis (int i) const;

  // Update functions
  /**
   * @brief Update the variable dislcoations with the currest list of dislocations.
   */
  void updateDislcoationList();
  
  // Operations
  /**
   * @brief Calculates the rotation matrix for this slip plane.
   * @details The slip plane has a local co-ordinate system whose axes are the following: z-axis||normal vector and x-axis||slip plane vector (vector joining the extremities). The rotation matrix is calculated in order to carry out transformations between the global and local co-ordinate systems.
   */
  void calculateRotationMatrix ();

  /**
   * @brief Calculates the total stress field experienced by each dislocation and stores it in the Dislocation::totalStress and also puts it at the end of the std::vector<Stress> Dislocation::totalStresses.
   * @details The total stress field is calculated as a superposition of the applied stress field and the stress fields experienced by each dislocation due to every other dislocation in the simulation.
   * @param appliedStress The stress applied externally.
   * @param mu Shear modulus of the material.
   * @param nu Poisson's ratio.
   */
  void calculateDislocationStresses (Stress appliedStress, double mu, double nu);

  /**
   * @brief This function calculates the Peach-Koehler force experienced by each dislocation and stores it in Dislocation::force and puts it at the end of std::vector<Vector3d> Dislocation::forces.
   * @details This function calculates the Peach-Koehler force experienced by each dislocation using the function Dislocation::forcePeachKoehler and the variable Stress Dislocation::totalStress.
   */
  void calculateDislocationForces ();

  /**
   * @brief Calculates the velocities of dislocations and stores them in the variable Vector3d Dislocation::velocity and also puts it at the end of std::vector<Vector3d> Dislocation::velocities.
   * @details The velocities of the dislocations are calculated and stored in the variable Vector3d Dislocation::velocity and also put at the end of std::vector<Vector3d> Dislocation::velocities. The velocities are calculated using the proportionality law between them and the Peach-Koehler force, using the drag coefficient B as the constant of proportionality.
   * param B The drag coefficient.
   */
  void calculateVelocities (double B);

  /**
   * @brief Calculate the time increment based on the velocities of the dislocations.
   * @details In order to avoid the collision of dislocations with similar sign of Burgers vector, it is important to specify a minimum distance of approach between dislocations. When a dislocation reaches this limit, it is pinned. The velocities of the dislocations all being different, a time increment needs to be evaluated, which will limit the distance traveled by the dislocations in a given iteration.
   * @param minDistance Minimum distance of approach between dislocations having Burgers vectors of the same sign.
   * @param minDt The smallest time step permissible. Dislocations having time steps smaller than this are made immobile for the present iteration.
   * @return STL vector container with the ideal time increments for all the dislocations.
   */
  std::vector<double> calculateTimeIncrement (double minDistance, double minDt);

  /**
   * @brief Displaces the dislocations according to their velocities and the time increment.
   * @details This function displaces the dislocations according to the velocities and time increment. If the time increment is smaller than the global time increment, the dislocation moves with this smaller value, effectively moving up to the limiting distance to the next defect and stopping there.
   * @param timeIncrement STL vector containing the timeIncrements of all the dislocations.
   */
  void moveDislocations (std::vector<double> timeIncrement);

  /**
   * @brief The distance of the point pos from the n^th extremity is returned.
   * @param pos Position vector of the point whose distance is to be calculated.
   * @param n Index of the extremity. Can be only 0 or 1. In all other cases 0.0 is returned.
   * @return Distance of the point pos from the n^th extremity of the slip plane.
   */
  double distanceFromExtremity(Vector3d pos, int n);

  /**
   * @brief Sorts the defects on the slip plane in the order of distance from the first extremity.
   */
  void sortDefects ();

  /**
   * @brief Returns a vector containing the stress values at different points along a slip plane.
   * @details The stress field (expressed in the global co-ordinate system) is calculated at points along the slip plane given as argument. This function only takes into account the dislocations present on itself for calculating the stress field.
   * @param points STL vector container with position vectors (Vector3d) of points at which the stress field is to be calculated.
   * @param appliedStress The externally applied stress (in the global co-ordinate system).
   * @param mu Shear modulus of the material in Pa.
   * @param nu Poisson's ratio.
   * @return STL vector container with the full stress tensor expressing the stress field (in the global co-ordinate system) at the points provided as input.
   */
  std::vector<Stress> getSlipPlaneStress_global (std::vector<Vector3d> points, Stress appliedStress, double mu, double nu);

  /**
   * @brief Returns a vector containing the stress values at different points along a slip plane.
   * @details The stress field (expressed in the local co-ordinate system) is calculated at points along the slip plane given as argument. This function only takes into account the dislocations present on itself for calculating the stress field.
   * @param points STL vector container with position vectors (Vector3d) of points at which the stress field is to be calculated.
   * @param appliedStress The externally applied stress (in the global co-ordinate system).
   * @param mu Shear modulus of the material in Pa.
   * @param nu Poisson's ratio.
   * @return STL vector container with the full stress tensor expressing the stress field (in the local co-ordinate system) at the points provided as input.
   */
  std::vector<Stress> getSlipPlaneStress_local (std::vector<Vector3d> points, Stress appliedStress, double mu, double nu);

  // Statistics
  /**
   * @brief Writes the attributes of the slip plane and all defects lying on it.
   * @details This function writes to a file (the name of which is provided in the string filename) all the attributes of the slip plane and all defects lying on it. The file may be useful as statistics or to start the simulation off from an intermediate stage.
   * @param filename The name of the file to which all the attributes are to be written.
   */
  void writeSlipPlane (std::string filename);
  
  /**
   * @brief Writes the stress distribution of stresses (in the slip plane's local co-ordinate system) along the slip plane with the given resolution.
   * @details This function writes out the distribution of stresses (in the slip plane's local co-ordinate system) along the slip plane, with the given resolution. The stress fields of all dislocations and the externally applied stress are all superposed points along the slip plane, and then the stress tensor at this point is transformed to the one in the slip plane's local co-ordinate system to obtain the final stress. The points where the stress is calculated are chosen according to the argument resolution, which provides the number of equally spaced points along the slip plane where the stress field is to be calculated. The output file contains the following information in each row: PointPosition(3) LocalStresses(s_xx s_yy s_zz s_xy s_xz s_yz) GlobalStresses(s_xx s_yy s_zz s_xy s_xz s_yz).
   * @param filename The name of the file into which the data is to be written.
   * @param resolution The number of points at which the stress field is to be calculated.
   * @param param Pointer to the instance of the parameter class which contains all the simulation parameters.
   */
  void writeSlipPlaneStressDistribution (std::string filename, int resolution, Parameter *param);
};

#endif
