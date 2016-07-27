//
// Created by kjell-olovhogdahl on 7/27/2016.
//

#ifndef CLANG_BCC_BACKEND_H
#define CLANG_BCC_BACKEND_H

/**
 * This is the BackEnd.h header in the FrontEnd-Core-BackEnd source code architecture idiom
 *
	FrontEnd.cpp	<—	FronEnd.h	—>	FrontEndImpl.h	->	FrontEndImpl.cpp
	    ^					            ^
	    |----------------------			    |
			  	  |			    |
	Core.cpp	<—	Core.h		->	CoreImpl.h	->	CoreImpl.cpp
	    ^						    ^
	    |----------------------			    |
			  	  |			    |

	BackEnd.cpp	<—	BackEnd.h	->	BackendImpl.h	->	BackendImpl.cpp
	    ^			\___________________________________/		      ^
	    |					 |				      |
	    |				     Isolated				      |
	    |									      |
	    ---------------------------------------------------------------------------
						 |
					Build Environment
					    Platform

 */

// NO API AND BUILD AGNOSTIC INCLUDES (FrontEnd-Core-BackEnd idiom)
//-----------------------------------------------------------------------------
#include <string>
#include <vector>
#include <memory>
#include <future>
//-----------------------------------------------------------------------------

// Root BackEnd types (Hides actual API types)
using API_ERROR_CODE = unsigned long;
using API_RESULT_CODE = unsigned long;
using API_STRING = std::string; // TODO: Decide when and how to use UNICODE (without including API, e.g., windows.h, headers)

namespace BackEnd {

	std::runtime_error runtime_exception_of_api_error_code(const std::string sPrefix, API_ERROR_CODE api_error_code);

	namespace process {
		using Path = std::string;
		using Parameter = std::string;
		using Parameters = std::vector<Parameter>;

		std::future<int> execute(const Path& cmd, const Parameters& parameters);
	}
}


#endif //CLANG_BCC_BACKEND_H
