//
// Created by kjell-olovhogdahl on 7/26/2016.
//
#ifdef __CODEGEARC__
#pragma hdrstop
#pragma argsused
#endif

#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
using API_RESULT_CODE = DWORD;
#else
typedef char _TCHAR;
#endif

// Suppress Visual Studio warnings about call to standard library with unchecked iterators (e.g., call to std::missmatch using boost path iterators)
#ifndef _SCL_SECURE_NO_WARNINGS
// Not defined by build environment (e.g. cmake) su define it here
#define _SCL_SECURE_NO_WARNINGS
#endif

#include "Helpers.h"
#include "parameters.h"
#include "Process.h"
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <future>

namespace app {
	namespace process {

		namespace win32 {
			class Process {
			public:
				Process(const Process&) = delete; // No copy
				Process& operator=(const Process&) = delete; // No assign

				Process(const Path& cmd, const Parameters& parameters) {
					// Init m_STARTUPINFO
					{
						m_STARTUPINFO.cb = sizeof(&m_STARTUPINFO);
						m_STARTUPINFO.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
						m_STARTUPINFO.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
						m_STARTUPINFO.hStdError = GetStdHandle(STD_ERROR_HANDLE);
						m_STARTUPINFO.dwFlags |= STARTF_USESTDHANDLES; // Execute in parent IO environment (stdin, stdout, stderr)
					}
					// Init m_PROCESS_INFORMATION
					{
						// Already C++11 zero-initialised in definition
					}

					std::stringstream ssCmdLine;
					ssCmdLine << R"(")" << cmd << R"(")"; // Ensure path is within string delimiters to preserve any spaces for Linux shells (MSYS2, MINGW, CywWin)
					std::for_each(std::begin(parameters), std::end(parameters), [&ssCmdLine](Parameter p) {ssCmdLine << " " << p; });
					std::string sCmdLine(ssCmdLine.str().c_str()); // copy to provide stack instance to API

					std::cout << "\n[[CLANG-BCC]]:CreateProcess=" << sCmdLine;
					std::cout << "\n" << std::flush; // Flush our entries to stdout before letting child process do its stuff
					// Start the child process.
					if (!CreateProcess(
						NULL,   // No module name (use command line)
						const_cast<LPSTR>(sCmdLine.c_str()),        // Command line
						NULL,           // Process handle not inheritable
						NULL,           // Thread handle not inheritable
						TRUE, // bInheritHandles
						0,
						NULL,           // Use parent's environment block
						NULL,           // Use parent's starting directory
						&m_STARTUPINFO,         // Pointer to STARTUPINFO structure
						&m_PROCESS_INFORMATION) // Pointer to PROCESS_INFORMATION structure
						)
					{
						throw app::win32::runtime_exception_of_win_error_code(std::string("CreateProcess ") + sCmdLine + " Failed", GetLastError());
					}
				}

				API_RESULT_CODE waitTerminate() {
					API_RESULT_CODE result = 0;
					WaitForSingleObject(m_PROCESS_INFORMATION.hProcess, INFINITE);
					if (!GetExitCodeProcess(m_PROCESS_INFORMATION.hProcess, &result)) {
					}
					return result;
				}

			private:
				STARTUPINFO m_STARTUPINFO{}; // C++11 zero initialized
				PROCESS_INFORMATION m_PROCESS_INFORMATION{}; // C++11 zero initialized
			};


		}// namespace win32

		std::future<int> execute(const Path& cmd, const Parameters& parameters) {
			// Launch deferred i.e., synchronosuly on client access to returned future.
			// NOTE: Lmda captures by value to have a copy available on actual call (after return from this call)
			// This ensures the std::cout made by Process class is not mixed up by concurrent execution with clinet std::cout calls
			// TODO: Ensure Process execution is "thread safe" before chaning launch policy to async?
			return std::async(std::launch::deferred, [cmd,parameters]()->int {
				win32::Process process(cmd, parameters);
				return process.waitTerminate();
			});
		}

	} // namespace process
} // namespace app


