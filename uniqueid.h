/**
 * @file uniqueid.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 14/11/2013
 * @brief Definition of the UniqueID class.
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

#ifndef UNIQUEID_H
#define UNIQUEID_H

#include <vector>
#include <string>
#include <fstream>

#include "defectType.h"

/**
 * @brief The UniqueID singleton class to handle unique identification for all objects in the simulation.
 */
class UniqueID
{
protected:
    /**
     * @brief UniqueID class constructor.
     * @details This contructor initializes the UniqueID singleton. This constructor is declares as protected so that only a member function of this class may call it.
     */
    UniqueID();
private:
    /**
     * @brief Pointer to access the instance.
     */
    static UniqueID* uid_instance;
    /**
     * @brief The counter that stores the current index.
     */
    int currentIndex;
    /**
     * @brief Vector of defect types corresponding to the unique id given to the defects.
     */
    std::vector<DefectType> defectTypeVector;
    /**
     * @brief STL vector containing the pointer to an array with parameters giving details of the object in the position corresponding to the unique id.
     * @details The parameters are as follows: 1. defectType=VACANCY No parameters 2. DefectType=INTERSTITIAL No parameters 3. DefectType=DISLOCATION BurgersVector (Highest available co-ordinate system); Line vector (Highest available co-ordinate system) 3. DefectType=FRANKREADSOURCE
     */
    std::vector<double*> parameters;
public:
    /**
     * @brief Get the instance of the UniqueID singleton.
     * @details This function returns a pointer to the UniqueID singleton instance. The function checks if an instance exists already. If it does, then a pointer to that instance is returned, if it does not, then a new one is created and a pointer to that instance is returned.
     * @return Pointer to the UniqueID singleton instance.
     */
    static UniqueID* getInstance()
    {
        if (uid_instance == NULL) {
            uid_instance = new UniqueID();
        }
        return (uid_instance);
    }

    /**
     * @brief Returns the current index value.
     * @return The value of the current index.
     */
    int getCurrentIndex () const;

    /**
     * @brief Creates a new index for the object.
     * @details This function increments the current index by 1, and returns this value. The argument defectType tells the function what kind of defect it is. The pointer parameters gives the location in memory of the parameters for this defect.
     * @param defectType The type of defect.
     * @param p Pointer to an array containing the parameters of the defect.
     * @return New index to be given to the object.
     */
    int newIndex (DefectType defectType, double *p);

    /**
     * @brief Get the parameters associated with a defect given its unique id.
     * @param uid Unique id of the defect.
     * @return Pointer to the array containing the parameters.
     */
    double* getParameters(int uid);

    /**
     * @brief Get the type of defect given its unique id.
     * @param uid Unique id of the defect.
     * @return The DefectType of the defect.
     */
    DefectType getDefectType(int uid);

    /**
     * @brief Writes the unique ids , defect types and parameters of all defects to file.
     * @param filename std::string containing the name of the file to which the data is to be written.
     */
    void writeDefects(std::string filename);
};

#endif // UNIQUEID_H
