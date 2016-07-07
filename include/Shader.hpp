
#pragma once

#include <string>

#include "gl.hpp"

class Shader
{
public:
	GLuint			id = 0;

	Shader();
	Shader(GLenum type, const std::string & path);
	~Shader();

	void	load(GLenum type, const std::string & path);

protected:
	void	_compile() const;
};