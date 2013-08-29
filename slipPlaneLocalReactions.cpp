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
        return (d0+1);
        break;
    case FREESURFACE:
        return (freeSurfaceInteractions (d0, d1));
        break;
    case FRANKREADSOURCE:
        return (d0+1);
        break;
    case DISLOCATION:
        return (dislocationInteractions (d0, d1));
        break;
    default:
        return (d0+1);
        break;
    }
}

/**
 * @brief Identify the reaction to occur between a free surface and another defect.
 * @param d0 Iterator indicating the free surface in SlipPlane::defects.
 * @param d1 Iterator indicating the other defect in freeSurfaceInteractions
 * @return Iterator to the position from where the function SlipPlane::checkLocalReactions should continue.
 */
std::vector<Defect*>::iterator SlipPlane::freeSurfaceInteractions(std::vector<Defect*>::iterator d0, std::vector<Defect*>::iterator d1)
{
    switch ( (*d1)->getDefectType() ) {
    case GRAINBOUNDARY:
    case FREESURFACE:
    case FRANKREADSOURCE:
        // In all the above cases, there is nothing to be done
        return (d0+1);
        break;
    case DISLOCATION:
        // The other defect is a dislocation
        // It should be absorbed into the free surface
        return (this->absorbDislocation(d1));
        break;
    default:
        // Unknown defect type - do nothing
        return (d0+1);
        break;
    }
}

/**
 * @brief Identify the reaction to occur between a dislocation and another defect.
 * @param d0 Iterator indicating the dislocation in SlipPlane::defects.
 * @param d1 Iterator indicating the other defect in SlipPlane::defects.
 * @return Iterator to the position from where the function SlipPlane::checkLocalReactions should continue.
 */
std::vector<Defect*>::iterator SlipPlane::dislocationInteractions(std::vector<Defect*>::iterator d0, std::vector<Defect*>::iterator d1)
{
    switch ( (*d1)->getDefectType() ) {
    case GRAINBOUNDARY:
        // Do nothing
        return (d0+1);
        break;
    case FREESURFACE:
        // The dislocation at d0 should be absorbed into the free surface d1
        return (this->absorbDislocation(d0));
        break;
    case DISLOCATION:
        return (this->dislocation_dislocationInteraction(d0, d1));
        break;
    default:
        return (d0+1);
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
    // Just remove the dislocation from the vectors
    this->dislocations.erase( this->findDislocationIterator(disl) );
    return ( this->defects.erase(disl) );
}

/**
 * @brief Checks for the kind of interaction between two dislocations.
 * @param d0 Iterator giving the first dislocation in SlipPlane::defects.
 * @param d1 Iterator giving the second dislocation in SlipPlane::defects.
 * @return Iterator to the position from where the function SlipPlane::checkLocalReactions should continue.
 */
std::vector<Defect*>::iterator SlipPlane::dislocation_dislocationInteraction (std::vector<Defect*>::iterator d0, std::vector<Defect*>::iterator d1)
{
    std::vector<Dislocation*>::iterator dislocation0_iterator = this->findDislocationIterator(d0);
    std::vector<Dislocation*>::iterator dislocation1_iterator = this->findDislocationIterator(d1);

    Dislocation* dislocation0 = *dislocation0_iterator;
    Dislocation* dislocation1 = *dislocation1_iterator;

    // Check for Burgers vectors
    Vector3d b0 = dislocation0->getBurgers();
    Vector3d b1 = dislocation1->getBurgers();

    if ( (b1-b0).magnitude() < SMALL_NUMBER ) {
        // The Burgers vectors are opposite - annihilate the dislocations
        this->dislocations.erase(dislocation0_iterator);
        this->dislocations.erase(dislocation1_iterator);
        return (this->defects.erase(d0,d1));
    }
    else {
        // No annihilation, no interaction
        return (d0 + 1);
    }
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
