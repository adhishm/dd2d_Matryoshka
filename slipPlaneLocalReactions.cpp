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
    dit = this->defects.begin();
    while (dit != this->defects.end()) {
        d0 = *dit;
        d1 = *(dit + 1);

        p0 = d0->getPosition();
        p1 = d1->getPosition();

        if ( (p1-p0).magnitude() <= reactionRadius ) {
            // The two defects are close to each other - a local reaction is imminent
            dit = this->identifyLocalReaction(dit, dit+1);
        }
        else {
            // Nothing happens - defects too far away
            dit++;
        }
    }
}

/**
 * @brief Identify the kind of local reaction that is to be applied to the defect pair and call the appropriate function.
 * @details This function checks for the kind of local reaction that is to be applied to the defect pair, calls the appropriate function, and returns the iterator to the next defect that is to be checked for local reactions. Returning the iterator is important because the vector SlipPlane::defects may lose members as a result of a local reaction, and the iterators in the calling function may become invalid.
 * @param d0 Iterator of type std::vector<Defect*> indicating the first defect that participates in the local reaction.
 * @param d1 Iterator of type std::vector<Defect*> indicating the second defect that participates in the local reaction.
 * @return Iterator to the next position that is to be checked for a local reaction.
 */
std::vector<Defect*>::iterator SlipPlane::identifyLocalReaction(std::vector<Defect*>::iterator d0, std::vector<Defect*>::iterator d1)
{
    switch ( (*d0)->getDefectType() ) {
    case GRAINBOUNDARY:
        return (d0);
        break;
    case FREESURFACE:
        return (freeSurfaceInteractions (d0, d1));
        break;
    case FRANKREADSOURCE:
        return (d0);
        break;
    case DISLOCATION:
        return (dislocationInteractions (d0, d1));
        break;
    default:
        return (d0);
        break;
    }
}



/**
 * @brief Absorb a dislocation into a free surface.
 * @details When a dislocation approaches a free surface, it is pulled toward it due to the diminishing strain energy, and eventually the dislocation gets absorbed into the surface. This function provides that functionality.
 * @param disl Pointer of type Defect* that is to be absorbed into the free surface.
 * @return Iterator to the position of the new dislocation that occupies the place of the dislocation that was absorbed.
 */
std::vector<Defect*>::iterator SlipPlane::absorbDislocation (std::vector<Defect*>::iterator disl)
{
    // Just remove the dislocation from the vector
    return ( this->defects.erase(disl) );
}

/**
 * @brief Two dislocations of opposite Burgers vectors annihilate when they approach each other closer than the reaction radius.
 * @param d0 Iterator of the vector SlipPlane::defects for the first dislocation.
 * @param d1 Iterator of the vector SlipPlane::defects for the second dislocation.
 * @return Iterator to the position of the new dislocation that occupies the place of the first dislocation that was annihilated.
 */
std::vector<Defect*>::iterator SlipPlane::annihilateDislocations (std::vector<Defect*>::iterator d0, std::vector<Defect*>::iterator d1)
{
    return (this->defects.erase(d0, d1));
}
