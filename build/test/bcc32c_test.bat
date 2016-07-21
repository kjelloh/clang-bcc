REM From: http://community.embarcadero.com/blogs/entry/using-cmake-with-the-free-embarcadero-c-compiler
@echo off
mkdir build-bcc32c
cd build-bcc32c
cmake -G"Borland Makefiles" -DCMAKE_CXX_COMPILER="bcc32c.exe" -DCMAKE_C_COMPILER="bcc32c.exe" -DCMAKE_VERBOSE_MAKEFILE=1 ..
make
cd ..
echo CMakeBCC: Results available in 'build' folder