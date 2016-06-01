
#include <GL/glew.h>

#include "ParticleSystem.hpp"
#include "ShaderProgram.hpp"
#include "GLContext.hpp"
#include "CLContext.hpp"
#include "Utils.hpp"
#include "Particle.hpp"

#include "ParticleSystem.inl"


ParticleSystem::ParticleSystem(GLContext & glContext, CLContext & clContext, cl_uint particleCount) :
	gl(glContext),
	cl(clContext),
	particleCount(particleCount)
{
	GLuint	vbo;
	GLuint	size = sizeof(Particle) * static_cast<GLuint>(particleCount);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	gl.vbos.push_back(vbo);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), nullptr);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)4);
	
	gl.vaos.push_back(vao);

	try
	{
		cl.vbos.push_back(cl::BufferGL(cl.context, CL_MEM_READ_WRITE, vbo, nullptr));
	}
	catch (const cl::Error & e)
	{
		Utils::die(
			"Error while creating the CL buffer: %s returned %i.\n",
			e.what(),
			e.err()
		);
	}

	cl.addSource(Utils::readFile("kernel/header.cl"));
	cl.addSource(Utils::readFile("kernel/init.cl"));
	cl.addSource(Utils::readFile("kernel/update.cl"));
	cl.buildProgram();

	program = new ShaderProgram("shader/vertex.glsl", "shader/fragment.glsl");

	gl.renderer = __render;
}

ParticleSystem::~ParticleSystem()
{
	delete program;
}

void		ParticleSystem::init()
{
	try
	{
		cl::CommandQueue &	queue = cl.queue;
		cl::Kernel	kernel(cl.program, "initialize_rect");

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
