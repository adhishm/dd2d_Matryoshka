/**
 * @file coordinatesystem.h
 * @author Adhish Majumdar
 * @version 0.0
 * @date 01/07/2013
 * @brief Definition of the class CoordinateSystem.
 * @details This file defines the class CoordinateSystem to represent a given co-ordinate system and the base system in which it is expressed. This will be especially useful in the handling of various objects, each carrying its own frame of reference.
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

#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "constants.h"
#include "vector3d.h"
#include "matrix33.h"
#include "rotationMatrix.h"
#include "stress.h"
#include "strain.h"

/**
 * @brief The CoordinateSystem class.
 * @details The CoordinateSystem class represents a co-ordinate system of an entity. It also includes a pointer to the instance of the same class representing the base on which it is expressed.
 */
class CoordinateSystem
{
protected:
    /**
     * @brief The three vectors of the co-ordinate system.
     * @details The three vectors if the co-ordinate system are expressed in this array. They should be mutually orthogonal and should also be unit vectors. If they are not mutually orthogonal, they will default to the default global vectors. However, if the vectors are orthogonal but not unit vectors, the constructors will take care of normalizing them.
     */
    Vector3d e[3];

    /**
     * @brief Origin of the local co-ordinate system expressed in the base system.
     * @details The origin of the local system may not coincide with the base system in case of a translation.
     */
    Vector3d o;

    /**
     * @brief Pointer to the base co-ordinate system in which the present co-ordinate system is expressed.
     * @details This pointer points to the base co-ordinate system in which the present co-ordinate system is expressed. This allows for encapsulating the local calculations without having to worry about any external co-ordinate system other than the one immediately above. The global co-ordinate system will have this pointer set to NULL to indicate the end of the line.
     */
    CoordinateSystem* base;

    /**
     * @brief An instance of the class RotationMatrix to express the system's rotation matrix for rotation from the base to the local system.
     */
    RotationMatrix rotationMatrix;
public:
    // Constructors
    /**
     * @brief Default constructor.
     * @details Calling the constructor without any arguments creates an instance of the class corresponding to the global co-ordinate system.
     */
    CoordinateSystem();
    /**
     * @brief Constructor specifying the axes.
     * @details This constructor specifies the three axes of the co-ordinate system. The origin is assumed to be at zero (no translation) and the base pointer is set to NULL.
     * @param axes Pointer to the array containing vectors representing the three axes.
     */
    CoordinateSystem(Vector3d* axes);
    /**
     * @brief Constructor specifying the three Euler angles (Bunge's notation) for the rotation from the base to the local system.
     * @param p Pointer to the array containing the three Euler angles.
     */
    CoordinateSystem(double* p);
    /**
     * @brief Constructor specifying the axes as well as the origin of the co-ordinate system.
     * @details This constructor specifies the axes and the origin. The base pointer is set to NULL.
     * @param axes Pointer to the array containing the vectors representing the three axes.
     * @param origin The origin of the co-ordinate system.
     */
    CoordinateSystem(Vector3d* axes, Vector3d origin);
    /**
     * @brief Constructor specifying the Euler angles and the origin of the co-ordinate system.
     * @param p Pointer to the array containing the three Euler angles.
     * @param origin The origin of the co-ordinate system.
     */
    CoordinateSystem(double* p, Vector3d origin);
    /**
     * @brief Constructor specifying all details: Axes, origin and base system.
     * @param axes Pointer to the array containing the vectors representing the three axes.
     * @param origin The origin of the co-ordinate system.
     * @param b Pointer to the instance of this class representing the base co-ordinate system.
     */
    CoordinateSystem(Vector3d* axes, Vector3d origin, CoordinateSystem* b);
    /**
     * @brief Constructor specifying the Euler angles, origin of the co-ordinate system and a pointer to the base.
     * @param p Pointer to the array containing the three Euler angles.
     * @param origin The origin of the co-ordinate system.
     * @param b Pointer to the instance of this class representing the base co-ordinate system.
     */
    CoordinateSystem(double* p, Vector3d origin, CoordinateSystem* b);

    // Destructor
    /**
     * @brief Destructor for the class CoordinateSystem.
     * @details The destructor is declared as virtual in order to avoid conflicts with derived class destructors.
     */
    virtual ~CoordinateSystem ()
    {

    }

    // Assignment functions
    /**
     * @brief Set the values of the axes.
     * @details The three axes are set according to the values provided. A check is performed to see if they are mutually orthogonal and unit vectors. If they are not, they are set to the three global vectors, and a false value is returned. If they are orthogonal, but not unit vectors, the function normalizes them.
     * @param axes Pointer to the array containing the vectors representing the three axes.
     * @return Boolean indicating success (true) or failure (false) of the operation.
     */
    bool setAxes(Vector3d* axes);
    /**
     * @brief Sets the value of the origin.
     * @param origin Vector3d object containing the origin.
     */
    void setOrigin(Vector3d origin);
    /**
     * @brief Sets the pointer base to indicate the co-ordinate system in which the current system is expressed.
     * @param b Pointer to the base co-ordinate system.
     */
    void setBase(CoordinateSystem* b);
    /**
     * @brief Sets the vectors to the default global vectors.
     */
    void setDefaultVectors();

    // Access functions
    /**
     * @brief Gets the axes indicated by the argument 0, 1 or 2. In all other cases a zero vector is returned.
     * @param i Index of the axis required: 0, 1, 2.
     * @return The vector containing the axis if i={0,1,2} or a zero vector.
     */
    Vector3d getAxis(int i) const;
    /**
     * @brief Get all the three axes in an array.
     * @return Pointer to the array containing the three axes.
     */
    Vector3d* getAxes();
    /**
     * @brief Returns the position vector of the origin.
     * @return The position vector of the origin.
     */
    Vector3d getOrigin() const;
    /**
     * @brief Pointer to the base co-ordinate system.
     * @return Pointer to the base co-ordinate system.
     */
    CoordinateSystem* getBase() const;
    /**
     * @brief Get the rotation matrix.
     * @return The rotation matrix.
     */
    RotationMatrix getRotationMatrix() const;

    // Operations
    /**
     * @brief Calculates the rotation matrix for rotation from the base to the local co-ordinate system.
     */
    void calculateRotationMatrix();
    /**
     * @brief Converts a vector expressed in the base co-ordinate system to the local system.
     * @param vBase The vector expressed in the base co-ordinate system.
     * @return The vector expressed in the local co-ordinate system.
     */
    Vector3d vector_BaseToLocal(Vector3d vBase) const;
    /**
     * @brief Overloaded function to convert a vector container containing vectors expressed in the base co-ordinate system to the local system.
     * @param vBase The vector container containing vectors expressed in the base co-ordinate system.
     * @return The vector container containing vectors expressed in the local co-ordinate system.
     */
    std::vector<Vector3d> vector_BaseToLocal(std::vector<Vector3d> vBase) const;
    /**
     * @brief Converts a vector expressed in the local co-ordinate system to the base system.
     * @param vLocal The vector expressed in the local co-ordinate system.
     * @return The vector expressed in the base co-ordinate system.
     */
    Vector3d vector_LocalToBase(Vector3d vLocal) const;
    /**
     * @brief Overloaded function to convert vectors expressed in the local co-ordinate system to the base system.
     * @param vLocal The vector container containing vectors expressed in the local co-ordinate system.
     * @return The vector container containing vectors expressed in the base co-ordinate system.
     */
    std::vector<Vector3d> vector_LocalToBase(std::vector<Vector3d> vLocal) const;
    /**
     * @brief Converts a vector expressed in the base co-ordinate system to the local system, but without the translation.
     * @details Some vectors, like force, should not be translated when changing from one system to another. This function is for such vectors.
     * @param vBase The vector expressed in the base co-ordinate system.
     * @return The vector expressed in the local co-ordinate system.
     */
    Vector3d vector_BaseToLocal_noTranslate(Vector3d vBase) const;
    /**
     * @brief Overloaded function  to convert vectors expressed in the base co-ordinate system to the local system, but without the translation.
     * @details Some vectors, like force, should not be translated when changing from one system to another. This function is for such vectors.
     * @param vBase The vector container containing vectors expressed in the base co-ordinate system.
     * @return The vector container containing vectors expressed in the local co-ordinate system.
     */
    std::vector<Vector3d> vector_BaseToLocal_noTranslate(std::vector<Vector3d> vBase) const;
    /**
     * @brief Converts a vector expressed in the local co-ordinate system to the base system, but without the translation.
     * @details Some vectors, like force, should not be translated when changing from one system to another. This function is for such vectors.
     * @param vLocal The vector expressed in the local co-ordinate system.
     * @return The vector expressed in the local co-ordinate system.
     */
    Vector3d vector_LocalToBase_noTranslate(Vector3d vLocal) const;
    /**
     * @brief Overloaded function to convert vectors expressed in the local co-ordinate system to the base system, but without the translation.
     * @details Some vectors, like force, should not be translated when changing from one system to another. This function is for such vectors.
     * @param vLocal The vector container containing vectors expressed in the local co-ordinate system.
     * @return The vector container containing vectors expressed in the local co-ordinate system.
     */
    std::vector<Vector3d> vector_LocalToBase_noTranslate(std::vector<Vector3d> vLocal) const;
    /**
     * @brief Rotates a stress tensor from the base to the local system.
     * @param s The stress tensor to be rotated.
     * @return The rotated stress tensor.
     */
    Stress stress_BaseToLocal(Stress s) const;
    /**
     * @brief Rotates a stress tensor from the local to the base system.
     * @param s The stress tensor to be rotated.
     * @return The rotated stress tensor.
     */
    Stress stress_LocalToBase(Stress s) const;
    /**
     * @brief Rotates a strain tensor from the base to the local system.
     * @param s The strain tensor to be rotated.
     * @return The rotated strain tensor.
     */
    Strain strain_BaseToLocal(Strain s) const;
    /**
     * @brief Rotates a strain tensor from the local to the base system.
     * @param s The strain tensor to be rotated.
     * @return The rotated strain tensor.
     */
    Strain strain_LocalToBase(Strain s) const;
};

#endif // COORDINATESYSTEM_H
