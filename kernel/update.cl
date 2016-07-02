
#define GRAVITY_POINTS_MAX		3
#define GRAVITY_MAX				2.0f
#define MINIMUM_VELOCITY		0.05f

float3			get_gp_effect(global Particle * particle, global GravityPoint * gp)
{
	float3	direction = gp->xyz - particle->position.xyz;
	float	distance = length(direction);
	float3	velocity = normalize(direction) * (1.f / (distance * 3));

	float scalarVelocity = length(velocity);

	if (scalarVelocity > GRAVITY_MAX)
		velocity = normalize(velocity) * GRAVITY_MAX;

	return velocity;
}

float3			get_gravitational_velocity(global Particle * particle, global GravityPoint * gps)
{
	global GravityPoint *	gp;
	float3					velocity = (float3)(0);

	for (uint i = 0; i < GRAVITY_POINTS_MAX; ++i)
	{
		gp = gps + i;

		if (gp->w != 0)
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

	particle->velocity += (float4)(get_gravitational_velocity(particle, gps), 0) * (deltaTime / 16);

	particle->position += particle->velocity / 3000.f * deltaTime;
}
