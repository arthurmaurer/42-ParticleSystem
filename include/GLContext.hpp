
#pragma once

#include <ostream>
#include <functional>
#include <vector>
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

class GLContext
{
public:
	GLContext(unsigned width = 600, unsigned height = 480);
	~GLContext();

	GLFWwindow *				window = nullptr;
	std::function<void(void *)>	renderer = nullptr;
	std::vector<GLuint>			vbos;
	std::vector<GLuint>			vaos;

	void			render(void * ptr) const;

};

std::ostream &		operator<<(std::ostream & os, const GLContext & gl);
