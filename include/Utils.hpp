
#pragma once

#include <string>
#include "cl.hpp"

#ifndef M_PI
# define M_PI	3.14159265358979323846
#endif

#ifndef M_PI_2
# define M_PI_2	1.57079632679489661923
#endif

class Vec3;
class Ray;

class Utils
{
public:
	static void			replaceInString(std::string & str, const std::string & from, const std::string & to);
	static std::string	readFile(const std::string & path);
	static void			die(const char * format, ...);
	static void			die(const char * message, const cl::Error & e);

	static float		rad(float deg);
	static Vec3			rad(const Vec3 & deg);
	static float		deg(float rad);
	static Vec3			deg(const Vec3 & rad);

	static float		clamp(float value, float min, float max);
	static unsigned		gcd(unsigned a, unsigned b);

	static float		getTime();
	static float		getDeltaTime();

	static Vec3			getRayPlaneIntersection(const Ray & ray, const Vec3 & planePosition, const Vec3 & planeNormal);
};