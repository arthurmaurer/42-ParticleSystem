
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <algorithm>

#ifndef _WIN32
	#include <sys/time.h>
#endif

#ifdef _WIN32
	#include <windows.h>
#endif

#include "Utils.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "CLContext.hpp"


void		Utils::replaceInString(std::string & str, const std::string & from, const std::string & to)
{
    if (from.empty())
        return ;

    size_t	start_pos = 0;

    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

std::string	Utils::readFile(const std::string & path)
{
	std::ifstream		file(path.c_str(), std::ios::in);
	std::stringstream	ss;

	if (!file.good())
		Utils::die("The script file \"%s\" cannot be opened (%s).\n", path.c_str(), strerror(errno));

	ss << file.rdbuf();

	return ss.str();
}

void		Utils::die(const char * format, ...)
{
	va_list	args;

	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	exit(EXIT_FAILURE);
}

void		Utils::die(const char * message, const cl::Error & e)
{
	die("%s: %s returned %s (%i)\n",
		message,
		e.what(),
		CLContext::getErrorString(e.err()).c_str(),
		e.err()
	);
}

float		Utils::rad(float deg)
{
	return (deg * (static_cast<float>(M_PI) / 180.f));
}

Vec3		Utils::rad(const Vec3 & deg)
{
	return Vec3(rad(deg.x), rad(deg.y), rad(deg.z));
}

float		Utils::deg(float rad)
{
	return ((rad * 180.f) / static_cast<float>(M_PI));
}

Vec3		Utils::deg(const Vec3 & rad)
{
	return Vec3(deg(rad.x), deg(rad.y), deg(rad.z));
}

float		Utils::clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;

	return value;
}

unsigned	Utils::gcd(unsigned a, unsigned b)
{
	unsigned remainder = a % b;

	if (remainder == 0)
		return b;

	return Utils::gcd(b, remainder);
}

float		Utils::getTime()
{
	static struct timeval	startTime;
	struct timeval			timeofday;

	getTimeOfDay(&timeofday, nullptr);

	if (startTime.tv_sec == 0)
		startTime = timeofday;

	return ((timeofday.tv_sec - startTime.tv_sec) + (timeofday.tv_usec - startTime.tv_usec) / 1000000.f);
}

float		Utils::getDeltaTime()
{
	static float	oldTime;
	float			newTime = Utils::getTime();
	float			deltaTime = newTime - oldTime;

	oldTime = newTime;

	return deltaTime;
}

Vec3		Utils::getRayPlaneIntersection(const Ray & ray, const Vec3 & planePosition, const Vec3 & planeNormal)
{
	float	distance = planeNormal.dot(planePosition - ray.origin) / planeNormal.dot(ray.direction);
	Vec3	hitPoint = ray.origin + ray.direction * distance;

	return hitPoint;
}

int Utils::getTimeOfDay(struct timeval* p, void* tz)
{
	#ifdef _WIN32
		ULARGE_INTEGER ul; // As specified on MSDN.
		FILETIME ft;

		// Returns a 64-bit value representing the number of
		// 100-nanosecond intervals since January 1, 1601 (UTC).
		GetSystemTimeAsFileTime(&ft);

		// Fill ULARGE_INTEGER low and high parts.
		ul.LowPart = ft.dwLowDateTime;
		ul.HighPart = ft.dwHighDateTime;
		// Convert to microseconds.
		ul.QuadPart /= 10ULL;
		// Remove Windows to UNIX Epoch delta.
		ul.QuadPart -= 11644473600000000ULL;
		// Modulo to retrieve the microseconds.
		p->tv_usec = (long)(ul.QuadPart % 1000000LL);
		// Divide to retrieve the seconds.
		p->tv_sec = (long)(ul.QuadPart / 1000000LL);

		return 0;
	#else
		return gettimeofday(p, tz);
	#endif
}
