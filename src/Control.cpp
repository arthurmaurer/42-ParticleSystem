
#include <iostream>

#include "Control.hpp"
#include "ParticleSystem.hpp"
#include "GLContext.hpp"

bool		Control::isMouseDown = false;
cl_float2	Control::lastPosition = { 0, 0 };

void	Control::onMouseMove(GLFWwindow * window, double x, double y)
{
	if (isMouseDown)
	{
		ParticleSystem &	ps = ParticleSystem::instance();
		GravityPoint &		gp = ps.gravityPoints[0];

		gp.position = {
			(cl_float)x / (ps.gl.width / 2) - 1.f,
			-1 * (cl_float)y / (ps.gl.height / 2) + 1.f
		};

		gp.enabled = 1;
	}

	Control::lastPosition = { (cl_float)x, (cl_float)y };
}

void	Control::onMouseClick(GLFWwindow * window, int button, int action, int _)
{
	if (button != 0)
		return;

	isMouseDown = (action == 1);


	ParticleSystem &	ps = ParticleSystem::instance();
	GravityPoint &		gp = ps.gravityPoints[0];

	if (isMouseDown)
	{
		gp.position = {
			lastPosition.x / (ps.gl.width / 2) - 1.f,
			-1 * lastPosition.y / (ps.gl.height / 2) + 1.f
		};
		gp.enabled = 1;
	}
	else
	{
		gp.enabled = 0;
	}
}

void	Control::onKeyDown(GLFWwindow * window, int key, int scancode, int action, int mods)
{

	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, true);
		break;
	case GLFW_KEY_R:
		ParticleSystem::instance().init();
	}
}
