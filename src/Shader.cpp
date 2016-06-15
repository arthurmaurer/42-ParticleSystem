
#include "Shader.hpp"
#include "Utils.hpp"

Shader::Shader(GLenum type, const std::string & path)
{
	load(type, path);
}

Shader::Shader()
{}

Shader::~Shader()
{
	if (id != 0)
		glDeleteShader(id);
}

void	Shader::load(GLenum type, const std::string & path)
{
	const std::string	code = Utils::readFile(path);
	const char *		cCode = code.c_str();
	const GLint			size = static_cast<GLint>(code.size());

	if (id == 0)
		id = glCreateShader(type);

	if (id == 0)
		Utils::die("Could not create the shader.");

	glShaderSource(id, 1, &cCode, &size);

	_compile();
}

void	Shader::_compile() const
{
	GLint				success;
	GLint				logLength;
	GLchar *			log;

	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
		log = new char[logLength];
		glGetShaderInfoLog(id, logLength, NULL, log);
		Utils::die(log);
	}
}
