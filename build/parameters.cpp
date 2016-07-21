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

bool isDefaultCompileCall(const Parameter& source_file_path, const Parameter& object_file_path, const Parameter& exe_file_path) {
	return ((source_file_path.size() > 0) && (object_file_path.size() == 0) && (exe_file_path.size() == 0));
}

bool isCompileToObjectFileCall(const Parameter& source_file_path, const Parameter& object_file_path, const Parameter& exe_file_path) {
	return ((source_file_path.size() > 0) && (object_file_path.size() > 0) && (exe_file_path.size() == 0));
}

bool isLinkToExeCall(const Parameter& source_file_path, const Parameter& object_file_path, const Parameter& exe_file_path) {
	return ((source_file_path.size() == 0) && (object_file_path.size() > 0) && (exe_file_path.size() > 0));
}

bool is_last(const Parameter& p,const std::string& s) {
	return (p.size() >= s.length()) && (p.rfind(s) == (p.size() - s.length())); // p=".c", s=".c", p.rfind(s) == 6, p.size() == 8, s.length() == 2, 6 == 8-2
}

Parameters fromClangtoBcc32cCompilerParameters(const Parameters& parameters) {
	Parameters result;

	Parameter source_file_path; // .c (C-file) or any source file (cpp-file)
	Parameter object_file_path; // .a (archive) or .obj (object file)
	Parameter exe_file_path; // An .exe file
	bool is_c_file;
	std::for_each(std::begin(parameters), std::end(parameters), [&](const Parameter& p) {
		if (p.find_first_of("-") == 0) {
			// An - parameter
		}
		else {
			// a file parameter
			if (   is_last(p,".a")
				|| is_last(p,".obj")) {
				// It is the archive/object path
				object_file_path = p;
			}
			else if (is_last(p,".exe")) {
				// It is the exe-file path
				exe_file_path = p;
			}
			else {
				// It is the source-file path
				source_file_path = p;
				is_c_file = is_last(source_file_path,".c"); 
			}
		}
	});


	if (parameters.size() == 0) {
		// Called with no parameters. Do nothing (returns empty result)
	}
	else if (isDefaultCompileCall(source_file_path, object_file_path, exe_file_path)) {
		std::cout << "\n[[CLANG-BCC]]:Default Compile Parameters ";
		result.push_back(source_file_path);
	}
	else if (isCompileToObjectFileCall(source_file_path, object_file_path, exe_file_path)) {
		std::cout << "\n[[CLANG-BCC]]:Compile to object/archive Parameters";
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
		if (is_c_file == false) { result.push_back("-P"); };
		result.push_back("-c");
		result.push_back(source_file_path);
	}
	else if (isLinkToExeCall(source_file_path, object_file_path, exe_file_path)) {
		std::cout << "\n[[CLANG-BCC]]:Link to Exe Parameters";
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

		result.push_back(object_file_path); // CMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj"
	}
	else {
		// Unknown transformation
		throw std::runtime_error("Unknown Parameter Transformation (Not default compile, compile object or link exe)");
	}

	//if ((source_file_path.size() > 0) && (object_file_path.size() == 0) && (exe_file_path.size() == 0)) {
	//	// Pass through for single source-file call
	//	// TODO: Perform 
	//	std::copy(std::begin(parameters), std::end(parameters), std::back_inserter(result));
	//}
	//else if (parameters.size() == 4) // -o CMakeFiles/cmTC_aa479.dir/testCXXCompiler.cxx.obj -c /C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-MSYS2-clang/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
	//{
	//	// Asume the folliwng (qick test hack)

	//	/**
	//	* (1) CMake compiler call for compiler identification compilation
	//	* clang++: /C/msys64/mingw64/bin/clang++.exe      -o CMakeFiles/cmTC_aa479.dir/testCXXCompiler.cxx.obj -c /C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-MSYS2-clang/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
	//	* Bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -DWIN32   -tM  -Od -v   -oCMakeFiles/cmTC_5530a.dir/testCXXCompiler.cxx.obj -P -c /C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
	//	*/

	//	//<clang++>
	//	//-o CMakeFiles/cmTC_aa479.dir/testCXXCompiler.cxx.obj 
	//	//-c 
	//	// /C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-MSYS2-clang/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
	//	Parameter object_file_path;
	//	Parameter source_file_path;
	//	std::for_each(std::begin(parameters), std::end(parameters), [&](const Parameter& p) {
	//		if (p.find_first_of("-") == 0) {
	//			// An - parameter
	//		}
	//		else {
	//			// a file parameter
	//			if (p.rfind(".obj") == (p.length() - 1)) {
	//				// It is the exe-file path
	//				object_file_path = p;
	//			}
	//			else {
	//				// It is the source-file path
	//				source_file_path = p;
	//			}
	//		}
	//	});


	//	//<bcc>
	//	//-tR 
	//	//-DWIN32   
	//	//-tM  
	//	//-Od 
	//	//-v   
	//	//-oCMakeFiles/cmTC_5530a.dir/testCXXCompiler.cxx.obj 
	//	//-P 
	//	//-c 
	//	///C/Users/kjell-olovhogdahl/Documents/GitHub/GSL/build-clang-bcc-frontend/CMakeFiles/CMakeTmp/testCXXCompiler.cxx

	//	bool is_c_file = (source_file_path.rfind(".c") == (source_file_path.length() - 1)); // E.g., source_file_path==".c", source_file_path.length()==2, source_file_path.rfind(".c")==1;

	//	result.push_back("-tR");
	//	result.push_back("-DWIN32");
	//	result.push_back("-tM");
	//	result.push_back("-Od");
	//	result.push_back("-v");
	//	result.push_back(Parameter("-o") + Parameter(object_file_path));
	//	if (is_c_file == false) { result.push_back("-P"); };
	//	result.push_back("-c");
	//	result.push_back(source_file_path);
	//}
	//else if (std::any_of(std::begin(parameters), std::end(parameters), [](const Parameter& p) {return (p.find(".exe") != std::string::npos); }))
	//{
	//	/**
	//	* (2) Cmake linker call for compiler identification object file
	//	* clang++: /C/msys64/mingw64/bin/clang++.exe       -Wl,--whole-archive CMakeFiles/cmTC_aa479.dir/objects.a -Wl,--no-whole-archive  -o cmTC_aa479.exe -Wl,--major-image-version,0,--minor-image-version,0  -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32
	//	* bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -ecmTC_5530a.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192   -v -tC  -tM  -Od -v   import32.lib  "CMakeFiles/cmTC_5530a.dir/testCXXCompiler.cxx.obj"
	//	*/

	//	//<clang>
	//	//-Wl,--whole-archive 
	//	//CMakeFiles/cmTC_aa479.dir/objects.a 
	//	//-Wl,--no-whole-archive  
	//	//-o 
	//	//cmTC_aa479.exe 
	//	//-Wl,--major-image-version,0,--minor-image-version,0  
	//	//-lkernel32 
	//	//-luser32 
	//	//-lgdi32 
	//	//-lwinspool
	//	//-lshell32
	//	//-lole32
	//	//-loleaut32
	//	//-luuid 
	//	//-lcomdlg32 
	//	//-ladvapi32
	//	
	//	Parameter exe_file_path;
	//	Parameter archive_file_path;
	//	std::for_each(std::begin(parameters), std::end(parameters), [&](const Parameter& p) {
	//		if (p.find_first_of("-") == 0) {
	//			// An - parameter
	//		}
	//		else {
	//			// a file parameter
	//			if (p.rfind(".exe") == (p.length()-1)) {
	//				// It is the exe-file path
	//				exe_file_path = p;
	//			}
	//			else if (     (p.rfind(".a") == (p.length() - 1))
	//				       || (p.rfind(".obj") == (p.length() - 1))) {
	//				// It is the archive/object path
	//				archive_file_path = p;
	//			}
	//		}
	//	});

	//	//<bcc>
	//	//-tR 
	//	//-ecmTC_5530a.exe 
	//	//-tM 
	//	//-lS:1048576 
	//	//-lSc:4098 
	//	//-lH:1048576 
	//	//-lHc:8192   
	//	//-v 
	//	//-tC  
	//	//-tM  
	//	//-Od 
	//	//-v
	//	//import32.lib  
	//	//"CMakeFiles/cmTC_5530a.dir/testCXXCompiler.cxx.obj"

	//	result.push_back("-tR");
	//	result.push_back(Parameter("-e") + exe_file_path);
	//	result.push_back("-tM");
	//	result.push_back("-lS:1048576");
	//	result.push_back("-lSc:4098");
	//	result.push_back("-lH:1048576");
	//	result.push_back("-lHc:8192");
	//	result.push_back("-v");
	//	result.push_back("-tC");
	//	result.push_back("-tM");
	//	result.push_back("-Od");
	//	result.push_back("-v"); // twice (as generated for borland by cmake)??

	//	/*
	//	bcc32c.exe: warning: argument unused during compilation: '-Xclang -cxx-abi'
	//	bcc32c.exe: warning: argument unused during compilation: '-Xclang borland'
	//	bcc32c.exe: warning: argument unused during compilation: '-nobuiltininc'


	//	*/

	//	result.push_back(archive_file_path); // CMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj"
	//}

	//{
	//	// Caught as (1) above
	//	/**
	//	* (3) Cmake compiler call to compile ABI identification compilation
	//	* clang++: /C/msys64/mingw64/bin/clang++.exe      -o CMakeFiles/cmTC_77780.dir/CMakeCXXCompilerABI.cpp.obj -c /C/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp
	//	* bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -DWIN32   -tM  -Od -v   -oCMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj -P -c /C/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp
	//	*/

	//	/*
	//	<clang>
	//	-o CMakeFiles/cmTC_77780.dir/CMakeCXXCompilerABI.cpp.obj 
	//	-c 
	//	/C/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp
	//	*/

	//	/*
	//	<bcc>
	//	-tR 
	//	-DWIN32   
	//	-tM  
	//	-Od 
	//	-v   
	//	-oCMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj 
	//	-P 
	//	-c 
	//	/C/msys64/mingw64/share/cmake-3.6/Modules/CMakeCXXCompilerABI.cpp
	//	*/
	//}

	//{
	//	// Caught as (2) above
	//	/**
	//	* (4) Cmake linker call for ABI identification object file
	//	* clang++: /C/msys64/mingw64/bin/clang++.exe      -v -Wl,--whole-archive CMakeFiles/cmTC_77780.dir/objects.a -Wl,--no-whole-archive  -o cmTC_77780.exe -Wl,--major-image-version,0,--minor-image-version,0
	//	* bcc: "/C/Program Files (x86)/Embarcadero/Studio/17.0/bin/bcc32c.exe"  -tR -ecmTC_f64ef.exe -tM -lS:1048576 -lSc:4098 -lH:1048576 -lHc:8192   -v -tC  -tM  -Od -v     "CMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj"
	//	*/

	//	/*
	//	<clang>
	//	-v
	//	-Wl,--whole-archive CMakeFiles/cmTC_77780.dir/objects.a
	//	-Wl,--no-whole-archive
	//	-o cmTC_77780.exe
	//	-Wl,--major-image-version,0,--minor-image-version,0
	//	*/

	//	/*
	//	<bcc>
	//	-tR
	//	-ecmTC_f64ef.exe
	//	-tM
	//	-lS:1048576
	//	-lSc:4098
	//	-lH:1048576
	//	-lHc:8192
	//	-v
	//	-tC
	//	-tM
	//	-Od
	//	-v
	//	"CMakeFiles/cmTC_f64ef.dir/CMakeCXXCompilerABI.cpp.obj"
	//	*/
	//}

	//if (parameters.size() != 0 && result.size() == 0) {
	//	// No transformation applied.
	//	//std::copy(std::begin(parameters), std::end(parameters), std::back_inserter(result)); // Pass through
	//	throw std::runtime_error("Parameter transform FAILED"); // Fail
	//}

	return result;
}
