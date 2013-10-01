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

#include "slipPlane.h"


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
public:
    /**
     * @brief Default constructor for the class SlipSystem
     */
    SlipSystem();
};

#endif // SLIPSYSTEM_H
