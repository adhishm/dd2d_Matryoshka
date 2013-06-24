/**
 * @file simulateSingleSlipPlane.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 18/06/2013
 * @brief Defintion various functions to simulate dislocation motion on a single slip plane.
 * @details This file defines various functions to simulate dislocation motion on a single slip plane. It also writes statistics to files which will be treated separately.
 */

#include "simulateSingleSlipPlane.h"

/**
 * @brief This function manages the simulation for a single slip plane.
 * @details This function is the point of entry into a simulation with a single slip plane.
 */
void simulateSingleSlipPlane ()
{
  std::string fName;
  std::string message;

  std::cout << "Parameter file name: ";
  std::cin >> fName;

  SlipPlane *slipPlane;

  Parameter *param = new Parameter;

  if ( param->getParameters( fName ) )
  {
      message = "Success: read file " + fName;
      displayMessage ( message );
      message.clear ();

      slipPlane = new SlipPlane;

      fName.clear ();
      fName = param->input_dir + "/" + param->dislocationStructureFile;
      if ( readSlipPlane ( fName, slipPlane ) )
      {
          message = "Success: read file " + fName;
          displayMessage ( message );
          message.clear ();

          singleSlipPlane_iterate ( param, slipPlane );
      }
      else {
          message = "Error: Unable to read slip plane from file " + fName;
          displayMessage ( message );
          message.clear ();
      }

      delete ( slipPlane );
      slipPlane = NULL;
      fName.clear ();
  }
  else {
      message = "Error: Unable to read parameter file " + fName;
      displayMessage ( message );
      message.clear ();
  }

  delete ( param );
  param = NULL;
}

/**
 * @brief Reads the slip plane details from the file.
 * @details The details of the slip plane and its dislocations are stored in a file the name of which is provided. This file is read and the information is saved into the instance of the SlipPlane class, the pointer to which is given.
 * @param fileName String containing the name of the file.
 * @param s Pointer to the instance of SlipPlane into which all data is to be stored.
 * @return Flag indicating the success or failure of the operation.
 */
bool readSlipPlane (std::string fileName, SlipPlane *s)
{
    std::ifstream fp ( fileName.c_str() );
    std::string line;

    Vector3d *e;
    int i,  n;

    if ( fp.is_open() )
    {
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
        delete ( e );
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
            s->insertDislocation ( readDislocationFromLine ( line ) );
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
            s->insertDislocationSource ( readDislocationSourceFromLine ( line ) );
        }

        fp.close();
	return (true);
    }
    else
    {
        return ( false );
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
 * @return The dislocation.
 */
Dislocation readDislocationFromLine (std::string s)
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

    return ( Dislocation ( bvec, lvec, pos, bmag, mob ) );
}

/**
 * @brief Reads the data from a line and builds a dislocation source from it.
 * @param s The string that is to be read from.
 * @return The dislocation source.
 */
DislocationSource readDislocationSourceFromLine (std::string s)
{
    std::stringstream ss ( s );
    std::string a;
    Vector3d pos, bvec, lvec;
    double bmag;
    double tau;
    double timeLimit;

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

    // Read critical stress
    ss >> a;
    tau = atof ( a.c_str() );

    // Read time limit for dipole emission
    ss >> a;
    timeLimit = atof ( a.c_str() );

    return ( DislocationSource ( bvec, lvec, pos, bmag, tau, timeLimit ) );
}

/**
 * @brief Carry out the iterations for the simulation of dislocation motion on a single slip plane.
 * @param param Pointer to the instance of the Parameter class containing all simulation parameters.
 * @param slipPlane Pointer to the instance of the SlipPlane class containing the data for the dislocation structure.
 */
void singleSlipPlane_iterate (Parameter *param, SlipPlane *slipPlane)
{
    double totalTime = 0.0;
    int nIterations = 0;

    std::vector<double> simulationTime;
    std::vector<double> timeIncrement;

    bool continueSimulation = true;

    std::string fileName;
    std::ostringstream timeString;
    std::ostringstream iterationString;
    std::string message;

    displayMessage ( "Starting simulation..." );

    while ( continueSimulation ) {
        // Calculate stresses
        slipPlane->calculateDislocationStresses ( param->appliedStress, param->mu, param->nu );

        // Calculate forces on dislocations
        slipPlane->calculateDislocationForces ( param->tau_crss );

        // Calculate dislocation velocities
        slipPlane->calculateVelocities ( param->B );

        // Calculate the time increment
        timeIncrement = slipPlane->calculateTimeIncrement ( ( param->limitingDistance * param->bmag ), param->limitingTimeStep );

        // Displace the dislocations
        slipPlane->moveDislocations ( timeIncrement );

        // Increment counters
        totalTime += slipPlane->getTimeIncrement ();
        simulationTime.push_back ( totalTime );
        nIterations++;

        timeString << totalTime;
        iterationString << nIterations;

        message = "Iteration " + iterationString.str() + "; Total time " + timeString.str();
        displayMessage ( message );
        message.clear ();

        // Write statistics
        if ( param->dislocationPositions.ifWrite() ) {
            fileName = param->output_dir + "/" + param->dislocationPositions.name + timeString.str() + ".txt";
            slipPlane->writeSlipPlane ( fileName );
            fileName.clear ();
        }

        if ( param->slipPlaneStressDistributions.ifWrite() ) {
            fileName = param->output_dir + "/" + param->slipPlaneStressDistributions.name + timeString.str() + ".txt";
            slipPlane->writeSlipPlaneStressDistribution ( fileName,
                                                          param->slipPlaneStressDistributions.parameters[0],
                                                          param);
            fileName.clear ();
        }

        // Check for stopping criterion
        if ( param->stopAfterTime ) {
            // The stopping criterion is time
            continueSimulation = ( totalTime <= param->stopTime );
        }
        else {
            // The stopping criterion is iterations
            continueSimulation = ( nIterations <= param->stopIterations );
        }

    }
}
