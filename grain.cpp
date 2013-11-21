/**
 * @file grain.cpp
 * @author Adhish Majumdar
 * @version 1.3
 * @date 20/11/2013
 * @brief Definition of the Grain class member functions.
 * @details This file defines member functions of the Grain class representing an grain/crystal in the simulation. A grain is considered to be a collection of slip systems.
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

#include "grain.h"

/**
 * @brief Default constructor for the Grain class.
 */
Grain::Grain()
{
}

// Destructor
/**
 * @brief Destructor for the class Grain.
 */
Grain::~Grain()
{
    std::vector<SlipSystem*>::iterator s_it;
    SlipSystem* s;

    // Delete individual slip systems
    for (s_it=this->slipSystems.begin(); s_it!=this->slipSystems.end(); s_it++) {
        s = *s_it;
        delete (s);
        s = NULL;
        *s_it = NULL;
    }

    // Clear the vector of pointers
    this->slipSystems.clear();
}
