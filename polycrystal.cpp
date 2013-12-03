/**
 * @file polycrystal.cpp
 * @author Adhish Majumdar
 * @version 1.3
 * @date 03/12/2013
 * @brief Definition of the Polycrystal class member functions.
 * @details This file defines member functions of the Polycrystal class representing an polycrystal in the simulation. A polycrystal is considered to be a collection of several grains.
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

#include "polycrystal.h"

Polycrystal::Polycrystal()
{
    this->grains.clear();
    this->orientations.clear();
    this->tessellation = Tess2d();
}
