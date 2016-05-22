
#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include "Utils.hpp"

ShaderProgram::ShaderProgram()
{}

ShaderProgram::ShaderProgram(const std::string & vertexPath, const std::string & fragmentPath)
{
	load(vertexPath, fragmentPath);
}

ShaderProgram::~ShaderProgram()
{
	disable();

	if (id != 0)
		glDeleteProgram(id);
}

void	ShaderProgram::load(const std::string & vertexPath, const std::string & fragmentPath)
{
	Shader		vertexShader(vertexPath, GL_VERTEX_SHADER);
	Shader		fragmentShader(fragmentPath, GL_FRAGMENT_SHADER);
	GLint		success;
	GLint		logLength;
	GLchar *	log = NULL;

	if (id == 0)
		id = glCreateProgram();

	if (id == 0)
		Utils::die("Could not create the program.");

	glAttachShader(id, vertexShader.id);
	glAttachShader(id, fragmentShader.id);
	glBindFragDataLocation(id, 0, "outColor");
	glLinkProgram(id);
	glValidateProgram(id);
	glDetachShader(id, vertexShader.id);
	glDetachShader(id, fragmentShader.id);
	glDeleteShader(vertexShader.id);
	glDeleteShader(fragmentShader.id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (success == GL_FALSE)
	{
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 1)
		{
			glGetProgramInfoLog(id, logLength, NULL, log);
			Utils::die(log);
		}
		else
			Utils::die("Unknown shader error.");
	}
}

void	ShaderProgram::enable() const
{
	glUseProgram(id);
}

void	ShaderProgram::disable() const
{
	glUseProgram(0);
}
