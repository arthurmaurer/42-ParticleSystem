
#include <cstdio>

#include "FPSCounter.hpp"

static void		__updateWindowTitle(ParticleSystem & ps)
{
	char	title[50];
	float	fps = FPSCounter::fps;

	if (fps < 0)
		return;

	sprintf(title, "%i fps", static_cast<int>(fps));
	glfwSetWindowTitle(ps.gl.window, title);
}

static void		__render(void * ptr)
{
	ParticleSystem &	ps = *(static_cast<ParticleSystem *>(ptr));
	CLContext &			cl = ps.cl;
	GLContext &			gl = ps.gl;
	cl::CommandQueue &	queue = cl.queue;

	try
	{
		cl::Kernel	kernel(cl.program, "update_particles");
		kernel.setArg(0, cl.vbos[0]);
		glFinish();
		queue.enqueueAcquireGLObjects(&cl.vbos);
		queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(ps.particleCount), cl::NullRange);
		queue.finish();
		queue.enqueueReleaseGLObjects(&cl.vbos);
	}
	catch (const cl::Error & e)
	{
		Utils::die(
			"An error occured while rendering: %s returned %i\n",
			e.what(),
			e.err()
		);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, gl.vbos[0]);
	glBindVertexArray(gl.vaos[0]);
	ps.program->enable();

	glDrawArrays(GL_POINTS, 0, ps.particleCount);

	ps.program->disable();

	FPSCounter::update();

	__updateWindowTitle(ps);
}
