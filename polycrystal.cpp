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
