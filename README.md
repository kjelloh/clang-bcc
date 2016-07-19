# clang-bcc
A clang compiler front-end that invokes an Embarcadero bcc compiler "behind the scene".

## Summary

* The idea when this project was created was to "fool" cmake it was using a clang compiler while behind the scene the Embarcadero RAD Studio C++ compiler was executed.
* The motivation was to be able to adopt Microsoft GSL library for teh Embarcadero RAD STudio C++ compilers.
* As it turns out cmake actually identifies the compiler from teh content of a compiled C++-file so it still identifies the Embarcadero compiler.
* The clang-bcc frontend is thus not a good name and this project should be renamed.

## Synopsis


    C:\...\GitHub\clang-bcc\build
    │   CMakeLists.txt
    │   main.cpp
    │
    └───build
        │   clang-bcc.exe  // front-end to be used by cmake to engage Embarcadero bcc32, bcc32c or bcc64 "behind the scenes"


* Place clang-bcc.exe short-cut in build folder below the cmake folder.
* Use CMake to generate clang tool chain for your project using clang-bcc.exe as compiler.
* clang-bcc.exe will transform passed options to the "behind the scene" Embarcadero Compiler
* cmake will be able to use clang-bcc.exe to identify compiler and linker abilities and generate a build build environment

## Example using MSYS2 and cmake and clang-bcc to generate a build environment for Microsoft GSL library

	C:\Users\kjell-olovhogdahl\Documents\GitHub\GSL>rm -r ./build-clang-bcc-frontend/*.*
	rm: cannot remove './build-clang-bcc-frontend/*.*': No such file or directory

	C:\Users\kjell-olovhogdahl\Documents\GitHub\GSL>cd build-clang-bcc-frontend

	C:\Users\kjell-olovhogdahl\Documents\GitHub\GSL\build-clang-bcc-frontend>ln -s  /c/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/build/Debug/clang-bcc.exe ./clang-bcc.exe

	C:\Users\kjell-olovhogdahl\Documents\GitHub\GSL\build-clang-bcc-frontend>cmake .. -DCMAKE_CXX_COMPILER=clang-bcc.exe -G "MSYS Makefiles"
	-- The CXX compiler identification is Embarcadero 7.10.35454
	-- Check for working CXX compiler: C:/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/clang-bcc.exe
	-- Check for working CXX compiler: C:/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/clang-bcc.exe -- works
	-- Detecting CXX compiler ABI info
	-- Detecting CXX compiler ABI info - done
	-- The C compiler identification is GNU 5.4.0
	-- Check for working C compiler: C:/msys64/mingw64/bin/gcc.exe
	-- Check for working C compiler: C:/msys64/mingw64/bin/gcc.exe -- works
	-- Detecting C compiler ABI info
	-- Detecting C compiler ABI info - done
	-- Detecting C compile features
	-- Detecting C compile features - done
	-- Performing Test COMPILER_SUPPORTS_CXX14
	-- Performing Test COMPILER_SUPPORTS_CXX14 - Success
	-- Performing Test COMPILER_SUPPORTS_CXX11
	-- Performing Test COMPILER_SUPPORTS_CXX11 - Success
	-- Configuring done
	-- Generating done
	-- Build files have been written to: C:/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend

	kjell-olovhogdahl@KJELL-OLOVHA74E MINGW64 /c/Users/kjell-olovhogdahl/Documents/GitHub/GSL
	$

## Example of the call CMake does to clang-bcc.exe during the make environment generation (From ./CMakeFiles/CMakeOutput.log)

	...
	Building CXX object CMakeFiles/cmTC_c22ef.dir/testCXXCompiler.cxx.obj
	/C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/clang-bcc.exe  -tR -DWIN32   -tM  -Od -v   -oCMakeFiles/cmTC_c22ef.dir/testCXXCompiler.cxx.obj -P -c /C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/CMakeFiles/CMakeTmp/testCXXCompiler.cxx

	clang-bcc:compiler=C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		[-tR]
		[-DWIN32]
		[-tM]
		[-Od]
		[-v]
		[-oCMakeFiles/cmTC_c22ef.dir/testCXXCompiler.cxx.obj]
		[-P]
		[-c]
		[C:/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/CMakeFiles/CMakeTmp/testCXXCompiler.cxx]

	clang-bcc:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -DWIN32 -tM -Od -v -oCMakeFiles/cmTC_c22ef.dir/testCXXCompiler.cxx.obj -P -c C:/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/CMakeFiles/CMakeTmp/testCXXCompiler.cxxnclang-bcc:START COMPILER

	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	C:/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/CMakeFiles/CMakeTmp/testCXXCompiler.cxx:

	clang-bcc:END

	...

	Linking CXX executable cmTC_c22ef.exe
	/C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/clang-bcc.exe  -tR -ecmTC_c22ef.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192   -v -tC  -tM  -Od -v   import32.lib  "CMakeFiles/cmTC_c22ef.dir/testCXXCompiler.cxx.obj"

	clang-bcc:compiler=C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		[-tR]
		[-ecmTC_c22ef.exe]
		[-tM]
		[-lS:1048576]
		[-lSc:4098]
		[-lH:1048576]
		[-lHc:8192]
		[-v]
		[-tC]
		[-tM]
		[-Od]
		[-v]
		[import32.lib]
		[CMakeFiles/cmTC_c22ef.dir/testCXXCompiler.cxx.obj]

	clang-bcc:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -ecmTC_c22ef.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192 -v -tC -tM -Od -v import32.lib CMakeFiles/cmTC_c22ef.dir/testCXXCompiler.cxx.objnclang-bcc:START COMPILER
	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	bcc32c.exe: warning: argument unused during compilation: '-Xclang -cxx-abi'
	bcc32c.exe: warning: argument unused during compilation: '-Xclang borland'
	bcc32c.exe: warning: argument unused during compilation: '-nobuiltininc'
	Turbo Incremental Link 6.72 Copyright (c) 1997-2015 Embarcadero Technologies, Inc.

	clang-bcc:END
	...

# Release 0.1

* + First pass of using clang-bcc.exe as compiler front-end to have cmake generate an "Embarcadero" build environment
* - No parameter adaption yet implemented.
* - Atual build with generated environment and clang-bcc.exe as compiler/linker not yet done.
