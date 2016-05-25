
#include <GL/glew.h>

#include "ParticleSystem.hpp"
#include "ShaderProgram.hpp"
#include "GLContext.hpp"
#include "CLContext.hpp"
#include "Utils.hpp"

#include "ParticleSystem.inl"

ParticleSystem::ParticleSystem(GLContext & glContext, CLContext & clContext) :
	gl(glContext),
	cl(clContext)
{
	GLuint	vbo;
	GLuint	size = 9 * sizeof(GLfloat);

	float points[] = {
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_DYNAMIC_DRAW);
	gl.vbos.push_back(vbo);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
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

	cl.addSource(Utils::readFile("kernel/default.cl"));
	cl.buildProgram();

	program = new ShaderProgram("shader/vertex.glsl", "shader/fragment.glsl");

	gl.renderer = __render;
}

ParticleSystem::~ParticleSystem()
{
	delete program;
}
