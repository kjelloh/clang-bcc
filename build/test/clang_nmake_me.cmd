REM Use Cmake to generate Visual Studio (VS) build environment
SET BUILD_DIR=build-clang-nmake
if exist %BUILD_DIR% (
	rmdir /s/q %BUILD_DIR%
)
mkdir %BUILD_DIR%
cd %BUILD_DIR%
REM use Cmake to generate default build environment (on windows it is Visual Studio)
cmake .. -G"NMake Makefiles" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_VERBOSE_MAKEFILE=1
cd ..