/**
 * @file parameter.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 12/06/2013
 * @brief Definition of member functions of the Parameter class which will hold all simulation parameters.
 * @details This file defines member functions of the Parameter class which will hold all simulation parameters.
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


#include "parameter.h"

/**
 * @brief Read parameters from file whose name is provided.
 * @param fileName Name of the file containing the parameters.
 * @return True/false indicating success/failure of parameter reading.
 */
bool Parameter::getParameters (std::string fileName)
{
  // Open file
  std::ifstream fp (fileName.c_str());
  std::string line;

  if (fp.is_open())
  {
    while (fp.good())
    {
      getline (fp, line);
      if ( !ignoreLine ( line ) )
          parseLineData (line);
    }
    fp.close();
    return (true);
  }
  else
  {
    return (false);
  }
}

/**
 * @brief Reads the data from the line and stores it into the appropriate variable.
 * @details The first word of the line indicates what kind of data it contains. This function then reads this data and stores it accordingly. If the first character of the line is #, the line is considered to be a comment and is ignored.
 * @param line String with the text present in the line.
 */
void Parameter::parseLineData (std::string line)
{
    std::stringstream ss(line);
    std::string first;
    std::string v;

    ss >> first;

    // Shear modulus
    if (first=="mu" || first=="Mu" || first=="MU")
    {
        ss >> v;
        this->mu = atof (v.c_str());
        return;
    }

    // Poisson's ratio
    if (first=="nu" || first=="Nu" || first=="NU")
    {
        ss >> v;
        this->nu = atof(v.c_str());
        return;
    }

    // Burgers vector magnitude
    if (first=="bmag" || first=="Bmag" || first=="BMag")
    {
        ss >> v;
        this->bmag = atof(v.c_str());
        return;
    }

    // Drag coefficient
    if ( first=="drag" || first=="Drag" )
    {
        ss >> v;
        this->B = atof( v.c_str() );
        return;
    }

    // Tau critical mean
    if ( first=="tauCritical_mean" ) {
        ss >> v;
        this->tauCritical_mean = atof ( v.c_str() );
        return;
    }

    // Tau critical standard deviation
    if ( first=="tauCritical_stdev" ) {
        ss >> v;
        this->tauCritical_stdev = atof ( v.c_str() );
        return;
    }

    // Tau critical time
    if ( first=="tauCritical_time" ) {
        ss >> v;
        this->tauCritical_time = atof ( v.c_str() );
        return;
    }

    // Applied stress
    if (first=="appliedStress")
    {
        int i;
        double principalStresses[3];
        double shearStresses[3];
        for (i=0; i<3; i++)
        {
            ss >> v;
            principalStresses[i] = atof(v.c_str());
        }
        for (i=0; i<3; i++)
        {
            ss >> v;
            shearStresses[i] = atof(v.c_str());
        }

        this->appliedStress = Stress(principalStresses, shearStresses);
        return;
    }

    // Stopping criterion
    if (first=="stopping" || first=="Stopping")
    {
      ss >> v;
      this->stopAfterTime = (v=="time" || v=="Time");

      ss >> v;

      if (this->stopAfterTime)
      {
          // There is a time limit
          this->stopTime = atof (v.c_str());
      }
      else
      {
          // There is an iterations limit
          this->stopIterations = atoi (v.c_str());
      }

      return;
    }

    // Time step kind
    if (first=="TimeStep" || first=="timestep" || first=="Timestep" || first=="timeStep")
    {
        ss >> v;
        if (v=="adaptive" || v=="Adaptive")
        {
            this->timeStepType = ADAPTIVE;
        }
        else
        {
            this->timeStepType = FIXED;
        }
    }

    // Limiting distance
    if (first=="limitingDistance" || first=="LimitingDistance")
    {
        ss >> v;
        this->limitingDistance = atof (v.c_str());
        return;
    }

    // Reaction radius
    if (first=="reactionRadius" || first=="ReactionRadius")
    {
        ss >> v;
        this->reactionRadius = atof (v.c_str());
        return;
    }

    // Limiting time step
    if (first=="limitingTimeStep" || first=="LimitingTimeStep")
    {
        ss >> v;
        this->limitingTimeStep = atof (v.c_str());
        return;
    }

    // Directories
    if ( first=="input" || first=="Input" ) {
        ss >> v;
        this->input_dir = v;
        return;
    }

    if ( first=="output" || first=="Output" ) {
        ss >> v;
        this->output_dir = v;
        return;
    }

    // Statistics dislocation positions
    if (first=="statsDislocationPositions")
    {
        ss >> v;
        int write = atoi(v.c_str());
        ss >> v;
        this->dislocationPositions = Statistics( (write==1), atof(v.c_str()));
        if ( write ) {
            // Read name
            ss >> v;
            this->dislocationPositions.addName ( v );
        }

        return;
    }

    // Statistics slip plane stress distribution
    if (first=="statsSlipPlaneStress" )
    {
        ss >> v;
        int write = atoi(v.c_str());
        ss >> v;
        this->slipPlaneStressDistributions = Statistics( (write==1), atof(v.c_str()));
        if ( write ) {
            // Read name
            ss >> v;
            this->slipPlaneStressDistributions.addName ( v );
            // Read additional parameter: resolution
            ss >> v;
            this->slipPlaneStressDistributions.addParameter ( atof ( v.c_str() ) );
        }
        return;
    }

    // Statistics all defect positions
    if (first=="statsAllDefects") {
        ss >> v;
        int write = atoi(v.c_str());
        ss >> v;
        this->allDefectPositions = Statistics ( (write==1), atof(v.c_str()));
        if ( write ) {
            // Read name
            ss >> v;
            this->allDefectPositions.addName(v);
        }
        return;
    }

    // Statistics slip system positions
    if (first=="statsSlipSystemObjects") {
        ss >> v;
        int write = atoi(v.c_str());
        ss >> v;
        this->slipSystemObjectPositions = Statistics ( (write==1), atof(v.c_str()));
        if ( write ) {
            // Read name
            ss >> v;
            this->slipSystemObjectPositions.addName(v);
        }
        return;
    }

    // File names
    if ( first=="structure" || first=="Structure" )
    {
        ss >> v;
        this->dislocationStructureFile = v;
        return;
    }

}

