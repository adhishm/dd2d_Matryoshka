/**
 * @file statistics.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 11/06/2013
 * @brief Declaration of the Statistics class which will hold the flag and frequency for various stastics.
 * @details This file declares the Statistics class which will hold the flag and frequency for various stastics.
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


#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <string>

/**
 * @brief Statistics class indicating a flag and frequency for writing statistics.
 */
class Statistics
{
public:
  /**
   * @brief Flag indicating whether or not this statistic is to be written.
   */
  bool write;
  /**
   * @brief Frequency (number of iterations) at which this statistic is to be written.
   */
  int frequency;
  /**
   * @brief Counter for the number of iterations since the last write.
   */
  int nIterationsSinceLastWrite;
  /**
   * @brief STD::vector container for storing various parameters for the statistic to be written.
   */
  std::vector<double> parameters;
  /**
   * @brief String with the name of the statistic, also to be used as the the template for filenames.
   */
  std::string name;
  
  // Constructors
  /**
   * @brief Default constructor.
   * @details Initialises the instance of this class with a false value for write and a frequency of 0.
   */
  Statistics ();
  
  /**
   * @brief Constructor for the Statistics class.
   * @param w Flag indicating if the statistic is to be written or not.
   * @param f Frequency of writing.
   */
  Statistics (bool w, int f);

  // Destructor
  /**
   * @brief Destructor for the class Statistics.
   * @details The destructor is declared as virtual in order to avoid conflicts with derived class destructors.
   */
  virtual ~Statistics ()
  {

  }

  /**
   * @brief If the time to write the statistic has arrived.
   * @return True/false indicating if the statistic is to be written or not.
   */
  bool ifWrite ();
  /**
   * @brief Adds a parameter to the vector parameters.
   * @param p The parameter to be added to the vector.
   */
  void addParameter (double p);
  /**
   * @brief Sets the name for the statistic.
   * @param n String containing the name.
   */
  void addName (std::string n);
};

#endif
