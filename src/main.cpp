
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

int		main(int ac, char ** av)
{
	Config &	config = Config::instance();
	initConfig(config);
	ConfigParser::parseConfig(config, ac, av);

	if (config["nparticles"].u == 0)
		Utils::die("Error: You must precise the number of particles with -nparticles.\n");

	GLContext		gl(1000, 1000);
	CLSupportInfo	clInfos = getSupportInfo(config);
	CLContext		cl(clInfos.platform, clInfos.device);

	ParticleSystem &	ps = ParticleSystem::instance(&gl, &cl, config["nparticles"].u);

	std::cout << ps << std::endl;

	ps.init("initialize_cube");

	FPSCounter::start();

	gl.render(&ps);

	return EXIT_SUCCESS;
}
