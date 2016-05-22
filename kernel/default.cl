
void kernel test_kernel(global float3 * particles)
{
	int		i = get_global_id(0);
	float3	particle = particles[i];

	particle.x = 0;
	particle.y = 0;
	particle.z = 0;
}
