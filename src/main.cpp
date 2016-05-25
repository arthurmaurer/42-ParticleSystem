
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>

#include "ParticleSystem.hpp"
#include "CLContext.hpp"
#include "GLContext.hpp"
#include "Utils.hpp"

static bool		isAnswerCorrect(const std::vector<std::string> & choices, const std::string & answer)
{
	int		n = atoi(answer.c_str());
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

static std::string	getPlatformName(const cl::Platform & platform)
{
	return platform.getInfo<CL_PLATFORM_NAME>();
}

static std::string	getDeviceName(const cl::Device & device)
{
	return device.getInfo<CL_DEVICE_NAME>();
}

static std::pair<cl::Platform, cl::Device>	selectDevice()
{
	std::vector<cl::Platform>	platforms;
	std::vector<cl::Device>		devices;
	std::vector<std::string>	choices;
	int							platformID;
	int							deviceID;

	cl::Platform::get(&platforms);
	choices.resize(platforms.size());

	std::transform(
		platforms.cbegin(), platforms.cend(),
		choices.begin(),
		getPlatformName
	);

	platformID = promptChoice(
		"Available OpenCL platforms on this computer:",
		"Which platform do you want to use ? ",
		choices
	);

	platforms[platformID].getDevices(CL_DEVICE_TYPE_ALL, &devices);
	choices.resize(devices.size());

	std::transform(
		devices.cbegin(), devices.cend(),
		choices.begin(),
		getDeviceName
	);

	std::cout << std::endl;

	deviceID = promptChoice(
		"Available OpenCL devices for this platform:",
		"Which device do you want to use ? ",
		choices
	);

	return { platforms[platformID], devices[deviceID] };
}

int		main()
{
	GLContext		gl;
	std::pair<cl::Platform, cl::Device>		clInfos = selectDevice();
	CLContext		cl(clInfos.first, clInfos.second);

	std::cout << gl << std::endl;
	std::cout << cl << std::endl;

	ParticleSystem	ps(gl, cl);

	gl.render(&ps);

	return EXIT_SUCCESS;
}
