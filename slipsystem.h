/**
 * @file slipsystem.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 02/10/2013
 * @brief Definition of the SlipSystem class.
 * @details This file defines the Slipsystem class representing a slip system in the simulation. A slip system is considered to be a set of slip planes, all parallel to each other. The attributes of a slip system are the slip plane normal and the slip direction, both expressed in the frame of reference of the grain.
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

#ifndef SLIPSYSTEM_H
#define SLIPSYSTEM_H

#include <algorithm>

#include "slipPlane.h"
#include "standardSlipSystem.h"

#ifndef SLIPSYSTEM_DEFAULT_NUMBERPLANES
/**
  * @brief The default number of slip planes in the slip system
  */
#define SLIPSYSTEM_DEFAULT_NUMBERPLANES 1
#endif

/**
 * @brief The SlipSystem class representing a slip system in the simulation.
 * @details In the simulation, a slip system is considered to be a collection of slip planes, all parallel to each other. The slip system is characterized by a slip plane normal and a slip direction, both represented in the crystal co-ordinate system, ie, the frame of reference of a grain.
 */
class SlipSystem
{
protected:
    /**
     * @brief Vector container with pointers to slip planes that make up this slip system.
     */
    std::vector<SlipPlane*> slipPlanes;
    /**
     * @brief The slip system's local co-ordinate system.
     */
    CoordinateSystem coordinateSystem;
    /**
     * @brief The normal to the slip planes making up this slip system, expressed in the crystal (grain) co-ordinate system.
     */
    Vector3d slipPlaneNormal;
    /**
     * @brief The direction of the slip plane, normal to the slip plane normal, expressed in the crystal (grain) co-ordinate system.
     */
    Vector3d slipPlaneDirection;
    /**
     * @brief Position of the origin of the slip system.
     */
    Vector3d position;
    /**
     * @brief The externally applied stress, in the base co-ordinate system.
     */
    Stress appliedStress_base;
    /**
     * @brief The externally applied stress, in the local co-ordinate system.
     */
    Stress appliedStress_local;
    /**
     * @brief Time increment for the slip system.
     */
    double dt;

public:
    /**
     * @brief Default constructor for the class SlipSystem.
     */
    SlipSystem();

    /**
     * @brief Constructor for the class SlipSystem, mentioning details of the slip system.
     * @param pos Position of the origin of the slip system, expressed in the base co-ordinate system.
     * @param normal The normal to the slip planes that are present in this slip system, expressed in the base co-ordinate system.
     * @param direction The direction of the slip plane, expressed in the crystal (grain) co-ordinate system.
     * @param base Pointer to the base co-ordinate system.
     * @param s The vector container with pointers to the slip planes that are part of the slip system.
     */
    SlipSystem(Vector3d pos, Vector3d normal, Vector3d direction, CoordinateSystem *base, std::vector<SlipPlane*> s);

    // Assignment functions
    /**
     * @brief Set the position of the origin of the slip system.
     * @param pos The position vector of the origin, in the base co-ordinate system.
     */
    void setPosition (Vector3d pos);
    /**
     * @brief Set the co-ordinate systems for all the slip planes.
     */
    void setSlipPlaneCoordinateSystems ();
    /**
     * @brief Set the normal vector for the slip system.
     * @param normal The normal vector of the slip system, in the base co-ordinate system.
     */
    void setNormal (Vector3d normal);
    /**
     * @brief Set the direction of the slip planes in the slip system.
     * @param direction The direction vector for the slip planes in the slip system.
     */
    void setDirection (Vector3d direction);
    /**
     * @brief Set the base co-ordinate system for the slip system.
     * @param base Pointer to the base co-ordinate system.
     */
    void setBaseCoordinateSystem (CoordinateSystem *base);
    /**
     * @brief Create the slip system's co-ordinate system.
     * @param base Pointer to the base co-ordinate system.
     */
    void createCoordinateSystem (CoordinateSystem *base);
    /**
     * @brief Insert a slip plane into the the list of slip planes.
     * @param s Pointer to the slip plane that is to be inserted.
     */
    void insertSlipPlane (SlipPlane *s);
    /**
     * @brief Insert a  list of slip planes.
     * @param sList STL vector container with pointers to slip planes.
     */
    void insertSlipPlaneList (std::vector<SlipPlane*> sList);
    /**
     * @brief Set the time increment for the slip system
     * @param t The value of the time increment.
     */
    void setTimeIncrement (double t);

    // Access functions
    /**
     * @brief Gets the co-ordinate system of the slip system.
     * @return Pointer to the co-ordinate system of the slip system.
     */
    CoordinateSystem* getCoordinateSystem ();
    /**
     * @brief Get the position vector of the origin of the slip system.
     * @return The position vector of the origin of the slip system.
     */
    Vector3d getPosition () const;
    /**
     * @brief Get the normal to all slip planes in the slip system.
     * @return Normal to the slip system.
     */
    Vector3d getNormal () const;
    /**
     * @brief Get the direction of all slip planes in the slip system.
     * @return The direction of slip planes in the slip system.
     */
    Vector3d getDirection () const;
    /**
     * @brief Get the vector container with pointers to all slip planes.
     * @return Vector container with pointers to all slip planes.
     */
    std::vector<SlipPlane*> getSlipPlanes ();
    /**
     * @brief Get the pointer to a specific slip plane, indicated by the argument. If the argument is greater than the size, a NULL pointer is returned.
     * @param i Index of the slip plane the pointer to which is required.
     * @return Pointer to the slip plane indicated by the argument. If the argument is greater than the size of the vector, a NULL pointer is returned.
     */
    SlipPlane* getSlipPlane (int i);
    /**
     * @brief Get the applied stress in the slip system's local co-ordinate system.
     * @return The applied stress in the slip system's local co-ordinate system.
     */
    Stress getAppliedStress_local () const;
    /**
     * @brief Get the applied stress in the slip system's base co-ordinate system.
     * @return The applied stress in the slip system's base co-ordinate system.
     */
    Stress getAppliedStress_base () const;
    /**
     * @brief Get the slip system time increment.
     * @return The slip system time increment.
     */
    double getTimeIncrement () const;
    /**
     * @brief Get the time increments of all the slip planes.
     * @return STL vector container with the time increments of all the slip planes.
     */
    std::vector<double> getSlipPlaneTimeIncrements ();

    // Sort functions
    /**
     * @brief Sort the slip planes in ascending order based on their positions.
     */
    void sortSlipPlanes ();

    // Clean up functions
    /**
     * @brief Clear the vector containing SlipPlanes.
     */
    void clearSlipPlanes ();

    // Stresses
    /**
     * @brief Calculate the applied stress, in the slip system co-ordinate system.
     * @param appliedStress
     */
    void calculateSlipSystemAppliedStress (Stress appliedStress);
    /**
     * @brief Calculate the applied stress on the slip planes, in their respective co-ordinate systems.
     */
    void calculateSlipPlaneAppliedStress ();
    /**
     * @brief Calculate the total stresses experienced by all defects on all the slip planes.
     * @param mu Shear modulus of the material (Pa).
     * @param nu Poisson's ratio.
     */
    void calculateAllStresses (double mu, double nu);
    /**
     * @brief Calculate the forces on all the dislocations on all the slip planes.
     * @param B The drag coefficient for the dislocations.
     */
    void calculateSlipPlaneDislocationForcesVelocities (double B);

    // Time increment
    /**
     * @brief Calculates the ideal time increments of all the slip planes in the slip system.
     * @param minDistance The minimum distance allowed between adjacent defects.
     * @param minDt The smallest time step allowed.
     * @return STL vector container with the time increments for each slip plane.
     */
    std::vector<double> calculateTimeIncrement (double minDistance, double minDt);

    // Move dislocations on all slip planes
    /**
     * @brief This function moves all the dislocations on all slip planes belonging to the slip system.
     * @details The function uses a constant time increment, and uses the function SlipPlane::moveDislocationsToLocalEquilibrium to bring dislocations to an equilibrium position (if this position is not too far away).
     * @param minDistance The minimum allowed distance between two defects.
     * @param dtGlobal The global time increment.
     * @param mu Shear modulus (Pa).
     * @param nu Poisson's ratio.
     */
    void moveSlipPlaneDislocations (double minDistance, double dtGlobal, double mu, double nu);

    // Check dislocation sources
    /**
     * @brief Check the dislocation sources lying on all the slip planes for dipole emissions.
     * @param timeIncrement The time increment for the current iteration.
     * @param mu Shear modulus (Pa).
     * @param nu Poisson's ratio.
     * @param limitingDistance Minimum distance allowed between two defects.
     */
    void checkSlipPlaneDislocationSources (double timeIncrement, double mu, double nu, double limitingDistance);

    // Local reactions
    /**
     * @brief Check for local reactions on all the slip planes.
     * @param reactionRadius The limiting distance between to defects for which a local reaction can take place.
     */
    void checkSlipPlaneLocalReactions (double reactionRadius);

    // Statistics
    /**
     * @brief Writes out the current time and the positions of all defects on the slip planes that belong to the slip system.
     * @details This function writes out, in a row, the time and the positions of all defects on the slip planes at that time. The function will be called several times during a simulation, so the file must be opened in append mode and the function should insert a newline after each entry.
     * @param fileName Name of the file into which the data is to be written.
     * @param t Value of time.
     */
    void writeAllDefects (std::string fileName, double t);
};

#endif // SLIPSYSTEM_H
