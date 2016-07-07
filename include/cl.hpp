
#ifndef __CL_ENABLE_EXCEPTIONS
	#define __CL_ENABLE_EXCEPTIONS
#endif

#include <GL/glew.h>

#ifdef __APPLE__
    #include "closx.hpp"
#else
    #include <CL/cl.hpp>
#endif
