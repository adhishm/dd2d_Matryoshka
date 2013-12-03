/**
 * @file polycrystal.h
 * @author Adhish Majumdar
 * @version 1.3
 * @date 03/12/2013
 * @brief Definition of the Polycrystal class which represents a polycrystal in the simulation.
 * @details This file declares member data and functions of the Polycrystal class representing an polycrystal in the simulation. A polycrystal is considered to be a collection of several grains.
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

#ifndef POLYCRYSTAL_H
#define POLYCRYSTAL_H

#include "grain.h"

/**
 * @brief The Polycrystal class.
 * @details This class represents a polycrystal in the simulation. A polycrystal is considered to be a collection of grains. Each grain has its grain boundary points and a crystallographic orientation.
 */
class Polycrystal
{
protected:
    /**
     * @brief STL vector container with pointers to the grains.
     * @details
     */
    std::vector<Grain*> grains;

    /**
     * @brief STL vector with the crystallographic orientations of the grains.
     */
    std::vector<Vector3d> orientations;
public:
    /**
     * @brief Default constructor for the Polycrystal class.
     */
    Polycrystal();

    /**
     * @brief Destructor for the Polycrystal class.
     */
    virtual ~Polycrystal();
};

#endif // POLYCRYSTAL_H
