/**
 * @file dislocationSourceDefaults.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 02/05/2013
 * @brief Definition of certain default values for members of the DislocationSource class.
 * @details This file defines some default values for members of the DislocationSource class representing a dislocation dipole source in the simulation.
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


#ifndef DISLOCATIONSOURCEDEFAULTS_H
#define DISLOCATIONSOURCEDEFAULTS_H

/**
 * @brief Default value of the critical shear stress for a dislocation source to emit a dipole.
 * @details Default value of the critical shear stress for a dislocation source to emit a dipole. The number is expressed in Pa.
 */
#define DEFAULT_TAU_CRITICAL 1.0e09

/**
 * @brief Default value of the amount of time required for a dislocation source to emit a dipole.
 * @details The dislocation source must experience a shear stress greater than the critical value in order to emit a dipole. This time is expressed here.
 */
#define DEFAULT_DIPOLEEMISSIONTIMELIMIT 1.0e-08

#endif
