/**
 * @file slipPlaneStatistics.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 17/07/2013
 * @brief Definition of the functions for writing out statistics pertaining to the SlipPlane class.
 * @details This file defines the functions for writing out statistics pertaining to the SlipPlane class.
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
 * @brief Writes the attributes of the slip plane and all defects lying on it.
 * @details This function writes to a file (the name of which is provided in the string filename) all the attributes of the slip plane and all defects lying on it. The file may be useful as statistics or to start the simulation off from an intermediate stage.
 * @param filename The name of the file to which all the attributes are to be written.
 * @param totalTime The value of time at this point.
 */
void SlipPlane::writeSlipPlane (std::string filename, double totalTime)
{
    std::ofstream fp ( filename.c_str() );
    if ( !fp.is_open() ) {
        return;
    }

    int i, j, nDisl, nDislSources;
    Vector3d v;
    Dislocation *d;
    DislocationSource *dSource;

    // Total time
    fp << "# Current time\n";
    fp << totalTime << std::endl;

    // Extremities
    fp << "# Extremities\n";
    v = this->getExtremity ( 0 );
    for ( i=0; i<3; i++ ) {
        fp << v.getValue ( i ) << " ";
    }
    fp << std::endl;
    v = this->getExtremity ( 1 );
    for ( i=0; i<3; i++ ) {
        fp << v.getValue ( i ) << " ";
    }
    fp << std::endl;

    // Normal vector
    fp << "# Normal vector\n";
    v = this->getNormal ();
    for ( i=0; i<3; i++ ) {
        fp << v.getValue ( i ) << " ";
    }
    fp << std::endl;

    // Position
    fp << "# Position\n";
    v = this->getPosition ();
    for ( i=0; i<3; i++ ) {
        fp << v.getValue ( i ) << " ";
    }
    fp << std::endl;

    // Dislocations
    nDisl = this->getNumDislocations ();
    fp << "# Number of dislocations" << std::endl << nDisl << std::endl;
    fp << "# Dislocations" << std::endl << "# Position(3) BurgersVector(3) LineVector(3) BurgersMagnitude(1) Mobile(1)" << std::endl;
    for ( i=0; i<nDisl; i++ ) {
        d = new Dislocation;
        if ( this->getDislocation ( i, d ) ) {
            v = d->getPosition ();
            for ( j=0; j<3; j++ ) {
                fp << v.getValue ( j ) << " ";
            }
            v = d->getBurgers ();
            for ( j=0; j<3; j++ ) {
                fp << v.getValue ( j ) << " ";
            }
            v = d->getLineVector ();
            for ( j=0; j<3; j++ ) {
                fp << v.getValue ( j ) << " ";
            }
            fp << d->getBurgersMagnitude () << " ";
            fp << ( int ) d->isMobile () << std::endl;
        }
        delete ( d );
        d = NULL;
    }

    // Dislocation sources
    nDislSources = this->getNumDislocationSources ();
    fp << "# Number of dislocation sources" << std::endl << nDislSources << std::endl;
    fp << "# Dislocation sources" << std::endl << "# Position(3) BurgersVector(3) LineVector(3) BurgersMagnitude(1) Tau_nuc(1) t_nuc(1)" << std::endl;
    for ( i=0; i<nDislSources; i++ ) {
        dSource = new DislocationSource;
        if ( this->getDislocationSource ( i, dSource ) ) {
            v = dSource->getPosition ();
            for ( j=0; j<3; j++ ) {
                fp << v.getValue ( j ) << " ";
            }
            v = dSource->getBurgers ();
            for ( j=0; j<3; j++ ) {
                fp << v.getValue ( j ) << " ";
            }
            v = dSource->getLineVector ();
            for ( j=0; j<3; j++ ) {
                fp << v.getValue ( j ) << " ";
            }
            fp << dSource->getBurgersMag () << " ";
            fp << dSource->getTauCritical () << " ";
            fp << dSource->getTimeTillEmit () << std::endl;
        }
        delete ( dSource );
        dSource = NULL;
    }

    // Close the file
    fp.close ();
}

/**
 * @brief Writes the stress distribution of stresses (in the slip plane's local co-ordinate system) along the slip plane with the given resolution.
 * @details This function writes out the distribution of stresses (in the slip plane's local co-ordinate system) along the slip plane, with the given resolution. The stress fields of all dislocations and the externally applied stress are all superposed points along the slip plane, and then the stress tensor at this point is transformed to the one in the slip plane's local co-ordinate system to obtain the final stress. The points where the stress is calculated are chosen according to the argument resolution, which provides the number of equally spaced points along the slip plane where the stress field is to be calculated. The output file contains the following information in each row: PointPosition(3) LocalStresses(s_xx s_yy s_zz s_xy s_xz s_yz) GlobalStresses(s_xx s_yy s_zz s_xy s_xz s_yz).
 * @param filename The name of the file into which the data is to be written.
 * @param resolution The number of points at which the stress field is to be calculated.
 * @param param Pointer to the instance of the parameter class which contains all the simulation parameters.
 */
void SlipPlane::writeSlipPlaneStressDistribution (std::string filename, int resolution, Parameter *param)
{
    std::ofstream fp ( filename.c_str() );
    if ( !fp.is_open() ) {
        return;
    }

    // Create the vector of points
    std::vector<Vector3d> points;
    Vector3d p0 = this->getExtremity ( 0 );
    Vector3d p1 = this->getExtremity ( 1 );
    Vector3d segment = ( p1 - p0 ) * ( 1.0 / ( resolution - 1 ) );
    Vector3d p;
    int i, j;

    p = p0;
    for ( i=1; i<=resolution; i++ ) {
        points.push_back ( p );
        p += segment;
    }

    std::vector<Stress> stressLocal  = this->getSlipPlaneStress_local  ( points, this->appliedStress_local, param->mu, param->nu );
    std::vector<Stress> stressGlobal = this->getSlipPlaneStress_base ( points, this->appliedStress_base, param->mu, param->nu );

    for ( i=0; i<resolution; i++ ) {
        // Position
        for ( j=0; j<3; j++ ) {
            fp << points[i].getValue ( j ) << " ";
        }
        // Local stresses
        fp << stressLocal[i].getValue(0,0) << " " << stressLocal[i].getValue(1,1) << " " << stressLocal[i].getValue(2,2) << " "
           << stressLocal[i].getValue(0,1) << " " << stressLocal[i].getValue(0,2) << " " << stressLocal[i].getValue(1,2) << " ";
        // Global stresses
        fp << stressGlobal[i].getValue(0,0) << " " << stressGlobal[i].getValue(1,1) << " " << stressGlobal[i].getValue(2,2) << " "
           << stressGlobal[i].getValue(0,1) << " " << stressGlobal[i].getValue(0,2) << " " << stressGlobal[i].getValue(1,2) << std::endl;
    }

    fp.close ();
}

/**
 * @brief Writes out the current time and the positions of all difects lying on the slip plane.
 * @details This function writes out, in a row, the time and the positions of all defects along the slip plane x-axis at that time. The function will be called several times during a simulation, so the file must be opened in append mode and the function should insert a newline after each entry.
 * @param filename Name of the file into which the data is to be written.
 * @param t Value of time.
 */
void SlipPlane::writeAllDefects (std::string filename, double t)
{
    std::ofstream fp (filename.c_str(), std::ios_base::app);
    int nDefects, i;
    Defect* def;
    Vector3d p;

    if (fp.is_open()) {
        nDefects = this->getNumDefects();
        fp << t << " ";
        for (i=0; i<nDefects; i++) {
            def = this->defects.at(i);
            p = def->getPosition();
            fp << p.getValue(0) << " ";
        }
        fp << std::endl;
        fp.close();
    }
}
