/**
 * @file simulateGrain.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 26/11/2013
 * @brief Defintion of various functions to simulate dislocation motion within a single grain.
 * @details This file defines the various functions to simulate dislocation motion within a single grain.
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

#include "simulateGrain.h"

/**
 * @brief This function manages the simulation of dislocation motion in a single grain. It is the point of entry into the simulation.
 */
void simulateSingleGrain ()
{
    std::string fileName;
    std::string message;

    std::cout << "Parameter file name: ";
    std::cin >> fileName;

    Grain *grain;
    Parameter *param = new Parameter;

    double currentTime;

    if (param->getParameters(fileName)) {
        message = "Success: read file " + fileName;
        displayMessage ( message );
        message.clear ();

        grain = new Grain;

        fileName.clear();
        fileName = param->input_dir + "/" + param->dislocationStructureFile;
        if (readGrain(fileName, grain, &currentTime, param)) {
            message = "Success: read file " + fileName;
            displayMessage ( message );
            message.clear ();

            grain_iterate(param, grain, currentTime);
        }
        else {
            message = "Error: Unable to read grain from file " + fileName;
            displayMessage ( message );
            message.clear ();
        }

        delete (grain);
        grain = NULL;
        fileName.clear();
    }
    else {
        message = "Error: Unable to read parameter file " + fileName;
        displayMessage ( message );
        message.clear ();
    }

    delete (param);
    param = NULL;
}

/**
 * @brief This is an overloaded function. This function manages the simulation of dislocation motion in a single grain. It is the point of entry into the simulation.
 * @param fileName String containing the name of the parameters file.
 */
void simulateSingleGrain(std::string fileName)
{
    std::string message;

    Grain *grain;
    Parameter *param = new Parameter;

    double currentTime;

    if (param->getParameters(fileName)) {
        message = "Success: read file " + fileName;
        displayMessage ( message );
        message.clear ();

        grain = new Grain;

        fileName.clear();
        fileName = param->input_dir + "/" + param->dislocationStructureFile;
        if (readGrain(fileName, grain, &currentTime, param)) {
            message = "Success: read file " + fileName;
            displayMessage ( message );
            message.clear ();

            grain_iterate(param, grain, currentTime);
        }
        else {
            message = "Error: Unable to read grain from file " + fileName;
            displayMessage ( message );
            message.clear ();
        }

        delete (grain);
        grain = NULL;
        fileName.clear();
    }
    else {
        message = "Error: Unable to read parameter file " + fileName;
        displayMessage ( message );
        message.clear ();
    }

    delete (param);
    param = NULL;
}

/**
 * @brief This function handles the iterations in the simulation of dislocation motion in a single grain.
 * @param param Pointer to the instance of the Parameter class containing the simulation parameters.
 * @param grain Pointer to the instance of the Grain class containing all data for the grain.
 * @param currentTime The value of the current simulation time.
 */
void grain_iterate (Parameter* param, Grain* grain, double currentTime)
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

    // Calculate the applied stress on the grain and it's slip systems
    grain->calculateGrainAppliedStress(param->appliedStress);
    grain->calculateSlipSystemAppliedStress();

    displayMessage("Starting simulation...");

    // Start the simulation
    while (continueSimulation) {
        // Calculate the stresses on all slip defects
        grain->calculateAllStresses(param->mu, param->nu);

        // Calculate the forces and velocities of the dislocations
        grain->calculateDislocationVelocities(param->B);

        // Time increment
        switch (param->timeStepType) {
        case ADAPTIVE:
            // This part is incomplete
            timeIncrement = grain->calculateTimeIncrement(limitingDistance, param->limitingTimeStep);
            break;
        case FIXED:
            grain->setSlipSystemTimeIncrements(param->limitingTimeStep);
            grain->moveAllDislocations(limitingDistance, param->limitingTimeStep, param->mu, param->nu);
            break;
        }

        // Check dislocation sources for dipole emissions
        grain->checkDislocationSources(param->limitingTimeStep, param->mu, param->nu, limitingDistance);

        // Check for local reactions
        grain->checkGrainLocalReactions(reactionRadius);

        // Increment counters
        totalTime += param->limitingTimeStep;
        simulationTime.push_back ( totalTime );
        nIterations++;

        message = "Iteration " + intToString ( nIterations ) + "; Total time " + doubleToString ( totalTime );
        displayMessage ( message );
        message.clear ();

        // Write statistics

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

    UniqueID* uid_instance = UniqueID::getInstance();
    std::string uniquesFileName = param->output_dir + "/uniquesFile.txt";
    uid_instance->writeDefects(uniquesFileName);
    uniquesFileName.clear();
}
