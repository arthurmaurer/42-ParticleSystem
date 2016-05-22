
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdarg.h>

#include "Utils.hpp"

#include "Utils.inl"

void		Utils::die(const std::string & message)
{
	std::cout << message << std::endl;
	system("pause");
	exit(EXIT_FAILURE);
}

std::string	Utils::readFile(const std::string & path)
{
	std::ifstream	file(path.c_str(), std::ios::in);
	std::stringstream	ss;

	if (!file.good())
	{
		Utils::die(Utils::formatString(
			"The script file \"$\" can not be opened.",
			path.c_str()
		));
	}

	ss << file.rdbuf();

	return ss.str();
}

std::string		Utils::formatString(const char * formatStr, ...)
{
	std::string		out;
	va_list			args;

	va_start(args, formatStr);
	out = __formatString(formatStr, args);
	va_end(args);

	return out;
}
