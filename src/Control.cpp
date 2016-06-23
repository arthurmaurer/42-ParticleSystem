
#include <iostream>

#include "Control.hpp"
#include "ParticleSystem.hpp"
#include "GLContext.hpp"
#include "Vec3.hpp"

bool			Control::isMouseDown = false;
int				Control::mouseButton = 0;
cl_float2		Control::lastPosition = { 0, 0 };
bool			Control::stackMode = false;
GravityPoint *	Control::currentGP = nullptr;

void	Control::onMouseMove(GLFWwindow * window, double x, double y)
{
	if (isMouseDown)
	{
		ParticleSystem &	ps = ParticleSystem::instance();

		if ((mouseButton == GLFW_MOUSE_BUTTON_LEFT || mouseButton == GLFW_MOUSE_BUTTON_RIGHT) && currentGP != nullptr)
		{
			*currentGP = {
				(cl_float)x / (ps.gl.width / 2) - 1.f,
				-1 * (cl_float)y / (ps.gl.height / 2) + 1.f,
				0,
				1
			};
		}
	}

	Control::lastPosition = { (cl_float)x, (cl_float)y };
}

void	Control::onMouseClick(GLFWwindow * window, int button, int action, int _)
{
	isMouseDown = (action == 1);
	mouseButton = button;

	if (isMouseDown)
	{
		ParticleSystem &	ps = ParticleSystem::instance();

		if (mouseButton == GLFW_MOUSE_BUTTON_LEFT || (mouseButton == GLFW_MOUSE_BUTTON_RIGHT && !stackMode))
			ps.gpManager.freeAllGPs();

		GravityPoint *	gp = ps.gpManager.getFreeGP();

		if (gp != nullptr)
		{
			currentGP = gp;

			*currentGP = {
				lastPosition.x / (ps.gl.width / 2) - 1.f,
				-1 * lastPosition.y / (ps.gl.height / 2) + 1.f,
				0,
				1
			};
		}
	}
	else
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && currentGP != nullptr)
			currentGP->w = 0;
	}
}

void	Control::onKeyboard(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	ParticleSystem &	ps = ParticleSystem::instance();
	Vec3 &				linearVelocity = ps.camera.linearVelocity;
	Vec3 &				angularVelocity = ps.camera.angularVelocity;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;
		case GLFW_KEY_A:
			linearVelocity.x = -TRANSLATION_SPEED;
			break;
		case GLFW_KEY_D:
			linearVelocity.x = TRANSLATION_SPEED;
			break;
		case GLFW_KEY_W:
			linearVelocity.z = -TRANSLATION_SPEED;
			break;
		case GLFW_KEY_S:
			linearVelocity.z = TRANSLATION_SPEED;
			break;
		case GLFW_KEY_LEFT:
			angularVelocity.y = ROTATION_SPEED;
			break;
		case GLFW_KEY_RIGHT:
			angularVelocity.y = -ROTATION_SPEED;
			break;
		case GLFW_KEY_1:
			ps.init("initialize_cube");
			break;
		case GLFW_KEY_2:
			ps.init("initialize_sphere");
			break;
		case GLFW_KEY_R:
			ps.initCamera();
			break;
		case GLFW_KEY_LEFT_SHIFT:
			stackMode = true;
			break;
		case GLFW_KEY_SPACE:
			ps.togglePause();
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_A:
		case GLFW_KEY_D:
			linearVelocity.x = 0;
			break;
		case GLFW_KEY_W:
		case GLFW_KEY_S:
			linearVelocity.z = 0;
			break;
		case GLFW_KEY_LEFT:
		case GLFW_KEY_RIGHT:
			angularVelocity.y = 0;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			stackMode = false;
			break;
		}
	}
}
