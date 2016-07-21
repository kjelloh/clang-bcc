#include "parameters.h"
#include <iterator>
#include <algorithm>
#include <iostream>

// CMake Generated MSYS calls
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

// Cmake Generated Borland Make calls fro bcc32c
// Test C++ compile:C:\PROGRA~2\EMBARC~1\Studio\17.0\bin\bcc32c.exe -tR -DWIN32   -tM -Od -v -oCMakeFiles\cmTC_9ae11.dir\testCXXCompiler.cxx.obj -P -c C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-bcc32c\CMakeFiles\CMakeTmp\testCXXCompiler.cxx
// Test C compile:	C:\PROGRA~2\EMBARC~1\Studio\17.0\bin\bcc32c.exe -tR -DWIN32   -tM -Od -v -oCMakeFiles\cmTC_10480.dir\testCCompiler.c.obj        -c C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-bcc32c\CMakeFiles\CMakeTmp\testCCompiler.c

// Test C++ link:	C:\PROGRA~2\EMBARC~1\Studio\17.0\bin\bcc32c.exe -tR -ecmTC_9ae11.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192 -v -tC -tM -Od -v @MAKE0000.@@@
// Test C link :	C:\PROGRA~2\EMBARC~1\Studio\17.0\bin\bcc32c.exe -tR -ecmTC_10480.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192 -v -tC -tM -Od -v @MAKE0000.@@@

// C++ ABI Compile: C:\PROGRA~2\EMBARC~1\Studio\17.0\bin\bcc32c.exe -tR -DWIN32   -tM -Od -v -oCMakeFiles\cmTC_4d1b5.dir\CMakeCXXCompilerABI.cpp.obj -P -c "C:\Program Files (x86)\CMake\share\cmake-3.5\Modules\CMakeCXXCompilerABI.cpp"
// C ABI compile:	C:\PROGRA~2\EMBARC~1\Studio\17.0\bin\bcc32c.exe -tR -DWIN32   -tM -Od -v -oCMakeFiles\cmTC_e1db6.dir\CMakeCCompilerABI.c.obj        -c "C:\Program Files (x86)\CMake\share\cmake-3.5\Modules\CMakeCCompilerABI.c"

// C++ ABI Link:	C:\PROGRA~2\EMBARC~1\Studio\17.0\bin\bcc32c.exe -tR -ecmTC_4d1b5.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192 -v -tC -tM -Od -v @MAKE0000.@@@
// C ABI Link:		C:\PROGRA~2\EMBARC~1\Studio\17.0\bin\bcc32c.exe -tR -ecmTC_e1db6.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192 -v -tC -tM -Od -v @MAKE0000.@@@
// 

Parameters fromClangtoBcc32cCompilerParameters(const Parameters& parameters) {
	Parameters result;

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

		bool is_c_file = ((source_file_path.length() - source_file_path.find_last_of(".c")) -1 == 0); // E.g., source_file_path==".c", source_file_path.length()==2, source_file_path.find_last_of(".c")==1;

		result.push_back("-tR");
		result.push_back("-DWIN32");
		result.push_back("-tM");
		result.push_back("-Od");
		result.push_back("-v");
		result.push_back(Parameter("-o") + Parameter(object_file_path));
		if (is_c_file == false) { result.push_back("-P"); };
		result.push_back("-c");
		result.push_back(source_file_path);
	}
	else if (std::any_of(std::begin(parameters), std::end(parameters), [](const Parameter& p) {return (p.find(".exe") != std::string::npos); }))
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
		
		Parameter exe_file_path;
		Parameter archive_file_path;
		enum e_ParseState {
			eParseState_Undefined
			, eParseState_ParseAny
			, eParseState_ParseArchivePath
			, eParseState_ParseExecPath
			, eParseState_Unknown
		};
		e_ParseState parse_state = eParseState_ParseAny;
		std::for_each(std::begin(parameters), std::end(parameters), [&](const Parameter& p) {
			switch (parse_state) {
			case eParseState_ParseAny:
				if (p.find("--whole-archive") != std::string::npos) { parse_state = eParseState_ParseArchivePath; }
				else if (p.find("-o") != std::string::npos) { parse_state = eParseState_ParseExecPath; }
				break;
			case eParseState_ParseArchivePath:
				archive_file_path = p;
				parse_state = eParseState_ParseAny;
				break;
			case eParseState_ParseExecPath:
				exe_file_path = p;
				parse_state = eParseState_ParseAny;
				break;
			};
		});

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

		result.push_back("-tR");
		result.push_back(Parameter("-e") + exe_file_path);
		result.push_back("-tM");
		result.push_back("-lS:1048576");
		result.push_back("-lSc:4098");
		result.push_back("-lH:1048576");
		result.push_back("-lHc:8192");
		result.push_back("-v");
		result.push_back("-tC");
		result.push_back("-tM");
		result.push_back("-Od");
		result.push_back("-v"); // twice (as generated for borland by cmake)??

		/*
		bcc32c.exe: warning: argument unused during compilation: '-Xclang -cxx-abi'
		bcc32c.exe: warning: argument unused during compilation: '-Xclang borland'
		bcc32c.exe: warning: argument unused during compilation: '-nobuiltininc'

		*/

		result.push_back(archive_file_path); // CMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj"
	}

	{
		// Caught as (1) above
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
		// Caught as (2) above
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

	return result;
}
