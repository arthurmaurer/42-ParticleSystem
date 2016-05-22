
#pragma once

#include <GL/glew.h>
#include <string>

class ShaderProgram
{
public:
	GLuint							id = 0;

	ShaderProgram();
	ShaderProgram(const std::string & vertexPath, const std::string & fragmentPath);
	~ShaderProgram();

	void			load(const std::string & vertexPath, const std::string & fragmentPath);

	void			enable() const;
	void			disable() const;
};
