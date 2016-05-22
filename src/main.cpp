
#include <string>
#include <iostream>

#include "ParticleSystem.hpp"
#include "CLContext.hpp"
#include "GLContext.hpp"
#include "Utils.hpp"

int		main()
{
	ParticleSystem	ps;
	CLContext &		cl = *ps.cl;
	GLContext &		gl = *ps.gl;

	std::cout << gl << std::endl;
	std::cout << cl << std::endl;

	gl.render(&ps);

	return EXIT_SUCCESS;
}
