
#pragma once

#include <iostream>
#include <map>

#include "cl.hpp"

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
	cl::Program				program;

	void			addSource(const std::string & code);
	void			buildProgram();

	static std::string	getErrorString(cl_int error);
};

std::ostream &	operator<<(std::ostream & os, const CLContext & cl);
