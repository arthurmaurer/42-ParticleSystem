
#include "gl.hpp"
#include "GLContext.hpp"
#include "ParticleSystem.hpp"
#include "Utils.hpp"

GLContext::GLContext(unsigned width, unsigned height) :
	windowSize((float)width, (float)height)
{
	if (!glfwInit())
		Utils::die("Count not init glfw.");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "Hello World", nullptr, nullptr);

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
	// glfwSwapInterval(0);
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
	ParticleSystem &	ps = ParticleSystem::instance();
	Camera &			camera = ps.camera;
	GLContext &			gl = ps.gl;
	Vec2				resolution((float)width, (float)height);

	glViewport(0, 0, width, height);

	gl.windowSize = resolution;
	camera.resolution = resolution;
	camera.updateProjectionMatrix();

	(void)window;
}

std::ostream &		operator<<(std::ostream & os, const GLContext & gl)
{
	os << glGetString(GL_VERSION);

	return os;

	(void)gl;
}
