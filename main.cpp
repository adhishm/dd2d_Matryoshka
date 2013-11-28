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

#include <iostream>

#include "parameter.h"
#include "simulateSingleSlipPlane.h"
#include "simulateSingleSlipSystem.h"
#include "simulateGrain.h"

using namespace std;

int main (int argc, char* argv[])
{
    if (argc == 1) {
        // No input arguments
        simulateSingleGrain();
    }
    else {
        // Argument list provided
        std::string filename;
        while (argc > 1) {
            filename = std::string(argv[--argc]);
            simulateSingleGrain(filename);
            filename.clear();
        }
    }

    return (0);
}

