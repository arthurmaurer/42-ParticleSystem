
static cl::Platform	__getDefaultPlatform()
{
	std::vector<cl::Platform>	platforms;

	cl::Platform::get(&platforms);

	if (platforms.size() == 0)
		Utils::die("No platforms found");

	for (auto i : platforms)
		std::cout << i.getInfo<CL_PLATFORM_NAME>() << std::endl;

	return platforms[1];
}

static cl::Device	__getDefaultDevice(const cl::Platform & platform)
{
	std::vector<cl::Device>		devices;

	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

	if (devices.size() == 0)
		Utils::die("No devices found");

	for (auto i : devices)
		std::cout << i.getInfo<CL_DEVICE_NAME>() << std::endl;

	return devices[0];
}
