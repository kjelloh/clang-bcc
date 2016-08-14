# clang-bcc

A clang compiler front-end that invokes an Embarcadero bcc compiler "behind the scene".

## Summary

* This project is an attempt to create a "clang front-end" to Embarcadero bcc compilers for Cmake generation of build environments
* The idea is to "trick" CMake into identifying clang-bcc as a clang compiler while in the background it actually invokes a bcc compiler.
* The clang-bcc front-end accomplish this by impersonating as a clang compiler and transform clang parameters to bcc parameters behind-the-scene 
* The motivation was to be able to adopt Microsoft GSL library for the Embarcadero RAD Studio C++ compilers (bcc32, bcc32c and bcc64.

## Synopsis

* Use clang-bcc as your clang compiler when calling CMake to generate build envuronment

```
    C:\...\<your cpp-project>\build
    │   CMakeLists.txt
    │   file1.cpp
    │   file2.cpp
    │   file3.cpp
    │   ...
    └───build
        │   clang-bcc.exe  // front-end to be used by cmake to engage Embarcadero bcc32, bcc32c or bcc64 "behind the scenes"
```

* Place clang-bcc.exe short-cut in build folder below the cmake folder.
* Use CMake to generate tool chain for your project using clang-bcc.exe as compiler.
```
    >cmake .. -G"MSYS Makefiles" -DCMAKE_CXX_COMPILER=clang-bcc.exe -DCMAKE_C_COMPILER=clang-bcc.exe
```
* clang-bcc will "fool" cmake into beleiving it is using a clang compiler (see "How clang-bcc tricks cmake to beleive it is using a clang compiler" below)
* clang-bcc.exe will transform passed clang compiler options to the "behind the scene" Embarcadero Compiler
* cmake will thus be able to use clang-bcc.exe to generate a build build environment that will call Embarcadero C++ compilers for build and link.
* clang-bcc.exe acts as both C and C++ front-end (calling back-end actual compiler with apropriate parameters to compile or link correctly)

### How clang-bcc tricks cmake to beleive it is using a clang compiler

1. When cmake as first step compiles its compiler identification c++ file (CMakeCXXCompilerId.cpp) it provides no compiler options.
    * When clang-bcc detects it is being called to compile Cmake spedial source files for compiler detection - it then calls clang to generate clang identification.
    * In this way cmake will detect that the provided cpp-file was in fact compiled with clang and this it asumes clang options to be used.

2. Cmake will then test if clang-bcc works with actual options.
    * When clang-bcc is called with options for compilation it will call an Embarcadero C++ compiler (transforming provided options to Embarcadero Compiler options to compile)

3. Cmake will then test if clang-bcc may be used to link the compiled binary.
    * When clang-bcc is called with options for linking it will call an Embarcadero C++ compiler (transforming provided options to Embarcadero Compiler options to link)

# Project

## Project files
```
Kjell-Olovs-MacBook-Pro:clang-bcc kjell-olovhogdahl$ tree -L 4
.
├── CMAKE_CLANG_LOG.md          // Some logs with comments for cmake behavior analysis
├── LICENSE
├── README.md
└── build
    ├── BackEnd.cpp             // backend interface (win32 calls in place)
    ├── BackEnd.h
    ├── CMakeLists.txt
    ├── Core.cpp                // Cross platform
    ├── Core.h
    ├── FrontEnd.cpp            // Frontend interface (win32 console)
    ├── FrontEnd.h
    ├── Poirot.cpp
    ├── Poirot.h
    └── vs_me.cmd               // DOS command script invokes cmake to create Visual Studio build environment

    ├── test                    // Cmake tests
    │   ├── CmakeLists.txt          // Cmake test project (build of dummy_main.cpp)
    │   ├── bcc32c-win-test.bat
    │   ├── build-bcc32c-win
    │   │   ├── CMakeFiles
    │   │   │   ├── CMakeOutput.log // Saved in Git for reference purposes
    │   │   ├── Makefile            // Saved in Git for reference purposes
    │   ├── build-clang-bcc-msys2
    │   │   ├── CMakeFiles
    │   │   │   ├── CMakeError.log  // Saved in Git for reference purposes
    │   │   │   ├── CMakeOutput.log // Saved in Git for reference purposes
    │   ├── build-clang-msys2
    │   │   ├── CMakeFiles
    │   │   │   ├── CMakeOutput.log // Saved in Git for reference purposes
    │   │   ├── Makefile            // Saved in Git for reference purposes
    │   ├── clang-bcc-msys2-test.sh
    │   ├── clang-m2sys-test.sh
    │   ├── clang-bcc-obj-test.sh
    │   └── dummy_main.cpp
    └── vs_me.cmd
    
```
## Builds with Visual Studio 2015

* Execute provided DOS command shell vs_me.cmd to create Visual Stuido build environment

```
    │   vs_me.cmd
    │
    ├───build_vs
    │   │   ALL_BUILD.vcxproj
    │   │   ALL_BUILD.vcxproj.filters
    │   │   clang-bcc.sln
    │   │   clang-bcc.VC.db
    │   │   clang-bcc.vcxproj
    │   │   clang-bcc.vcxproj.filters
    │   │   clang-bcc.vcxproj.user
    │   │   CMakeCache.txt
    │   │   cmake_install.cmake
    │   │   ZERO_CHECK.vcxproj
    │   │   ZERO_CHECK.vcxproj.filters
    │   │
    │   ├───Debug
    │           clang-bcc.exe
``` 

## Tests

* Contains a number of scripts for CMake generation of build tool-chains in DOS and MinGW (MSYS2)
* Cmake ==> DOS[Borland Make bcc32c] means CMake generation to DOS shell tool-chain of Borland Make using bcc32c compiler.
* Scripts generating DOS shell build environments must be executed in a DOS shell.
* Scripts generating MinGW shell build environments must be executed in MinGW/MSYS2 shell.
* Scripts generating Microsoft NMake tool chain must be executed in Visual Stuio Developer Command prompt (PATH set to namke tool)

```
    └───test
        │   bcc32c_win_me.bat           // Cmake ==> DOS[Borland Make bcc32c] in build-bcc32c-win
        │   clang-bcc-obj-test.sh       // clang-bcc default compile in build-clang-bcc-bin 
        │   clang_bccmake_me.bat        // Cmake ==> DOS[Borland make clang-bcc] build-clang-bccmake
        │   clang-bcc_msys2_me.sh       // Cmake ==> MinGW[MSYS2 make clang-bcc] build-bcc-msys2
        │   clang_m2sys_me.sh           // CMake ==> MinGW[MSYS2 make default (GCC)] in build-clang-msys2
        │   clang_nmake_me.cmd          // CMake ==> DOS[Microsoft NMake clang] in buld-clang-nmake
        │   CmakeLists.txt
        │   dummy_main.cpp
        │

        │
        ├───build-clang-bcc-msys2
        │   └── clang-bcc.exe           // On test - Copied from 

                                        ├───build_vs
                                        │   ├───Debug
                                            │           clang-bcc.exe        
        │   │
        │   └───CMakeFiles
        │       │   CMakeError.log
        │       │   CMakeOutput.log

        ├── clang-bcc-bin
        │   ├── dummy_main.obj		// Output of clang-bcc on success (For object file format studies) 
        │   └── clang-bcc.exe           // On test - Copied from 

                                        ├───build_vs
                                        │   ├───Debug
                                            │           clang-bcc.exe

        ├───build-clang-bccmake
        │   │
        │   └───CMakeFiles
        │       │   CMakeError.log
        │       │   CMakeOutput.log

        ├───build-bcc32c-win            // CMake success too-chain using Borland Make and bcc32c 
        │   │   Makefile
        │   │
        │   └───CMakeFiles
        │       │   CMakeOutput.log

        ├───build-clang-msys2       // CMake success tool-chain using MSYS2 make and clang/clang++ 
        │   │   Makefile
        │   │
        │   └───CMakeFiles
        │       │   CMakeOutput.log

        │
        ├───build-clang-nmake
        │   │   CMakeCache.txt
        │   │
        │   └───CMakeFiles
        │       │   CMakeError.log
        │       │   CMakeOutput.log

```

## Object file format Issues (bcc output not in the same format as impersonated compiler format)

To impersonate as another compiler we have the problem of generating object files with the same format as the compiler we personate as.

**Build-tool-chain ==> Clang front-end :: clang-bcc :: bcc-compiler ==> bcc object file format**

* We know the clang-bcc frontend is always run on Windows (Embarcadero compilers exist onwindows only)
* In MinGW shell the tool-chain (automake emulation) expect to generate MinGW clang object files
* But by actually engaging a bcc compiler (bcc32, bcc32c, bcc64) it generates object files of Embarcadero compiler format.

  * bcc32 	==> OMF (http://docwiki.embarcadero.com/RADStudio/Seattle/en/BCC32)
  * bcc32c	==> OMF (http://docwiki.embarcadero.com/RADStudio/Seattle/en/BCC32C)
  * bcc64	==> ELF (http://docwiki.embarcadero.com/RADStudio/Seattle/en/BCC64)

  * MinGW64 clang	==> COFF??

* TODO: We have to conform that MinGW clang generates ELF format and that MinGW ar-command line (archive tool) generates ELF archives.

  * If so we should be able to use bcc64 as backend compiler nad have it work on MinGW build tool chain (ELF all the way)?

```

```

## Version 0.35

* \+ Introduced FronetEnd-Core-Backend source code architecture idiom
* \+ Refactored Process and API Error Code excpetion into BackEnd.
* \+ Introduced compile-time decision to select win32 backend calls for platform agnostic backend calls.

## Version 0.3

* \+ Refactored to true RAII Porcess class (throws on failure to create compiler process)
* \+ Refactored to have process execution call return an std::future with child process return value
* \+ Refactored to use app namespace with sub-namespaces to isloate possible futire lib code (e.g. app::process::win32)
* \- Does not yet work as a Cmake clang replacement (see logs below)

## Version 0.2

  * \+ Now act as front-end for both C and C++ compiler
  * \+ back-end call and parameter transform only for bcc32c
  * \+ Added MINGW shell test of MSYS make file generation using clang-bcc as front-end
  * \+ Added DOS whll test of Borland Make file generation using bcc32c (embarcadero design)
  * \- clang-bcc fails for C-link using bcc32c (_main not found)

## Version 0.1

  * \+ First pass of using clang-bcc.exe as compiler front-end to have cmake generate an "Embarcadero" build environment
  * \- No parameter adaption yet implemented.
  * \- Atual build with generated environment and clang-bcc.exe as compiler/linker not yet done.

## Status: CMake ==> DOS[Borland MAKE for Clang]

* For some reason CMake generated NMake build does not seem to feed clang with clang parameters?

```
Determining if the C compiler works failed with the following output:
Change Dir: C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bccmake/CMakeFiles/CMakeTmp

Run Build Command:"make" "cmTC_e8a9e\fast"
MAKE Version 5.41  Copyright (c) 1987, 2014 Embarcadero Technologies, Inc.

	make -f CMakeFiles\cmTC_e8a9e.dir\build.make -l -o  CMakeFiles\cmTC_e8a9e.dir\build

MAKE Version 5.41  Copyright (c) 1987, 2014 Embarcadero Technologies, Inc.

Building C object CMakeFiles/cmTC_e8a9e.dir/testCCompiler.c.obj

	C:\PROGRA~1\LLVM\bin\clang.exe @MAKE0000.@@@

clang.exe: error: no such file or directory: '/nologo'
clang.exe: error: no such file or directory: '/DWIN32'
clang.exe: error: no such file or directory: '/D_WINDOWS'
clang.exe: error: no such file or directory: '/W3'
clang.exe: error: no such file or directory: '/D_DEBUG'
clang.exe: error: no such file or directory: '/MDd'
clang.exe: error: no such file or directory: '/Zi'
clang.exe: error: no such file or directory: '/Ob0'
clang.exe: error: no such file or directory: '/Od'
clang.exe: error: no such file or directory: '/RTC1'
clang.exe: error: no such file or directory: '/FoCMakeFilescmTC_e8a9e.dirtestCCompiler.c.obj'
clang.exe: error: no such file or directory: '/FdCMakeFilescmTC_e8a9e.dir -c'
clang.exe: error: no such file or directory: 'C:Userskjell-olovhogdahlDocumentsGitHubclang-bccbuildtestbuild-clang-bccmakeCMakeFilesCMakeTmptestCCompiler.c'
clang.exe: error: no input files

** error 1 ** deleting CMakeFiles\cmTC_e8a9e.dir\testCCompiler.c.obj
** error 1 ** deleting cmTC_e8a9e\fast
```

  
## Status: CMake ==> DOS[Microsoft NMAKE for Clang]

* For some reason CMake generated NMake build does not seem to feed clang with clang parameters?

```
Run Build Command:"make" "cmTC_e8a9e\fast"
MAKE Version 5.41  Copyright (c) 1987, 2014 Embarcadero Technologies, Inc.

	make -f CMakeFiles\cmTC_e8a9e.dir\build.make -l -o  CMakeFiles\cmTC_e8a9e.dir\build

MAKE Version 5.41  Copyright (c) 1987, 2014 Embarcadero Technologies, Inc.

Building C object CMakeFiles/cmTC_e8a9e.dir/testCCompiler.c.obj

	C:\PROGRA~1\LLVM\bin\clang.exe @MAKE0000.@@@

clang.exe: error: no such file or directory: '/nologo'
clang.exe: error: no such file or directory: '/DWIN32'
clang.exe: error: no such file or directory: '/D_WINDOWS'
clang.exe: error: no such file or directory: '/W3'
clang.exe: error: no such file or directory: '/D_DEBUG'
clang.exe: error: no such file or directory: '/MDd'
clang.exe: error: no such file or directory: '/Zi'
clang.exe: error: no such file or directory: '/Ob0'
clang.exe: error: no such file or directory: '/Od'
clang.exe: error: no such file or directory: '/RTC1'
clang.exe: error: no such file or directory: '/FoCMakeFilescmTC_e8a9e.dirtestCCompiler.c.obj'
clang.exe: error: no such file or directory: '/FdCMakeFilescmTC_e8a9e.dir -c'
clang.exe: error: no such file or directory: 'C:Userskjell-olovhogdahlDocumentsGitHubclang-bccbuildtestbuild-clang-bccmakeCMakeFilesCMakeTmptestCCompiler.c'
clang.exe: error: no input files
```

## Status: CMake ==> MinGW[MSYS2 make for clang-bcc front-end]

  * The test is invoked with project memner mingw_test.sh in test sub-folder of build folder.
```
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
```

  1. clang-bcc fails to compile C idnetification file CMakeCCompilerId.c (impersonating as clang)
```
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
```
  * TODO: Call correct back-end clang compiler for C-compilation.

  2. clang-bcc succeeds to compile C++ identification CMakeCXXCompilerId.cpp (impersonating as clang)
```
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
```

  3. clang-cpp succeeds to compile C test file (calling back-end bcc32c)
```
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
```
  4. clang-bcc succeeds to link C-compiled test code (using back-end bcc32c as linker)
```
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
```
  5. clang-bcc succeeds to compile C ABI identification file CMakeCCompilerABI.c
```
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
```
  6. clang-bcc succeeds to link the C ABI identification CMakeCCompilerABI.c.obj to exe
```
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
```
  7. clang-bcc succeeds to compile test C++ file testCXXCompiler.cxx (using back-end bcc32c)
```
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
```
  8. clang-bcc fails to link the C++ test file object code
```
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
```

  * TODO: Figure out why cmake first calls to generate "CMakeFiles/cmTC_caac7.dir/testCXXCompiler.cxx.obj" but then asks to link "CMakeFiles/cmTC_caac7.dir/objects.a"?

  9. clang-bcc succeeds to compile the C++ ABI detection source CMakeCXXCompilerABI.cpp
```
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
```
  8. clang-bcc fails to link the C++ ABI detection exe
```
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
```
  * TODO: Figure out why cmake first calls to generate "CMakeFiles/cmTC_9068c.dir/CMakeCXXCompilerABI.cpp.obj" but then asks to link "CMakeFiles/cmTC_9068c.dir/objects.a"?

  10. clang-bcc fails to pass clang c++14 switch to back-end bcb32c (diabsling cmake to determine c++14 support)
```
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
```
  * TODO: Fails transformation of passsed clang c++14 to bcb32c (or pass suatble parameter at have bcb32c fail appropriatly)

  11. clang-bcc fails to link C++ compiler option build
```
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
```
  * TODO: Figure out why cmake first calls to generate "CMakeFiles/cmTC_9068c.dir/CMakeCXXCompilerABI.cpp.obj" but then asks to link "CMakeFiles/cmTC_9068c.dir/objects.a"?
