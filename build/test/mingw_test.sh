#!/bin/bash -v
rm -rf build
mkdir build
cd build
cp ../../build/Debug/clang-bcc.exe .
cmake .. -DCMAKE_CXX_COMPILER=clang-bcc.exe -G 'MSYS Makefiles'
PAUSE
