
#pragma once

class ParticleSystem;

class Renderer
{
public:
	static void		render(const ParticleSystem & ps);

protected:
	static void		_renderParticles(const ParticleSystem & ps);
	static void		_renderGPs(const ParticleSystem & ps);
	static void		_updateWindowTitle(const ParticleSystem & ps);
};

