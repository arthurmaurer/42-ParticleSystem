
#pragma once

#include <CL/cl.hpp>

class CLContext;
class GLContext;
class ShaderProgram;

class ParticleSystem
{
public:
	ParticleSystem(GLContext & gl, CLContext & cl, cl_uint particleCount);
	~ParticleSystem();

	void			init();

	CLContext &		cl;
	GLContext &		gl;
	ShaderProgram *	program;
	cl_uint			particleCount;
};
