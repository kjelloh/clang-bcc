//
// Created by kjell-olovhogdahl on 7/26/2016.
//

#ifndef app_HELPERS_H
#define app_HELPERS_H

#ifdef _WIN32
#include <windows.h>
using API_ERROR_CODE = DWORD;
#else
using API_ERROR_CODE = unsigned int;
#endif

#include <stdexcept>

namespace app {
    namespace win32 {
        std::runtime_error runtime_exception_of_win_error_code(const std::string sPrefix, API_ERROR_CODE api_error_code);
}}
#endif //app_HELPERS_H
