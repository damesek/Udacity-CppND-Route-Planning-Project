#!/bin/bash

# full reset and create directory
rm -rf ./build && mkdir build && cd build

# choose the right test
#cmake ..
#cmake .. "-DTESTING=RouteModel" 
cmake .. "-DTESTING=RMNodeClass" 
#cmake .. "-DTESTING=RMSNodes" 
#cmake .. "-DTESTING=NodeDist" 
#cmake .. "-DTESTING=NodeToRoad" 
#cmake .. "-DTESTING=FindNeighbors" 
#cmake .. "-DTESTING=FindClosest" 
#cmake .. "-DTESTING=AStarStub" 
#cmake .. "-DTESTING=AStarSearch"


make 
../bin/test
