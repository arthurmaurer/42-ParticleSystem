
#pragma once

#include <GL/glew.h>
#include <string>

class Shader
{
public:
	GLuint			id = 0;

	Shader();
	Shader(const std::string & path, GLenum type);
	~Shader();

	void	load(const std::string & path, GLenum type);

protected:
	void	_compile() const;
};