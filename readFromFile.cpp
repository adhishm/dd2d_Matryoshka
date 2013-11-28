/**
 * @file readFromFile.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 10/10/2013
 * @brief Definition various functions to read data from files.
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

#include "readFromFile.h"

/**
 * @brief Reads the slip plane details from the file.
 * @details The details of the slip plane and its dislocations are stored in a file the name of which is provided. This file is read and the information is saved into the instance of the SlipPlane class, the pointer to which is given.
 * @param fileName String containing the name of the file.
 * @param s Pointer to the instance of SlipPlane into which all data is to be stored.
 * @param currentTime Pointer to the variable storing the initial time.
 * @param param Pointer to the Parameter class object containing the simulation parameters.
 * @return Flag indicating the success or failure of the operation.
 */
bool readSlipPlane (std::string fileName, SlipPlane *s, double *currentTime, Parameter *param)
{
    std::ifstream fp ( fileName.c_str() );
    std::string line;

    Dislocation* disl;
    DislocationSource* dSource;

    Vector3d *e;
    int i,  n;

    /**
     * @brief baseCoordinateSystem This is the basis for the slip plane co-ordinate system.
     */
    CoordinateSystem* baseCoordinateSystem = new CoordinateSystem();

    if ( fp.is_open() )
    {
        // Read the initial time
        do {
            if ( fp.good() ) {
                getline (fp, line);
            }
            else {
                fp.close();
                return (false);
            }
        } while ( ignoreLine(line) );
        *currentTime = atof(line.c_str());

        // Read the extremities
        e = new Vector3d[2];
        do {
            if ( fp.good() ) {
                getline ( fp, line );
            }
            else {
                fp.close ();
                return ( false );
            }
        } while ( ignoreLine ( line ) );
        e[0] = readVectorFromLine ( line );

        do {
            if ( fp.good() ) {
                getline ( fp, line );
            }
            else {
                fp.close ();
                return ( false );
            }
        } while ( ignoreLine ( line ) );
        e[1] = readVectorFromLine ( line );

        s->setExtremities( e );
        delete[] ( e );
        e = NULL;

        // Read the normal vector
        do {
            if ( fp.good() ) {
                getline ( fp, line );
            }
            else {
                fp.close ();
                return ( false );
            }
        } while ( ignoreLine ( line ) );
        s->setNormal( readVectorFromLine ( line ) );

        // Read the position
        do {
            if ( fp.good() ) {
                getline ( fp, line );
            }
            else {
                fp.close ();
                return ( false );
            }
        } while ( ignoreLine ( line ) );
        s->setPosition( readVectorFromLine ( line ) );

        // Create the co-ordinate system
        s->createCoordinateSystem(baseCoordinateSystem);

        // Read number of dislocations
        do {
            if ( fp.good() ) {
                getline ( fp, line );
            }
            else {
                fp.close ();
                return ( false );
            }
        } while ( ignoreLine ( line ) );
        n = atoi ( line.c_str() );
        // Clear the dislocations vector before inserting new dislocations.
        s->clearDislocations();
        // Read the dislocations
        for ( i=0; i<n; i++ ) {
            do {
                if ( fp.good() ) {
                    getline ( fp, line );
                }
                else {
                    fp.close ();
                    return ( false );
                }
            } while ( ignoreLine ( line ) );
            disl = readDislocationFromLine(line);
            disl->setBaseCoordinateSystem(s->getCoordinateSystem());
            disl->calculateRotationMatrix();
            disl->calculateBurgersLocal();
            s->insertDislocation ( disl );
        }

        // Read number of dislocation sources
        do {
            if ( fp.good() ) {
                getline ( fp, line );
            }
            else {
                fp.close ();
                return ( false );
            }
        } while ( ignoreLine ( line ) );
        n = atoi ( line.c_str() );
        // Create the Gaussian distribution of values for values of tauCritical
        std::vector<double> tauC_values = rng_Gaussian( n, param->tauCritical_mean, param->tauCritical_stdev );
       // Clear the dislocationSources vector before inserting new dislocation sources
        s->clearDislocationSources();
        // Read the dislocation sources
        for ( i=0; i<n; i++ ) {
            do {
                if ( fp.good() ) {
                    getline ( fp, line );
                }
                else {
                    fp.close ();
                    return ( false );
                }
            } while ( ignoreLine ( line ) );
            dSource = readDislocationSourceFromLine( line );
            // Set the tauCritical and time
            dSource->setTauCritical(tauC_values[i]);
            dSource->setTimeTillDipoleEmission(param->tauCritical_time);
            dSource->setBaseCoordinateSystem(s->getCoordinateSystem());
            dSource->refreshDislocation();
            dSource->calculateRotationMatrix();
            s->insertDislocationSource ( dSource );
        }

        fp.close();

        // Sort the dislocation and dislocation source lists
        s->sortDislocations();
        s->sortDislocationSources();
        // Update the defect list
        s->updateDefects();
        return (true);
    }
    else
    {
        return ( false );
    }
}

/**
 * @brief Read the slip system from file.
 * @param fileName Name of the file containing the data of the slip system.
 * @param s Pointer to the instance of the SlipSystem class that will contain the data. Memory for this instance should be pre-allocated.
 * @param currentTime Pointer to the variable holding the present time. Memory for this varibale should be pre-allocated.
 * @param param Pointer to the instance of the Parameter class, containing the parameters for the simulation.
 * @return Boolean flag indicating success or failure of the reading operation.
 */
bool readSlipSystem (std::string fileName, SlipSystem *s, double *currentTime, Parameter *param)
{
    std::ifstream fp ( fileName.c_str() );
    std::string line;

    Dislocation* disl;
    DislocationSource* dSource;
    SlipPlane* slipPlane;

    Vector3d *e;

    int nSlipPlanes, nDislocations, nDislocationSources;
    int i, j;
    int dSourceCount = 0;

    /**
     * @brief baseCoordinateSystem This is the basis for the slip plane co-ordinate system.
     */
    CoordinateSystem* baseCoordinateSystem = new CoordinateSystem();

    if ( fp.is_open() )
    {
        // Read the initial time
        do {
            if ( fp.good() ) {
                getline (fp, line);
            }
            else {
                fp.close();
                return (false);
            }
        } while ( ignoreLine(line) );
        *currentTime = atof(line.c_str());

        // Read the position
        do {
            if ( fp.good() ) {
                getline ( fp, line );
            }
            else {
                fp.close ();
                return ( false );
            }
        } while ( ignoreLine ( line ) );
        s->setPosition( readVectorFromLine ( line ) );

        // Read the normal
        do {
            if ( fp.good() ) {
                getline ( fp, line );
            }
            else {
                fp.close ();
                return ( false );
            }
        } while ( ignoreLine ( line ) );
        s->setNormal ( readVectorFromLine(line) );

        // Read the direction
        do {
            if ( fp.good() ) {
                getline ( fp, line );
            }
            else {
                fp.close ();
                return ( false );
            }
        } while ( ignoreLine ( line ) );
        s->setDirection ( readVectorFromLine(line) );

        // Create the co-ordinate system
        s->createCoordinateSystem(baseCoordinateSystem);

        // Read number of slip planes
        do {
            if ( fp.good() ) {
                getline ( fp, line );
            }
            else {
                fp.close ();
                return ( false );
            }
        } while ( ignoreLine ( line ) );
        nSlipPlanes = atoi ( line.c_str() );

        // Create the Gaussian distribution of values for values of tauCritical
        std::vector<double> tauC_values = rng_Gaussian( nSlipPlanes*MEAN_NUM_DISLOCATION_SOURCES_PERSLIPPLANE,
                                                        param->tauCritical_mean, param->tauCritical_stdev );

        // Clear the slip planes
        s->clearSlipPlanes();
        // Read the slip planes
        for (i=0; i<nSlipPlanes; i++) {
            // Allocate memory for the new slip plane
            slipPlane = new SlipPlane;

            // Read the position
            do {
                if ( fp.good() ) {
                    getline ( fp, line );
                }
                else {
                    fp.close ();
                    return ( false );
                }
            } while ( ignoreLine ( line ) );
            slipPlane->setPosition ( readVectorFromLine(line) );

            // Create the slip plane co-ordinate system
            slipPlane->createCoordinateSystem(s->getCoordinateSystem());

            // Read the extremities
            e = new Vector3d[2];
            do {
                if ( fp.good() ) {
                    getline ( fp, line );
                }
                else {
                    fp.close ();
                    return ( false );
                }
            } while ( ignoreLine ( line ) );
            e[0] = readVectorFromLine ( line );

            do {
                if ( fp.good() ) {
                    getline ( fp, line );
                }
                else {
                    fp.close ();
                    return ( false );
                }
            } while ( ignoreLine ( line ) );
            e[1] = readVectorFromLine ( line );

            slipPlane->setExtremities( e );
            delete[] ( e );
            e = NULL;

            // The normal to the slip plane is the z-axis of the slip system
            slipPlane->setNormal(Vector3d::unitVector(2));

            // Read number of dislocations
            do {
                if ( fp.good() ) {
                    getline ( fp, line );
                }
                else {
                    fp.close ();
                    return ( false );
                }
            } while ( ignoreLine ( line ) );
            nDislocations = atoi ( line.c_str() );
            // Clear the dislocations vector before inserting new dislocations.
            slipPlane->clearDislocations();
            // Read the dislocations
            for (j=0; j<nDislocations; j++) {
                do {
                    if ( fp.good() ) {
                        getline ( fp, line );
                    }
                    else {
                        fp.close ();
                        return ( false );
                    }
                } while ( ignoreLine ( line ) );
                disl = readDislocationFromLine(line);
                disl->setBaseCoordinateSystem(slipPlane->getCoordinateSystem());
                disl->calculateRotationMatrix();
                disl->calculateBurgersLocal();
                slipPlane->insertDislocation ( disl );
            }

            // Read number of dislocation sources
            do {
                if ( fp.good() ) {
                    getline ( fp, line );
                }
                else {
                    fp.close ();
                    return ( false );
                }
            } while ( ignoreLine ( line ) );
            nDislocationSources = atoi ( line.c_str() );

           // Clear the dislocationSources vector before inserting new dislocation sources
            slipPlane->clearDislocationSources();
            // Read the dislocation sources
            for ( j=0; j<nDislocationSources; j++ ) {
                do {
                    if ( fp.good() ) {
                        getline ( fp, line );
                    }
                    else {
                        fp.close ();
                        return ( false );
                    }
                } while ( ignoreLine ( line ) );
                dSource = readDislocationSourceFromLine( line );
                // Set the tauCritical and time
                dSource->setTauCritical(tauC_values[dSourceCount++]);
                if (dSourceCount == tauC_values.size()) {
                    displayMessage("Total number of dislocation sources exceeded population of critical stress values. Adjust variable MEAN_NUM_DISLOCATION_SOURCES_PERSLIPPLANE in file slipPlaneDefaults.h");
                    dSourceCount = 0;
                }
                dSource->setTimeTillDipoleEmission(param->tauCritical_time);
                dSource->setBaseCoordinateSystem(slipPlane->getCoordinateSystem());
                dSource->refreshDislocation();
                dSource->calculateRotationMatrix();
                slipPlane->insertDislocationSource ( dSource );
            }

            // All data for the slip plane has been read
            // Sort the dislocation and dislocation source lists
            slipPlane->sortDislocations();
            slipPlane->sortDislocationSources();
            // Update the defect list
            slipPlane->updateDefects();

            // Insert the slip plane into the vector containing slip planes
            s->insertSlipPlane(slipPlane);
        }

        // All slip planes have been read

        // Close the file
        fp.close();

        // Sort the slip planes according to position
        s->sortSlipPlanes();

        return (true);
    }
    else {
        return (false);
    }
}

/**
 * @brief Read the grain from file.
 * @param fileName Name of the file containing the data of the grain.
 * @param g Pointer to the instance of the Grain class that will contain the data. Memory for this instance should be pre-allocated.
 * @param currentTime Pointer to the variable holding the present time. Memory for this varibale should be pre-allocated.
 * @param param Pointer to the instance of the Parameter class, containing the parameters for the simulation.
 * @return Boolean flag indicating success or failure of the reading operation.
 */
bool readGrain (std::string fileName, Grain *g, double *currentTime, Parameter *param)
{
    std::ifstream fp ( fileName.c_str() );
    std::string line;

    Dislocation* disl;
    DislocationSource* dSource;
    SlipPlane* slipPlane;
    SlipSystem* slipSystem;

    // Vector3d *e;
    Vector3d slipPlaneTrace;
    Vector3d viewPlaneNormal;
    Vector3d slipNormalTrace;
    Vector3d S[2];
    Vector3d R, P, Q;

    int nSlipSystems, nSlipPlanes, nDislocations, nDislocationSources, nGBPoints;
    int i, j, k;
    int dSourceCount = 0;
    int nIntersections;
    std::vector<Vector3d> gbPoints;
    int d0d, d1d;

    /**
     * @brief baseCoordinateSystem This is the basis for the grain co-ordinate system.
     */
    CoordinateSystem* baseCoordinateSystem = new CoordinateSystem();

    if ( fp.is_open() )
    {
        // Read the initial time
        do {
            if ( fp.good() ) {
                getline (fp, line);
            }
            else {
                fp.close();
                return (false);
            }
        } while ( ignoreLine(line) );
        *currentTime = atof(line.c_str());

        // Read the grain orientation
        do {
            if ( fp.good() ) {
                getline (fp, line);
            }
            else {
                fp.close();
                return (false);
            }
        } while ( ignoreLine(line) );
        g->setOrientation(readVectorFromLine(line));

        // Read the grain boundary points
        do {
            if ( fp.good() ) {
                getline (fp, line);
            }
            else {
                fp.close();
                return (false);
            }
        } while ( ignoreLine(line) );
        nGBPoints = atof(line.c_str());

        gbPoints.clear();
        for (i=0; i<nGBPoints; i++) {
            do {
                if ( fp.good() ) {
                    getline (fp, line);
                }
                else {
                    fp.close();
                    return (false);
                }
            } while ( ignoreLine(line) );
            gbPoints.push_back(readVectorFromLine(line));
        }
        g->setGBPoints(gbPoints);

        g->calculateCoordinateSystem();
        g->setBaseCoordinateSystem(baseCoordinateSystem);
        g->calculateGBPointsLocal();

        // This is the polycrystal Z-axis, expressed in the local co-ordinate system.
        viewPlaneNormal = g->getCoordinateSystem()->vector_BaseToLocal_noTranslate(Vector3d::unitVector(2));

        // Read number of slip systems
        do {
            if ( fp.good() ) {
                getline (fp, line);
            }
            else {
                fp.close();
                return (false);
            }
        } while ( ignoreLine(line) );
        nSlipSystems = atoi (line.c_str());

        // Create the Gaussian distribution of values for values of tauCritical
        std::vector<double> tauC_values = rng_Gaussian( nSlipSystems*MEAN_NUM_SLIPPLANES_PER_SLIPSYSTEM*MEAN_NUM_DISLOCATION_SOURCES_PERSLIPPLANE,
                                                        param->tauCritical_mean, param->tauCritical_stdev );

        g->clearSlipSystems();
        for (i=0; i<nSlipSystems; i++) {
            // Allocate memory for the slip system
            slipSystem = new SlipSystem;
            // Read the position
            do {
                if ( fp.good() ) {
                    getline ( fp, line );
                }
                else {
                    fp.close ();
                    return ( false );
                }
            } while ( ignoreLine ( line ) );
            slipSystem->setPosition( readVectorFromLine ( line ) );

            // Read the normal
            do {
                if ( fp.good() ) {
                    getline ( fp, line );
                }
                else {
                    fp.close ();
                    return ( false );
                }
            } while ( ignoreLine ( line ) );
            slipSystem->setNormal ( readVectorFromLine(line) );

            /**
             * @brief slipPlaneTrace The trace of the slip plane on the view plane.
             * @details The trace of the slip plane on the view plane is required in order to calculate the extremities of the slip planes, which in turn will define the boundaries of the grain.
             */
            slipPlaneTrace = ( viewPlaneNormal ^ slipSystem->getNormal() ).normalize();
            // Since the slipPlaneTrace gives the slip direction, there is no need to get the slipDirection from file
            slipSystem->setDirection( slipPlaneTrace );

            /*
            // Read the direction
            do {
                if ( fp.good() ) {
                    getline ( fp, line );
                }
                else {
                    fp.close ();
                    return ( false );
                }
            } while ( ignoreLine ( line ) );
            slipSystem->setDirection ( readVectorFromLine(line) );
            */

            // Create the co-ordinate system
            slipSystem->createCoordinateSystem(g->getCoordinateSystem());

            // Read number of slip planes
            do {
                if ( fp.good() ) {
                    getline ( fp, line );
                }
                else {
                    fp.close ();
                    return ( false );
                }
            } while ( ignoreLine ( line ) );
            nSlipPlanes = atoi ( line.c_str() );

            slipSystem->clearSlipPlanes();
            for (j=0; j<nSlipPlanes; j++) {
                // Allocate memory for the slip plane
                slipPlane = new SlipPlane;

                // Read the position
                do {
                    if ( fp.good() ) {
                        getline ( fp, line );
                    }
                    else {
                        fp.close ();
                        return ( false );
                    }
                } while ( ignoreLine ( line ) );
                slipPlane->setPosition ( readVectorFromLine(line) );

                // Create the slip plane co-ordinate system
                slipPlane->createCoordinateSystem(slipSystem->getCoordinateSystem());

                // Read the extremities
                /*
                e = new Vector3d[2];
                do {
                    if ( fp.good() ) {
                        getline ( fp, line );
                    }
                    else {
                        fp.close ();
                        return ( false );
                    }
                } while ( ignoreLine ( line ) );
                e[0] = readVectorFromLine ( line );

                do {
                    if ( fp.good() ) {
                        getline ( fp, line );
                    }
                    else {
                        fp.close ();
                        return ( false );
                    }
                } while ( ignoreLine ( line ) );
                e[1] = readVectorFromLine ( line );
                */

                // Check for the intersections with the grain boundary
                // slipPlaneTrace = e[1] - e[0];   // Slip plane trace in the slip system co-ordinate system
                // slipPlaneTrace = slipSystem->getCoordinateSystem()->vector_LocalToBase_noTranslate(slipPlaneTrace); // Slip plane trace in the grain co-ordinate system

                R = slipSystem->getCoordinateSystem()->vector_LocalToBase(slipPlane->getPosition());    // Slip Plane position in grain co-ordinate system
                gbPoints = g->getGBPoints_local();  // Grain boundary points in the grain co-ordinate system
                // Detect intersections
                nIntersections = 0;
                for (k=0; k<(nGBPoints-1); k++) {
                    P = gbPoints.at(k);
                    Q = gbPoints.at(k+1);
                    if (intersection(R, slipPlaneTrace, P, Q, (S+nIntersections))) {
                        nIntersections++;
                        if (nIntersections==2) {
                            break;
                        }
                    }
                }

                if (nIntersections==2) {
                    // Both intersections were found. We can now create the slip plane
                    S[0] = slipSystem->getCoordinateSystem()->vector_BaseToLocal(S[0]);
                    S[1] = slipSystem->getCoordinateSystem()->vector_BaseToLocal(S[1]);
                    slipPlane->setExtremities(S);

                    // The normal to the slip plane is the z-axis of the slip system
                    slipPlane->setNormal(Vector3d::unitVector(2));

                    // Read number of dislocations
                    do {
                        if ( fp.good() ) {
                            getline ( fp, line );
                        }
                        else {
                            fp.close ();
                            return ( false );
                        }
                    } while ( ignoreLine ( line ) );
                    nDislocations = atoi ( line.c_str() );
                    // Clear the dislocations vector before inserting new dislocations.
                    slipPlane->clearDislocations();
                    // Read the dislocations
                    for (k=0; k<nDislocations; k++) {
                        do {
                            if ( fp.good() ) {
                                getline ( fp, line );
                            }
                            else {
                                fp.close ();
                                return ( false );
                            }
                        } while ( ignoreLine ( line ) );
                        disl = readDislocationFromLine(line);
                        disl->setBaseCoordinateSystem(slipPlane->getCoordinateSystem());
                        disl->calculateRotationMatrix();
                        disl->calculateBurgersLocal();
                        d0d = (int) Defect::compareDefectPositions(slipPlane->getGrainBoundary(0), disl);
                        d1d = (int) Defect::compareDefectPositions(slipPlane->getGrainBoundary(1), disl);
                        if (d0d != d1d) {
                            // The dislocation is really inside the slip plane
                            slipPlane->insertDislocation ( disl );
                        }
                        else {
                            delete (disl);
                            disl = NULL;
                        }
                    }

                    // Read number of dislocation sources
                    do {
                        if ( fp.good() ) {
                            getline ( fp, line );
                        }
                        else {
                            fp.close ();
                            return ( false );
                        }
                    } while ( ignoreLine ( line ) );
                    nDislocationSources = atoi ( line.c_str() );

                   // Clear the dislocationSources vector before inserting new dislocation sources
                    slipPlane->clearDislocationSources();
                    // Read the dislocation sources
                    for ( k=0; k<nDislocationSources; k++ ) {
                        do {
                            if ( fp.good() ) {
                                getline ( fp, line );
                            }
                            else {
                                fp.close ();
                                return ( false );
                            }
                        } while ( ignoreLine ( line ) );
                        dSource = readDislocationSourceFromLine( line );
                        // Set the tauCritical and time
                        dSource->setTauCritical(tauC_values[dSourceCount++]);
                        if (dSourceCount == tauC_values.size()) {
                            displayMessage("Total number of dislocation sources exceeded population of critical stress values. Adjust variable MEAN_NUM_DISLOCATION_SOURCES_PERSLIPPLANE in file slipPlaneDefaults.h");
                            dSourceCount = 0;
                        }
                        dSource->setTimeTillDipoleEmission(param->tauCritical_time);
                        dSource->setBaseCoordinateSystem(slipPlane->getCoordinateSystem());
                        dSource->refreshDislocation();
                        dSource->calculateRotationMatrix();
                        d0d = (int) Defect::compareDefectPositions(slipPlane->getGrainBoundary(0), dSource);
                        d1d = (int) Defect::compareDefectPositions(slipPlane->getGrainBoundary(1), dSource);
                        if (d0d != d1d) {
                            // The dislocation is really inside the slip plane
                            slipPlane->insertDislocationSource ( dSource );
                        }
                        else {
                            delete (dSource);
                            dSource = NULL;
                        }
                    }

                    // All data for the slip plane has been read
                    // Sort the dislocation and dislocation source lists
                    slipPlane->sortDislocations();
                    slipPlane->sortDislocationSources();
                    // Update the defect list
                    slipPlane->updateDefects();

                    // Insert the slip plane into the vector containing slip planes
                    slipSystem->insertSlipPlane(slipPlane);
                }
                else {
                    // This slip plane does not lie within the grain - ignore it
                    delete (slipPlane);
                    slipPlane = NULL;
                    continue;   // Go to next slip plane
                }


            }

            // Insert slip system into grain
            g->insertSlipSystem(slipSystem);
        }

        fp.close();
        return (true);
    }
    else {
        return (false);
    }
}

/**
 * @brief Reads 3 values from a string and returns them in a Vector3d.
 * @param s The string that is to be read from.
 * @return Vector3d object containing the 3 values read.
 */
Vector3d readVectorFromLine (std::string s)
{
    std::stringstream ss ( s );
    std::string a;
    int i;
    Vector3d v;

    for ( i=0; i<3; i++ )
    {
        ss >> a;
        v.setValue( i, atof( a.c_str() ) );
    }

    return ( v );
}

/**
 * @brief Reads the data from a line and builds a dislocation from it.
 * @param s The string that is to be read from.
 * @return Pointer to the dislocation.
 */
Dislocation* readDislocationFromLine (std::string s)
{
    std::stringstream ss ( s );
    std::string a;
    Vector3d pos, bvec, lvec;
    double bmag;
    bool mob;

    int i;

    // Read position
    for ( i=0; i<3; i++ ) {
        ss >> a;
        pos.setValue ( i, atof ( a.c_str() ) );
    }

    // Read Burgers vector
    for ( i=0; i<3; i++ ) {
        ss >> a;
        bvec.setValue ( i, atof ( a.c_str() ) );
    }

    // Read line vector
    for ( i=0; i<3; i++ ) {
        ss >> a;
        lvec.setValue ( i, atof ( a.c_str() ) );
    }

    // Read Burgers vector magnitude
    ss >> a;
    bmag = atof ( a.c_str() );

    // Read mobility
    ss >> a;
    mob = ( bool ) atoi ( a.c_str() );

    Dislocation* dislocation = new Dislocation ( bvec, lvec, pos, bmag, mob );
    return (dislocation);
}

/**
 * @brief Reads the data from a line and builds a dislocation source from it.
 * @param s The string that is to be read from.
 * @return Pointer to the dislocation source.
 */
DislocationSource* readDislocationSourceFromLine(std::string s)
{
    std::stringstream ss ( s );
    std::string a;
    Vector3d pos, bvec, lvec;
    double bmag;

    int i;

    // Read position
    for ( i=0; i<3; i++ ) {
        ss >> a;
        pos.setValue ( i, atof ( a.c_str() ) );
    }

    // Read Burgers vector
    for ( i=0; i<3; i++ ) {
        ss >> a;
        bvec.setValue ( i, atof ( a.c_str() ) );
    }

    // Read line vector
    for ( i=0; i<3; i++ ) {
        ss >> a;
        lvec.setValue ( i, atof ( a.c_str() ) );
    }

    // Read Burgers vector magnitude
    ss >> a;
    bmag = atof ( a.c_str() );

    DislocationSource* dSource = new DislocationSource ( bvec, lvec, pos, bmag, 0.0, 0.0 );
    return (dSource);
}
