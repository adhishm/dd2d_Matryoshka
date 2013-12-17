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

/**
 * @brief Default constructor for the Polycrystal class.
 */
Polycrystal::Polycrystal()
{
    this->grains.clear();
    this->orientations.clear();
    this->tessellation = Tess2d();

    this->coordinateSystem = CoordinateSystem();
}

/**
 * @brief Destructor for the Polycrystal class.
 */
Polycrystal::~Polycrystal()
{
    std::vector<Grain*>::iterator g_it;
    Grain* g;

    for (g_it=this->grains.begin(); g_it!=this->grains.end(); g_it++) {
        g = *g_it;
        delete (g);
        *g_it = NULL;
    }

    this->grains.clear();
    this->orientations.clear();
}

// Assignment functions
/**
 * @brief Set the Voronoi tessellation for the polycrystal from the tessellation file provided.
 * @param tessellationFileName Name of the files containing the Voronoi tessellation.
 */
void Polycrystal::setTessellation (std::string tessellationFileName)
{
    this->tessellation = Tess2d(tessellationFileName);
}

/**
 * @brief Set the orientations vector by reading orientations from a file.
 * @param orientationsFileName Name of the file containing the orientations.
 */
void Polycrystal::setOrientations (std::string orientationsFileName)
{
    this->orientations.clear();
    std::ifstream fp (orientationsFileName.c_str());
    std::string line;

    if (fp.is_open()) {
        while (fp.good()) {
            do {
                if (fp.good()) {
                    getline (fp, line);
                }
                else {
                    fp.close();
                    return;
                }
            } while (ignoreLine(line));
            this->orientations.push_back(readVectorFromLine(line));
        }
        fp.close();
    }
}

/**
 * @brief Initialize the Grain vector.
 */
void Polycrystal::initializeGrainVector ()
{
    this->grains.clear();
    this->grains.assign(this->tessellation.getNumberOfCells(), new Grain);
}

/**
 * @brief Set the grain boundaries for each grain using data from the tessellation.
 */
void Polycrystal::setGrainBoundaries ()
{
    std::vector<Vector3d> gbPoints;

    int nGrains = this->grains.size();
    int nPoints;
    int i, j;
    Grain* g;
    int* cell;

    for (i=0; i<nGrains; i++) {
        g = this->grains.at(i);

        cell = this->tessellation.getCell(i);
        nPoints = this->tessellation.getNVertices(i);
        gbPoints.clear();
        for (j=0; j<nPoints; j++) {
            gbPoints.push_back(this->tessellation.getVertex(cell[j]));
        }

        g->setGBPoints(gbPoints);
    }
}

/**
 * @brief Set the grain orientations from the orientations list.
 */
void Polycrystal::setGrainOrientations ()
{
    if (this->grains.size() > this->orientations.size()) {
        return;
    }

    int i;
    Grain* g;

    for (i=0; i<this->grains.size(); i++) {
        g = this->grains.at(i);
        g->setOrientation(this->orientations.at(i));
    }
}

/**
 * @brief Insert a new grain into the polycrystal.
 * @param g Pointer to the grain (instance of the class Grain).
 */
void Polycrystal::insertGrain (Grain* g)
{
    this->grains.push_back(g);
}

/**
 * @brief Set the applied stress on the polycrystal.
 * @param s The value of the applied stress.
 */
void Polycrystal::setAppliedStress (Stress s)
{
    this->appliedStress_base = s;
    this->appliedStress_local = this->coordinateSystem.stress_BaseToLocal(s);
}

// Access functions
/**
 * @brief Get the pointer to a grain indicated by the index given as argument.
 * @details The grains are stored in memory and pointers to them are stored in the vector Polycrystal::grains. The index i provided as argument indicates which grain is required and the pointer to that grain is returned. If the index is invalid, NULL is returned.
 * @param i Index of the grain in the vector Polycrystal::grains.
 * @return Pointer to the grain at the position i.
 */
Grain* Polycrystal::getGrain (int i)
{
    if ( (i>=0) && (i<this->grains.size()) ) {
        return (this->grains.at(i));
    }
    else {
        return (NULL);
    }
}

/**
 * @brief Get the applied stress on the polycrystal, expressed in the base co-ordinate system.
 * @return The applied stress on the polycrystal, expressed in the base co-ordinate system.
 */
Stress Polycrystal::getAppliedStress_base () const
{
    return (this->appliedStress_base);
}

/**
 * @brief Get the applied stress on the polycrystal, expressed in the local co-ordinate system.
 * @return The applied stress on the polycrystal, expressed in the local co-ordinate system.
 */
Stress Polycrystal::getAppliedStress_local () const
{
    return (this->appliedStress_local);
}

/**
 * @brief Get a pointer to the Grain CoordinateSystem.
 * @return Pointer to the Grain co-ordinate system.
 */
CoordinateSystem* Polycrystal::getCoordinateSystem()
{
    return (&(this->coordinateSystem));
}

// Stresses
/**
 * @brief Calculate the applied stress on all the grains in the polycrystal.
 */
void Polycrystal::calculateGrainAppliedStress ()
{
    std::vector<Grain*>::iterator git;
    Grain* g;

    for (git=this->grains.begin(); git!=this->grains.end(); git++) {
        g = *git;
        g->calculateGrainAppliedStress(this->appliedStress_local);
        g->calculateSlipSystemAppliedStress();
    }
}

/**
 * @brief Calculate all the stresses in all the defects in the simulation.
 * @param mu Shear modulus (Pa).
 * @param nu Poisson's ratio.
 */
void Polycrystal::calculateAllStresses (double mu, double nu)
{
    std::vector<Grain*>::iterator sourceGrain_it;
    std::vector<Grain*>::iterator destinationGrain_it;

    Grain* sourceGrain;
    Grain* destinationGrain;

    std::vector<Defect*> defects;
    std::vector<Defect*> defects_it;
    Defect* defect;

    std::vector<Vector3d> defectPositions;
    std::vector<Vector3d> defectPositions_it;

    Stress totalStress;
    Stress totalStress_grain;
    Stress totalStress_slipSystem;
    Stress totalStress_slipPlane;
    Stress totalStress_defect;

    for (destinationGrain_it=this->grains.begin(); destinationGrain_it!=this->grains.end(); destinationGrain_it++) {
        destinationGrain = *destinationGrain_it;
        // Get all the defect position vectors
        defects = destinationGrain->getAllDefectPositions_base();
        defectPositions = destinationGrain->getAllDefectPositions_base();
        for (defectPositions_it=defectPositions.begin(), defects_it=defects.begin();
             defectPositions_it!=defectPositions.end();
             defectPositions_it++, defects_it++) {
            // Set the total stress to the polycrystal applied stress
            totalStress = this->appliedStress_local;
            defect = *defects_it;
            for (sourceGrain_it=this->grains.begin(); sourceGrain_it!=this->grains.end(); sourceGrain_it++) {
                sourceGrain = *sourceGrain_it;
                totalStress += sourceGrain->grainStressField(*defectPositions_it, mu, nu);
            }
            // The total stress is in the polycrystal co-ordinate system
            totalStress_grain = destinationGrain->getCoordinateSystem()->stress_BaseToLocal(totalStress);
            totalStress_slipSystem = defect->getCoordinateSystem()->getBase()->getBase()->stress_BaseToLocal(totalStress_grain);
            totalStress_slipPlane  = defect->getCoordinateSystem()->getBase()->stress_BaseToLocal(totalStress_slipSystem);
            totalStress_defect     = defect->getCoordinateSystem()->stress_BaseToLocal(totalStress_slipPlane);
            defect->setTotalStress(totalStress_defect);
        }
    }
}

// Iteration functions
/**
 * @brief Calculate the Peach-Koehler force on all dislocations and their resulting velocities.
 * @param B The drag coefficient.
 */
void Polycrystal::calculateDislocationVelocities (double B)
{
    std::vector<Grain*>::iterator g_it;
    Grain* g;

    for (g_it=this->grains.begin(); g_it!=this->grains.end(); g_it++) {
        g = *g_it;
        g->calculateDislocationVelocities(B);
    }
}
