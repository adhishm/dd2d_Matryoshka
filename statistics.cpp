/**
 * @file statistics.cpp
 * @author Adhish Majumdar
 * @version 1.0
 * @date 11/06/2013
 * @brief Definition of member functions of the Statistics class which will hold the flag and frequency for various stastics.
 * @details This file defines the member functions of the Statistics class which will hold the flag and frequency for various stastics.
 */

#include "statistics.h"

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
      