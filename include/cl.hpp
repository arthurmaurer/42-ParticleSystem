
#ifndef __CL_ENABLE_EXCEPTIONS
	#define __CL_ENABLE_EXCEPTIONS
#endif


#ifndef GLEW_STATIC
	#define GLEW_STATIC
#endif

#include <GL/glew.h>

#ifdef __APPLE__
    #include "closx.hpp"
#else
    #include <CL/cl.hpp>
#endif
