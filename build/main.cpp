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

#include "parameters.h"

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

using Path = std::string;

std::runtime_error runtime_exception_of_win_error_code(const std::string sPrefix, DWORD api_error_code) {
	std::stringstream ssMessage;
	ssMessage << sPrefix << " Error ";
	ssMessage << api_error_code << " : \"";

	LPTSTR lpMsgBuf; // Asume 

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		api_error_code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	ssMessage << lpMsgBuf << "\"";
	return std::runtime_error(ssMessage.str());
}

template <typename H>
class Pipe : private std::pair<H, H> {
public:
	typedef std::shared_ptr<Pipe> shared_ptr;
	Pipe(std::string sName) : 
		 std::pair<H, H>(nullptr, nullptr)
		,m_sName(sName)
		,m_psaAttr(new SECURITY_ATTRIBUTES)
		,m_getRx(std::bind(&Pipe::initAndGetRx,this))
		,m_getTx(std::bind(&Pipe::initAndGetTx,this)) {
		m_psaAttr->nLength = sizeof(SECURITY_ATTRIBUTES);
		m_psaAttr->bInheritHandle = TRUE;
		m_psaAttr->lpSecurityDescriptor = NULL;
	};
	H& rx() { return this->m_getRx(); };
	H& tx() { return this->m_getTx(); };
private:
	std::string m_sName;
	std::shared_ptr<SECURITY_ATTRIBUTES> m_psaAttr;
	std::function<H&()> m_getRx;
	std::function<H&()> m_getTx;
	void init() {
		const int use_deafult_buffer_size = 0;
		if (CreatePipe(&this->first,&this->second,m_psaAttr.get(), use_deafult_buffer_size)) {
			// Getters don't need to do init on next call
			this->m_getRx = std::bind(&Pipe::getRx,this);
			this->m_getTx = std::bind(&Pipe::getTx,this);
		}
		else {
			throw runtime_exception_of_win_error_code(std::string("Creation of pipe ") + this->m_sName + " failed", GetLastError());
		}
	};
	H& initAndGetRx() {
		init();
		return getRx();
	};
	H& initAndGetTx() {
		init();
		return getTx();
	}
	H& getRx() {
		return this->first;
	}
	H& getTx() {
		return this->second;
	}
};

typedef Pipe<HANDLE> StdIOPipe;

class Process {
public:
	typedef std::shared_ptr<Process> shared_ptr;
	Process(Path executable) :
		 m_executable(executable)
		,m_pSTARTUPINFO(nullptr)
		,m_pPROCESS_INFORMATION(nullptr)
	{
	};

	~Process() {
		if (this->m_pPROCESS_INFORMATION) {
			CloseHandle(m_pPROCESS_INFORMATION->hProcess);
			CloseHandle(m_pPROCESS_INFORMATION->hThread);
		}
	}

	/**
	  * Dont allow copy construct not assignment to ensure pointer to structs bound to Process
	  * does not get screwed up.
	  */
	Process(Process const&) = delete; // Copy not allowed
	void operator=(Process const&) = delete; // Assignement not allowed

	void execute(
		 Parameters parameters
		,StdIOPipe::shared_ptr pToProcessStdIn
		,StdIOPipe::shared_ptr pFromProcessStdOut
		,StdIOPipe::shared_ptr pFromProcessStdErr) {
		this->create_process(parameters, pToProcessStdIn, pFromProcessStdOut, pFromProcessStdErr);
		this->waitTerminate();
	}

private:
	Path m_executable;
	std::unique_ptr<STARTUPINFO> m_pSTARTUPINFO; // shared in case support for copy (ensure STARTUPINFO address follows Process Handle)
	std::unique_ptr<PROCESS_INFORMATION> m_pPROCESS_INFORMATION; // shared in case support for copy (ensure STARTUPINFO address follows Process Handle)
	void create_process(
		  Parameters parameters
		, StdIOPipe::shared_ptr pToProcessStdIn
		, StdIOPipe::shared_ptr pFromProcessStdOut
		, StdIOPipe::shared_ptr pFromProcessStdErr) {
		// 
		//	m_pToProcessStdIn.tx					m_pFromProcessStdOut.rx		m_pFromProcessStdErr.rx
		//        |												^					  ^
		//        v												|					  |
		//  m_pToProcessStdIn.rx-stdin---->child---->stdout-m_pFromProcessStdOut	  |
		//										 |									  |
		//										 \-->stderr-m_pFromProcessStdErr.tx --/
		//

		// Init m_pSTARTUPINFO in a way to avoid typos
		{
			m_pSTARTUPINFO.reset(new STARTUPINFO);
			int size_of_STARTUPINFO = sizeof(*m_pSTARTUPINFO.get());
			ZeroMemory(m_pSTARTUPINFO.get(), size_of_STARTUPINFO);
			m_pSTARTUPINFO->cb = size_of_STARTUPINFO;
			//m_pSTARTUPINFO->hStdInput = pToProcessStdIn->rx();
			//m_pSTARTUPINFO->hStdOutput = pFromProcessStdOut->tx();
			//m_pSTARTUPINFO->hStdError = pFromProcessStdErr->tx();
			m_pSTARTUPINFO->hStdInput = GetStdHandle(STD_INPUT_HANDLE);
			m_pSTARTUPINFO->hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			m_pSTARTUPINFO->hStdError = GetStdHandle(STD_ERROR_HANDLE);
			m_pSTARTUPINFO->dwFlags |= STARTF_USESTDHANDLES;
		}
		// Init m_pPROCESS_INFORMATION in a way to avoid typos
		{
			m_pPROCESS_INFORMATION.reset(new PROCESS_INFORMATION);
			int size_of_PROCESS_INFORMATION = sizeof(*m_pPROCESS_INFORMATION.get());
			ZeroMemory(m_pPROCESS_INFORMATION.get(), size_of_PROCESS_INFORMATION);
		}

		std::stringstream ssCmdLine;
		ssCmdLine << '\"' << m_executable << '\"'; // Ensure path is within string delimiters to peserve any spaces
		std::for_each(std::begin(parameters), std::end(parameters), [&ssCmdLine](Parameter p) {ssCmdLine << " " << p; });
		std::string sCmdLine(ssCmdLine.str().c_str()); // copy to provide stack instance to API

		std::cout << "\n[[CLANG-BCC]]:CreateProcess=" << sCmdLine;
		std::cout << std::flush; // Flush our entries to stdout before letting child process do its stuff
		// Start the child process. 
		if (!CreateProcess(
			NULL,   // No module name (use command line)
			const_cast<LPSTR>(sCmdLine.c_str()),        // Command line
			// "notepad", // Test that a visible application really starts
			// "&%¤#", // sure to fail!
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			TRUE, // bInheritHandles 
			0,
			// CREATE_NEW_CONSOLE, // 
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			m_pSTARTUPINFO.get(),         // Pointer to STARTUPINFO structure
			m_pPROCESS_INFORMATION.get()) // Pointer to PROCESS_INFORMATION structure
			)
		{
			throw runtime_exception_of_win_error_code(std::string("CreateProcess ") + sCmdLine + " Failed", GetLastError());
		}
	}

	void waitTerminate() {
		if (m_pPROCESS_INFORMATION) {
			WaitForSingleObject(m_pPROCESS_INFORMATION->hProcess, INFINITE);
		}
	}

};

struct Compiler {
	void execute(Parameters parameters);
	Path m_path;
};

void Compiler::execute(Parameters parameters) {
	auto pPipeToCompiler = std::make_shared<StdIOPipe>("Pipe_To_Compiler");
	auto pPipeFromCompiler = std::make_shared<StdIOPipe>("Pipe_From_Compiler");
	auto pCompilerProcess = std::make_shared<Process>(m_path);

	{
		std::cout << "\n[[CLANG-BCC]]:Actual Compiler = " << this->m_path;
		std::cout << "\n\t<Parameter List (vaules between [...]>";
		std::for_each(std::begin(parameters), std::end(parameters), [](const Parameter& p) {std::cout << "\n\t[" << p << "]"; });
	}
	std::cout << "\n[[CLANG-BCC]]:START COMPILER";
	pCompilerProcess->execute(parameters, pPipeToCompiler, pPipeFromCompiler, pPipeFromCompiler);
	std::cout << "\n[[CLANG-BCC]]:COMPILER END";
}

enum e_BccCompiler {
	e_BccCompiler_Undefined
	, e_BccCompiler_bcc32
	, e_BccCompiler_bcc32c
	, e_BccCompiler_bcc64
	, e_BccCompiler_Unknown
};

Path pathToCompiler(e_BccCompiler compiler_id) {
	Path result("#unknown_compiler#");
	switch (compiler_id) {
	case e_BccCompiler_bcc32:
		result = R"(C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32.exe)"; // Hard code to use embarcadero compiler to see how cmake reacts?
		break;

	case e_BccCompiler_bcc32c:
		result = R"(C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc32c.exe)"; // Hard code to use embarcadero compiler to see how cmake reacts?
		break;
	case e_BccCompiler_bcc64:
		result = R"(C:\Program Files (x86)\Embarcadero\Studio\17.0\bin\bcc64.exe)"; // Hard code to use embarcadero compiler to see how cmake reacts?
		break;
	}

	return result;
}

 int _tmain(int argc, _TCHAR* argv[])
{
	try {
		std::cout << "\n[[CLANG-BCC]]:START";

		std::string sOurPath(argv[0]); // Path to us
		Parameters parameters(&argv[1], &argv[argc]); // skip argv[0] which is the path to "us" 
		//e_BccCompiler bcc_compiler = e_BccCompiler_bcc32;
		e_BccCompiler bcc_compiler = e_BccCompiler_bcc32c;
		//e_BccCompiler bcc_compiler = e_BccCompiler_bcc64;
		Path compiler_path(pathToCompiler(bcc_compiler)); // default

		// Process non-compiler parameters (set test purpose parameters)
		{
			if (parameters.size() >= 2) {
				if (parameters[0] == "---") {
					compiler_path = parameters[1]; // E.g., as in \n[[CLANG-BCC]] --- bcc32c
					parameters.erase(parameters.begin()); // strip-off non-compiler parameter
					parameters.erase(parameters.begin()); // strip-off non-compiler parameter
				}
			}

			if (parameters.size() == 1) {
				if (parameters[0] == "CMakeCXXCompilerId.cpp") {
					// Asume we are called by cmake to compile the compler identification source file (e.g., CMakeCXXCompilerId.cpp)
					compiler_path = "clang++.exe"; // Use clang to fool cmake "we" are a clang compiler
					std::cout << "\n[[CLANG-BCC]]:CMake compiler identification compilation detected";
					std::cout << "\n[[CLANG-BCC]]:Preparing to use actual compiler ==> " << compiler_path;
				}
			}
		}

		e_BccCompiler forced_compiler = e_BccCompiler_Undefined; // Do not force the compiler to use
		//e_BccCompiler forced_compiler = e_BccCompiler_bcc32c; // Development test

		if (forced_compiler > e_BccCompiler_Undefined && forced_compiler < e_BccCompiler_Unknown) {
			Path forced_compiler_path = pathToCompiler(forced_compiler);
			if (forced_compiler_path != compiler_path) {
				compiler_path = forced_compiler_path;
				std::cout << "\n[[CLANG-BCC]]:Forced Compiler Mode: Actual compiler forced to ==> "  << forced_compiler_path;
			}
		}

		Compiler actual_compiler{ compiler_path };
		actual_compiler.execute(toActualCompilerParameters(parameters));
	}
	catch (std::runtime_error& e) {
		std::cout << "\n[[CLANG-BCC]]: Failed - Exception = " << e.what();
	}
    
	std::cout << "\n[[CLANG-BCC]]:END" << std::endl; // Report end and flush
	return 0;
}
