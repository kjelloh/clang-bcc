#!/bin/bash -v
rm -rf build-clang-bcc
mkdir build-clang-bcc
cd build-clang-bcc
cp ../../build_vs/Debug/clang-bcc.exe .
#cmake .. -DCMAKE_CXX_COMPILER=clang-bcc.exe -G 'MSYS Makefiles'
cmake .. -G"MSYS Makefiles" -DCMAKE_CXX_COMPILER=clang-bcc.exe -DCMAKE_C_COMPILER=clang-bcc.exe
