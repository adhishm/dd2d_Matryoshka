/**
 * @file parameter.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 11/06/2013
 * @brief Declaration of the Parameter class which will hold all simulation parameters.
 * @details This file declares the Parameter class which will hold all simulation parameters.
 */

#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "stress.h"
#include "statistics.h"

/**
 * @brief Parameter class to hold all simulation parameters.
 * @details The simulation needs several parameters - such as material properties, stopping criterion, time steps, etc. - in order to function. An instance of this class will hold all these values in one place for easy access throughout the simulation. All data in this class is made public to facilitate access throughout the simulation.
 */
class Parameter
{
public:
    // Material properties
    /**
     * @brief Shear modulus of the material, in Pa.
     */
    double mu;
    
    /**
     * @brief Poisson's ratio, dimensionless.
     */
    double nu;
    
    /**
     * @brief Magnitude of the Burgers vector, in m.
     */
    double bmag;
    
    // Load
    /**
     * @brief The externally applied load.
     * @details The externally applied load is expressed as a complete stress tensor.
     */
    Stress appliedStress;

    // Dislocation structure data / source file names
    std::string dislocationStructureFile;
    
    // Simulation parameters
    /**
     * @brief Stopping criterion.
     * @details This variable is a flag to indicate the stopping criterion. If it is true, then the simulation will stop when it reaches the time specified in the variable stopTime. If it is false, the simulation will stop after reaching the number of iterations specified in the variable stopIterations.
     */
    bool stopAfterTime;
    
    /**
     * @brief The amount of time (in the simulation) after which the simulation will stop.
     */
    double stopTime;
    
    /**
     * @brief The number of iterations after which the simulation will stop.
     */
    int stopIterations;
    
    /**
     * @brief The minimum distance permitted between defects on a given slip plane, as a multiple of the Burgers vector magnitude.
     * @details In the simulation, a limiting distance of approach is specified in order to avoid one defect overtaking another without interacting with it. This distance is given by this variable. It is specified as a multiple of the magnitude of the Burger vector. For example, if the Burgers vector is 5 nm and the limiting distance is 20 nm, this variable should have the value 4.0.
     */
    double limitingDistance;
    
    /**
     * @brief The radius around a defect in which local reactions with other defects will be searched for, as a multiple of the Burgers vector magnitude.
     * @details In the simulation, two defects may collide and the resulting reaction depends on the type of defects. This collision is considered to happen within a certain radius around the defect. This radius is given by this variable as a multiple of the Burgers vector magnitude. It should typically be just a little larger than the limitingDistance variable.
     */
    double reactionRadius;
    
    /**
     * @brief The smallest time step permitted in an iteration.
     * @details In the simulations, the time increment is calculated in each iteration depending on the velocities of the defects. However, the time increment is not allowed to be smaller than the value provided in this variable.
     */
    double limitingTimeStep;
    
    // Satistics
    /**
     * @brief Indicator about writing dislocation positions to file and its frequency.
     */
    Statistics dislocationPositions;
    
    /**
     * @brief Indicator about writing the slip plane stress distribution to file and its frequency.
     */
    Statistics slipPlaneStressDistributions;

    // Functions
    /**
     * @brief Read parameters from file whose name is provided.
     * @param fileName Name of the file containing the parameters.
     * @return True/false indicating success/failure of parameter reading.
     */
    bool getParameters (std::string fileName);
    
    /**
     * @brief Reads the data from the line and stores it into the appropriate variable.
     * @details The first word of the line indicates what kind of data it contains. This function then reads this data and stores it accordingly. If the first character of the line is #, the line is considered to be a comment and is ignored.
     * @param line String with the text present in the line.
     */
    void parseLineData (std::string line);
};

#endif
