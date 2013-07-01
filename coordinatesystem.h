/**
 * @file coordinatesystem.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 01/07/2013
 * @brief Definition of the class CoordinateSystem.
 * @details This file defines the the class CoordinateSystem to represent a given co-ordinate system and the base system in which it is expressed. This will be especially useful in the handling of various objects, each carrying its own frame of reference.
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

#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

/**
 * @brief The CoordinateSystem class.
 * @details The CoordinateSystem class represents a co-ordinate system of an entity. It also includes a pointer to the instance of the same class representing the base on which it is expressed.
 */
class CoordinateSystem
{
public:
    CoordinateSystem();
};

#endif // COORDINATESYSTEM_H
