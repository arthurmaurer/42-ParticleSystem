
void kernel test_kernel(global float4 * A)
{
	int		i = get_global_id(0);

	A[i].x = 0;
	A[i].y = 0;
	A[i].z = 0;
}
