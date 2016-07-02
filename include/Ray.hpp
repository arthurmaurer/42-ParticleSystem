
#pragma once

#include "Vec3.hpp"

class Ray
{
public:
	Ray(const Vec3 & origin, const Vec3 & direction);

	Vec3	origin;
	Vec3	direction;
};
