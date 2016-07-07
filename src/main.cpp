
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

int		main()
{
	Config &	config = Config::instance();

	config["platform"].s = strdup("NVIDIA CUDA");
	config["device"].s = strdup("GeForce GTX 720M");
	config["particleCount"].u = 3000000;

	GLContext		gl(1000, 1000);
	CLSupportInfo	clInfos = DeviceSelector::selectDevice("Apple", "GeForce GTX 660M");
	CLContext		cl(clInfos.platform, clInfos.device);

	std::cout << gl << std::endl;
	std::cout << cl << std::endl;

	ParticleSystem &	ps = ParticleSystem::instance(&gl, &cl, config["particleCount"].u);
	ps.init("initialize_cube");

	FPSCounter::start();

	gl.render(&ps);

	return EXIT_SUCCESS;
}
