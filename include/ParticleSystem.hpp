
#pragma once

#include <iostream>

#include "cl.hpp"
#include "GravityPointManager.hpp"
#include "Camera.hpp"
#include "Matrix4.hpp"
#include "Vec3.hpp"

#define PARTICLES_PER_KERNEL 2

class CLContext;
class GLContext;
class Renderer;

class ParticleSystem
{
public:
	static ParticleSystem &	instance(GLContext * gl = nullptr, CLContext * cl = nullptr, cl_uint particleCount = 0);

	void			init(const std::string & initFunction);
	void			initCamera();
	void			update();
	void			updateGPBuffer() const;
	void			updateParticles() const;
	void			updateUniforms() const;
	void			togglePause();
	Vec3			screenToWorldCoord(const Vec3 & screenPosition) const;

	CLContext &			cl;
	GLContext &			gl;
	Camera				camera;
	GravityPointManager	gpManager;
	cl_uint				particleCount;
	cl_uint				localSize;
	cl_uint				globalSize;

protected:
	void			_createBuffers();
	void			_configureParticleBuffer();
	void			_configureGPBuffer();
	void			_createShaderPrograms();
	void			_updateLocalAndGlobalSizes();

	bool			_paused = false;

private:
	ParticleSystem(GLContext & gl, CLContext & cl, cl_uint particleCount);
	~ParticleSystem();
};

std::ostream &	operator<<(std::ostream & os, const ParticleSystem & ps);
