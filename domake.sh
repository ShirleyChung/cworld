#!/bin/bash
if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake -DBUILD_LIBRARY=OFF -DBUILD_EXECUTABLE=ON ../
make
cp cworld ../.
