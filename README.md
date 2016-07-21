# clang-bcc
A clang compiler front-end that invokes an Embarcadero bcc compiler "behind the scene".

## Summary

* The idea when this project was created was to "fool" cmake it was using a clang compiler while behind the scene the Embarcadero RAD Studio C++ compiler was executed.
* The motivation was to be able to adopt Microsoft GSL library for teh Embarcadero RAD STudio C++ compilers.
* As it turns out cmake actually identifies the compiler from teh content of a compiled C++-file so it still identifies the Embarcadero compiler.
* The clang-bcc frontend is thus not a good name and this project should be renamed.

## Synopsis

>C:\...\GitHub\clang-bcc\build
>│   CMakeLists.txt
>│   main.cpp
>│
>└───build
>    │   clang-bcc.exe  // front-end to be used by cmake to engage Embarcadero bcc32, bcc32c or bcc64 "behind the scenes"

* Place clang-bcc.exe short-cut in build folder below the cmake folder.
* Use CMake to generate tool chain for your project using clang-bcc.exe as compiler.
* clang-bcc will "fool" cmake into beleiving it is using a clang compiler (see "How clang-bcc tricks cmake to beleive it is using a clang compiler" below)
* clang-bcc.exe will transform passed clang compiler options to the "behind the scene" Embarcadero Compiler
* cmake will thus be able to use clang-bcc.exe to generate a build build environment that will call Embarcadero C++ compilers for build and link.
* clang-bcc.exe acts as both C and C++ front-end (calling back-end actual compiler with apropriate parameters to compile or link correctly)

## How clang-bcc tricks cmake to beleive it is using a clang compiler

1. When cmake as first step compiles its compiler identification c++ file (CMakeCXXCompilerId.cpp) it provides no compiler options.
  
  * When clang-bcc detects it is being called to compile Cmake spedial source files for compiler detection - it then calls clang to generate clang identification.
  * In this way cmake will detect that the provided cpp-file was in fact compiled with clang and this it asumes clang options to be used.

2. Cmake will then test if clang-bcc works with actual options.

  * When clang-bcc is called with options for compilation it will call an Embarcadero C++ compiler (transforming provided options to Embarcadero Compiler options to compile)

3. Cmake will then test if clang-bcc may be used to link the compiled binary.

  * When clang-bcc is called with options for linking it will call an Embarcadero C++ compiler (transforming provided options to Embarcadero Compiler options to link)

#Version 0.2

* clang-bcc - Nearer to work as clang front-end for cmake
+ Now act as front-end for both C and C++ compiler
+ back-end call and parameter transform only for bcc32c
+ Added MINGW shell test of MSYS make file generation using clang-bcc as front-end
+ Added DOS whll test of Borland Make file generation using bcc32c (embarcadero design)
- clang-bcc fails for C-link using bcc32c (_main not found)

# Version 0.1

* + First pass of using clang-bcc.exe as compiler front-end to have cmake generate an "Embarcadero" build environment
* - No parameter adaption yet implemented.
* - Atual build with generated environment and clang-bcc.exe as compiler/linker not yet done.

## Version 0.2 status for MINGW console test generating MSYS make files

* The test is invoked with project memner mingw_test.sh in test sub-folder of build folder.

	kjell-olovhogdahl@KJELL-OLOVHA74E MINGW64 /c/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test
	$ ./mingw_test.sh
	#!/bin/bash -v
	rm -rf build-clang-bcc
	mkdir build-clang-bcc
	cd build-clang-bcc
	cp ../../build/Debug/clang-bcc.exe .
	#cmake .. -DCMAKE_CXX_COMPILER=clang-bcc.exe -G 'MSYS Makefiles'
	cmake .. -G"MSYS Makefiles" -DCMAKE_CXX_COMPILER=clang-bcc.exe -DCMAKE_C_COMPILER=clang-bcc.exe
	-- The C compiler identification is unknown
	-- The CXX compiler identification is Clang 3.8.0
	-- Check for working C compiler: C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/clang-bcc.exe
	-- Check for working C compiler: C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/clang-bcc.exe -- works
	-- Detecting C compiler ABI info
	-- Detecting C compiler ABI info - done
	-- Check for working CXX compiler: C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/clang-bcc.exe
	-- Check for working CXX compiler: C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/clang-bcc.exe -- works
	-- Detecting CXX compiler ABI info
	-- Detecting CXX compiler ABI info - failed
	-- Detecting CXX compile features
	-- Detecting CXX compile features - failed
	-- Configuring done
	-- Generating done
	-- Build files have been written to: C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc

	kjell-olovhogdahl@KJELL-OLOVHA74E MINGW64 /c/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test
	$


1. clang-bcc fails to compile C idnetification file CMakeCCompilerId.c (impersonating as clang)

	[[CLANG-BCC]]:START
	[[CLANG-BCC]]:CMake <<compiler identification>> call detected
	[[CLANG-BCC]]:Decided to use actual compiler clang++
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[CMakeCCompilerId.c]
		<OUT Parameter List (vaules between [...]>
		[CMakeCCompilerId.c]
	[[CLANG-BCC]]:Actual Compiler = clang++
		<Parameter List (vaules between [...]>
		[CMakeCCompilerId.c]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="clang++" CMakeCCompilerId.c
	clang++.exe: warning: treating 'c' input as 'c++' when in C++ mode, this behavior is deprecated
	CMakeCCompilerId.c:2:3: error: "A C++ compiler has been selected for C."
	# error "A C++ compiler has been selected for C."
	^
	1 error generated.

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END

* TODO: Call correct back-end clang compiler for C-compilation.

2. clang-bcc succeeds to compile C++ identification CMakeCXXCompilerId.cpp (impersonating as clang)

	[[CLANG-BCC]]:START
	[[CLANG-BCC]]:C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/clang-bcc.exe CMakeCXXCompilerId.cpp
	[[CLANG-BCC]]:CMake <<compiler identification>> call detected
	[[CLANG-BCC]]:Decided to use actual compiler clang++
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[CMakeCXXCompilerId.cpp]
		<OUT Parameter List (vaules between [...]>
		[CMakeCXXCompilerId.cpp]
	[[CLANG-BCC]]:Actual Compiler = clang++
		<Parameter List (vaules between [...]>
		[CMakeCXXCompilerId.cpp]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="clang++" CMakeCXXCompilerId.cpp

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END


	Compilation of the CXX compiler identification source "CMakeCXXCompilerId.cpp" produced "a.exe"

3. clang-cpp succeeds to compile C test file (calling back-end bcc32c)

	[[CLANG-BCC]]:START
	[[CLANG-BCC]]:C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-clang-bcc\clang-bcc.exe -o CMakeFiles/cmTC_214da.dir/testCCompiler.c.obj -c C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCCompiler.c
	[[CLANG-BCC]]:Build call asumed
	[[CLANG-BCC]]:Decided to use actual compiler C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[-o]
		[CMakeFiles/cmTC_214da.dir/testCCompiler.c.obj]
		[-c]
		[C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCCompiler.c]
	[[CLANG-BCC]]:Compile to object/archive Parameters
		<OUT Parameter List (vaules between [...]>
		[-tR]
		[-DWIN32]
		[-tM]
		[-Od]
		[-v]
		[-oCMakeFiles/cmTC_214da.dir/testCCompiler.c.obj]
		[-c]
		[C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCCompiler.c]
	[[CLANG-BCC]]:Actual Compiler = C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		<Parameter List (vaules between [...]>
		[-tR]
		[-DWIN32]
		[-tM]
		[-Od]
		[-v]
		[-oCMakeFiles/cmTC_214da.dir/testCCompiler.c.obj]
		[-c]
		[C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCCompiler.c]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -DWIN32 -tM -Od -v -oCMakeFiles/cmTC_214da.dir/testCCompiler.c.obj -c C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCCompiler.c
	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCCompiler.c:

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END

4. clang-bcc succeeds to link C-compiled test code (using back-end bcc32c as linker)

	[[CLANG-BCC]]:START
	[[CLANG-BCC]]:C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-clang-bcc\clang-bcc.exe CMakeFiles/cmTC_214da.dir/testCCompiler.c.obj -o cmTC_214da.exe
	[[CLANG-BCC]]:Build call asumed
	[[CLANG-BCC]]:Decided to use actual compiler C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[CMakeFiles/cmTC_214da.dir/testCCompiler.c.obj]
		[-o]
		[cmTC_214da.exe]
	[[CLANG-BCC]]:Link to Exe Parameters
		<OUT Parameter List (vaules between [...]>
		[-tR]
		[-ecmTC_214da.exe]
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
		[CMakeFiles/cmTC_214da.dir/testCCompiler.c.obj]
	[[CLANG-BCC]]:Actual Compiler = C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		<Parameter List (vaules between [...]>
		[-tR]
		[-ecmTC_214da.exe]
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
		[CMakeFiles/cmTC_214da.dir/testCCompiler.c.obj]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -ecmTC_214da.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192 -v -tC -tM -Od -v CMakeFiles/cmTC_214da.dir/testCCompiler.c.obj
	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	bcc32c.exe: warning: argument unused during compilation: '-Xclang -cxx-abi'
	bcc32c.exe: warning: argument unused during compilation: '-Xclang borland'
	bcc32c.exe: warning: argument unused during compilation: '-nobuiltininc'
	Turbo Incremental Link 6.72 Copyright (c) 1997-2015 Embarcadero Technologies, Inc.

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END

5. clang-bcc succeeds to compile C ABI identification file CMakeCCompilerABI.c 

	[[CLANG-BCC]]:START
	[[CLANG-BCC]]:C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-clang-bcc\clang-bcc.exe -o CMakeFiles/cmTC_8410f.dir/CMakeCCompilerABI.c.obj -c C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCCompilerABI.c
	[[CLANG-BCC]]:CMake <<compiler ABI output identification>> call detected
	[[CLANG-BCC]]:Decided to use actual compiler C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[-o]
		[CMakeFiles/cmTC_8410f.dir/CMakeCCompilerABI.c.obj]
		[-c]
		[C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCCompilerABI.c]
	[[CLANG-BCC]]:Compile to object/archive Parameters
		<OUT Parameter List (vaules between [...]>
		[-tR]
		[-DWIN32]
		[-tM]
		[-Od]
		[-v]
		[-oCMakeFiles/cmTC_8410f.dir/CMakeCCompilerABI.c.obj]
		[-c]
		[C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCCompilerABI.c]
	[[CLANG-BCC]]:Actual Compiler = C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		<Parameter List (vaules between [...]>
		[-tR]
		[-DWIN32]
		[-tM]
		[-Od]
		[-v]
		[-oCMakeFiles/cmTC_8410f.dir/CMakeCCompilerABI.c.obj]
		[-c]
		[C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCCompilerABI.c]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -DWIN32 -tM -Od -v -oCMakeFiles/cmTC_8410f.dir/CMakeCCompilerABI.c.obj -c C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCCompilerABI.c
	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCCompilerABI.c:

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END

6. clang-bcc succeeds to link the C ABI identification CMakeCCompilerABI.c.obj to exe

	[[CLANG-BCC]]:START
	[[CLANG-BCC]]:C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-clang-bcc\clang-bcc.exe CMakeFiles/cmTC_8410f.dir/CMakeCCompilerABI.c.obj -o cmTC_8410f.exe
	[[CLANG-BCC]]:CMake <<compiler ABI output identification>> call detected
	[[CLANG-BCC]]:Decided to use actual compiler C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[CMakeFiles/cmTC_8410f.dir/CMakeCCompilerABI.c.obj]
		[-o]
		[cmTC_8410f.exe]
	[[CLANG-BCC]]:Link to Exe Parameters
		<OUT Parameter List (vaules between [...]>
		[-tR]
		[-ecmTC_8410f.exe]
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
		[CMakeFiles/cmTC_8410f.dir/CMakeCCompilerABI.c.obj]
	[[CLANG-BCC]]:Actual Compiler = C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		<Parameter List (vaules between [...]>
		[-tR]
		[-ecmTC_8410f.exe]
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
		[CMakeFiles/cmTC_8410f.dir/CMakeCCompilerABI.c.obj]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -ecmTC_8410f.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192 -v -tC -tM -Od -v CMakeFiles/cmTC_8410f.dir/CMakeCCompilerABI.c.obj
	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	bcc32c.exe: warning: argument unused during compilation: '-Xclang -cxx-abi'
	bcc32c.exe: warning: argument unused during compilation: '-Xclang borland'
	bcc32c.exe: warning: argument unused during compilation: '-nobuiltininc'
	Turbo Incremental Link 6.72 Copyright (c) 1997-2015 Embarcadero Technologies, Inc.

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END

7. clang-bcc succeeds to compile test C++ file testCXXCompiler.cxx (using back-end bcc32c)

	[[CLANG-BCC]]:START
	[CLANG-BCC]]:C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-clang-bcc\clang-bcc.exe -o CMakeFiles/cmTC_caac7.dir/testCXXCompiler.cxx.obj -c C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
	[[CLANG-BCC]]:Build call asumed
	[[CLANG-BCC]]:Decided to use actual compiler C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[-o]
		[CMakeFiles/cmTC_caac7.dir/testCXXCompiler.cxx.obj]
		[-c]
		[C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCXXCompiler.cxx]
	[[CLANG-BCC]]:Compile to object/archive Parameters
		<OUT Parameter List (vaules between [...]>
		[-tR]
		[-DWIN32]
		[-tM]
		[-Od]
		[-v]
		[-oCMakeFiles/cmTC_caac7.dir/testCXXCompiler.cxx.obj]
		[-P]
		[-c]
		[C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCXXCompiler.cxx]
	[[CLANG-BCC]]:Actual Compiler = C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		<Parameter List (vaules between [...]>
		[-tR]
		[-DWIN32]
		[-tM]
		[-Od]
		[-v]
		[-oCMakeFiles/cmTC_caac7.dir/testCXXCompiler.cxx.obj]
		[-P]
		[-c]
		[C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCXXCompiler.cxx]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -DWIN32 -tM -Od -v -oCMakeFiles/cmTC_caac7.dir/testCXXCompiler.cxx.obj -P -c C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCXXCompiler.cxx:

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END

6. clang-bcc fails to link the C++ test file object code

	[[CLANG-BCC]]:START
	[[CLANG-BCC]]:C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-clang-bcc\clang-bcc.exe -Wl,--whole-archive CMakeFiles/cmTC_caac7.dir/objects.a -Wl,--no-whole-archive -o cmTC_caac7.exe -Wl,--major-image-version,0,--minor-image-version,0 -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32
	[[CLANG-BCC]]:Build call asumed
	[[CLANG-BCC]]:Decided to use actual compiler C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[-Wl,--whole-archive]
		[CMakeFiles/cmTC_caac7.dir/objects.a]
		[-Wl,--no-whole-archive]
		[-o]
		[cmTC_caac7.exe]
		[-Wl,--major-image-version,0,--minor-image-version,0]
		[-lkernel32]
		[-luser32]
		[-lgdi32]
		[-lwinspool]
		[-lshell32]
		[-lole32]
		[-loleaut32]
		[-luuid]
		[-lcomdlg32]
		[-ladvapi32]
	[[CLANG-BCC]]:Link to Exe Parameters
		<OUT Parameter List (vaules between [...]>
		[-tR]
		[-ecmTC_caac7.exe]
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
		[CMakeFiles/cmTC_caac7.dir/objects.a]
	[[CLANG-BCC]]:Actual Compiler = C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		<Parameter List (vaules between [...]>
		[-tR]
		[-ecmTC_caac7.exe]
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
		[CMakeFiles/cmTC_caac7.dir/objects.a]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -ecmTC_caac7.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192 -v -tC -tM -Od -v CMakeFiles/cmTC_caac7.dir/objects.a
	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	bcc32c.exe: warning: argument unused during compilation: '-Xclang -cxx-abi'
	bcc32c.exe: warning: argument unused during compilation: '-Xclang borland'
	bcc32c.exe: warning: argument unused during compilation: '-nobuiltininc'
	Turbo Incremental Link 6.72 Copyright (c) 1997-2015 Embarcadero Technologies, Inc.
	Error: 'C:\USERS\KJELL-OLOVHOGDAHL\DOCUMENTS\GITHUB\CLANG-BCC\BUILD\TEST\BUILD-CLANG-BCC\CMAKEFILES\CMAKETMP\CMAKEFILES\CMTC_CAAC7.DIR\OBJECTS.A' contains invalid OMF record, type 0x21 (possibly COFF)
	bcc32c.exe: error: linker command failed with exit code 2 (use -Xdriver -v to see invocation)

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END

* TODO: Figure out why cmake first calls to generate "CMakeFiles/cmTC_caac7.dir/testCXXCompiler.cxx.obj" but then asks to link "CMakeFiles/cmTC_caac7.dir/objects.a"?

7. clang-bcc succeeds to compile the C++ ABI detection source CMakeCXXCompilerABI.cpp

	[[CLANG-BCC]]:START
	[[CLANG-BCC]]:C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-clang-bcc\clang-bcc.exe -o CMakeFiles/cmTC_9068c.dir/CMakeCXXCompilerABI.cpp.obj -c C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp
	[[CLANG-BCC]]:CMake <<compiler ABI output identification>> call detected
	[[CLANG-BCC]]:Decided to use actual compiler C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[-o]
		[CMakeFiles/cmTC_9068c.dir/CMakeCXXCompilerABI.cpp.obj]
		[-c]
		[C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp]
	[[CLANG-BCC]]:Compile to object/archive Parameters
		<OUT Parameter List (vaules between [...]>
		[-tR]
		[-DWIN32]
		[-tM]
		[-Od]
		[-v]
		[-oCMakeFiles/cmTC_9068c.dir/CMakeCXXCompilerABI.cpp.obj]
		[-P]
		[-c]
		[C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp]
	[[CLANG-BCC]]:Actual Compiler = C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		<Parameter List (vaules between [...]>
		[-tR]
		[-DWIN32]
		[-tM]
		[-Od]
		[-v]
		[-oCMakeFiles/cmTC_9068c.dir/CMakeCXXCompilerABI.cpp.obj]
		[-P]
		[-c]
		[C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -DWIN32 -tM -Od -v -oCMakeFiles/cmTC_9068c.dir/CMakeCXXCompilerABI.cpp.obj -P -c C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp
	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	C:/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp:

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END

8. clang-bcc fails to link the C++ ABI detection exe 

	[[CLANG-BCC]]:START
	[[CLANG-BCC]]:C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-clang-bcc\clang-bcc.exe -v -Wl,--whole-archive CMakeFiles/cmTC_9068c.dir/objects.a -Wl,--no-whole-archive -o cmTC_9068c.exe -Wl,--major-image-version,0,--minor-image-version,0
	[[CLANG-BCC]]:Build call asumed
	[[CLANG-BCC]]:Decided to use actual compiler C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[-v]
		[-Wl,--whole-archive]
		[CMakeFiles/cmTC_9068c.dir/objects.a]
		[-Wl,--no-whole-archive]
		[-o]
		[cmTC_9068c.exe]
		[-Wl,--major-image-version,0,--minor-image-version,0]
	[[CLANG-BCC]]:Link to Exe Parameters
		<OUT Parameter List (vaules between [...]>
		[-tR]
		[-ecmTC_9068c.exe]
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
		[CMakeFiles/cmTC_9068c.dir/objects.a]
	[[CLANG-BCC]]:Actual Compiler = C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		<Parameter List (vaules between [...]>
		[-tR]
		[-ecmTC_9068c.exe]
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
		[CMakeFiles/cmTC_9068c.dir/objects.a]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -ecmTC_9068c.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192 -v -tC -tM -Od -v CMakeFiles/cmTC_9068c.dir/objects.a
	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	bcc32c.exe: warning: argument unused during compilation: '-Xclang -cxx-abi'
	bcc32c.exe: warning: argument unused during compilation: '-Xclang borland'
	bcc32c.exe: warning: argument unused during compilation: '-nobuiltininc'
	Turbo Incremental Link 6.72 Copyright (c) 1997-2015 Embarcadero Technologies, Inc.
	Error: 'C:\USERS\KJELL-OLOVHOGDAHL\DOCUMENTS\GITHUB\CLANG-BCC\BUILD\TEST\BUILD-CLANG-BCC\CMAKEFILES\CMAKETMP\CMAKEFILES\CMTC_9068C.DIR\OBJECTS.A' contains invalid OMF record, type 0x21 (possibly COFF)
	bcc32c.exe: error: linker command failed with exit code 2 (use -Xdriver -v to see invocation)

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END

* TODO: Figure out why cmake first calls to generate "CMakeFiles/cmTC_9068c.dir/CMakeCXXCompilerABI.cpp.obj" but then asks to link "CMakeFiles/cmTC_9068c.dir/objects.a"?

9. clang-bcc fails to pass clang c++14 switch to back-end bcb32c (diabsling cmake to determine c++14 support)

	[[CLANG-BCC]]:START
	[[CLANG-BCC]]:C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-clang-bcc\clang-bcc.exe -std=c++14 -o CMakeFiles/cmTC_64b1f.dir/feature_tests.cxx.obj -c C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/feature_tests.cxx
	[[CLANG-BCC]]:Build call asumed
	[[CLANG-BCC]]:Decided to use actual compiler C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[-std=c++14]
		[-o]
		[CMakeFiles/cmTC_64b1f.dir/feature_tests.cxx.obj]
		[-c]
		[C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/feature_tests.cxx]
	[[CLANG-BCC]]:Compile to object/archive Parameters
		<OUT Parameter List (vaules between [...]>
		[-tR]
		[-DWIN32]
		[-tM]
		[-Od]
		[-v]
		[-oCMakeFiles/cmTC_64b1f.dir/feature_tests.cxx.obj]
		[-P]
		[-c]
		[C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/feature_tests.cxx]
	[[CLANG-BCC]]:Actual Compiler = C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		<Parameter List (vaules between [...]>
		[-tR]
		[-DWIN32]
		[-tM]
		[-Od]
		[-v]
		[-oCMakeFiles/cmTC_64b1f.dir/feature_tests.cxx.obj]
		[-P]
		[-c]
		[C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/feature_tests.cxx]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -DWIN32 -tM -Od -v -oCMakeFiles/cmTC_64b1f.dir/feature_tests.cxx.obj -P -c C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/feature_tests.cxx
	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/feature_tests.cxx:

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END

* TODO: Fails transformation of passsed clang c++14 to bcb32c (or pass suatble parameter at have bcb32c fail appropriatly)

10. clang-bcc fails to link C++ compiler option build 

	[[CLANG-BCC]]:START
	[[CLANG-BCC]]:C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-clang-bcc\clang-bcc.exe -Wl,--whole-archive CMakeFiles/cmTC_64b1f.dir/objects.a -Wl,--no-whole-archive -o cmTC_64b1f.exe -Wl,--major-image-version,0,--minor-image-version,0 -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32
	[[CLANG-BCC]]:Build call asumed
	[[CLANG-BCC]]:Decided to use actual compiler C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
	[[CLANG-BCC]]:Parameter Transformation
		<IN Parameter List (vaules between [...]>
		[-Wl,--whole-archive]
		[CMakeFiles/cmTC_64b1f.dir/objects.a]
		[-Wl,--no-whole-archive]
		[-o]
		[cmTC_64b1f.exe]
		[-Wl,--major-image-version,0,--minor-image-version,0]
		[-lkernel32]
		[-luser32]
		[-lgdi32]
		[-lwinspool]
		[-lshell32]
		[-lole32]
		[-loleaut32]
		[-luuid]
		[-lcomdlg32]
		[-ladvapi32]
	[[CLANG-BCC]]:Link to Exe Parameters
		<OUT Parameter List (vaules between [...]>
		[-tR]
		[-ecmTC_64b1f.exe]
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
		[CMakeFiles/cmTC_64b1f.dir/objects.a]
	[[CLANG-BCC]]:Actual Compiler = C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe
		<Parameter List (vaules between [...]>
		[-tR]
		[-ecmTC_64b1f.exe]
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
		[CMakeFiles/cmTC_64b1f.dir/objects.a]
	[[CLANG-BCC]]:START COMPILER
	[[CLANG-BCC]]:CreateProcess="C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe" -tR -ecmTC_64b1f.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192 -v -tC -tM -Od -v CMakeFiles/cmTC_64b1f.dir/objects.a
	Embarcadero C++ 7.10 for Win32 Copyright (c) 2012-2015 Embarcadero Technologies, Inc.
	bcc32c.exe: warning: argument unused during compilation: '-Xclang -cxx-abi'
	bcc32c.exe: warning: argument unused during compilation: '-Xclang borland'
	bcc32c.exe: warning: argument unused during compilation: '-nobuiltininc'
	Turbo Incremental Link 6.72 Copyright (c) 1997-2015 Embarcadero Technologies, Inc.
	Error: 'C:\USERS\KJELL-OLOVHOGDAHL\DOCUMENTS\GITHUB\CLANG-BCC\BUILD\TEST\BUILD-CLANG-BCC\CMAKEFILES\CMAKETMP\CMAKEFILES\CMTC_64B1F.DIR\OBJECTS.A' contains invalid OMF record, type 0x21 (possibly COFF)
	bcc32c.exe: error: linker command failed with exit code 2 (use -Xdriver -v to see invocation)

	[[CLANG-BCC]]:COMPILER END
	[[CLANG-BCC]]:END

* TODO: Figure out why cmake first calls to generate "CMakeFiles/cmTC_9068c.dir/CMakeCXXCompilerABI.cpp.obj" but then asks to link "CMakeFiles/cmTC_9068c.dir/objects.a"?
