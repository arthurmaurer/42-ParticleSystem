
#pragma once

#include <CL/cl.hpp>

#define CONTROL_NULL_POSITION	-9999999

struct GLFWwindow;

class Control
{
public:
	static bool			isMouseDown;
	static cl_float2	lastPosition;

	static void		onMouseMove(GLFWwindow * window, double x, double y);
	static void		onMouseClick(GLFWwindow * window, int button, int action, int x);
	static void		onKeyDown(GLFWwindow * window, int key, int scancode, int action, int mods);
};

