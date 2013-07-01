/**
 * @file coordinatesystem.cpp
 * @author Adhish Majumdar
 * @version 0.0
 * @date 01/07/2013
 * @brief Definition of functions of the class CoordinateSystem.
 * @details This file defines the functions of the class CoordinateSystem to represent a given co-ordinate system and the base system in which it is expressed. This will be especially useful in the handling of various objects, each carrying its own frame of reference.
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

#include "coordinatesystem.h"

// Constructors
/**
 * @brief Default constructor.
 * @details Calling the constructor without any arguments creates an instance of the class corresponding to the global co-ordinate system.
 */
CoordinateSystem::CoordinateSystem()
{
    this->setDefaultVectors();
    this->o = Vector3d();
    // Base
    this->base = NULL;
}

/**
 * @brief Constructor specifying the axes.
 * @details This constructor specifies the three axes of the co-ordinate system. The origin is assumed to be at zero (no translation) and the base pointer is set to NULL.
 * @param axes Pointer to the array containing vectors representing the three axes.
 */
CoordinateSystem::CoordinateSystem(Vector3d* axes)
{
    this->setAxes(axes);
    this->setOrigin(Vector3d());
    this->base = NULL;
}

/**
 * @brief Constructor specifying the axes as well as the origin of the co-ordinate system.
 * @details This constructor specifies the axes and the origin. The base pointer is set to NULL.
 * @param axes Pointer to the array containing the vectors representing the three axes.
 * @param origin The origin of the co-ordinate system.
 */
CoordinateSystem::CoordinateSystem(Vector3d* axes, Vector3d origin)
{
    this->setAxes(axes);
    this->setOrigin(origin);
    this->base = NULL;
}

/**
 * @brief Constructor specifying all details: Axes, origin and base system.
 * @param axes Pointer to the array containing the vectors representing the three axes.
 * @param origin The origin of the co-ordinate system.
 * @param b Pointer to the instance of this class representing the base co-ordinate system.
 */
CoordinateSystem::CoordinateSystem(Vector3d* axes, Vector3d origin, CoordinateSystem* b)
{
    this->setAxes(axes);
    this->setOrigin(origin);
    this->setBase(b);
}

// Assignment functions
/**
 * @brief Set the values of the axes.
 * @details The three axes are set according to the values provided. A check is performed to see if they are mutually orthogonal and unit vectors. If they are not, they are set to the three global vectors, and a false value is returned. If they are orthogonal, but not unit vectors, the function normalizes them.
 * @param axes Pointer to the array containing the vectors representing the three axes.
 * @return Boolean indicating success (true) or failure (false) of the operation.
 */
bool CoordinateSystem::setAxes(Vector3d* axes)
{
    int i, j;   // Counter variables
    // Check axis magnitudes
    double mag[3];
    for (i=0; i<3; i++) {
        mag[i] = axes[i].magnitude();
        if (mag[i]<=SMALL_NUMBER) {
            // The vector is too small!
            this->setDefaultVectors();
            return(false);
        }

        // Normalize
        if (fabs(1.0-mag[i]) >= SMALL_NUMBER ) {
            // This vector is not normalized
            axes[i] *= (1.0/mag[i]);
        }
    }

    // Check orthogonality
    double dotProduct;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            if (i==j) {
                continue;
            }
            else {
                dotProduct = axes[i] * axes[j];
                if (fabs(dotProduct) >= SMALL_NUMBER) {
                    // Not orthogonal!
                    this->setDefaultVectors();
                    return (false);
                }
            }
        }
    }

    // If we are still here, it means that everything is fine
    for (i=0; i<3; i++) {
        this->e[i] = axes[i];
    }

    return(true);
}

/**
 * @brief Sets the value of the origin.
 * @param origin Vector3d object containing the origin.
 */
void CoordinateSystem::setOrigin(Vector3d origin)
{
    this->o = origin;
}

/**
 * @brief Sets the pointer base to indicate the co-ordinate system in which the current system is expressed.
 * @param b Pointer to the base co-ordinate system.
 */
void CoordinateSystem::setBase(CoordinateSystem* b)
{
    this->base = b;
}

/**
 * @brief Sets the vectors to the default global vectors.
 */
void CoordinateSystem::setDefaultVectors()
{
    for (int i=0; i<3; i++) {
        this->e[i] = Vector3d();
        this->e[i].setValue(i, 1.0);
    }
}

// Access functions
/**
 * @brief Gets the axes indicated by the argument 0, 1 or 2. In all other cases a zero vector is returned.
 * @param i Index of the axis required: 0, 1, 2.
 * @return The vector containing the axis if i={0,1,2} or a zero vector.
 */
Vector3d CoordinateSystem::getAxis(int i) const
{
    if (i>=0 && i<=2) {
        return(this->e[i]);
    }
    else {
        return(Vector3d());
    }
}
/**
 * @brief Get all the three axes in an array.
 * @return Pointer to the array containing the three axes.
 */
Vector3d* CoordinateSystem::getAxes()
{
    return(this->e);
}
/**
 * @brief Returns the position vector of the origin.
 * @return The position vector of the origin.
 */
Vector3d CoordinateSystem::getOrigin() const
{
    return(this->o);
}
/**
 * @brief Pointer to the base co-ordinate system.
 * @return Pointer to the base co-ordinate system.
 */
CoordinateSystem* CoordinateSystem::getBase() const
{
    return(this->base);
}
/**
 * @brief Get the rotation matrix.
 * @return The rotation matrix.
 */
RotationMatrix CoordinateSystem::getRotationMatrix() const
{
    return(this->rotationMatrix);
}

// Operations
/**
 * @brief Calculates the rotation matrix for rotation from the base to the local co-ordinate system.
 */
void CoordinateSystem::calculateRotationMatrix()
{
    if (this->base) {
        // Only valid for non-NULL nase pointers
        this->rotationMatrix = RotationMatrix(this->base->getAxes(), this->getAxes());
    }
    else {
        int i, j;
        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {
                this->rotationMatrix.setValue(i, j, (double)(i==j));
            }
        }
    }
}

/**
 * @brief Converts a vector expressed in the base co-ordinate system to the local system.
 * @param vBase The vector expressed in the base co-ordinate system.
 * @return The vector expressed in the local co-ordinate system.
 */
Vector3d CoordinateSystem::vector_BaseToLocal(Vector3d vBase)
{
    // Translation
    Vector3d vTranslated = vBase - this->o;
    // Rotation
    Vector3d vLocal = this->rotationMatrix * vTranslated;

    return(vLocal);
}

/**
 * @brief Converts a vector expressed in the local co-ordinate system to the base system.
 * @param vLocal The vector expressed in the local co-ordinate system.
 * @return The vector expressed in the base co-ordinate system.
 */
Vector3d CoordinateSystem::vector_LocalToBase(Vector3d vLocal)
{
    // Rotation
    Vector3d vRotated = this->rotationMatrix.transpose() * vLocal;
    // Translation
    Vector3d vBase = vRotated + this->o;

    return(vBase);
}

/**
 * @brief Converts a vector expressed in the base co-ordinate system to the local system, but without the translation.
 * @details Some vectors, like force, should not be translated when changing from one system to another. This function is for such vectors.
 * @param vBase The vector expressed in the base co-ordinate system.
 * @return The vector expressed in the local co-ordinate system.
 */
Vector3d CoordinateSystem::vector_BaseToLocal_noTranslate(Vector3d vBase)
{
    Vector3d vLocal = this->rotationMatrix * vBase;
    return(vLocal);
}

/**
 * @brief Converts a vector expressed in the local co-ordinate system to the base system, but without the translation.
 * @details Some vectors, like force, should not be translated when changing from one system to another. This function is for such vectors.
 * @param vLocal The vector expressed in the local co-ordinate system.
 * @return The vector expressed in the local co-ordinate system.
 */
Vector3d CoordinateSystem::vector_LocalToBase_noTranslate(Vector3d vLocal)
{
    Vector3d vBase = this->rotationMatrix.transpose() * vLocal;
    return(vBase);
}

/**
 * @brief Rotates a stress tensor from the base to the local system.
 * @param s The stress tensor to be rotated.
 * @return The rotated stress tensor.
 */
Stress CoordinateSystem::stress_BaseToLocal(Stress s)
{
    return (s.rotate(this->rotationMatrix));
}

/**
 * @brief Rotates a stress tensor from the local to the base system.
 * @param s The stress tensor to be rotated.
 * @return The rotated stress tensor.
 */
Stress CoordinateSystem::stress_LocalToBase(Stress s)
{
    return (s.rotate(this->rotationMatrix.transpose()));
}

/**
 * @brief Rotates a strain tensor from the base to the local system.
 * @param s The strain tensor to be rotated.
 * @return The rotated strain tensor.
 */
Strain CoordinateSystem::strain_BaseToLocal(Strain s)
{
    return (s.rotate(this->rotationMatrix));
}

/**
 * @brief Rotates a strain tensor from the local to the base system.
 * @param s The strain tensor to be rotated.
 * @return The rotated strain tensor.
 */
Strain CoordinateSystem::strain_LocalToBase(Strain s)
{
    return (s.rotate(this->rotationMatrix.transpose()));
}
