
void kernel test_kernel(global float * A)
{
	int		i = get_global_id(0) * 3;

	A[i] = 0;
	A[i + 1] = 0;
	A[i + 2] = 0;
}
