#!/bin/bash
if [ ! -d "build_lib" ]; then
    mkdir build_lib
fi
cd build_lib
cmake ../
make
cp libcworld.a ../.
