
#include <GL/glew.h>

#include "ParticleSystem.hpp"
#include "ShaderProgram.hpp"
#include "GLContext.hpp"
#include "CLContext.hpp"
#include "Utils.hpp"

#include "ParticleSystem.inl"

ParticleSystem::ParticleSystem()
{
	GLuint	vbo;
	GLuint	size = 9 * sizeof(GLfloat);

	float points[] = {
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};

	gl = new GLContext();
	cl = new CLContext();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_DYNAMIC_DRAW);
	gl->vbos.push_back(vbo);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	gl->vaos.push_back(vao);

	cl->vbos.push_back(cl::BufferGL(cl->context, CL_MEM_READ_WRITE, vbo, nullptr));

	cl->addSource(Utils::readFile("kernel/default.cl"));
	cl->buildProgram();

	program = new ShaderProgram("shader/vertex.glsl", "shader/fragment.glsl");

	gl->renderer = __render;
}

ParticleSystem::~ParticleSystem()
{
	delete program;
	delete cl;
	delete gl;
}
