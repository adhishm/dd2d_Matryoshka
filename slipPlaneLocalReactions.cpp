/**
 * @file slipPlaneLocalReactions.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 26/08/2013
 * @brief Definition of all functions carrying out local reactions between defects on a slip plane.
 * @details This file defines functions of the SlipPlane class that carry out the local reactions between defects lying on the slip plane.
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

#include "slipPlane.h"

/**
 * @brief Function to check for local reactions between defects present on the slip plane.
 * @details When two defects approach each other closer than the reaction radius, there is a possibility of an interaction between them. These interactions are detected and triggered by this function.
 * @param reactionRadius The limiting distance between to defects for which a local reaction can take place.
 */
void SlipPlane::checkLocalReactions(double reactionRadius)
{
    // Iterator for defects
    std::vector<Defect*>::iterator dit;
    std::vector<Defect*>::iterator dFirst = this->defects.begin();
    std::vector<Defect*>::iterator dLast  = this->defects.end();
    // Neighbouring defect pair and their positions
    Defect* d0; Vector3d p0;
    Defect* d1; Vector3d p1;


    // Check for neighbouring defects that lie too close
    for (dit=dFirst; dit!=(dLast-1); dit++) {
        d0 = *dit;
        d1 = *(dit + 1);

        p0 = d0->getPosition();
        p1 = d1->getPosition();

        if ( (p1-p0).magnitude() <= reactionRadius ) {
            // The two defects are close to each other - a local reaction is imminent
        }
    }
}
