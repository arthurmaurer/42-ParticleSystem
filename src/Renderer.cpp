
#include <iostream>
#include <GL/glew.h>

#include "Renderer.hpp"
#include "ParticleSystem.hpp"
#include "CLContext.hpp"
#include "GLContext.hpp"
#include "Utils.hpp"
#include "FPSCounter.hpp"
#include "ShaderProgram.hpp"

void		Renderer::render(const ParticleSystem & ps)
{
	CLContext &			cl = ps.cl;
	GLContext &			gl = ps.gl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Renderer::_renderParticles(ps);
	Renderer::_renderGPs(ps);
	Renderer::_updateWindowTitle(ps);

	FPSCounter::update();
}

void		Renderer::_renderParticles(const ParticleSystem & ps)
{
	GLContext &		gl = ps.gl;
	ShaderProgram *	program = gl.programs["particle"];

	glBindVertexArray(gl.vaos["particle"]);
	program->enable();
	glDrawArrays(GL_POINTS, 0, ps.particleCount);
	program->disable();
	glBindVertexArray(0);
}

void		Renderer::_renderGPs(const ParticleSystem & ps)
{
	GLContext &		gl = ps.gl;
	ShaderProgram *	program = gl.programs["gp"];

	glBindVertexArray(gl.vaos["gp"]);
	program->enable();
	glDrawArrays(GL_POINTS, 0, ps.gpManager.gpCount);
	program->disable();
	glBindVertexArray(0);
}

void		Renderer::_updateWindowTitle(const ParticleSystem & ps)
{
	char	title[50];
	float	fps = FPSCounter::fps;

	if (fps < 0)
		return;

	sprintf(title, "%i fps", static_cast<int>(fps));
	glfwSetWindowTitle(ps.gl.window, title);
}