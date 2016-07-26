#!/bin/bash -v
BUILD_DIR=build-clang-bcc-msys2
rm -rf $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR
cp ../../build_vs/Debug/clang-bcc.exe .
cmake .. -DCMAKE_CXX_COMPILER=clang-bcc.exe -G 'MSYS Makefiles' -DCMAKE_VERBOSE_MAKEFILE=1
# cmake .. -G"MSYS Makefiles" -DCMAKE_CXX_COMPILER=clang-bcc.exe -DCMAKE_C_COMPILER=clang-bcc.exe -DCMAKE_VERBOSE_MAKEFILE=1
