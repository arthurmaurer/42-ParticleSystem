
#pragma once

#include <CL/cl.hpp>

#include "GravityPointManager.hpp"
#include "Camera.hpp"
#include "Matrix4.hpp"
#include "Vec3.hpp"

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

	CLContext &			cl;
	GLContext &			gl;
	cl_uint				particleCount;
	Matrix4				projectionMatrix;
	Camera				camera;
	GravityPointManager	gpManager;

protected:
	void			_createBuffers();
	void			_configureParticleBuffer();
	void			_configureGPBuffer();
	void			_createShaderPrograms();

	bool			_paused = false;

private:
	ParticleSystem(GLContext & gl, CLContext & cl, cl_uint particleCount);
	~ParticleSystem();
};
