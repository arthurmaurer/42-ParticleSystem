
#include <iostream>

#include "ConfigParser.hpp"
#include "Config.hpp"
#include "Utils.hpp"

void	ConfigParser::parseConfig(Config & config, int ac, char ** av)
{
	ConfigParser::Option				option;
	std::vector<ConfigParser::Option>	options = {
		{ "platform", String },
		{ "device", String },
		{ "particles", Integer }
	};

	for (int i = 1; i < ac; ++i)
	{
		std::string	optionName = std::string(av[i]).substr(1);

		if (!_findOption(options, optionName, option))
			Utils::die("Option %s doesn't exist\n", optionName.c_str());

		if (i + 1 >= ac)
			Utils::die("No value for option %s\n", optionName.c_str());

		_writeValue(config, option, av[i + i]);

		++i;
	}
}

bool	ConfigParser::_findOption(
	const std::vector<ConfigParser::Option> & options,
	const std::string str,
	ConfigParser::Option & outOption
)
{
	for (const ConfigParser::Option & option : options)
	{
		if (option.name == str)
		{
			outOption = option;
			return true;
		}
	}

	return false;
}

void	ConfigParser::_writeValue(Config & config, const Option & option, const std::string & value)
{
	switch (option.type)
	{
		case String:
			break;
		case Integer:
			break;
	}

	(void)config;
	(void)value;
}
