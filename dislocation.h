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
#include "dislocationDefaults.h"

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
/**
 * @brief Boolean term indicating mobility.
 * @details For mobile dislocations this term is true and for pinned dislocations it is false.
 */
    bool mobile;
    
public:
// Constructors
/**
 * @brief Default constructor.
 * @details Initializes the dislocation with the following default parameters:
 * Position: (0.0, 0.0, 0.0)
 * Burgers vector: Default value set in defaults file.
 * Line vector: Default value set in defaults file.
 * Mobile: true.
 */
    Dislocation ();
/**
 * @brief Constructor that explicitly specifies all parameters.
 * @details All parameters: Burgers vector, line vector, position, are specified.
 * @param burgers Burgers vector.
 * @param line Line vector.
 * @param position Position of the dislocation.
 * @param m Mobility (true/false).
 */
    Dislocation (Vector3d burgers, Vector3d line, Vector3d position, bool m);

// Assignment functions
/**
 * @brief Sets the Burgers vector of the dislocation.
 */
    void setBurgers (Vector3d burgers);
/**
 * @brief Sets the line vector of the dislocation.
 */
    void setLineVector (Vector3d line);
/**
 * @brief Sets the dislocation as mobile.
 * @details Sets the flag mobile to true.
 */
    void setMobile ();
/**
 * @brief Sets the dislocation as pinned.
 * @details Sets the flag mobile to false.
 */
    void setPinned ();
        
// Access functions
/**
 * @brief Gets the Burgers vector of the dislocation.
 * @return Burgers vector in a variable of type Vector3d.
 */
    Vector3d getBurgers ();
    /**
     * @brief Gets the line vector of the dislocation.
     * @return Line vector in a variable of type Vector3d.
     */
    Vector3d getLineVector ();

// Stress field
/**
 * @brief Calculates the stress field due to this dislocation at the position given as argument.
 * @details The stress field of the dislocation is calculated at the position indicated by the argument.
 * @param p Position vector of the point where the stress field is to be calculated.
 * @return Stress tensor giving the value of the stress field at position p.
 */
    Stress stressField (Vector3d p);
    
    
};

#endif
