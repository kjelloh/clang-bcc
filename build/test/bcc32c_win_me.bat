REM From: http://community.embarcadero.com/blogs/entry/using-cmake-with-the-free-embarcadero-c-compiler
@echo off
SET BUILD_DIR=build-bcc32c-win
if exist %BUILD_DIR% (
	rmdir /s/q %BUILD_DIR%
)
mkdir %BUILD_DIR%
cd %BUILD_DIR%
cmake -G"Borland Makefiles" -DCMAKE_CXX_COMPILER="bcc32c.exe" -DCMAKE_C_COMPILER="bcc32c.exe" -DCMAKE_VERBOSE_MAKEFILE=1 ..
make
cd ..
echo Generated build environment is in %BUILD_DIR% 