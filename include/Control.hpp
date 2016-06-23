
#pragma once

#include <CL/cl.hpp>
#include <GravityPoint.hpp>

#define TRANSLATION_SPEED	0.04f
#define MOUSE_SPEED_FACTOR	0.003f
#define ROTATION_SPEED		0.05f

struct GLFWwindow;
class ParticleSystem;
class Vec3;

class Control
{
public:
	static bool				isMouseDown;
	static int				mouseButton;
	static cl_float2		lastPosition;
	static bool				stackMode;
	static GravityPoint *	currentGP;

	static void		onMouseMove(GLFWwindow * window, double x, double y);
	static void		onMouseClick(GLFWwindow * window, int button, int action, int x);
	static void		onKeyboard(GLFWwindow * window, int key, int scancode, int action, int mods);
};
