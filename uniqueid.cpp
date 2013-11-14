/**
 * @file uniqueid.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 14/11/2013
 * @brief Definition of the UniqueID class functions.
 * @details This file defines the UniqueID singleton class representing the structure to deal with allocating unique identification to all objects in the simulation.
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

#include "uniqueid.h"

// Set the UniqueId singleteon instance to NULL for the beginning.
UniqueID* UniqueID::uid_instance = NULL;

/**
 * @brief UniqueID class constructor.
 * @details This contructor initializes the UniqueID singleton. This constructor is declares as protected so that only a member function of this class may call it.
 */
UniqueID::UniqueID()
{
    this->currentIndex = 0;
    this->defectTypeVector.clear();
    this->parameters.clear();
}

/**
 * @brief Returns the current index value.
 * @return The value of the current index.
 */
int UniqueID::getCurrentIndex () const
{
    return (this->currentIndex);
}

/**
 * @brief Creates a new index for the object.
 * @details This function increments the current index by 1, and returns this value. The argument defectType tells the function what kind of defect it is. Depending on the type of defect, the STL vector parameters specifies the parameters, which are then
 * @param defectType The type of defect.
 * @param parameters Parameters of the defect.
 * @return New index to be given to the object.
 */
int UniqueID::newIndex (DefectType defectType, std::vector<double> parameters)
{
    this->currentIndex++;
    this->defectTypeVector.push_back(defectType);
    this->parameters.push_back(parameters.data());
    return(this->currentIndex);
}

/**
 * @brief Get the parameters associated with a defect given its unique id.
 * @param uid Unique id of the defect.
 * @return Pointer to the array containing the parameters.
 */
double* UniqueID::getParameters(int uid)
{
    if ((uid>=0) && (uid<this->currentIndex)) {
        return(this->parameters.at(uid));
    }
    else {
        return(NULL);
    }
}

/**
 * @brief Get the type of defect given its unique id.
 * @param uid Unique id of the defect.
 * @return The DefectType of the defect.
 */
DefectType UniqueID::getDefectType(int uid)
{
    if ((uid>=0) && (uid<this->currentIndex)) {
        return(this->defectTypeVector.at(uid));
    }
    else {
        return(0);
    }
}
