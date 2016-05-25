
#pragma once

#include <CL/cl.hpp>

class CLContext;
class GLContext;
class ShaderProgram;

class ParticleSystem
{
public:
	ParticleSystem(GLContext & gl, CLContext & cl);
	~ParticleSystem();

	CLContext &		cl;
	GLContext &		gl;
	ShaderProgram *	program;
};
