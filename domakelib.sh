#!/bin/bash
if [ ! -d "build_lib" ]; then
    mkdir build_lib
fi
cd build_lib
cmake -DBUILD_LIBRARY=ON -DBUILD_EXECUTABLE=OFF ../
make
cp libcworld.a ../.
