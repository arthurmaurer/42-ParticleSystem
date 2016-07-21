
#define GRAVITY_POINTS_MAX		3
#define GRAVITY_POINTS_FORCE	3
#define GRAVITY_MAX				2.5f
#define MINIMUM_VELOCITY		0.2f
#define PARTICLES_PER_WORK_ITEM	2
#define PARTICLE_DECELERATION	0.9f

float4			get_gp_effect(Particle * particle, GravityPoint * gp)
{
	float4	particleToGP = *gp - particle->position;
	float	distance = fast_length(particleToGP);
	float4	direction = particleToGP / distance;
	float4	velocity = direction * (0.333333333f / distance) * GRAVITY_POINTS_FORCE;

	float	scalar_velocity = fast_length(velocity);

	if (scalar_velocity > GRAVITY_MAX)
		velocity = fast_normalize(velocity) * GRAVITY_MAX;

	return velocity;
}

float4			get_gravitational_velocity(Particle * particle, GravityPoint * gps)
{
	GravityPoint *	gp;
	float4			velocity = (float4)(0);

	for (uint i = 0; i < GRAVITY_POINTS_MAX; ++i)
	{
		gp = gps + i;

		if (gp->w != 0)
			velocity += get_gp_effect(particle, gp);
	}

	return velocity;
}

void			cache_gps(GravityPoint * cached_gps, global GravityPoint * gps, uint length)
{
	for (uint i = 0; i < length; ++i)
		cached_gps[i] = gps[i];
}

void			cache_particles(Particle * cached_particles, global Particle * particles, uint offset, uint length)
{
	for (uint i = 0; i < length; ++i)
		cached_particles[i] = particles[offset + i];
}

void			push_cached_particles(global Particle * particles, Particle * cached_particles, uint offset, uint length)
{
	for (uint i = 0; i < length; ++i)
		particles[offset + i] = cached_particles[i];
}

void			update_particle(Particle * particle, GravityPoint * gps, float delta_time)
{
	float v = fast_length(particle->velocity);

	if (v != 0 && v > MINIMUM_VELOCITY)
		particle->velocity *= PARTICLE_DECELERATION;

	particle->velocity += get_gravitational_velocity(particle, gps);
	particle->position += particle->velocity * delta_time;
}

void kernel		update_particles(global Particle * particles, global GravityPoint * gps, float delta_time)
{
	int					id = get_global_id(0) * PARTICLES_PER_WORK_ITEM;
	Particle			cached_particles[PARTICLES_PER_WORK_ITEM];
	GravityPoint		cached_gps[GRAVITY_POINTS_MAX];

	cache_gps(cached_gps, gps, GRAVITY_POINTS_MAX);
	cache_particles(cached_particles, particles, id, PARTICLES_PER_WORK_ITEM);

	for (uint i = 0; i < PARTICLES_PER_WORK_ITEM; ++i)
		update_particle(cached_particles + i, cached_gps, delta_time);

	push_cached_particles(particles, cached_particles, id, PARTICLES_PER_WORK_ITEM);
}
