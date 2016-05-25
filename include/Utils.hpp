
#pragma once

#include <string>

class Utils
{
public:
	static std::string	readFile(const std::string & path);
	static void			die(const char * format, ...);
};