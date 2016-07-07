
#include <iostream>

#include "Utils.hpp"
#include "DeviceSelector.hpp"

static bool		isAnswerCorrect(const std::vector<std::string> & choices, const std::string & answer)
{
	unsigned	n = atoi(answer.c_str());
	return (n > 0 && n <= choices.size());
}

static int		promptChoice(
	const std::string & questionText,
	const std::string & answerText,
	const std::vector<std::string> & choices
)
{
	unsigned	i = 1;
	std::string	answer;

	std::cout << questionText << std::endl;

	for (const auto choice : choices)
	{
		std::cout
			<< "  " << i << ". "
			<< choice
			<< std::endl;
		++i;
	}

	std::cout << std::endl;

	do
	{
		std::cout << answerText;
	} while (std::getline(std::cin, answer) && !isAnswerCorrect(choices, answer));

	return atoi(answer.c_str()) - 1;
}

CLSupportInfo	DeviceSelector::selectDevice(
					const std::string & defaultPlatformName,
					const std::string & defaultDeviceName
				)
{
	CLSupportInfo	info;

	info.platform = getPlatform(defaultPlatformName);
	info.device = getDevice(info.platform, defaultDeviceName);

	return info;
}

cl::Platform	DeviceSelector::getPlatform(const std::string & defaultName)
{
	std::vector<cl::Platform>	platforms;
	std::vector<std::string>	choices;
	size_t						platformID;

	cl::Platform::get(&platforms);

	choices.resize(platforms.size());

	std::transform(
		platforms.cbegin(), platforms.cend(),
		choices.begin(),
		getPlatformName
	);

	if (defaultName.empty())
	{
		platformID = promptChoice(
			"Available OpenCL platforms on this computer:",
			"Which platform do you want to use ? ",
			choices
		);
	}
	else
	{
		const auto occ = std::find(choices.cbegin(), choices.cend(), defaultName);

		if (occ == choices.cend())
			Utils::die("The platform \"%s\" does not exist.\n", defaultName.c_str());

		platformID = occ - choices.cbegin();
	}

	return platforms[platformID];
}

cl::Device		DeviceSelector::getDevice(const cl::Platform & platform, const std::string & defaultName)
{
	std::vector<cl::Device>		devices;
	std::vector<std::string>	choices;
	size_t						deviceID;

	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

	choices.resize(devices.size());

	std::transform(
		devices.cbegin(), devices.cend(),
		choices.begin(),
		getDeviceName
	);

	if (defaultName.empty())
	{
		deviceID = promptChoice(
			"Available OpenCL platforms on this computer:",
			"Which platform do you want to use ? ",
			choices
		);
	}
	else
	{
		const auto occ = std::find(choices.cbegin(), choices.cend(), defaultName);

		if (occ == choices.cend())
			Utils::die("The device \"%s\" does not exist.\n", defaultName.c_str());

		deviceID = occ - choices.cbegin();
	}

	return devices[deviceID];
}

std::string		DeviceSelector::getPlatformName(const cl::Platform & platform)
{
	return platform.getInfo<CL_PLATFORM_NAME>();
}

std::string		DeviceSelector::getDeviceName(const cl::Device & device)
{
	return device.getInfo<CL_DEVICE_NAME>();
}
