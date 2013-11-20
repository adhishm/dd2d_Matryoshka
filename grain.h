/**
 * @file grain.h
 * @author Adhish Majumdar
 * @version 1.3
 * @date 20/11/2013
 * @brief Definition of the Grain class.
 * @details This file defines the Grain class representing an grain/crystal in the simulation. A grain is considered to be a collection of slip systems.
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

#ifndef GRAIN_H
#define GRAIN_H

#include "slipsystem.h"

class Grain
{
protected:
    /**
     * @brief STL vector container with pointers to all slip systems that belong to this grain.
     */
    std::vector<SlipSystem*> slipSystems;
public:
    /**
     * @brief Default constructor for the Grain class.
     */
    Grain();
};

#endif // GRAIN_H
