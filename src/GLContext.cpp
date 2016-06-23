
#include <GL/glew.h>

#include "GLContext.hpp"
#include "ParticleSystem.hpp"
#include "Utils.hpp"

GLContext::GLContext(unsigned width, unsigned height) :
	width(width),
	height(height)
{
	if (!glfwInit())
		Utils::die("Count not init glfw.");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		Utils::die("Could not create a window.");
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
		Utils::die("Count not init glew.");

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, 1.f);
	//glfwSwapInterval(0);
}

GLContext::~GLContext()
{
	glfwTerminate();
}

void				GLContext::render(void * ptr) const
{
	while (!glfwWindowShouldClose(window))
	{
		if (renderer != nullptr)
			renderer(ptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void				GLContext::resizeWindow(GLFWwindow * window, int width, int height)
{
	GLContext &			gl = ParticleSystem::instance().gl;

	gl.width = width;
	gl.height = height;

	glViewport(0, 0, width, height);
}

std::ostream &		operator<<(std::ostream & os, const GLContext & gl)
{
	os << glGetString(GL_VERSION);

	return os;
}
