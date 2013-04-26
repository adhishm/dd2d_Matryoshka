/**
 * @file dislocation.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 26/04/2013
 * @brief Definition of the Dislocation class.
 * @details This file defines the Dislocation class representing a dislocation in the simulation. This class inherits from the Defect class.
 */

#ifndef DISLOCATION_H
#define DISLOCATION_H

#include "defect.h"

/**
 * @brief Dislocation class representing a dislocation in the simulation.
 * @details The Dislocation class represents a dislocation in the simulation. The class inherits from the Defect class. A dislocation has several properties like a Burgers vector, line vector, etc. which will all be declared here.
 */
class Dislocation : public Defect
{
protected:
/**
 * @brief Burgers vector of the dislocation.
 */
    Vector3d bvec;
/**
 * @brief Line vector if the dislocation.
 */
    Vector3d lvec;
public:
/**
 * @brief Default constructor.
 * @details Initializes the dislocation with the following default parameters:
 * Position: (0.0, 0.0, 0.0)
 * Burgers vector: Default value set in defaults file.
 * Line vector: Default value set in defaults file.
 */
    Dislocation ();
/**
 * @brief Constructor that explicitly specifies all parameters.
 * @details All parameters: Burgers vector, line vector, position, are specified.
 * @param burgers Burgers vector.
 * @param line Line vector.
 * @param position Position.
 */
    Dislocation (Vector3d burgers, Vector3d line, Vector3d position);
    
};

#endif
