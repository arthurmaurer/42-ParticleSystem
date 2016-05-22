
#pragma once

#include <CL/cl.hpp>

class CLContext;
class GLContext;
class ShaderProgram;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	CLContext *		cl;
	GLContext *		gl;
	ShaderProgram *	program;
};
