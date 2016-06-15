
#pragma once

#include <GL/glew.h>
#include <string>

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