
static void		__render(void * ptr)
{
	ParticleSystem *	ps = static_cast<ParticleSystem *>(ptr);
	CLContext *			cl = ps->cl;
	GLContext *			gl = ps->gl;
	cl::CommandQueue &	queue = cl->queue;

	glFinish();

	queue.enqueueAcquireGLObjects(&ps->cl->vbos);

	cl::Kernel	kernel(cl->program, "test_kernel");
	kernel.setArg(0, cl->vbos[0]);
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(9), cl::NullRange);

	queue.enqueueReleaseGLObjects(&cl->vbos);

	queue.finish();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, gl->vbos[0]);
	glBindVertexArray(gl->vaos[0]);
	ps->program->enable();

	glDrawArrays(GL_POINTS, 0, 3);

	ps->program->disable();
}
