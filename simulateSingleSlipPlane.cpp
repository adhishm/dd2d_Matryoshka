/**
 * @file simulateSingleSlipPlane.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 17/07/2013
 * @brief Defintion various functions to simulate dislocation motion on a single slip plane.
 * @details This file defines various functions to simulate dislocation motion on a single slip plane. It also writes statistics to files which will be treated separately.
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

    double currentTime;

    if ( param->getParameters( fName ) )
    {
        message = "Success: read file " + fName;
        displayMessage ( message );
        message.clear ();

        slipPlane = new SlipPlane;

        fName.clear ();
        fName = param->input_dir + "/" + param->dislocationStructureFile;
        if ( readSlipPlane ( fName, slipPlane, &currentTime, param ) )
        {
            message = "Success: read file " + fName;
            displayMessage ( message );
            message.clear ();

            singleSlipPlane_iterate ( param, slipPlane, currentTime );
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

    delete (slipPlane);
    slipPlane = NULL;
}

/**
 * @brief Carry out the iterations for the simulation of dislocation motion on a single slip plane.
 * @param param Pointer to the instance of the Parameter class containing all simulation parameters.
 * @param slipPlane Pointer to the instance of the SlipPlane class containing the data for the dislocation structure.
 * @param currentTime The value of time at the beginning of the simulation.
 */
void singleSlipPlane_iterate (Parameter *param, SlipPlane *slipPlane, double currentTime)
{
    double totalTime = currentTime;
    int nIterations = 0;

    std::vector<double> simulationTime;
    std::vector<double> timeIncrement;

    bool continueSimulation = true;

    std::string fileName;
    std::string message;

    double limitingDistance = ( param->limitingDistance * param->bmag );
    double reactionRadius = ( param->reactionRadius * param->bmag );

    // Calculate stresses in slip plane system.
    slipPlane->calculateSlipPlaneAppliedStress(param->appliedStress);

    displayMessage ( "Starting simulation..." );

    // Write statistics
    if ( param->dislocationPositions.ifWrite() ) {
        fileName = param->output_dir + "/" + param->dislocationPositions.name + doubleToString ( totalTime ) + ".txt";
        slipPlane->writeSlipPlane ( fileName, totalTime );
        fileName.clear ();
    }

    if ( param->slipPlaneStressDistributions.ifWrite() ) {
        fileName = param->output_dir + "/" + param->slipPlaneStressDistributions.name + doubleToString ( totalTime ) + ".txt";
        slipPlane->writeSlipPlaneStressDistribution ( fileName,
                                                      param->slipPlaneStressDistributions.parameters[0],
                                                      param );
        fileName.clear ();
    }

    while ( continueSimulation ) {
        // Calculate stresses on all defects
        slipPlane->calculateDefectStresses ( param->mu, param->nu );

        /*
         * Treat the dislocations
         */
        // Calculate forces on dislocations
        slipPlane->calculateDislocationForces ();
        // Calculate dislocation velocities
        slipPlane->calculateDislocationVelocities ( param->B );
        switch (param->timeStepType) {
        case ADAPTIVE:
            // Calculate the time increment
            timeIncrement = slipPlane->calculateTimeIncrement ( limitingDistance,
                                                                param->limitingTimeStep );
            // Displace the dislocations
            slipPlane->moveDislocations ( timeIncrement );
            break;

        case FIXED:
            slipPlane->setTimeIncrement(param->limitingTimeStep);
            slipPlane->moveDislocationsToLocalEquilibrium( limitingDistance,
                                                           param->limitingTimeStep,
                                                           param->mu, param->nu );
            break;
        }

        /*
         * Treat the dislocation sources
         */
        slipPlane->checkDislocationSources(slipPlane->getTimeIncrement(),param->mu, param->nu,limitingDistance);

        // Check for local reactions
        slipPlane->checkLocalReactions(reactionRadius);

        // Increment counters
        totalTime += slipPlane->getTimeIncrement ();
        simulationTime.push_back ( totalTime );
        nIterations++;

        message = "Iteration " + intToString ( nIterations ) + "; Total time " + doubleToString ( totalTime );
        displayMessage ( message );
        message.clear ();

        // Write statistics
        if ( param->dislocationPositions.ifWrite() ) {
            fileName = param->output_dir + "/" + param->dislocationPositions.name + doubleToString ( totalTime ) + ".txt";
            slipPlane->writeSlipPlane ( fileName, totalTime );
            fileName.clear ();
        }

        if ( param->slipPlaneStressDistributions.ifWrite() ) {
            fileName = param->output_dir + "/" + param->slipPlaneStressDistributions.name + doubleToString ( totalTime ) + ".txt";
            slipPlane->writeSlipPlaneStressDistribution ( fileName,
                                                          param->slipPlaneStressDistributions.parameters[0],
                                                          param );
            fileName.clear ();
        }

        if ( param->allDefectPositions.ifWrite() ) {
            fileName = param->output_dir + "/" + param->allDefectPositions.name + ".txt";
            slipPlane->writeAllDefects( fileName, totalTime );
            fileName.clear();
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
