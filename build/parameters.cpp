#include "parameters.h"
#include <iterator>
#include <algorithm>
#include <iostream>

/**
  * (1) CMake compiler call for compiler identification compilation
  * clang++: /C/msys64/mingw64/bin/clang++.exe      -o CMakeFiles/cmTC_aa479.dir/testCXXCompiler.cxx.obj -c /C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-MSYS2-clang/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
  * Bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -DWIN32   -tM  -Od -v   -oCMakeFiles/cmTC_5530a.dir/testCXXCompiler.cxx.obj -P -c /C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
  */

/**
  * (2) Cmake linker call for compiler identification object file
  * clang++: /C/msys64/mingw64/bin/clang++.exe       -Wl,--whole-archive CMakeFiles/cmTC_aa479.dir/objects.a -Wl,--no-whole-archive  -o cmTC_aa479.exe -Wl,--major-image-version,0,--minor-image-version,0  -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 
  * bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -ecmTC_5530a.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192   -v -tC  -tM  -Od -v   import32.lib  "CMakeFiles/cmTC_5530a.dir/testCXXCompiler.cxx.obj" 
  */

/**
  * (3) Cmake compiler call to compile ABI identification compilation
  * clang++: /C/msys64/mingw64/bin/clang++.exe      -o CMakeFiles/cmTC_77780.dir/CMakeCXXCompilerABI.cpp.obj -c /C/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp 
  * bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -DWIN32   -tM  -Od -v   -oCMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj -P -c /C/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp
  */

/**
  * (4) Cmake linker call for ABI identification object file
  * clang++: /C/msys64/mingw64/bin/clang++.exe      -v -Wl,--whole-archive CMakeFiles/cmTC_77780.dir/objects.a -Wl,--no-whole-archive  -o cmTC_77780.exe -Wl,--major-image-version,0,--minor-image-version,0   
  * bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -ecmTC_f64ef.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192   -v -tC  -tM  -Od -v     "CMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj" 
  */

Parameters toActualCompilerParameters(const Parameters parameters) {
	Parameters result;

	std::cout << "\n[[CLANG-BCC]]:Parameter Transformation";
	std::cout << "\n\t<IN Parameter List (vaules between [...]>";
	std::for_each(std::begin(parameters), std::end(parameters), [](const Parameter& p) {std::cout << "\n\t[" << p << "]"; });

	if (parameters.size() == 1) {
		// Pass through for no-parameter call (i.e., asume only source file provided)
		std::copy(std::begin(parameters), std::end(parameters), std::back_inserter(result)); // Pass through
	}
	else if (parameters.size() == 4) // -o CMakeFiles/cmTC_aa479.dir/testCXXCompiler.cxx.obj -c /C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-MSYS2-clang/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
	{
		// Asume the folliwng (qick test hack)

		/**
		* (1) CMake compiler call for compiler identification compilation
		* clang++: /C/msys64/mingw64/bin/clang++.exe      -o CMakeFiles/cmTC_aa479.dir/testCXXCompiler.cxx.obj -c /C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-MSYS2-clang/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
		* Bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -DWIN32   -tM  -Od -v   -oCMakeFiles/cmTC_5530a.dir/testCXXCompiler.cxx.obj -P -c /C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
		*/

		//<clang++>
		//-o CMakeFiles/cmTC_aa479.dir/testCXXCompiler.cxx.obj 
		//-c 
		// /C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-MSYS2-clang/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
		Parameter object_file_path = parameters[1];
		Parameter source_file_path = parameters[3];

		//<bcc>
		//-tR 
		//-DWIN32   
		//-tM  
		//-Od 
		//-v   
		//-oCMakeFiles/cmTC_5530a.dir/testCXXCompiler.cxx.obj 
		//-P 
		//-c 
		///C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/CMakeFiles/CMakeTmp/testCXXCompiler.cxx

		result.push_back("-tR");
		result.push_back("-DWIN32");
		result.push_back("-tM");
		result.push_back("-Od");
		result.push_back("-v");
		result.push_back(Parameter("-o") + Parameter(object_file_path));
		result.push_back("-P");
		result.push_back("-c");
		result.push_back(source_file_path);		
	}
	else if ((parameters.size() > 4)?(parameters[1].find("-W1") != std::string::npos):false) // -Wl,--whole-archive CMakeFiles/cmTC_aa479.dir/objects.a -Wl,--no-whole-archive  -o cmTC_aa479.exe -Wl,--major-image-version,0,--minor-image-version,0  -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 
	{
		/**
		* (2) Cmake linker call for compiler identification object file
		* clang++: /C/msys64/mingw64/bin/clang++.exe       -Wl,--whole-archive CMakeFiles/cmTC_aa479.dir/objects.a -Wl,--no-whole-archive  -o cmTC_aa479.exe -Wl,--major-image-version,0,--minor-image-version,0  -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 
		* bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -ecmTC_5530a.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192   -v -tC  -tM  -Od -v   import32.lib  "CMakeFiles/cmTC_5530a.dir/testCXXCompiler.cxx.obj"
		*/

		//<clang>
		//-Wl,--whole-archive CMakeFiles/cmTC_aa479.dir/objects.a 
		//-Wl,--no-whole-archive  
		//-o cmTC_aa479.exe 
		//-Wl,--major-image-version,0,--minor-image-version,0  
		//-lkernel32 
		//-luser32 
		//-lgdi32 
		//-lwinspool
		//-lshell32
		//-lole32
		//-loleaut32
		//-luuid 
		//-lcomdlg32 
		//-ladvapi32
		//
		//<bcc>
		//-tR 
		//-ecmTC_5530a.exe 
		//-tM 
		//-lS:1048576 
		//-lSc:4098 
		//-lH:1048576 
		//-lHc:8192   
		//-v 
		//-tC  
		//-tM  
		//-Od 
		//-v
		//import32.lib  
		//"CMakeFiles/cmTC_5530a.dir/testCXXCompiler.cxx.obj"

	}
	{
		/**
		* (3) Cmake compiler call to compile ABI identification compilation
		* clang++: /C/msys64/mingw64/bin/clang++.exe      -o CMakeFiles/cmTC_77780.dir/CMakeCXXCompilerABI.cpp.obj -c /C/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp
		* bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -DWIN32   -tM  -Od -v   -oCMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj -P -c /C/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp
		*/

		/*
		<clang>
		-o CMakeFiles/cmTC_77780.dir/CMakeCXXCompilerABI.cpp.obj 
		-c 
		/C/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp
		*/

		/*
		<bcc>
		-tR 
		-DWIN32   
		-tM  
		-Od 
		-v   
		-oCMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj 
		-P 
		-c 
		/C/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp
		*/
	}
	{
		/**
		* (4) Cmake linker call for ABI identification object file
		* clang++: /C/msys64/mingw64/bin/clang++.exe      -v -Wl,--whole-archive CMakeFiles/cmTC_77780.dir/objects.a -Wl,--no-whole-archive  -o cmTC_77780.exe -Wl,--major-image-version,0,--minor-image-version,0
		* bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -ecmTC_f64ef.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192   -v -tC  -tM  -Od -v     "CMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj"
		*/

		/*
		<clang>
		-v 
		-Wl,--whole-archive CMakeFiles/cmTC_77780.dir/objects.a 
		-Wl,--no-whole-archive  
		-o cmTC_77780.exe 
		-Wl,--major-image-version,0,--minor-image-version,0
		*/

		/*
		<bcc>
		-tR 
		-ecmTC_f64ef.exe 
		-tM 
		-lS:1048576 
		-lSc:4098 
		-lH:1048576 
		-lHc:8192   
		-v 
		-tC  
		-tM  
		-Od 
		-v     
		"CMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj"
		*/
	}

	if (parameters.size() != 0 && result.size() == 0) {
		// No transformation applied.
		//std::copy(std::begin(parameters), std::end(parameters), std::back_inserter(result)); // Pass through
		throw std::runtime_error("Parameter transform FAILED"); // Fail
	}

	std::cout << "\n\t<OUT Parameter List (vaules between [...]>";
	std::for_each(std::begin(result), std::end(result), [](const Parameter& p) {std::cout << "\n\t[" << p << "]"; });

	return result;
}
