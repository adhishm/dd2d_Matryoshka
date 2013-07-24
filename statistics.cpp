/**
 * @file statistics.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 11/06/2013
 * @brief Definition of member functions of the Statistics class which will hold the flag and frequency for various stastics.
 * @details This file defines the member functions of the Statistics class which will hold the flag and frequency for various stastics.
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


#include "statistics.h"

/**
 * @brief Default constructor.
 * @details Initialises the instance of this class with a false value for write and a frequency of 0.
 */
Statistics::Statistics ()
{
    this->write = false;
    this->frequency = 0;
    this->nIterationsSinceLastWrite = 0;
}

/**
 * @brief Constructor for the Statistics class.
 * @param w Flag indicating if the statistic is to be written or not.
 * @param f Frequency of writing.
 */
Statistics::Statistics (bool w, int f)
{
  this->write = w;
  this->frequency = f;
  this->nIterationsSinceLastWrite = 0;
}

/**
 * @brief If the time to write the statistic has arrived.
 * @return True/false indicating if the statistic is to be written or not.
 */
bool Statistics::ifWrite ()
{
  if (this->write)
  {
    if (this->nIterationsSinceLastWrite >= this->frequency)
    {
      this->nIterationsSinceLastWrite = 0;
      return (true);
    }
    else
    {
      this->nIterationsSinceLastWrite++;
      return (false);
    }
  }
  else
  {
    return (false);
  }
}

/**
 * @brief Adds a parameter to the vector parameters.
 * @param p The parameter to be added to the vector.
 */
void Statistics::addParameter (double p)
{
    this->parameters.push_back ( p );
}

/**
 * @brief Sets the name for the statistic.
 * @param n String containing the name.
 */
void Statistics::addName (std::string n)
{
    this->name = n;
}
