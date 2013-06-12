/**
 * @file statistics.h
 * @author Adhish Majumdar
 * @version 1.0
 * @date 11/06/2013
 * @brief Declaration of the Statistics class which will hold the flag and frequency for various stastics.
 * @details This file declares the Statistics class which will hold the flag and frequency for various stastics.
 */

#ifndef STATISTICS_H
#define STATISTICS_H

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
   * @brief Constructor for the Statistics class.
   * @param w Flag indicating if the statistic is to be written or not.
   * @param f Frequency of writing.
   */
  Statistics (bool w, int f);
  
  /**
   * @brief If the time to write the statistic has arrived.
   * @return True/false indicating if the statistic is to be written or not.
   */
  bool ifWrite ();
};

#endif
