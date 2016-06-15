
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "Utils.hpp"
#include "ShaderProgram.hpp"
#include "Shader.hpp"

GLFWwindow *	init()
{
	if (!glfwInit())
		Utils::die("Count not init glfw.");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *	window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		Utils::die("Could not create a window.");
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
		Utils::die("Count not init glew.");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, 1.f);

	return window;
}

int		main_()
{
	GLFWwindow *	window = init();

	ShaderProgram program({
		&Shader(GL_VERTEX_SHADER, "shader/particle_vertex.glsl"),
		&Shader(GL_FRAGMENT_SHADER, "shader/particle_fragment.glsl")
	});

	GLuint	vao;
	GLuint	vbo;

	GLfloat		buffer[] = {
		0.5, 0.5, 0, 1,
		1, 1, 1, 1,
		-0.5, 0.5, 0, 1,
		1, 1, 1, 1,
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);

	GLint	posAttrib = glGetAttribLocation(program.id, "inPosition");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);

	GLint	colorAttrib = glGetAttribLocation(program.id, "inColor");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 4));

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glBindVertexArray(vao);
		program.enable();
		glDrawArrays(GL_POINTS, 0, 2);
		program.disable();
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return (0);
}
