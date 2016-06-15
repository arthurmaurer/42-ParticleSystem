
static void		__update(void * ptr)
{
	const ParticleSystem *	ps = static_cast<ParticleSystem *>(ptr);
	const GravityPoint &	gp = ps->gravityPoints[0];
	const ShaderProgram *	program = ps->gl.programs["particle"];

	ps->updateParticles();

	program->enable();
	GLint uniID = glGetUniformLocation(program->id, "gp");
	
	glUniform4f(
		uniID,
		gp.position.x,
		gp.position.y,
		0.f,
		gp.enabled
	);
	program->disable();

	Renderer::render(*ps);
}
