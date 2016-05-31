
static void		__render(void * ptr)
{
	ParticleSystem *	ps = static_cast<ParticleSystem *>(ptr);
	CLContext &			cl = ps->cl;
	GLContext &			gl = ps->gl;
	cl::CommandQueue &	queue = cl.queue;

	try
	{
		glFinish();

		queue.enqueueAcquireGLObjects(&cl.vbos);
		cl::Kernel	kernel(cl.program, "test_kernel");
		kernel.setArg(0, cl.vbos[0]);
		queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(3), cl::NullRange);
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
	ps->program->enable();

	glDrawArrays(GL_POINTS, 0, 3);

	ps->program->disable();
}
