# DD2D - A Matryoshka approach

## Introduction

The files in this program provide a hierarchical data structure system for carrying out dislocation dynamics simulations in two dimensions. The base class is Defect, which represents a generic defect in a metallic crystal. All other defects, such as dislocations, dislocation sources, precipitates, etc., are represented by their own classes which inherit certain functions from the Defect class.

The goal of carrying out these simulations in two dimensions is to be able to simulate plastic deformation of up to a few percent. Current three dimensional dislocation dynamics simulations are computationally expensive. This approach hopes to sacrifice some of the precision in order to gain in speed and flexibility.

## Intended structure

The program is under development now, with the data structures being defined. When it will be complete, it is intended to have data structures nested within each other, hence the name <a href="https://en.wikipedia.org/wiki/Matryoshka_doll" target="_blank">Matryoshka</a>. For example, a polycrystal is a collection of grains; a grain is a collection of slip systems; a slip system is a collection of slip planes; a slip plane is a collection of dislocations, dislocation sources and other defects. Once the base simulations execute successfully, other defects will be introduced.
