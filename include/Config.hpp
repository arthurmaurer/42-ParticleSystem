
#pragma once

#include <map>
#include <string>

class Config
{
public:
	union Value
	{
		cl_int		i;
		cl_uint		u;
		char *		s;
	};

	~Config() = delete;

	Value &			operator[](const std::string & key);

	static Config &	instance();

	Value &			get(const std::string & key);
	bool			has(const std::string & key) const;

protected:
	std::map<std::string, Value>	_values;

private:
	Config() = default;
};

#include "../src/Config.inl"
