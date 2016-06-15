
#include <GL/glew.h>
#include <cstdio>
#include <ctime>

#include "FPSCounter.hpp"
#include "ParticleSystem.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "GLContext.hpp"
#include "CLContext.hpp"
#include "Utils.hpp"
#include "Particle.hpp"
#include "GravityPoint.hpp"
#include "Renderer.hpp"
#include "Control.hpp"

#include "ParticleSystem.inl"

ParticleSystem &	ParticleSystem::instance(GLContext * glContext, CLContext * clContext, cl_uint particleCount)
{
	static ParticleSystem *	ps;

	if (ps == nullptr)
	{
		if (glContext != nullptr && clContext != nullptr)
			ps = new ParticleSystem(*glContext, *clContext, particleCount);
		else
			Utils::die("The first call to ParticleSystem::instance must have a GL context and a CL context.");
	}

	return *ps;
}

ParticleSystem::ParticleSystem(GLContext & glContext, CLContext & clContext, cl_uint particleCount) :
	gl(glContext),
	cl(clContext),
	particleCount(particleCount)
{
	gravityPoints.resize(GRAVITY_POINTS_MAX);
	memset(gravityPoints.data(), 0, sizeof(GravityPoint) * GRAVITY_POINTS_MAX);

	_createShaderPrograms();

	_createBuffers();

	cl.addSource(Utils::readFile("kernel/header.cl"));
	cl.addSource(Utils::readFile("kernel/init.cl"));
	cl.addSource(Utils::readFile("kernel/update.cl"));
	cl.buildProgram();

	gl.renderer = __update;

	glfwSetKeyCallback(gl.window, Control::onKeyDown);
	glfwSetMouseButtonCallback(gl.window, Control::onMouseClick);
	glfwSetCursorPosCallback(gl.window, Control::onMouseMove);
	glfwSetWindowSizeCallback(gl.window, GLContext::resizeWindow);
}

ParticleSystem::~ParticleSystem()
{
	delete gl.programs["particle"];
	delete gl.programs["gp"];
}

void		ParticleSystem::init()
{
	try
	{
		cl::CommandQueue &	queue = cl.queue;
		cl::Kernel			kernel(cl.program, "initialize_rect");

		kernel.setArg(0, cl.vbos[0]);
		kernel.setArg(1, sizeof(cl_uint), &particleCount);

		queue.enqueueAcquireGLObjects(&cl.vbos);
		queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(particleCount), cl::NullRange);
		queue.finish();
		queue.enqueueReleaseGLObjects(&cl.vbos);
	}
	catch (const cl::Error & e)
	{
		Utils::die(
			"Error while initializing particles: %s returned %s (%i).\n",
			e.what(),
			CLContext::getErrorString(e.err()).c_str(),
			e.err()
		);
	}
}

void		ParticleSystem::updateGPBuffer() const
{
	glBindBuffer(GL_ARRAY_BUFFER, gl.vbos["gp"]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GravityPoint) * GRAVITY_POINTS_MAX, gravityPoints.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void		ParticleSystem::updateParticles() const
{
	static std::clock_t	lastTime = std::clock();
	std::clock_t		newTime;
	cl_float			deltaTime;

	try
	{
		cl::CommandQueue &	queue = cl.queue;

		updateGPBuffer();

		newTime = std::clock();
		deltaTime = 1000.f * (newTime - lastTime) / CLOCKS_PER_SEC;
		lastTime = newTime;

		cl::Kernel	kernel(cl.program, "update_particles");
		kernel.setArg(0, cl.vbos[0]);
		kernel.setArg(1, cl.vbos[1]);
		kernel.setArg(2, sizeof(cl_float), &deltaTime);

		glFinish();

		queue.enqueueAcquireGLObjects(&cl.vbos);
		queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(particleCount), cl::NullRange);
		queue.finish();
		queue.enqueueReleaseGLObjects(&cl.vbos);
	}
	catch (const cl::Error & e)
	{
		Utils::die("An error occured while particles updating", e);
	}
}

void		ParticleSystem::_createBuffers()
{
	GLuint	vbos[2];
	GLuint	vaos[2];

	glGenBuffers(2, vbos);
	gl.vbos["particle"] = vbos[0];
	gl.vbos["gp"] = vbos[1];

	glGenVertexArrays(2, vaos);
	gl.vaos["particle"] = vaos[0];
	gl.vaos["gp"] = vaos[1];

	_configureParticleBuffer();
	_configureGPBuffer();

	try
	{
		cl::BufferGL	clBuffer;

		cl.vbos.push_back(cl::BufferGL(cl.context, CL_MEM_READ_WRITE, gl.vbos["particle"], nullptr));
		cl.vbos.push_back(cl::BufferGL(cl.context, CL_MEM_READ_ONLY, gl.vbos["gp"], nullptr));
	}
	catch (const cl::Error & e)
	{
		Utils::die("Error while creating the particle CL buffer", e);
	}
}

void		ParticleSystem::_configureParticleBuffer()
{
	GLuint	size = sizeof(Particle) * static_cast<GLuint>(particleCount);
	GLuint	vbo = gl.vbos["particle"];
	GLuint	vao = gl.vaos["particle"];
	GLuint	programID = gl.programs["particle"]->id;
	GLuint	attribID;

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STREAM_DRAW);

	attribID = glGetAttribLocation(programID, "inPosition");
	glEnableVertexAttribArray(attribID);
	glVertexAttribPointer(attribID, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), nullptr);

	attribID = glGetAttribLocation(programID, "inVelocity");
	glEnableVertexAttribArray(attribID);
	glVertexAttribPointer(attribID, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *)(sizeof(cl_float2)));

	glBindVertexArray(0);
}

void		ParticleSystem::_configureGPBuffer()
{
	GLuint	size = sizeof(GravityPoint) * GRAVITY_POINTS_MAX;
	GLuint	vbo = gl.vbos["gp"];
	GLuint	vao = gl.vaos["gp"];

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, gravityPoints.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GravityPoint), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(GravityPoint), (void *)2);

	glBindVertexArray(0);
}

void		ParticleSystem::_createShaderPrograms()
{
	gl.programs["particle"] = new ShaderProgram({
		&Shader(GL_VERTEX_SHADER, "shader/particle_vertex.glsl"),
		&Shader(GL_FRAGMENT_SHADER, "shader/particle_fragment.glsl")
	});

	gl.programs["gp"] = new ShaderProgram({
		&Shader(GL_VERTEX_SHADER, "shader/gp_vertex.glsl"),
		&Shader(GL_GEOMETRY_SHADER, "shader/gp_geometry.glsl"),
		&Shader(GL_FRAGMENT_SHADER, "shader/gp_fragment.glsl")
	});
}
