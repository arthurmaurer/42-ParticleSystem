
#include <iostream>

#include "Control.hpp"
#include "ParticleSystem.hpp"
#include "GLContext.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Utils.hpp"

bool			Control::isMouseDown = false;
int				Control::mouseButton = 0;
Vec2			Control::lastPosition = { 0, 0 };
bool			Control::stackMode = false;
GravityPoint *	Control::currentGP = nullptr;

void	Control::onMouseMove(GLFWwindow * window, double x, double y)
{
	Vec2	screenPosition((float)x, (float)y);

	if (isMouseDown)
	{
		ParticleSystem & ps = ParticleSystem::instance();

		if ((mouseButton == GLFW_MOUSE_BUTTON_LEFT ||
			(mouseButton == GLFW_MOUSE_BUTTON_RIGHT && ps.gpManager.getFreeGP() != nullptr)) && currentGP != nullptr)
		{
			Vec3 position = _getMouseOnControlPlane(screenPosition);
			_setCurrentGPPosition(position);
		}
	}

	Control::lastPosition = screenPosition;
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
			Vec3 position = _getMouseOnControlPlane(lastPosition);
			currentGP = gp;
			_setCurrentGPPosition(position);
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

Vec3	Control::_getMouseOnControlPlane(const Vec2 & screenPosition)
{
	Camera &	camera = ParticleSystem::instance().camera;
	Ray			ray = camera.screenPointToRay(screenPosition);
	Vec3		hitPoint = Utils::getRayPlaneIntersection(ray, Vec3::zero, camera.rotation * Vec3::back);

	return hitPoint;
}

void	Control::_setCurrentGPPosition(const Vec3 & position)
{
	*currentGP = { position.x, position.y, position.z, 1.f };
}
