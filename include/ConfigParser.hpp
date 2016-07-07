
#pragma once

#include <vector>
#include <string>

class Config;

class ConfigParser
{
public:
	enum	OptionType
	{
		String,
		Integer
	};

	struct	Option
	{
		std::string	name;
		OptionType	type;
	};

	static void		parseConfig(Config & config, int ac, char ** av);

protected:
	static bool		_findOption(const std::vector<ConfigParser::Option> & options, const std::string str, ConfigParser::Option & outOption);
	static void		_writeValue(Config & config, const Option & option, const std::string & value);
};
