
#define GRAVITY_POINTS_MAX		1.f
#define GRAVITY_MAX				2.0f
#define MINIMUM_VELOCITY		0.02f

float2			get_gp_effect(global Particle * particle, global GravityPoint * gp)
{
	float2	direction = gp->position - particle->position;
	float	distance = length(direction);

	float2	velocity = normalize(direction) * (1.f / (distance * 3));

	float scalarVelocity = length(velocity);

	if (scalarVelocity > GRAVITY_MAX)
		velocity = normalize(velocity) * GRAVITY_MAX;

	return velocity;
}

float2			get_gravitational_velocity(global Particle * particle, global GravityPoint * gps)
{
	global GravityPoint *	gp;
	float2					velocity = (float2)(0);

	for (uint i = 0; i < GRAVITY_POINTS_MAX; ++i)
	{
		gp = gps + i;

		if (gp->enabled != 0)
			velocity += get_gp_effect(particle, gp);
	}

	return velocity;
}

void kernel		update_particles(global Particle * particles, global GravityPoint * gps, float deltaTime)
{
	int					i = get_global_id(0);
	global Particle *	particle = particles + i;

	if (length(particle->velocity) > MINIMUM_VELOCITY)
		particle->velocity /= 1.04f;

	particle->velocity += get_gravitational_velocity(particle, gps);

	particle->position += particle->velocity / 3000.f * deltaTime;
}
