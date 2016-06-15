
#pragma once

#include <ostream>
#include <functional>
#include <vector>
#include <map>
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

class ShaderProgram;

class GLContext
{
public:
	GLContext(unsigned width, unsigned height);
	~GLContext();

	unsigned								width;
	unsigned								height;
	GLFWwindow *							window = nullptr;
	std::function<void(void *)>				renderer = nullptr;
	std::map<std::string, ShaderProgram *>	programs;
	std::vector<GLuint>						ubos;
	std::map<std::string, GLuint>			vbos;
	std::map<std::string, GLuint>			vaos;

	void			render(void * ptr) const;

	static void		resizeWindow(GLFWwindow * window, int width, int height);
};

std::ostream &		operator<<(std::ostream & os, const GLContext & gl);
