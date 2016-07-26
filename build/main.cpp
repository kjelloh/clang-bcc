#ifdef __CODEGEARC__
#pragma hdrstop
#pragma argsused
#endif

#ifdef _WIN32
	#include <tchar.h>
#else
	typedef char _TCHAR;
	#define _tmain main
#endif

// Suppress Visual Studio warnings about call to standard library with unchecked iterators (e.g., call to std::missmatch using boost path iterators)
#ifndef _SCL_SECURE_NO_WARNINGS
	// Not defined by build environment (e.g. cmake) su define it here
	#define _SCL_SECURE_NO_WARNINGS 
#endif

#include "Helpers.h"
#include "parameters.h"
#include "Process.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
// #include <boost/filesystem.hpp>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <functional>
#include <memory>

// namespace filesystem = boost::filesystem; // Enable change of applied filesystem by later changing alias (e.g., to C++17 std::filesystem)
// using Path = filesystem::path;
// using Paths = std::vector<Path>;

// namespace local { namespace detail {
// 	// until filesystem::relative in http://www.boost.org/doc/libs/1_61_0/libs/filesystem/doc/reference.html#op-relative
// 	using path = filesystem::path;
// 	path relative(const path& p, const path& base=filesystem::current_path()) {
// 		path result;
// 		auto iter_pair = std::mismatch(
// 			 std::begin(base),std::end(base)
// 			,std::begin(p));
// 		std::for_each(iter_pair.second,std::end(p),[&result](const path& p) {result /= p;});
// // std::cout << "missmatch of " << p << " and " << base << " returns " << result << "\n";
// 		return result;
// 	}
// }}

using Path = app::process::Path;


struct Compiler {
	int execute(Parameters parameters);
	Path m_path;
};

int Compiler::execute(Parameters parameters) {
	int result = 0;
	{
		std::cout << "\n[[CLANG-BCC]]:Actual Compiler = " << this->m_path;
		std::cout << "\n\t<Parameter List (vaules between [...]>";
		std::for_each(std::begin(parameters), std::end(parameters), [](const Parameter& p) {std::cout << "\n\t[" << p << "]"; });
	}
	std::cout << "\n[[CLANG-BCC]]:START COMPILER";
	auto compile_result = app::process::execute(this->m_path, parameters);
	result = compile_result.get(); // Wait for process to end and access the returned code
	std::cout << "\n[[CLANG-BCC]]:COMPILER END";
	return result;
}

Path pathToCompiler(e_CompilerId compiler_id) {
	Path result("#unknown_compiler#");
	switch (compiler_id) {
	case eCompilerId_clang:
		result = R"(clang++)"; 
		break;
	case eCompilerId_bcc32:
		result = R"(C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32.exe)";
		break;

	case eCompilerId_bcc32c:
		result = R"(C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe)";
		break;
	case eCompilerId_bcc64:
		result = R"(C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc64.exe)";
		break;
	}

	return result;
}

bool isCmakeComplierIdCall(Parameters parameters) {
	bool result = false;
	result = std::any_of(std::begin(parameters), std::end(parameters), [](Parameter p) {
		return (    (p.find("CMakeCXXCompilerId") != std::string::npos)
			     || (p.find("CMakeCCompilerId.c") != std::string::npos));
	});
	return result;
}

bool isCmakeComplierABIIdCall(Parameters parameters) {
	bool result = false;
	result = std::any_of(std::begin(parameters), std::end(parameters), [](Parameter p) {
		return (    (p.find("CMakeCXXCompilerABI") != std::string::npos)
			     || (p.find("CMakeCCompilerABI.c") != std::string::npos));
	});
	return result;
}

enum e_CallMode {
	eCallMode_Undefined
	, e_CallMode_CMakeCompilerIdCall
	, e_CallMode_CmakeCompilerOutABIIdCall
	, e_CallMode_BuildEnvrionmentCall
	, e_CallMode_Unknown
};

e_CallMode detectedCallMode(Parameters parameters) {
	e_CallMode result = eCallMode_Undefined;
	if (isCmakeComplierIdCall(parameters)) {
		result = e_CallMode_CMakeCompilerIdCall;
	}
	else if (isCmakeComplierABIIdCall(parameters)) {
		result = e_CallMode_CmakeCompilerOutABIIdCall;
	}
	else {
		result = e_CallMode_BuildEnvrionmentCall;
	}
	return result;
}

 int _tmain(int argc, _TCHAR* argv[])
{
	 int result = 0;
	try {
		std::cout << "\n[[CLANG-BCC]]:START";

		std::string sOurPath(argv[0]); // Path to us
		Parameters parameters(&argv[1], &argv[argc]); // skip argv[0] which is the path to "us"

		// Log the call to us
		// E.g., C:\Users\kjell-olovhogdahl\Documents\GitHub\clang-bcc\build\test\build-clang-bcc\clang-bcc.exe -o CMakeFiles/cmTC_8228c.dir/testCXXCompiler.cxx.obj -c C:/Users/kjell-olovhogdahl/Documents/GitHub/clang-bcc/build/test/build-clang-bcc/CMakeFiles/CMakeTmp/testCXXCompiler.cxx
		{
			std::cout << "\n[[CLANG-BCC]]:" << sOurPath;
			std::for_each(std::begin(parameters), std::end(parameters), [](const Parameter& p) {std::cout << " " << p;});
		}

		// Hard code the bcc compiler to use as back-end
		//const e_CompilerId bcc_compiler_id = eCompilerId_bcc32;
		const e_CompilerId bcc_compiler_id = eCompilerId_bcc32c;
		//const e_CompilerId bcc_compiler_id = eCompilerId_bcc64;

		const e_CompilerId impersonated_compiler_id = eCompilerId_clang; // Impersoante as clang compiler
		const e_CompilerId abi_identification_compiler_id = bcc_compiler_id; // use bcc compiler for Cmake abi identification call
		const e_CompilerId build_compiler_id = bcc_compiler_id; // use bcc compiler as actual compiler (build environment compiler call)

		// Decide on back-end compiler to use depending on identified call
		e_CompilerId backend_compiler_id = eCompilerId_Undefined;
		{
			switch (detectedCallMode(parameters)) {
			case e_CallMode_CMakeCompilerIdCall:
				// Select compiler to use for cmake compiler identification.
				// This will be the compielr we trick cmake to think that "we" are (i.e., we will  impersonate a fron-end to this compiler)
				backend_compiler_id = impersonated_compiler_id;
				std::cout << "\n[[CLANG-BCC]]:CMake <<compiler identification>> call detected";
				break;
			case e_CallMode_CmakeCompilerOutABIIdCall:
				// Select compiler to use for cmake compiler output ABI identification
				backend_compiler_id = abi_identification_compiler_id;
				std::cout << "\n[[CLANG-BCC]]:CMake <<compiler ABI output identification>> call detected";
				break;
			default:
				// Build environment compiler call
				backend_compiler_id = bcc_compiler_id;
				std::cout << "\n[[CLANG-BCC]]:Build call asumed";
				break;
			}
			std::cout << "\n[[CLANG-BCC]]:Decided to use back-end compiler " << pathToCompiler(backend_compiler_id);
		}

		// Force a compiler if set for developemnt test purposes
		{
			e_CompilerId forced_compiler_id = eCompilerId_Undefined; // Do not force the compiler to use
			//e_CompilerId forced_compiler = eCompilerId_bcc32c; // Development test

			if (forced_compiler_id > eCompilerId_Undefined && forced_compiler_id < eCompilerId_Unknown) {
				if (forced_compiler_id != backend_compiler_id) {
					backend_compiler_id = forced_compiler_id;
					std::cout << "\n[[CLANG-BCC]]:Forced Compiler Mode: Actual compiler forced to ==> " << pathToCompiler(backend_compiler_id);
				}
			}
		}

		Path backend_compiler_path(pathToCompiler(backend_compiler_id));

		// Process non-compiler parameters (set test purpose parameters)
		{
			if (parameters.size() >= 2) {
				if (parameters[0] == "---") {
					backend_compiler_path = parameters[1]; // Override decided back-end compiler, E.g., as in call "clang-bcc --- bcc32c"
					parameters.erase(parameters.begin()); // strip-off non-compiler parameter
					parameters.erase(parameters.begin()); // strip-off non-compiler parameter
				}
			}
		}

		// TEST: Engage back-end compiler in a way that will surely fail (process class constructor will throw)
		{
			// Compiler backend_compiler{ "%&_invalid_path_!#" }; // TEST failure to create compiler process (constructor will throw)
			// result = backend_compiler.execute(fromCompilerParameters<impersonated_compiler_id>::to(backend_compiler_id, parameters));
		}

		// Engage the back-end compiler with transformed parameters
		{
			Compiler backend_compiler{ backend_compiler_path };
			result = backend_compiler.execute(fromCompilerParameters<impersonated_compiler_id>::to(backend_compiler_id, parameters));
		}		
	}
	catch (std::runtime_error& e) {
		std::cout << "\n[[CLANG-BCC]]: Failed - Exception = " << e.what();
		result = 1; // Failed
	}
    
	std::cout << "\n[[CLANG-BCC]]:END" << std::endl; // Report end and flush
	return result;
}
