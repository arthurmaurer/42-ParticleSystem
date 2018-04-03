
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>

#include "ParticleSystem.hpp"
#include "CLContext.hpp"
#include "GLContext.hpp"
#include "Utils.hpp"
#include "Config.hpp"
#include "FPSCounter.hpp"
#include "DeviceSelector.hpp"
#include "ConfigParser.hpp"

static void	initConfig(Config & config)
{
	config["platform"].s = nullptr;
	config["device"].s = nullptr;
	config["nparticles"].u = 0;
}

static CLSupportInfo	getSupportInfo(Config & config)
{
	std::string		platformName;
	std::string		deviceName;
	CLSupportInfo	clInfos;

	if (config["platform"].s != nullptr)
		platformName = config["platform"].s;

	if (config["device"].s != nullptr)
		deviceName = config["device"].s;

	clInfos = DeviceSelector::selectDevice(platformName, deviceName);

	return clInfos;
}

static void printUsageAndExit(char * programName)
{
	std::cout << 
		"\nusage: " << programName << " -nparticles x [-platform platform_name] [-device device_name]\n"
		"  -nparticles x   Number (x) of particles to instanciate\n"
		"  -platform       The name of the platform to use\n"
		"  -device         The name of the device to use\n\n"

		"other options:\n"
		"  -h              Print usage\n\n"

		"controls:\n"
		"  left click      Draggable gravity point\n"
		"  right click     Static gravity point\n"
		"  shift           Stack gravity points (3 max)\n"
		"  W A S D         Camera position\n"		
		"  Arrows          Camera angle\n"
		"  R               Reset camera\n"
		"  1               Rectangle initialization\n"
		"  2               Sphere initialization\n"
		"  space           Pause\n"
		"  escape          Quit\n"
	<< std::endl;

	exit(0);
}

int		main(int ac, char ** av)
{
	Config &	config = Config::instance();
	initConfig(config);
	ConfigParser::parseConfig(config, ac, av);

	if (config.has("h"))
		printUsageAndExit(av[0]);

	if (config["nparticles"].u == 0)
		Utils::die("Error: You must precise the number of particles with -nparticles.\nUse -h option for help.\n");

	GLContext		gl(1000, 1000);
	CLSupportInfo	clInfos = getSupportInfo(config);
	CLContext		cl(clInfos.platform, clInfos.device);

	ParticleSystem &	ps = ParticleSystem::instance(&gl, &cl, config["nparticles"].u);

	std::cout << ps << std::endl;

	ps.init("initialize_cube");

	gl.render(&ps);

	return EXIT_SUCCESS;
}
