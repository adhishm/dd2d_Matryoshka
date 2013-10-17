/**
 * @file slipPlane.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 23/09/2013
 * @brief Definition of the member functions of the SlipPlane class.
 * @details This file defines the member functions of the SlipPlane class.
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


#include "slipPlane.h"

// Constructors
/**
 * @brief Default constructor.
 * @details The slip plane is initialized with default parameters specified in the file slipPlaneDefaults.h.
 */
SlipPlane::SlipPlane ()
{
    // Initialize the default variables.
    Vector3d pos(DEFAULT_SLIPPLANE_POSITION_0,
                 DEFAULT_SLIPPLANE_POSITION_1,
                 DEFAULT_SLIPPLANE_POSITION_2);
    Vector3d normal(DEFAULT_SLIPPLANE_NORMALVECTOR_0,
                    DEFAULT_SLIPPLANE_NORMALVECTOR_1,
                    DEFAULT_SLIPPLANE_NORMALVECTOR_2);
    Vector3d ends[2];
    ends[0] = Vector3d(DEFAULT_SLIPPLANE_EXTREMITY1_0,
                       DEFAULT_SLIPPLANE_EXTREMITY1_1,
                       DEFAULT_SLIPPLANE_EXTREMITY1_2);
    ends[1] = Vector3d(DEFAULT_SLIPPLANE_EXTREMITY2_0,
                       DEFAULT_SLIPPLANE_EXTREMITY2_1,
                       DEFAULT_SLIPPLANE_EXTREMITY2_2);

    Dislocation* d = new Dislocation();
    DislocationSource* dSource = new DislocationSource();

    std::vector<Dislocation*> dislocationList(1, d);
    std::vector<DislocationSource*> dislocationSourceList(1, dSource);

    *this = SlipPlane(ends, pos, NULL, dislocationList, dislocationSourceList);
}

/**
 * @brief Constructor that specifies all members explicitly.
 * @details The slip plane is initialized with parameters specified in the arguments.
 * @param ends Pointer to an array of type Vector3d, containing the position vectors of the extremities of the slip plane in consecutive locations.
 * @param pos The position vector of the slip plane. (This parameter is useful for locating the slip plane within a slip system)
 * @param base Pointer to the co-ordinate system of the base.
 * @param dislocationList A vector container of type Dislocation* containing the dislocations lying on this slip plane.
 * @param dislocationSourceList A vector container of type DislocationSource* containing the dislocation sources lying on this slip plane.
 */
SlipPlane::SlipPlane (Vector3d *ends, Vector3d pos, CoordinateSystem* base, std::vector<Dislocation*> dislocationList, std::vector<DislocationSource*> dislocationSourceList)
{
    this->setPosition (pos);
    this->createCoordinateSystem(base);
    this->setExtremities(ends);
    this->setNormal(Vector3d::unitVector(2));   // The normal to the slip plane is the Z-axis of the slip system
    this->dislocations = dislocationList;
    this->insertDislocationList(dislocationList);
    this->dislocationSources = dislocationSourceList;
    this->insertDislocationSourceList(dislocationSourceList);


    // Time increment
    this->dt = 0;
}

// Assignment functions
/**
 * @brief Set the extremities of the slip plane.
 * @param ends Pointer to an array of type Vector3d, containing the position vectors of the extremities of the slip plane in consecutive locations.
 */
void SlipPlane::setExtremities (Vector3d *ends)
{
    this->extremities[0] = Defect(GRAINBOUNDARY,
                                  this->coordinateSystem.vector_BaseToLocal(ends[0]),
                                  Vector3d::standardAxes(),
                                  this->getCoordinateSystem());
    this->extremities[1] = Defect(GRAINBOUNDARY,
                                  this->coordinateSystem.vector_BaseToLocal(ends[1]),
                                  Vector3d::standardAxes(),
                                  this->getCoordinateSystem());
}

/**
 * @brief Set the normal vector of the slip plane.
 * @param normal The normal vector of the slip plane.
 */
void SlipPlane::setNormal (Vector3d normal)
{
    this->normalVector = normal;
}

/**
 * @brief Set the position of the slip plane.
 * @param pos The position vector of the slip plane. (This parameter is useful for locating the slip plane within a slip system)
 */
void SlipPlane::setPosition (Vector3d pos)
{
    this->position = pos;
}

/**
 * @brief Creates the co-ordinate system using information from the extremities, position, normal etc. The base co-ordinate system must be provided.
 * @details The co-ordinate system of the slip plane is as follows: X-axis=line joining the extremities; Z-axis=Normal vector; Y-axis=cross(Z,X).
 * @param base Pointer to the base co-ordinate system.
 */
void SlipPlane::createCoordinateSystem(CoordinateSystem* base)
{
    // Calculate the local co-ordinate system
    this->coordinateSystem.setOrigin(this->position);
    // No need to calculate axes because the slip plane has the same axes as the slip system
    this->coordinateSystem.setAxes(Vector3d::standardAxes());
    // Base co-ordinate system
    this->coordinateSystem.setBase(base);
    // Rotation matrix
    this->coordinateSystem.calculateRotationMatrix();
}

/**
 * @brief Insert a list of dislocations into the slip plane's defect list
 * @param dList The list of pointers to dislocations.
 */
void SlipPlane::insertDislocationList (std::vector<Dislocation*> dList)
{
    this->dislocations.insert(this->dislocations.end(),
                              dList.begin(),
                              dList.end());
}

/**
 * @brief Inserted the provided dislocation into the slip plane's dislocation list.
 * @param d Pointer to the dislocation that is to be inserted into the silp plane's dislocation list.
 */
void SlipPlane::insertDislocation (Dislocation *d)
{
    this->dislocations.push_back(d);
}

/**
 * @brief Insert a list of dislocation sources on the slip plane.
 * @param dislocationSourceList A vector container of type DislocationSource* containing pointers the dislocation sources lying on this slip plane.
 */
void SlipPlane::insertDislocationSourceList (std::vector<DislocationSource*> dislocationSourceList)
{
    this->dislocationSources.insert(dislocationSources.end(),
                                    dislocationSourceList.begin(),
                                    dislocationSourceList.end());
}

/**
 * @brief Inserted the provided dislocation source into the slip plane's dislocation source list.
 * @param d Pointer the dislocation source that is to be inserted into the silp plane's dislocation source list.
 */
void SlipPlane::insertDislocationSource (DislocationSource *d)
{
    this->dislocationSources.push_back(d);
}

/**
 * @brief Set the time increment value for the slip plane.
 * @param t The value of the time increment.
 */
void SlipPlane::setTimeIncrement (double t)
{
    this->dt = t;
}

/**
 * @brief Set the Base CoordinateSystem for the slip plane.
 * @param base Pointer to the base coordinate system.
 */
void SlipPlane::setBaseCoordinateSystem (CoordinateSystem *base)
{
    this->coordinateSystem.setBase(base);
}

// Access functions
/**
 * @brief Get the position vector of the extremity whose index is provided as argument.
 * @param i Index of the extremity. Possible values: 0, 1
 * @return Position vector of the extremity indicated by the argument, returned as a variable of type Vector3d.
 */
Vector3d SlipPlane::getExtremity (int i) const
{
    if (i==0 || i==1)
    {
        return (this->extremities[i].getPosition());
    }
    else
    {
        return (Vector3d());
    }
}

/**
 * @brief Get the normal vector of the slip plane.
 * @return The normal vector of the slip plane, in a variable of type Vector3d.
 */
Vector3d SlipPlane::getNormal () const
{
    return (this->normalVector);
}

/**
 * @brief Get the position vector of the slip plane.
 * @details This function returns the position vector of the slip plane. The position vector is redundant because the slip plane is completely defined by its extremities and the normal vector. Nevertheless, this value can be useful to locate the slip plane within a slip system.
 * @return Position vector of the slip plane, in a variable of type Vector3d.
 */
Vector3d SlipPlane::getPosition () const
{
    return (this->position);
}

/**
 * @brief Gets a pointer to the co-ordinate system.
 * @details The pointer to the co-ordinate system is useful for entities (defects) that lie on the slip plane.
 * @return Pointer to the instance of CoordinateSystem that is a member of this class.
 */
CoordinateSystem* SlipPlane::getCoordinateSystem()
{
    return(&(this->coordinateSystem));
}

/**
 * @brief Get the dislocation on the slip plane indicated by the index provided as argument.
 * @details The slip plane contains several dislocations that are stored in a vector container. This function returns the dislocation in that vector that corresponds to the index provided as argument.
 * @param i Index of the required dislocation in the vector. This value should be greater than or equal to 0 and less than the number of dislocations on the slip plane.
 * @param d Pointer to the memory location where the required dislocation is to be stored. Space in memory must be pre-allocated.
 * @return True if the provided index is greater than or equal to 0 and less than the number of dislocations on the slip plane (the memory location pointed to by d is populated with the Dislocation data). Otherwise, the return value is false.
 */
bool SlipPlane::getDislocation (int i, Dislocation* d) const
{
    if (i>=0 && i<(this->dislocations.size())) {
        *d = *(this->dislocations[i]);
        return (true);
    }
    else {
        return (false);
    }
}

/**
 * @brief Get the entire vector container which holds the pointers to all the defects
 * @return The vector of the defects lying on the slip plane.
 */
std::vector<Defect*> SlipPlane::getDefectList ()
{
    return (this->defects);
}

/**
 * @brief Return the positions of all the defects, expressed in the slip plane base co-ordinate system.
 * @return STL vector container with position vectors of all the defects, expressed in the the slip plane base co-ordinate system.
 */
std::vector<Vector3d> SlipPlane::getAllDefectPositions_base ()
{
    // Get positions in loal system
    std::vector<Vector3d> defectPositions = this->getAllDefectPositions_local();
    std::vector<Vector3d>::iterator defect_it = defectPositions.begin();

    while (defect_it!=defectPositions.end()) {
        *defect_it = this->coordinateSystem.vector_LocalToBase(*defect_it);
        defect_it++;
    }

    return (defectPositions);
}

/**
 * @brief Return the positions of all the defects, expressed in the slip plane local co-ordinate system.
 * @return STL vector container with position vectors of all the defects, expressed in the the slip plane local co-ordinate system.
 */
std::vector<Vector3d> SlipPlane::getAllDefectPositions_local ()
{
    std::vector<Vector3d> defectPositions (this->getNumDefects(),Vector3d());
    std::vector<Vector3d>::iterator position_it;

    std::vector<Defect*>::iterator defect_it;
    Defect* defect;

    defect_it = this->defects.begin();
    position_it = defectPositions.begin();
    while (defect_it!=this->defects.end()) {
        defect = *defect_it;
        *position_it = defect->getPosition();
        defect_it++;
        position_it++;
    }

    return (defectPositions);
}

/**
 * @brief Return the number of defects lying in the slip plane.
 * @return The number of defects lying in the slip plane.
 */
int SlipPlane::getNumDefects () const
{
    return (this->defects.size());
}

/**
 * @brief Get the entire vector container which holds the dislocations lying on this slip plane.
 * @return The vector of dislocations lying on this slip plane.
 */
std::vector<Dislocation*> SlipPlane::getDislocationList ()
{
    return (this->dislocations);
}

/**
 * @brief Get the number of dislocations.
 * @return The number of dislocations on the slip plane.
 */
int SlipPlane::getNumDislocations () const
{
    return (this->dislocations.size());
}

/**
 * @brief Get the dislocation source on the slip plane indicated by the index provided as argument.
 * @details The slip plane contains several dislocation sources that are stored in a vector container. This function returns the dislocation source in that vector that corresponds to the index provided as argument.
 * @param i Index of the required dislocation source in the vector. This value should be greater than or equal to 0 and less than the number of dislocation sources on the slip plane.
 * @param dSource Pointer to the memory location where the required dislocation source is to be stored. Space in memory must be pre-allocated.
 * @return True if the provided index is greater than or equal to 0 and less than the number of dislocation sources on the slip plane (the memory location pointed to by d is populated with the DislocationSource data). Otherwise, the return value is false.
 */
bool SlipPlane::getDislocationSource (int i, DislocationSource* dSource) const
{
    if (i>=0 && i<this->dislocationSources.size ())
    {
        *dSource = *(this->dislocationSources[i]);
        return (true);
    }
    else
    {
        return (false);
    }
}

/**
 * @brief Get the entire vector container which holds the dislocation sources lying on this slip plane.
 * @return The vector of dislocation sources lying on this slip plane.
 */
std::vector<DislocationSource*> SlipPlane::getDislocationSourceList () const
{
    return (this->dislocationSources);
}

/**
 * @brief Get the number of dislocation sources.
 * @return The number of dislocation sources on the slip plane.
 */
int SlipPlane::getNumDislocationSources () const
{
    return (this->dislocationSources.size ());
}

/**
 * @brief Get the rotation matrix for this slip plane.
 * @return The rotation matrix of this slip plane, in a variable of type RotationMatrix.
 */
RotationMatrix SlipPlane::getRotationMatrix () const
{
    return (this->coordinateSystem.getRotationMatrix());
}

/**
 * @brief Get the time increment for this slip plane in the current iteration.
 * @return The time increment for the slip plane in the current iteration.
 */
double SlipPlane::getTimeIncrement () const
{
    return ( this->dt );
}

/**
 * @brief Get the axis (expressed in the global co-ordinate system) of the slip plane's local co-ordinate system, as indicated by the argument. (0, 1, 2)=(x, y, z).
 * @param i Index of the axis that is to be returned. (0, 1, 2)=(x, y, z).
 * @return The desired axis of the slip plane's local co-ordinate system, expressed in the global co-ordinate system. In case of invalid argument, a zero vector is returned.
 */
Vector3d SlipPlane::getAxis (int i) const
{
    Vector3d axis;

    if (i==2)
    {
        // Z-axis
        axis = this->normalVector;
    }

    if (i==0)
    {
        // X-axis
        Vector3d *e1 = new Vector3d;
        Vector3d *e2 = new Vector3d;

        *e1 = this->extremities[0].getPosition();
        *e2 = this->extremities[1].getPosition();
        axis = ((*e2) - (*e1));

        delete(e1);  e1 = NULL;
        delete(e2);  e2 = NULL;
    }

    if (i==1)
    {
        // Y-axis = Z x X
        axis = this->getAxis(2) ^ this->getAxis(0);
    }

    return ( axis.normalize() );
}

/**
 * @brief Returns the applied stress expressed in the local co-ordinate system.
 * @return Applied stress in the local co-ordinate system.
 */
Stress SlipPlane::getAppliedStress_local () const
{
    return (this->appliedStress_local);
}

/**
 * @brief Returns the applied stress expressed in the base co-ordinate system.
 * @return Applied stress in the base co-ordinate system.
 */
Stress SlipPlane::getAppliedStress_base() const
{
    return (this->appliedStress_base);
}

/**
 * @brief Finds the dislocation corresponding to a member of the vector defects.
 * @param defect_iterator Iterator indicating an element of the vector SlipPlane::defects.
 * @return Pointer to the dislocation corresponding to the defect given by the iterator.
 */
Dislocation* SlipPlane::findDislocation(std::vector<Defect*>::iterator defect_iterator)
{
    /*
    std::vector<Defect*>::iterator dit = this->defects.begin();
    std::vector<Dislocation*>::iterator dislocation_iterator = this->dislocations.begin();

    while (dit != this->defects.end()) {
        if ((*dit)->getDefectType() == DISLOCATION) {
            // This defect is a dislocation - check if it is the one we need
            if (dit == defect_iterator) {
                // This is the dislocation we need
                return ( *dislocation_iterator );
            }
            else {
                // This is not the dislocation we need - increment the count
                dislocation_iterator++;
                dit++;
            }
        }
    }

    // If we are still here, the dislocation was not found
    return (NULL);
    */

    std::vector<Dislocation*>::iterator disl = this->findDislocationIterator(defect_iterator);

    if (disl == this->dislocations.end()) {
        // The dislocation was not found
        return (NULL);
    }
    else {
        return ( *disl );
    }
}

/**
 * @brief Finds the dislocation corresponding to a member of the vector defects.
 * @param defect_iterator Iterator indicating an element of the vector SlipPlane::defects.
 * @return Iterator indicating the element of SlipPlane::dislocations corresponding to the defect provided in the argument.
 */
std::vector<Dislocation*>::iterator SlipPlane::findDislocationIterator (std::vector<Defect*>::iterator defect_iterator)
{
    std::vector<Defect*>::iterator dit = this->defects.begin();
    std::vector<Dislocation*>::iterator dislocation_iterator = this->dislocations.begin();

    while (dit != this->defects.end()) {
        if ((*dit)->getDefectType() == DISLOCATION) {
            // This defect is a dislocation - check if it is the one we need
            if (dit == defect_iterator) {
                // This is the dislocation we need
                return ( dislocation_iterator );
            }
            else {
                // This is not the dislocation we need - increment the count
                dislocation_iterator++;
                dit++;
            }
        }
        else {
            dit++;
        }
    }

    // If we are still here, the dislocation was not found
    return (this->dislocations.end());
}

// Update functions
/**
 * @brief Update the defects vector.
 * @details The vector defects contains pointers to all defects lying on the slip plane. They are also sorted in ascending order of their distance from the first extremity of the slip plane.
 */
void SlipPlane::updateDefects()
{
    // Assign the extremities
    this->clearDefects();
    this->defects.push_back(this->extremities);
    this->defects.push_back(this->extremities + 1);
    // Insert the dislocations
    this->defects.insert(this->defects.begin()+1,
                         this->dislocations.begin(),
                         this->dislocations.end());
    // Insert the dislocation sources
    this->defects.insert(this->defects.begin()+1,
                         this->dislocationSources.begin(),
                         this->dislocationSources.end());
    this->sortDefects();
}

/**
 * @brief Clear the vector dislocations leaving the container with zero size.
 */
void SlipPlane::clearDislocations()
{
    this->dislocations.clear();
}

/**
 * @brief Clear the vector dislocationSources leaving the container with zero size.
 */
void SlipPlane::clearDislocationSources()
{
    this->dislocationSources.clear();
}

/**
 * @brief Clear the vector defects leaving the container with zero size.
 */
void SlipPlane::clearDefects()
{
    this->defects.clear();
}

// Operations
/**
 * @brief Calculates the rotation matrix for this slip plane.
 * @details The slip plane has a local co-ordinate system whose axes are the following: z-axis||normal vector and x-axis||slip plane vector (vector joining the extremities). The rotation matrix is calculated in order to carry out transformations between the global and local co-ordinate systems.
 */
void SlipPlane::calculateRotationMatrix ()
{
    this->coordinateSystem.calculateRotationMatrix();
}

// Treat defects
/**
 * @brief This function calculates the total stress fields on all defects lying on the slip plane and stores the stress field tensors in the members Defect::totalStress and Defect::totalStresses.
 * @param mu Shear modulus of the material.
 * @param nu Poisson's ratio.
 */
void SlipPlane::calculateDefectStresses (double mu, double nu)
{
    std::vector<Defect*>::iterator destinationDefect_it;
    std::vector<Defect*>::iterator sourceDefect_it;

    Defect *destinationDefect;
    Defect *sourceDefect;

    Stress s;
    Vector3d p;

    for (destinationDefect_it=this->defects.begin(); destinationDefect_it!=this->defects.end(); destinationDefect_it++) {
        s = this->appliedStress_local;
        destinationDefect = *destinationDefect_it;
        p = destinationDefect->getPosition();
        for (sourceDefect_it=this->defects.begin(); sourceDefect_it!=this->defects.end(); sourceDefect_it++) {
            sourceDefect = *sourceDefect_it;
            // Superpose the stress fields of all other defects
            s = s + sourceDefect->stressField(p, mu, nu);
        }
        destinationDefect->setTotalStress(s);
    }
}

/**
 * @brief This function looks for defects lying between the two points p0 and p1 provided. The elements of the vector are ordered such that they appear as they would when travelling from p0 to p1.
 * @details The function creates a vector container with pointers to defects lying between two given position vectors p0 and p1 (both specified in the slip plane co-ordinate system). The order of pointers within the vector is the one that one would have when travels from p0 to p1. In the case where there are no defects lying in between these two points, an empty container is returned.
 * @param p0 The position vector, in the slip-plane co-ordinate system, of the first point.
 * @param p1 The position vector, in the slip-plane co-ordinate system, of the second point.
 * @return A vector container with the defects that lie between p0 and p1, in the order as they would appear when travelling from p0 to p1.
 */
std::vector<Defect*> SlipPlane::findDefectsBetweenPoints (Vector3d p0, Vector3d p1)
{
    // The vector that will hold the pointers to the defects lying within the range
    std::vector<Defect*> defectList;

    // Since we are dealing only with the slip plane, extract the x co-ordinates of the limiting points
    double x0 = p0.getValue(0);
    double x1 = p1.getValue(0);

    // Iterator and pointer for browsing the defect list
    std::vector<Defect*>::iterator defects_it;
    std::vector<Defect*>::reverse_iterator defects_rit;
    Defect *defect;
    Vector3d pd;
    double xd;

    if (x0 < x1) {
        // The direction of travel from p0 to p1 is the same as the positive x-direction of the slip plane
        for (defects_it=this->defects.begin(); defects_it!=this->defects.end(); defects_it++) {
            defect = *defects_it;
            pd = defect->getPosition();
            xd = pd.getValue(0);
            if ( (xd>x0) && (xd<x1) ) {
                // The defect lies in between
                defectList.push_back(defect);
            }
        }
    }
    else {
        // The direction of travel from p0 to p1 is opposite to the positive x-direction of the slip plane
        for (defects_rit=this->defects.rbegin(); defects_rit!=this->defects.rend(); ++defects_rit) {
            defect = *defects_rit;
            pd = defect->getPosition();
            xd = pd.getValue(0);
            if ( (xd>x1) && (xd<x0) ) {
                // The defect lies in between
                defectList.push_back(defect);
            }
        }
    }

    return (defectList);

}

// Treat the dislocations
/**
 * @brief Calculates the total stress field experienced by each dislocation and stores it in the Dislocation::totalStress and also puts it at the end of the std::vector<Stress> Dislocation::totalStresses.
 * @details The total stress field is calculated as a superposition of the applied stress field and the stress fields experienced by each dislocation due to every other dislocation in the simulation.
 * @param mu Shear modulus of the material.
 * @param nu Poisson's ratio.
 */
void SlipPlane::calculateDislocationStresses (double mu, double nu)
{
    std::vector<Dislocation*>::iterator disl_it;  // Iterator for each dislocation
    std::vector<Defect*>::iterator defect_it;   // Iterator for defects
    Stress s;                                // Variable for stress

    Dislocation* disl;
    Defect* defect;

    Vector3d p;                              // Position vector

    for (disl_it=this->dislocations.begin(); disl_it!=this->dislocations.end(); disl_it++) {
        s = this->appliedStress_local;
        disl = *disl_it;
        p = disl->getPosition();
        for (defect_it = this->defects.begin(); defect_it!=this->defects.end(); defect_it++) {
            defect = *defect_it;
            // Superpose the stress fields of all other dislocations
            s = s + defect->stressField(p, mu, nu);
        }
        disl->setTotalStress(s);
    }
}

/**
 * @brief This function calculates the Peach-Koehler force experienced by each dislocation and stores it in Dislocation::force and puts it at the end of std::vector<Vector3d> Dislocation::forces.
 * @details This function calculates the Peach-Koehler force experienced by each dislocation using the function Dislocation::forcePeachKoehler and the variable Stress Dislocation::totalStress.
 */
void SlipPlane::calculateDislocationForces ()
{
    std::vector<Dislocation*>::iterator d;  // Iterator for dislocations

    for (d = this->dislocations.begin(); d!=this->dislocations.end(); d++)
    {
        (*d)->setTotalForce ( (*d)->forcePeachKoehler((*d)->getTotalStress()) );
    }
}

/**
 * @brief Calculates the velocities of dislocations and stores them in the variable Vector3d Dislocation::velocity and also puts it at the end of std::vector<Vector3d> Dislocation::velocities.
 * @details The velocities of the dislocations are calculated and stored in the variable Vector3d Dislocation::velocity and also put at the end of std::vector<Vector3d> Dislocation::velocities. The velocities are calculated using the proportionality law between them and the Peach-Koehler force, using the drag coefficient B as the constant of proportionality.
 * param B The drag coefficient.
 */
void SlipPlane::calculateDislocationVelocities (double B)
{
    std::vector<Dislocation*>::iterator d;  // Iterator for dislocations
    Dislocation* disl;

    Vector3d v;

    for ( d=this->dislocations.begin(); d != this->dislocations.end(); d++)
    {
        disl = *d;
        if (disl->isMobile())
        {
            // Velocity directly proportional to Peach-Koehler force
            v =  disl->getTotalForce() * (1.0/B);

            // No climb is allowed for the moment. Only gliding along slip plane line.
            v = Vector3d(v.getValue(0), 0.0, 0.0);
        }
        else
        {
            v = Vector3d(0.0, 0.0, 0.0);
        }

        disl->setVelocity (v);
    }
}

/**
 * @brief Displaces the dislocations according to their velocities and the time increment.
 * @details This function displaces the dislocations according to the velocities and time increment. If the time increment is smaller than the global time increment, the dislocation moves with this smaller value, effectively moving up to the limiting distance to the next defect and stopping there.
 * @param timeIncrement STL vector containing the timeIncrements of all the dislocations.
 */
void SlipPlane::moveDislocations (std::vector<double> timeIncrement)
{
    std::vector<Dislocation*>::iterator d;
    std::vector<double>::iterator t;
    Vector3d p;

    d = this->dislocations.begin();
    t = timeIncrement.begin();

    while (d != this->dislocations.end())
    {
        p = (*d)->getPosition();
        if (*t <= this->dt)
        {
            // Move the dislocation up to the defect and stop it there
            p += (*d)->getVelocity() * (*t);
        }
        else
        {
            p += (*d)->getVelocity() * (this->dt);
        }
        (*d)->setPosition(p);

        d++;
        t++;
    }
}

/**
 * @brief Function to move dislocations to local a equilibrium position.
 * @details For each dislocation, an equilibrium position is calculated where the interaction force from the next defect, in the direction of the balances the total Peach-Koehler force experienced by it. If the next defect has no stress field, then the dislocation is moved to within the minimum permissible distance.
 * @param minDistance Minimum distance of approach between two defects.
 * @param mu Shear modulus in Pascals.
 * @param nu Poisson's ratio.
 * @param dtGlobal The global time increment.
 */
void SlipPlane::moveDislocationsToLocalEquilibrium(double minDistance, double dtGlobal, double mu, double nu)
{
    std::vector<Defect*>::iterator dit; // Iterator for defects

    // Dislocation access variables
    int count_disl;
    Dislocation* disl;

    // Defect access variables
    int count_def;
    Defect* def;

    Vector3d velocity;
    int vSign;  // The direction of the dislocation velocity
    double maxDistance; // Maximum distance allowed for dislocation velocity and global time increment
    Vector3d equilibriumPosition;
    Vector3d pDisl, pDef, middle, pDislPrime;
    double distance_disl_def;
    double distance_disl_eq;

    // Vector container with the new positions of defects on the slip plane. Initialized with zero vectors.
    std::vector<Vector3d> newPositions(this->getNumDefects(), Vector3d::zeros());
    std::vector<Vector3d>::iterator pit;    // Position iterator

    count_def = 0;
    count_disl = 0;
    for (dit=this->defects.begin(); dit!=this->defects.end(); dit++,count_def++) {
        if ((*dit)->getDefectType() == DISLOCATION) {
            // The only defect that will move
            disl = this->dislocations[count_disl++];
            velocity = disl->getVelocity();
            // Maximum distance
            maxDistance = velocity.magnitude() * dtGlobal;
            // Direction of movement
            vSign = sgn(velocity.getValue(0));
            switch (vSign) {
            case -1:
                // The dislocation is moving towards the previous defect.
                def = *(dit-1);
                break;
            case 0:
                // The dislocation is not moving at all - do nothing
                continue;
                break;
            case 1:
                // The dislocation is moving towards the next defect.
                def = *(dit+1);
                break;
            default:
                // Unknown behaviour - do nothing
                continue;
                break;
            }

            /* Treat the interaction according to the type of defect */

            // Find equilibrium position
            equilibriumPosition = def->equilibriumDistance(disl->getTotalForce(), disl->getBurgers(), mu, nu);
            pDisl = disl->getPosition();
            pDef = def->getPosition();

            // Check for overtaking
            distance_disl_def = (pDef - pDisl).magnitude();
            distance_disl_eq  = (equilibriumPosition - pDisl).magnitude();

            if (distance_disl_eq >= (distance_disl_def - minDistance)) {
                // There is an imminent collision
                // Treat according to the type of defect with which it may collide
                switch (def->getDefectType()) {
                case DISLOCATION :
                    // This is a dislocation of opposite Burgers vector.
                    middle = ( pDisl + pDef ) * 0.5;    // Mid-point between the two
                    pDislPrime = middle - ( (pDef - pDisl) * (minDistance / distance_disl_def) );
                    break;
                case GRAINBOUNDARY :
                    // The other defect is a grain boundary
                    // The equilibrium position should be a point at the minDistance
                    // in order to create a pile up
                    pDislPrime = pDef - ( (pDef - pDisl) * (minDistance / distance_disl_def) );
                    break;
                case FREESURFACE :
                    // The next defect is a free surface
                    // The FREESURFACE is a sink for dislocations
                    pDislPrime = pDef;
                    break;
                case FRANKREADSOURCE:
                    // The next defect is a Frank-Read source
                    // The dislocation is allowed to approach it as it would approach another dislocation
                    middle = ( pDisl + pDef ) * 0.5;    // Mid-point between the two
                    pDislPrime = middle - ( (pDef - pDisl) * (minDistance / distance_disl_def) );
                    break;
                default :
                    // Unknown defect type - do nothing
                    pDislPrime = pDisl;
                    break;
                }
            }
            else {
                // No collision - so it is safe to move the dislocation to the equilibrium position
                pDislPrime = equilibriumPosition;
            }

            // Check how far the dislocation has to go to reach the equilibrium position
            if ( (pDislPrime - pDisl).magnitude() <= maxDistance ) {
                // The new position is not too far
                newPositions[count_def] = pDislPrime;
            }
            else {
                // Too far. Move only by maxDistance
                newPositions[count_def] = pDisl + (Vector3d(vSign,0.0,0.0) * maxDistance);
            }
        }
        else {
            // This defect is not a dislocation - it will remain immobile
            newPositions[count_def] = (*dit)->getPosition();
        }
    }

    // Populate the new positions into the defects
    for (pit=newPositions.begin(), dit = this->defects.begin(); pit != newPositions.end(); pit++, dit++) {
        (*dit)->setPosition(*pit);
    }
}

// Treat dislocation sources
/**
 * @brief This function calculates the total stress field acting on each dislocation source lying in the slip plane by superposing contributions from all defects in the simulation, and stores it in the data members Defect::totalStress and Defect::totalStresses.
 * @param mu Shear modulus of the material.
 * @param nu Poisson's ratio.
 */
void SlipPlane::calculateDislocationSourceStresses(double mu, double nu)
{
    std::vector<DislocationSource*>::iterator dSource_it;   // Iterator for each dislocation source
    std::vector<Defect*>::iterator defect_it;               // Iterator for all defects
    Stress s;                                               // Variable for stress

    DislocationSource *dSource;
    Defect *defect;

    Vector3d p;                                             // Position vector

    for (dSource_it=this->dislocationSources.begin(); dSource_it!=this->dislocationSources.end(); dSource_it++) {
        s = this->appliedStress_local;
        dSource = *dSource_it;
        p = dSource->getPosition();
        for (defect_it=this->defects.begin(); defect_it!=this->defects.end(); defect_it++) {
            defect = *defect_it;
            // Superpose the stress fields of all other defects
            s = s + defect->stressField(p, mu, nu);
        }
        dSource->setTotalStress(s);
    }
}

/**
 * @brief Checks all the dislocation sources for emission of dislocation dipoles.
 * @param timeIncrement The time increment at this iteration. This is required to measure the progress of a dislocation source till emission of a dipole.
 * @param mu Shear modulus of the material.
 * @param nu Poisson's ratio.
 * @param limitingDistance Minimum distance permitted between adjacent defects.
 */
void SlipPlane::checkDislocationSources (double timeIncrement, double mu, double nu, double limitingDistance)
{
    // Iterator and pointer to browse the dislocation source vector
    std::vector<DislocationSource*>::iterator dSource_it;
    DislocationSource *dSource;

    // Dipole nucleation length and stress at the dislocation source
    double Lnuc;
    Stress tau;

    // Pointers to the two dislocations that will form the dipoles that may be emitted
    Dislocation *d0;
    Dislocation *d1;

    // Position vectors for the dislocation source and the dipole emitted
    Vector3d ps, p0, p1;
    Vector3d pn;    // New position for the dislocation, if needed

    // Vector container for defects lying in between two positions
    std::vector<Defect*> defectsLyingInBetween;
    Defect *nearestDefect;

    for (dSource_it=this->dislocationSources.begin(); dSource_it!=this->dislocationSources.end(); dSource_it++) {
        dSource = *dSource_it;
        tau = dSource->getTotalStress();
        // Increment the time count according to the motion of the dislocation within the source
        dSource->incrementTimeCount( timeIncrement * dSource->checkStress(tau) );
        // Check if a dipole should be emitted
        if (dSource->ifEmitDipole()) {
            // Yes, a dipole will be emitted
            Lnuc = dSource->dipoleNucleationLength(tau.getValue(0,2),mu,nu);
            // Allocate memory to the new dislocations
            d0 = new Dislocation;
            d1 = new Dislocation;
            dSource->emitDipole(Lnuc, d0, d1);
            // Check for the positions of the new dislocations - they should not cross existing defects
            ps = dSource->getPosition();
            p0 = d0->getPosition();
            p1 = d1->getPosition();

            // Check for defects lying between the source and d0
            defectsLyingInBetween = this->findDefectsBetweenPoints(ps, p0);
            if ( ! defectsLyingInBetween.empty() ) {
                // There are defects lying between the source and the theoretical position of the dislocation
                nearestDefect = defectsLyingInBetween.front();
                pn = nearestDefect->getPosition();
                if ((ps-pn).magnitude() >= limitingDistance) {
                    // New position for the dislocation - within limitingDistance of the defect nearest to the source
                    d0->setPosition( pn + ((ps-pn).normalize() * limitingDistance) );
                }
                else {
                    // The nearest defect is too close - place the dislocation midway between the two
                    d0->setPosition((pn+ps)*0.5);
                }
            }
            defectsLyingInBetween.clear();

            // Check for defects lying between the source and d1
            defectsLyingInBetween = this->findDefectsBetweenPoints(ps, p1);
            if ( ! defectsLyingInBetween.empty() ) {
                // There are defects lying between the source and the theoretical position of the dislocation
                nearestDefect = defectsLyingInBetween.front();
                pn = nearestDefect->getPosition();
                if ((ps-pn).magnitude() >= limitingDistance) {
                    // New position for the dislocation - within limitingDistance of the defect nearest to the source
                    d1->setPosition( pn + ((ps-pn).normalize() * limitingDistance) );
                }
                else {
                    // The nearest defect is too close - place the dislocation midway between the two
                    d1->setPosition((pn+ps)*0.5);
                }
            }
            defectsLyingInBetween.clear();

            // The new dislocations are created and placed on the slip plane
            // They should now be inserted into the slip plane list
            this->insertDislocation(d0);
            this->insertDislocation(d1);
            // Sort dislocations
            this->sortDislocations();
            // Update defects
            this->updateDefects();
        }
    }

}

// Time increment
/**
 * @brief Calculate the time increment based on the velocities of the dislocations.
 * @details In order to avoid the collision of dislocations with similar sign of Burgers vector, it is important to specify a minimum distance of approach between dislocations. When a dislocation reaches this limit, it is pinned. The velocities of the dislocations all being different, a time increment needs to be evaluated, which will limit the distance traveled by the dislocations in a given iteration.
 * @param minDistance Minimum distance of approach between dislocations having Burgers vectors of the same sign.
 * @param minDt The smallest time step permissible. Dislocations having time steps smaller than this are made immobile for the present iteration.
 * @return STL vector container with the ideal time increments for all the dislocations.
 */
std::vector<double> SlipPlane::calculateTimeIncrement (double minDistance, double minDt)
{
    // Get the number of dislocations
    int nDisl = this->dislocations.size();

    // Vector of time increments
    std::vector<double> timeIncrement(nDisl, LARGE_NUMBER);

    int i=0;         // Counter for the loop
    double t1, t2;
    double dtMin;  // Minimum time increment

    std::vector<Defect*>::iterator defect_it;
    Defect* defect;

    for (defect_it=this->defects.begin(); defect_it!=this->defects.end(); defect_it++) {
        defect = *defect_it;
        if (defect->getDefectType() == DISLOCATION) {
            // Only dislocations have a time increment
            t1 = defect->idealTimeIncrement(minDistance, *(defect_it-1));
            t2 = defect->idealTimeIncrement(minDistance, *(defect_it+1));
            timeIncrement[i++] = std::min(t1, t2);
        }
    }

    // Find smallest non-zero time increment
    dtMin = LARGE_NUMBER;
    for (i=0; i<nDisl; i++)
    {
        if (timeIncrement[i] > 0.0)
        {
            if (timeIncrement[i] < dtMin)
            {
                dtMin = timeIncrement[i];
            }
        }
    }

    this->dt = std::max ( dtMin, minDt );  // Choose dtMin greater than minDt.
    if (this->dt == LARGE_NUMBER) {
        // None of the time increments were smaller than LARGE_NUMBER
        this->dt = minDt;
    }
    return (timeIncrement);
}



/**
 * @brief The distance of the point pos from the n^th extremity is returned.
 * @param pos Position vector of the point whose distance is to be calculated.
 * @param n Index of the extremity. Can be only 0 or 1. In all other cases 0.0 is returned.
 * @return Distance of the point pos from the n^th extremity of the slip plane.
 */
double SlipPlane::distanceFromExtremity(Vector3d pos, int n)
{
    if (n!=0 && n!=1)
    {
        return (0.0);
    }

    Vector3d r = this->extremities[n].getPosition();
    return ( (r-pos).magnitude() );
}

/**
 * @brief Sorts the defects on the slip plane in the order of distance from the first extremity.
 */
void SlipPlane::sortDefects ()
{
    std::sort (this->defects.begin(), this->defects.end(), Defect::compareDefectPositions);
}

/**
 * @brief Sorts the dislocations on the slip plane in ascending order of distance from the first extremity.
 */
void SlipPlane::sortDislocations ()
{
    std::sort (this->dislocations.begin(), this->dislocations.end(), Defect::compareDefectPositions);
}

/**
 * @brief Sorts the dislocations on the slip plane in ascending order of distance from the first extremity.
 */
void SlipPlane::sortDislocationSources ()
{
    std::sort (this->dislocationSources.begin(), this->dislocationSources.end(), Defect::compareDefectPositions);
}

// Stresses
/**
 * @brief Calculates the stress applied on the slip plane given the stress in the base system.
 * @details Calculates the stress applied on the slip plane given the stress in the base system. The result is stored in the variable appliedStress_local.
 * @param appliedStress The stress applied on the slip plane, expressed in the base co-ordinate system.
 */
void SlipPlane::calculateSlipPlaneAppliedStress (Stress appliedStress)
{
    this->appliedStress_base = appliedStress;
    this->appliedStress_local = this->coordinateSystem.stress_BaseToLocal(appliedStress);
}

/**
 * @brief Calculate the total stress field due to all defects on this slip plane, at a position p.
 * @details All defects in the simulation have a stress field (some of them have zero stress fields). This function superposes the stress fields of all defects lying on the slip plane at a position p provided as argument. Both the position p and the stress field returned are expressed in the base co-ordinate system.
 * @param p Position vector, in the base co-ordinate system, of the point at which the stress field is to be calculated.
 * @param mu Shear modulus (Pa).
 * @param nu Poisson's ratio.
 * @return Stress field, in the base co-ordinate system, due to all defects on this slip plane.
 */
Stress SlipPlane::slipPlaneStressField (Vector3d p, double mu, double nu)
{
    // Convert position vector to local system
    Vector3d p_local = this->coordinateSystem.vector_BaseToLocal(p);
    // Stress
    Stress s;
    // Iterator for defects
    std::vector<Defect*>::iterator dit;
    Defect *d;

    for (dit=this->defects.begin(); dit!=this->defects.end(); dit++) {
        d = *dit;
        s += d->stressField(p_local, mu, nu);
    }

    return (this->coordinateSystem.stress_LocalToBase(s));
}

/**
 * @brief Returns a vector containing the stress values at different points along a slip plane.
 * @details The stress field (expressed in the global co-ordinate system) is calculated at points along the slip plane given as argument. This function only takes into account the dislocations present on itself for calculating the stress field.
 * @param points STL vector container with position vectors (Vector3d) of points at which the stress field is to be calculated.
 * @param appliedStress The externally applied stress (in the base co-ordinate system).
 * @param mu Shear modulus of the material in Pa.
 * @param nu Poisson's ratio.
 * @return STL vector container with the full stress tensor expressing the stress field (in the global co-ordinate system) at the points provided as input.
 */
std::vector<Stress> SlipPlane::getSlipPlaneStress_base (std::vector<Vector3d> points, Stress appliedStress, double mu, double nu)
{
    // Initialize the vector for holding Stress values
    std::vector<Stress> stressVector(points.size(), Stress());
    // Iterator for the stress
    std::vector<Stress>::iterator s = stressVector.begin();

    // Iterator for the points
    std::vector<Vector3d>::iterator p = points.begin();

    // Iterator for the defects
    std::vector<Defect*>::iterator d = this->defects.begin();


    // Temporary variable for stress
    Stress sTemp;

    while (p != points.end())
    {
        sTemp = appliedStress;

        while (d != this->defects.end())
        {
            sTemp += (*d)->stressField (*p, mu, nu);
            d++;
        }
        *s = sTemp;

        s++;
        p++;
    }

    return (stressVector);
}

/**
 * @brief Returns a vector containing the stress values at different points along a slip plane.
 * @details The stress field (expressed in the local co-ordinate system) is calculated at points along the slip plane given as argument. This function only takes into account the dislocations present on itself for calculating the stress field.
 * @param points STL vector container with position vectors (Vector3d) of points at which the stress field is to be calculated.
 * @param appliedStress The externally applied stress (in the global co-ordinate system).
 * @param mu Shear modulus of the material in Pa.
 * @param nu Poisson's ratio.
 * @return STL vector container with the full stress tensor expressing the stress field (in the local co-ordinate system) at the points provided as input.
 */
std::vector<Stress> SlipPlane::getSlipPlaneStress_local (std::vector<Vector3d> points, Stress appliedStress, double mu, double nu)
{
    // Initialize the vector for holding Stress values
    std::vector<Stress> stressVector(points.size(), Stress());
    // Iterator for the stress
    std::vector<Stress>::iterator s = stressVector.begin();

    // Iterator for the points
    std::vector<Vector3d>::iterator p = points.begin();

    // Iterator for the defects
    std::vector<Defect*>::iterator d = this->defects.begin();


    // Temporary variable for stress
    Stress sTemp;

    while (p != points.end())
    {
        sTemp = appliedStress;

        while (d != this->defects.end())
        {
            sTemp += (*d)->stressField (*p, mu, nu);
            d++;
        }

        // Convert to local co-ordinate system
        *s = this->coordinateSystem.stress_BaseToLocal(sTemp);

        s++;
        p++;
    }

    return (stressVector);
}
