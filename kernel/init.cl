
#define SQUARE_SIZE		1.0f
#define SPHERE_RADIUS	0.5f

void kernel initialize_sphere(global Particle * particles, int particleCount)
{
	int				i = get_global_id(0);
	global float4 *	position = &(particles[i].position);

	uint	subDivCount = cbrt((float)particleCount);
	float2	delta = (float2)(M_PI * 2 / subDivCount, M_PI / subDivCount);
	float	radiusDelta = SPHERE_RADIUS / subDivCount;

	uint	x = fmod(i, (float)subDivCount);
	uint	y = fmod((float)i / subDivCount, (float)subDivCount);
	uint	r = i / (subDivCount * subDivCount);

	float radius = radiusDelta * r;

	float2	offset = (r % 2 == 0)
		? delta / 2
		: (float2)(0);

	position->x = radius * sin(delta.x * y + offset.x) * sin(delta.y * x + offset.y);
	position->y = radius * cos(delta.x * y + offset.x);
	position->z = radius * sin(delta.x * y + offset.x) * cos(delta.y * x + offset.y);

	particles[i].velocity = (float4)(0);
}

void kernel initialize_cube(global Particle * particles, int particleCount)
{
	int				i = get_global_id(0);
	global float4 *	position = &(particles[i].position);

	uint	subDivCount = cbrt((float)particleCount);

	uint	x = fmod((float)i, (float)subDivCount);
	uint	y = fmod((float)i / subDivCount, (float)subDivCount);
	uint	z = i / (subDivCount * subDivCount);

	float	subDivSize = SQUARE_SIZE / subDivCount;
	float	subDivSize2 = subDivSize / 2.0f;

	position->x = x * subDivSize - 0.5 + subDivSize2;
	position->y = y * subDivSize - 0.5 + subDivSize2;
	position->z = z * subDivSize - 0.5 + subDivSize2;

	particles[i].velocity = (float4)(0);
}
