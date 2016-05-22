
#include <CL/cl.hpp>
#include <vector>

#if _WIN32
	#include <windows.h>
#endif

#include "CLContext.hpp"
#include "GLContext.hpp"
#include "Utils.hpp"

#include "CLContext.inl"

CLContext::CLContext() :
	platform(__getDefaultPlatform()),
	device(__getDefaultDevice(platform))
{
	cl_context_properties	properties[] = {
		CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
		CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
		CL_CONTEXT_PLATFORM, (cl_context_properties)platform(),
		0
	};

	context = cl::Context(device, properties);

	queue = cl::CommandQueue(context, device);

	if (context() == nullptr)
		Utils::die("Could not create the OpenCL context.");
}

CLContext::~CLContext()
{
}

void			CLContext::addSource(const std::string & code)
{
	sources.push_back({ _strdup(code.c_str()), code.size() });
}

void			CLContext::buildProgram()
{
	program = cl::Program(context, sources);

	if (program.build({ device }) != CL_SUCCESS)
		Utils::die(program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device));
}

std::ostream &	operator<<(std::ostream & os, const CLContext & cl)
{
	os
		<< "Using platform "
		<< cl.platform.getInfo<CL_PLATFORM_NAME>()
		<< std::endl
		<< "Using device "
		<< cl.device.getInfo<CL_DEVICE_NAME>()
		<< std::endl;

	return os;
}
