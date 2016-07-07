
#pragma once

#include <ostream>
#include <functional>
#include <vector>
#include <map>

#include "gl.hpp"
#include "Matrix4.hpp"
#include "Vec2.hpp"

class ShaderProgram;

class GLContext
{
public:
	GLContext(unsigned width, unsigned height);
	~GLContext();

	void			render(void * ptr) const;

	static void		resizeWindow(GLFWwindow * window, int width, int height);

	Vec2									windowSize;
	GLFWwindow *							window = nullptr;
	std::function<void(void *)>				renderer = nullptr;
	std::map<std::string, ShaderProgram *>	programs;
	std::vector<GLuint>						ubos;
	std::map<std::string, GLuint>			vbos;
	std::map<std::string, GLuint>			vaos;
};

std::ostream &		operator<<(std::ostream & os, const GLContext & gl);
