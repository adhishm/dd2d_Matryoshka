/**
 * @file simulatePolycrystal.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 16/12/2013
 * @brief Definition of various functions to simulate dislocation motion within a polycrystal.
 * @details This file defines various functions to simulate dislocation motion within a polycrystal.
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

#include "simulatePolycrystal.h"

/**
 * @brief This function manages the simulation of dislocation motion in a polycrystal. It is the point of entry into the simulation.
 */
void simulateSinglePolycrystal ()
{
    std::string fileName;
    std::cout << "Parameter file name: ";
    std::cin >> fileName;

    simulateSinglePolycrystal(fileName);
    fileName.clear();
}

/**
 * @brief This is an overloaded function. This function manages the simulation of dislocation motion in a polycrystal. It is the point of entry into the simulation.
 * @param fileName String containing the name of the parameters file.
 */
void simulateSinglePolycrystal(std::string fileName)
{
    std::string message;

    Polycrystal* polycrystal;
    Parameter* param = new Parameter;

    double currentTime;

    if (param->getParameters(fileName)) {
        message = "Success: read file " + fileName;
        displayMessage(message);
        message.clear();

        polycrystal = new Polycrystal;

        fileName.clear();
        fileName = param->input_dir + "/" + param->dislocationStructureFile;

        if (readPolycrystal(fileName, polycrystal, &currentTime, param)) {
            message = "Success: read file " + fileName;
            displayMessage ( message );
            message.clear ();

            polycrystal_iterate(param, polycrystal, currentTime);
        }
        else {
            message = "Error: Unable to read polycrystal from file " + fileName;
            displayMessage ( message );
            message.clear ();
        }

        delete (polycrystal);
        polycrystal = NULL;
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
 * @brief This function handles the iterations in the simulation of dislocation motion in a single polycrystal.
 * @param param Pointer to the instance of the Parameter class containing the simulation parameters.
 * @param polycrystal Pointer to the instance of the Polycrystal class containing all data for the polycrystal.
 * @param currentTime The value of the current simulation time.
 */
void polycrystal_iterate (Parameter* param, Polycrystal* polycrystal, double currentTime)
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
    polycrystal->setAppliedStress(param->appliedStress);
    polycrystal->calculateGrainAppliedStress();

    displayMessage("Starting simulation...");

    // Start the simulation
    while (continueSimulation) {
        // Calculate the stress on all defects
        polycrystal->calculateAllStresses(param->mu, param->nu);

        // Calculate dislocation velocities
        polycrystal->calculateDislocationVelocities(param->B);

        // Time increment
        switch (param->timeStepType) {
        case ADAPTIVE:
            // This section is incomplete; do nothing
            break;
        case FIXED:
            polycrystal->setGrainTimeIncrements(param->limitingTimeStep);
            polycrystal->moveAllDislocations(limitingDistance, param->limitingTimeStep, param->mu, param->nu);
            break;
        }

        // Check dislocation sources for dipole emissions
        polycrystal->checkDislocationSources(param->limitingTimeStep, param->mu, param->nu, limitingDistance);

        // Check for local reactions
        polycrystal->checkPolycrystalLocalReactions(reactionRadius);

        // Increment counters
        totalTime += param->limitingTimeStep;
        simulationTime.push_back ( totalTime );
        nIterations++;

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
