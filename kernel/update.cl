
#define GRAVITY_POINTS_MAX		3
#define GRAVITY_POINTS_FORCE	3
#define GRAVITY_MAX				50.0f
#define MINIMUM_VELOCITY		0.2f

float4			get_gp_effect(Particle * particle, GravityPoint * gp)
{
	float4	direction = *gp - particle->position;
	float	distance = fast_length(direction);
	float4	velocity = fast_normalize(direction) * (1.f / (distance * 3)) * GRAVITY_POINTS_FORCE;
	float	scalarVelocity = fast_length(velocity);

	if (scalarVelocity > GRAVITY_MAX)
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

void kernel		update_particles(global Particle * particles, global const GravityPoint * gps, float deltaTime)
{
	int					i = get_global_id(0);
	Particle			cacheParticle = particles[i];
	GravityPoint		cachedGps[GRAVITY_POINTS_MAX];

	for (int i = 0; i < GRAVITY_POINTS_MAX; ++i)
		cachedGps[i] = gps[i];

	float v = fast_length(cacheParticle.velocity);

	if (v > MINIMUM_VELOCITY && v != 0)
		cacheParticle.velocity /= 1.04f;

	cacheParticle.velocity += get_gravitational_velocity(&cacheParticle, cachedGps);
	cacheParticle.position += cacheParticle.velocity * 0.001f;

	particles[i] = cacheParticle;
}
