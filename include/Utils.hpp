
#pragma once

#include <string>

class Utils
{
public:
	static void			die(const std::string & message);
	static std::string	readFile(const std::string & path);
	static std::string	formatString(const char * formatStr, ...);
};