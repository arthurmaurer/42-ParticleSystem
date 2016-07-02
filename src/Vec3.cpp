
#include <cmath>
#include <cassert>

#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Quaternion.hpp"

Vec3 Vec3::zero = Vec3(0, 0, 0);
Vec3 Vec3::up = Vec3(0, 1.0f, 0);
Vec3 Vec3::down = Vec3(0, -1.0f, 0);
Vec3 Vec3::left = Vec3(-1.0f, 0, 0);
Vec3 Vec3::right = Vec3(1.0f, 0, 0);
Vec3 Vec3::forward = Vec3(0, 0, 1.0f);
Vec3 Vec3::back = Vec3(0, 0, -1.0f);

Vec3::Vec3() :
	x(0),
	y(0),
	z(0)
{}

Vec3::Vec3(const Vec3 & src)
{
	*this = src;
}

Vec3::Vec3(float xVal, float yVal, float zVal) :
	x(xVal),
	y(yVal),
	z(zVal)
{}

Vec3::Vec3(const Vec4 & src) :
	x(src.x),
	y(src.y),
	z(src.z)
{}

Vec3 &	Vec3::operator=(const Vec3 & rhs)
{
	if (this == &rhs)
		return *this;

	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

Vec3 &	Vec3::operator=(float scalar)
{
	x = scalar;
	y = scalar;
	z = scalar;

	return *this;
}

Vec3	Vec3::operator+(const Vec3 & rhs) const
{
	Vec3	vec(*this);

	vec += rhs;

	return vec;
}

Vec3	Vec3::operator-(const Vec3 & rhs) const
{
	Vec3	vec(*this);

	vec -= rhs;

	return vec;
}

Vec3	Vec3::operator*(const Vec3 & rhs) const
{
	Vec3	vec(*this);

	vec *= rhs;

	return vec;
}


Vec3	Vec3::operator*(float factor) const
{
	Vec3	vec(*this);

	vec *= factor;

	return vec;
}

Vec3	Vec3::operator/(const Vec3 & rhs) const
{
	Vec3	vec(*this);

	vec /= rhs;

	return vec;
}

Vec3	Vec3::operator/(float factor) const
{
	Vec3	vec(*this);

	vec /= factor;

	return vec;
}

Vec3 &	Vec3::operator+=(const Vec3 & rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Vec3 &	Vec3::operator-=(const Vec3 & rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

Vec3 &	Vec3::operator*=(const Vec3 & rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

Vec3 &	Vec3::operator*=(float factor)
{
	x *= factor;
	y *= factor;
	z *= factor;

	return *this;
}

Vec3 &	Vec3::operator/=(const Vec3 & rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;

	return *this;
}

Vec3 &	Vec3::operator/=(float factor)
{
	x /= factor;
	y /= factor;
	z /= factor;

	return *this;
}

bool	Vec3::operator==(const Vec3 & rhs) const
{
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

bool	Vec3::operator!=(const Vec3 & rhs) const
{
	return (x != rhs.x || y != rhs.y || z != rhs.z);
}

void	Vec3::set(float xVal, float yVal, float zVal)
{
	this->x = xVal;
	this->y = yVal;
	this->z = zVal;
}

bool	Vec3::isNull() const
{
	return (x == 0 && y == 0 && z == 0);
}

float	Vec3::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

Vec3	Vec3::normalize() const
{
	return (Vec3(*this) / magnitude());
}

float	Vec3::dot(const Vec3 & vec) const
{
	return (x * vec.x + y * vec.y + z * vec.z);
}

Vec3	Vec3::cross(const Vec3 & vec) const
{
	Vec3	out;

	out.x = y * vec.z - z * vec.y;
	out.y = z * vec.x - x * vec.z;
	out.z = x * vec.y - y * vec.x;

	// TODO: WTF ?
	return vec;
}

std::ostream &	operator<<(std::ostream & os, const Vec3 & rhs)
{
	os
		<< "Vec3("
		<< rhs.x << ", "
		<< rhs.y << ", "
		<< rhs.z << ")"
		;

	return os;
}
