/**
 * @file grainStatistics.cpp
 * @author Adhish Majumdar
 * @version 1.3
 * @date 20/11/2013
 * @brief Definition of the Grain class member functions that deal with writing statistics.
 * @details This file defines member functions of the Grain class that deal with writing statistics to file.
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

#include "grain.h"

/**
 * @brief Writes out the current time and the positions of all defects on the slip planes that belong to all the slip systems within this grain.
 * @details This function writes out, in a row, the time and the positions of all defects on the slip planes at that time. The function will be called several times during a simulation, so the file must be opened in append mode and the function should insert a newline after each entry.
 * @param fileName Name of the file into which the data is to be written.
 * @param t Value of time.
 */
void Grain::writeAllDefects (std::string fileName, double t)
{
    std::ofstream fp (fileName.c_str(), std::ios_base::app);

    if (fp.is_open()) {
        std::vector<Vector3d> defectPositions = this->getAllDefectPositions_base();
        std::vector<Vector3d>::iterator defectPositions_it;
        Vector3d defectPosition;

        fp << t << " ";
        defectPositions_it = defectPositions.begin();
        while (defectPositions_it!=defectPositions.end()) {
            defectPosition = *defectPositions_it;
            fp << defectPosition.getValue(0) << " " << defectPosition.getValue(1) << " "; // << defectPosition.getValue(2) << " ";
            defectPositions_it++;
        }

        fp << std::endl;
        fp.close();
    }
}

/**
 * @brief Write the six unique components of the stress field tensor, expressed in the base co-ordinate system, along the line between p0 and p1 with a resolution that is specified.
 * @param fileName Name of the file into which the data will be written.
 * @param t The current value of time in the simulation.
 * @param p0 Position vector, in the base co-ordinate system, of the starting point.
 * @param p1 Position vector, in the base co-ordinate system, of the ending point.
 * @param resolution The number of points, starting from p0, at which the stress field will be calculated.
 * @param mu Shear modulus (Pa).
 * @param nu Poisson's ratio.
 */
void Grain::writeStressField (std::string fileName, double t, Vector3d p0, Vector3d p1, int resolution, double mu, double nu)
{
    if (resolution <= 0) {
        // Invalid resolution
        return;
    }

    std::string outFileName = fileName + doubleToString(t) + ".txt";
    std::ofstream fp (outFileName.c_str(), std::ios_base::app);

    if (fp.is_open()) {
        Vector3d p = p0;
        Vector3d r = (p1-p0)*(1.0/resolution);
        Stress s;

        int i=0;
        while (i < resolution) {
            p += (r*i);
            s = this->grainStressField(p, mu, nu);

            fp << p.getValue(0) << " " << p.getValue(1) << " " << s.getPrincipalStress(0) << " " << s.getPrincipalStress(1) << " " << s.getPrincipalStress(2) << " " << s.getShearStress(0) << " " << s.getShearStress(1) << " " << s.getShearStress(2) << std::endl;
            i++;
        }

        fp.close();
    }
}
