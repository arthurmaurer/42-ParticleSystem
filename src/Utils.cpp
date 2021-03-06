
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdarg>
#include <cstdio>

#include "Utils.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "CLContext.hpp"

std::string	Utils::readFile(const std::string & path)
{
	std::ifstream		file(path.c_str(), std::ios::in);
	std::stringstream	ss;

	if (!file.good())
		Utils::die("The script file \"%s\" cannot be opened.\n", path.c_str());

	ss << file.rdbuf();

	return ss.str();
}

void		Utils::die(const char * format, ...)
{
	va_list	args;

	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	system("pause");
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

Vec3		Utils::getRayPlaneIntersection(const Ray & ray, const Vec3 & planePosition, const Vec3 & planeNormal)
{
	float	distance = planeNormal.dot(planePosition - ray.origin) / planeNormal.dot(ray.direction);
	Vec3	hitPoint = ray.origin + ray.direction * distance;

	return hitPoint;
}
