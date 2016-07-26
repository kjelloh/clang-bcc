#!/bin/bash -v
BUILD_DIR=./build-clang-msys2
if [ -d "$BUILD_DIR" ]
then 
	rm -rf "$BUILD_DIR"
fi
mkdir "$BUILD_DIR"
cd "$BUILD_DIR"
cmake .. -G"MSYS Makefiles" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_VERBOSE_MAKEFILE=1
