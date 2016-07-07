
#pragma once

#include "cl.hpp"
#include "CLSupportInfo.hpp"

class DeviceSelector
{
public:
	static CLSupportInfo	selectDevice(
		const std::string & defaultPlatformName,
		const std::string & defaultDeviceName
	);
	static cl::Platform		getPlatform(const std::string & defaultName);
	static cl::Device		getDevice(const cl::Platform & platform, const std::string & defaultName);
	static std::string		getPlatformName(const cl::Platform & platform);
	static std::string		getDeviceName(const cl::Device & device);
};
