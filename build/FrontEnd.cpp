//
// Created by kjell-olovhogdahl on 7/27/2016.
//

/**
 * This is the FrontEnd in the Frontend-Core-Backend source code architecture idiom.
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

#include "FrontEnd.h"
#include "Core.h"
#include "BackEnd.h"

namespace frontend {

}
