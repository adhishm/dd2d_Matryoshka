/**
 * @file tess2d.cpp
 * @author Adhish Majumdar
 * @version 1.4
 * @date 03/12/2013
 * @brief Definition of the Tess2d class member functions.
 * @details This file defines member functions of the Tess2d class representing a Voronoi tessellation in 2 dimensions.
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

#include "tess2d.h"

/**
 * @brief Default constructor for the Tess2d class.
 * @details Since no data is provided, an instance of the class with empty vectors is created.
 */
Tess2d::Tess2d()
{
    this->vertices.clear();
    this->nVertices.clear();
    this->cells.clear();
}

/**
 * @brief Constructor for the class Tess2d, members initialized from file data.
 * @details The data for the tessellation is read from two files. The vertices are read from a file with the .nod extension, and the cells are read from a file with the .cll extension. The argument fileName provides only the name without extensions.
 * @param fileName Name of the files containing the tessellation data.
 */
Tess2d::Tess2d(std::string fileName)
{
    // Initialize filenames
    std::string nodFileName = fileName + ".nod";
    std::string cllFileName = fileName + ".cll";

    this->readVertices(nodFileName);
}

/**
 * @brief Destructor for the Tess2d class.
 */
Tess2d::~Tess2d()
{
    this->vertices.clear();
    this->nVertices.clear();

    // Delete data stored at the pointer locations
    std::vector<int*>::iterator it;
    it = this->cells.begin();
    while (it != this->cells.end()) {
        delete[] (*it);
        *it = NULL;
        it++;
    }
    this->cells.clear();
}

// Read from file functions
/**
 * @brief Read vertices from the file and store it in Tess2d::vertices.
 * @param nodFileName Name of the file containing the vertex co-ordinates.
 */
void Tess2d::readVertices (std::string nodFileName)
{
    std::ifstream fp (nodFileName.c_str());
    std::string line;

    this->vertices.clear();

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
            this->vertices.push_back(readVectorFromLine(line));
        }
        fp.close();
    }
}

/**
 * @brief Read the Voronoi cells from the cll file and store them in Tess2d::cells and Tess2d::nVertices.
 * @param cllFileName Name of the file containing the cell vertex ids.
 */
void Tess2d::readCells (std::string cllFileName)
{
    std::ifstream fp (cllFileName.c_str());
    std::string line;

    this->cells.clear();
    this->nVertices.clear();

    int vertexCount;

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
            // Now to read the vertices from the line
            this->cells.push_back(readIntegersFromLine(line, &vertexCount));
            this->nVertices.push_back(vertexCount);
        }
        fp.close();
    }
}

// Access functions
/**
 * @brief Return the vertex at the i^th position in the vector Tess2d::vertices.
 * @param i Index giving the position fo the vertex.
 * @return The vertex at the i^th position in the vector Tess2d::vertices.
 */
Vector3d Tess2d::getVertex (int i)
{
    if (i < this->vertices.size()) {
        return (this->vertices.at(i));
    }
}

/**
 * @brief Get the pointer to the cell vertex array at position i in the vector Tess2d::cells.
 * @param i Indexof the position of the cell array.
 * @return Pointer to the cell vertex array at position i in the vector Tess2d::cells.
 */
int* Tess2d::getCell (int i)
{
    if (i < this->cells.size()) {
        return (this->cells.at(i));
    }
}

/**
 * @brief Get the number of vertices for the i^th cell from the vector Tess2d::nVertices.
 * @param i Indexof the position in the vector.
 * @return Number of vertices for the i^th cell from the vector Tess2d::nVertices.
 */
int Tess2d::getNVertices (int i)
{
    if (i < this->nVertices.size()) {
        return (this->nVertices.at(i));
    }
}
