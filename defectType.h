/**
 * @file defectType.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 28/06/2013
 * @brief Definition of the DefectType enum.
 * @details This file defines the DefectType enum representing the different types of defects.
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


#ifndef DEFECTTYPE_H
#define DEFECTTYPE_H

/**
 * @brief Enumerated class indicating the kind of defect that this is.
 */
enum DefectType {
    VACANCY = 0,
    INTERSTITIAL,
    DISLOCATION,
    FRANKREADSOURCE,
    GRAINBOUNDARY,
    FREESURFACE
};

/**
  * @brief The default defect type is defined here.
  **/
#ifndef DEFAULT_DEFECT_TYPE
#define DEFAULT_DEFECT_TYPE DISLOCATION
#endif

#endif // DEFECTTYPE_H
