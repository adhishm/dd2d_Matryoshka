/**
 * @file parameter.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 12/06/2013
 * @brief Definition of member functions of the Parameter class which will hold all simulation parameters.
 * @details This file defines member functions of the Parameter class which will hold all simulation parameters.
 */

/**
 * @brief Read parameters from file whose name is provided.
 * @param fileName Name of the file containing the parameters.
 * @return True/false indicating success/failure of parameter reading.
 */
bool Parameter::getParameters (std::string fileName)
{
  // Open file
  std::ifstream fp (fileName);
  std::string line;
  
  if (fp.is_open())
  {
    while (fp.good())
    {
      getline (fp, line);
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
  if (line.at(0) == '#')
  {
    // This line is a comment. Ignore
    return;
  }
  
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
  if (first=="limitingTimeStep" || "LimitingTimeStep")
  {
    ss >> v;
    this->limitingTimeStep = atof (v.c_str());
    return;
  }
  
  // Statistics dislocation positions
  if (first=="statsDislocationPositions")
  {
    ss >> v;
    int write = atoi(v.c_str());
    ss >> v;
    this->dislocationPositions = Statistics( (write==1), atof(v.c_str()));
    return;
  }
  
  // Statistics slip plane stress distribution
  if (first=="statsSlipPlaneStress"
  {
    ss >> v;
    int write = atoi(v.c_str());
    ss >> v;
    this->slipPlaneStressDistributions = Statistics( (write==1), atof(v.c_str()));
    return;
  }
}
  
