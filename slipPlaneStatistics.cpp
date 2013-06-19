/**
 * @file slipPlaneStatistics.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 18/06/2013
 * @brief Definition of the functions for writing out statistics pertaining to the SlipPlane class.
 * @details This file defines the functions for writing out statistics pertaining to the SlipPlane class.
 */

#include "slipPlane.h"

/**
 * @brief Writes the attributes of the slip plane and all defects lying on it.
 * @details This function writes to a file (the name of which is provided in the string filename) all the attributes of the slip plane and all defects lying on it. The file may be useful as statistics or to start the simulation off from an intermediate stage.
 * @param filename The name of the file to which all the attributes are to be written.
 */
void SlipPlane::writeSlipPlane (std::string filename)
{
    std::ofstream fp ( filename );
    int i, j, nDisl, nDislSources;
    Vector3d v;
    Dislocation *disl;
    DislocationSource *dSource;

    if ( !fp.is_open() ) {
        return;
    }

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
            fp << d->getBurgersMag () << " ";
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

}

/**
 * @brief Writes the stress distribution of stresses (in the slip plane's local co-ordinate system) along the slip plane with the given resolution.
 * @details This function writes out the distribution of stresses (in the slip plane's local co-ordinate system) along the slip plane, with the given resolution. The stress fields of all dislocations and the externally applied stress are all superposed points along the slip plane, and then the stress tensor at this point is transformed to the one in the slip plane's local co-ordinate system to obtain the final stress. The points where the stress is calculated are chosen according to the argument resolution, which provides the number of equally spaced points along the slip plane where the stress field is to be calculated. The output file contains the following information in each row: PointPosition(3) LocalStresses(s_xx s_yy s_zz s_xy s_xz s_yz) GlobalStresses(s_xx s_yy s_zz s_xy s_xz s_yz).
 * @param filename The name of the file into which the data is to be written.
 * @param resolution The number of points at which the stress field is to be calculated.
 */
void writeSlipPlaneStressDistribution (std::string filename, int resolution);
