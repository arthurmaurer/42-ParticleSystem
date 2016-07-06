
#pragma once

#include <GL/glew.h>
#include <string>
#include <map>
#include <vector>

#include "cl.hpp"

class Shader;

class ShaderProgram
{
public:
	GLuint							id = 0;
	std::map<std::string, GLint>	uniforms;

	ShaderProgram();
	ShaderProgram(const std::vector<Shader *> & shaders);
	~ShaderProgram();

	void			load(const std::vector<Shader *> & shaders);

	GLint			getUniformLocation(const std::string & name);
	void			loadUniform(const std::string & name, GLfloat value) const;
	void			loadUniform(const std::string & name, GLfloat * buffer, GLsizei length) const;
	void			loadUniform(const std::string & name, GLint value) const;
	void			loadUniform(const std::string & name, bool value) const;
	void			loadUniform(const std::string & name, const cl_float2 & vec) const;
	void			loadUniform(const std::string & name, const cl_float4 & vec) const;

	void			enable() const;
	void			disable() const;
};
