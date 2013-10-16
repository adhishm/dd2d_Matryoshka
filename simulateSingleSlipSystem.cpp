/**
 * @file simulateSingleSlipSystem.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 10/10/2013
 * @brief Definition various functions to simulate dislocation motion on a single slip system.
 * @details This file defines various functions to simulate dislocation motion on a single slip system.
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

#include "simulateSingleSlipSystem.h"

/**
 * @brief This function is the point of entry for simulating a single slip system.
 * @details This function handles the simulation of a single slip system, from reading input files, to calling managing the iterations.
 */
void simulateSingleSlipSystem ()
{
    std::string fName;
    std::string message;

    std::cout << "Parameter file name: ";
    std::cin >> fName;

    SlipSystem *slipSystem;

    Parameter *param = new Parameter;

    double currentTime;

    if ( param->getParameters( fName ) )
    {
        message = "Success: read file " + fName;
        displayMessage ( message );
        message.clear ();

        slipSystem = new SlipSystem;

        fName.clear ();
        fName = param->input_dir + "/" + param->dislocationStructureFile;
        if ( readSlipSystem ( fName, slipSystem, &currentTime, param ) ) {
            message = "Success: read file " + fName;
            displayMessage ( message );
            message.clear ();

            singleSlipSystem_iterate( param, slipSystem, currentTime );
        }
        else {
            message = "Error: Unable to read slip plane from file " + fName;
            displayMessage ( message );
            message.clear ();
        }

        delete ( slipSystem );
        slipSystem = NULL;
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
 * @brief Carry out the iterations for the simulation of dislocation motion on a single slip system.
 * @param param Pointer to the instance of the Parameter class containing all simulation parameters.
 * @param slipSystem Pointer to the instance of the SlipSystem class containing the data for the dislocation structure.
 * @param currentTime The value of time at the beginning of the simulation.
 */
void singleSlipSystem_iterate (Parameter *param, SlipSystem *slipSystem, double currentTime)
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

    // Calculate the applied stress in the slip system's co-ordinate systems
    // as well as on each slip plane, in their local co-ordinate systems
    slipSystem->calculateSlipSystemAppliedStress(param->appliedStress);
    slipSystem->calculateSlipPlaneAppliedStress();

    displayMessage ( "Starting simulation..." );

    // Start the simulation
    while (continueSimulation) {
        // Calculate stresses on all defects
        slipSystem->calculateAllStresses(param->mu, param->nu);

        // Calculate dislocation velocities
        slipSystem->calculateSlipPlaneDislocationForcesVelocities(param->B);

        // Time increment
        switch (param->timeStepType) {
        case ADAPTIVE:
            // This part is pending
            break;

        case FIXED:
            //
            break;
        }

        //
    }
}
