
#pragma once

#include <string>
#include <CL/cl.hpp>

class Utils
{
public:
	static std::string	readFile(const std::string & path);
	static void			die(const char * format, ...);
	static void			die(const char * message, const cl::Error & e);
};