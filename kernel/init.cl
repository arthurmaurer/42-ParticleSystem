
#define WIDTH	1.0
#define HEIGHT	1.0

void kernel initialize_rect(global Particle * particles, int particleCount)
{
	int				i = get_global_id(0);
	global float2 *	position = &(particles[i].position);
	global float2 *	velocity = &(particles[i].velocity);

	float	subCount = sqrt((float)particleCount);
	uint	x = fmod(i, subCount);
	uint	y = i / subCount;
	float2	subSize = (WIDTH / subCount, HEIGHT / subCount);
	float2	subSize2 = subSize / (float2)(2.0f);

	position->x = x * subSize.x - 0.5 + subSize2.x;
	position->y = y * subSize.y - 0.5 + subSize2.y;

	velocity->x = 0;
	velocity->y = 0;
}
