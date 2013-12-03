/**
 * @file tess2d.h
 * @author Adhish Majumdar
 * @version 1.4
 * @date 03/12/2013
 * @brief Definition of the Tess2d class.
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

#ifndef TESS2D_H
#define TESS2D_H

#include "vector3d.h"
#include "tools.h"
#include "readFromFile.h"

#include <vector>
#include <iterator>

/**
 * @brief The Tess2d class.
 * @details This class represents a Voronoi tessellation in 2 dimensions.
 */
class Tess2d
{
protected:
    /**
     * @brief STL vector container with the vertices of the 2d Voronoi tessellation.
     * @details The vertices form the the triple points between cells in 2 dimensions. Obviously, the component of the 3rd dimension is always 0. Vector3d type has been used merely for convenience as it is used everywhere else in the simulations.
     */
    std::vector<Vector3d> vertices;

    /**
     * @brief STL vector container with numbers indicating the number of vertices for each cell.
     * @details This vector contains the number of vertices for each cell. The size of this vector must not be less than the size of the cells vector.
     */
    std::vector<int> nVertices;

    /**
     * @brief STL vector container with pointers to arrays containing the list of vertices for each cell. The size of this vector must not be more than the size of the nVertices vector.
     */
    std::vector<int*> cells;
public:
    // Constructors
    /**
     * @brief Default constructor for the Tess2d class.
     * @details Since no data is provided, an instance of the class with empty vectors is created.
     */
    Tess2d();

    /**
     * @brief Constructor for the class Tess2d, members initialized from file data.
     * @details The data for the tessellation is read from two files. The vertices are read from a file with the .nod extension, and the cells are read from a file with the .cll extension. The argument fileName provides only the name without extensions.
     * @param fileName Name of the files containing the tessellation data.
     */
    Tess2d(std::string fileName);

    // Destructor
    /**
     * @brief Destructor for the Tess2d class.
     */
    virtual ~Tess2d();

    // Read from file functions
    /**
     * @brief Read vertices from the file and store it in Tess2d::vertices.
     * @param nodFileName Name of the file containing the vertex co-ordinates.
     */
    void readVertices (std::string nodFileName);

    /**
     * @brief Read the Voronoi cells from the cll file and store them in Tess2d::cells and Tess2d::nVertices.
     * @param cllFileName Name of the file containing the cell vertex ids.
     */
    void readCells (std::string cllFileName);

    // Assignment functions

    // Access functions
    /**
     * @brief Return the vertex at the i^th position in the vector Tess2d::vertices.
     * @param i Index giving the position fo the vertex.
     * @return The vertex at the i^th position in the vector Tess2d::vertices.
     */
    Vector3d getVertex (int i);

    /**
     * @brief Get the pointer to the cell vertex array at position i in the vector Tess2d::cells.
     * @param i Indexof the position of the cell array.
     * @return Pointer to the cell vertex array at position i in the vector Tess2d::cells.
     */
    int* getCell (int i);

    /**
     * @brief Get the number of vertices for the i^th cell from the vector Tess2d::nVertices.
     * @param i Indexof the position in the vector.
     * @return Number of vertices for the i^th cell from the vector Tess2d::nVertices.
     */
    int getNVertices (int i);
};

#endif // TESS2D_H
