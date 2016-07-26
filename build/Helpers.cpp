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
#else
typedef char _TCHAR;
#endif

#include "Helpers.h"
#include <sstream>

namespace app {
    namespace win32 {
        std::runtime_error runtime_exception_of_win_error_code(const std::string sPrefix, API_ERROR_CODE api_error_code) {
            std::stringstream ssMessage;
            ssMessage << sPrefix << " Error ";
            ssMessage << api_error_code << " : \"";

            LPTSTR lpMsgBuf = nullptr; // Asume not UNICODE

			if (FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				api_error_code,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&lpMsgBuf,
				0, NULL) == 0) {
				ssMessage << "#??#";
			}
			else {
				ssMessage << lpMsgBuf << "\"";
			}

            return std::runtime_error(ssMessage.str());
        }
    }
}
