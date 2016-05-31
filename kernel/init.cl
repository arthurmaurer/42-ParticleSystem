
#define WIDTH	1.0
#define HEIGHT	1.0

void kernel initialize_rect(global float4 * particles, int particleCount)
{
	int		i = get_global_id(0);
	float	subCount = sqrt((float)particleCount);
	uint	x = fmod(i, subCount);
	uint	y = i / subCount;
	float2	subSize = (WIDTH / subCount, HEIGHT / subCount);
	float2	subSize2 = subSize / (float2)(2.0f);

	particles[i].x = x * subSize.x - 0.5 + subSize2.x;
	particles[i].y = y * subSize.y - 0.5 + subSize2.y;
	particles[i].z = 0;
	particles[i].w = 1;
}
