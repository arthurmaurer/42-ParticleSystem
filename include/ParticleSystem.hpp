
#pragma once

#include <CL/cl.hpp>

#include "GravityPoint.hpp"

#define GRAVITY_POINTS_MAX	1

class CLContext;
class GLContext;
class Renderer;

class ParticleSystem
{
public:
	static ParticleSystem &	instance(GLContext * gl = nullptr, CLContext * cl = nullptr, cl_uint particleCount = 0);

	void			init();
	void			updateGPBuffer() const;
	void			updateParticles() const;

	CLContext &		cl;
	GLContext &		gl;
	cl_uint			particleCount;

	std::vector<GravityPoint>	gravityPoints;

protected:
	void			_createBuffers();
	void			_configureParticleBuffer();
	void			_configureGPBuffer();

	void			_createShaderPrograms();

private:
	ParticleSystem(GLContext & gl, CLContext & cl, cl_uint particleCount);
	~ParticleSystem();
};
