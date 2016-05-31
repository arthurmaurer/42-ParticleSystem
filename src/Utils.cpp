
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdarg>
#include <cstdio>

#include "Utils.hpp"

#include "Utils.inl"

std::string	Utils::readFile(const std::string & path)
{
	std::ifstream	file(path.c_str(), std::ios::in);
	std::stringstream	ss;

	if (!file.good())
		Utils::die("The script file \"%s\" cannot be opened.\n", path.c_str());

	ss << file.rdbuf();

	return ss.str();
}

void		Utils::die(const char * format, ...)
{
	va_list	args;

	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	system("pause");
	exit(EXIT_FAILURE);
}
