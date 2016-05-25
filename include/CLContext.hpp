
#pragma once

#include <CL/cl.hpp>
#include <iostream>
#include <map>

class CLContext
{
public:
	typedef std::map<std::string, cl::Kernel>	KernelMap;

	CLContext(cl::Platform & platform, cl::Device & device);
	~CLContext();

	cl::Platform			platform;
	cl::Device				device;
	cl::Context				context;
	cl::Program::Sources	sources;
	cl::CommandQueue		queue;
	std::vector<cl::Memory>	vbos;
	KernelMap				kernels;
	cl::Program				program;

	void			addSource(const std::string & code);
	void			buildProgram();
};

std::ostream &	operator<<(std::ostream & os, const CLContext & cl);
