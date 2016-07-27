//
// Created by kjell-olovhogdahl on 7/27/2016.
//

#ifndef CLANG_BCC_CORE_H
#define CLANG_BCC_CORE_H

/**
 *  This is the Core header in the FrontEnd-Core-BackEnd source code architecture idiom

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

namespace core {
    
}

#endif //CLANG_BCC_CORE_H
