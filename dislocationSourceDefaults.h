/**
 * @file dislocationSourceDefaults.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 02/05/2013
 * @brief Definition of certain default values for members of the DislocationSource class.
 * @details This file defines some default values for members of the DislocationSource class representing a dislocation dipole source in the simulation.
 */

#ifndef DISLOCATIONSOURCEDEFAULTS_H
#define DISLOCATIONSOURCEDEFAULTS_H

/**
 * @brief Default value of the critical shear stress for a dislocation source to emit a dipole.
 * @details Default value of the critical shear stress for a dislocation source to emit a dipole. The number is expressed in Pa.
 */
#define DEFAULT_TAU_CRITICAL 1.0e09

/**
 * @brief Default value of the number of iterations required for a dislocation source to emit a dipole.
 * @details The dislocation source must experience a shear stress greater than the critical value in order to emit a dipole. This time is expressed in terms of the number of iterations here.
 */
#define DEFAULT_NITERATIONS 10

#endif
