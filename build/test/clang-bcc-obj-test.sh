#!/bin/bash -v
BUILD_DIR=./clang-bcc-bin
if [ -d "$BUILD_DIR" ]
then
	echo
else
	mkdir "$BUILD_DIR"
	cp ../build_vs/Debug/clang-bcc.exe ./"$BUILD_DIR"
fi
cd "$BUILD_DIR" 
./clang-bcc -o dummy_main.obj ../dummy_main.cpp
 objdump -a dummy_main.obj
cd ..
