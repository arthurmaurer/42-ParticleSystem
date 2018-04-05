
#include <iostream>

#include "ConfigParser.hpp"
#include "Config.hpp"
#include "Utils.hpp"

#ifdef _WIN32
	#define strdup _strdup
#endif

void	ConfigParser::parseConfig(Config & config, int ac, char ** av)
{
	ConfigParser::Option				option;
	std::vector<ConfigParser::Option>	options = {
		{ "h", None },
		{ "platform", String },
		{ "device", String },
		{ "nparticles", UInteger }
	};

	#ifdef __APPLE__
		#pragma clang diagnostic push
		#pragma clang diagnostic ignored "-Wfor-loop-analysis"
	#endif

	for (int keyIndex = 1; keyIndex < ac; ++keyIndex)
	{
		std::string	optionName = std::string(av[keyIndex]).substr(1);

		if (!_findOption(options, optionName, option))
			Utils::die("Option %s doesn't exist\n", optionName.c_str());

		if (option.type != None)
		{
			int	valueIndex = keyIndex + 1;

			if (valueIndex >= ac)
				Utils::die("No value for option %s\n", optionName.c_str());

			_writeValue(config, option, av[valueIndex]);
		}
		else
			_writeValue(config, option, "");

		++keyIndex;
	}

	#ifdef __APPLE__
		#pragma clang diagnostic pop
	#endif
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
	Config::Value &	entry = config[option.name];

	switch (option.type)
	{
		case String:
			entry.s = strdup(value.c_str());
			break;
		case Integer:
			entry.i = atoi(value.c_str());
			break;
		case UInteger:
			entry.u = static_cast<unsigned>(atoi(value.c_str()));
			break;
	}
}
