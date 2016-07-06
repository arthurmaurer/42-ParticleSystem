
#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include "Utils.hpp"

ShaderProgram::ShaderProgram()
{}

ShaderProgram::ShaderProgram(const std::vector<Shader *> & shaders)
{
	load(shaders);
}

ShaderProgram::~ShaderProgram()
{
	disable();

	if (id != 0)
		glDeleteProgram(id);
}

void	ShaderProgram::load(const std::vector<Shader *> & shaders)
{
	GLint		success;

	if (id == 0)
		id = glCreateProgram();

	if (id == 0)
		Utils::die("Could not create the program.");

	for (const Shader * shader : shaders)
		glAttachShader(id, shader->id);

	glLinkProgram(id);
	glValidateProgram(id);

	for (const Shader * shader : shaders)
		glDetachShader(id, shader->id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint		logLength;
		GLchar *	log = nullptr;

		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 1)
		{
			glGetProgramInfoLog(id, logLength, nullptr, log);
			Utils::die(log);
		}
		else
			Utils::die("Unknown shader error.\n");
	}
}

GLint	ShaderProgram::getUniformLocation(const std::string & name)
{
	uniforms[name] = glGetUniformLocation(id, name.c_str());

	return uniforms[name];
}

void	ShaderProgram::loadUniform(const std::string & name, GLfloat value) const
{
	glUniform1f(uniforms.at(name), value);
}

void	ShaderProgram::loadUniform(const std::string & name, GLfloat * buffer, GLsizei length) const
{
	glUniform1fv(uniforms.at(name), length, buffer);
}

void	ShaderProgram::loadUniform(const std::string & name, GLint value) const
{
	glUniform1i(uniforms.at(name), value);
}

void	ShaderProgram::loadUniform(const std::string & name, bool value) const
{
	GLint	v = (value) ? 1 : 0;

	glUniform1i(uniforms.at(name), v);
}

void	ShaderProgram::loadUniform(const std::string & name, const cl_float2 & vec) const
{
	glUniform2f(uniforms.at(name), vec.s[0], vec.s[1]);
}

void	ShaderProgram::loadUniform(const std::string & name, const cl_float4 & vec) const
{
	glUniform4f(uniforms.at(name), vec.s[3], vec.s[0], vec.s[1], vec.s[2]);
}

void	ShaderProgram::enable() const
{
	glUseProgram(id);
}

void	ShaderProgram::disable() const
{
	glUseProgram(0);
}
