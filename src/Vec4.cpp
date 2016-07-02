
#include <cmath>

#include "Vec4.hpp"
#include "Vec3.hpp"

Vec4::Vec4() :
	x(0),
	y(0),
	z(0),
	w(0)
{}

Vec4::Vec4(const Vec4 & src)
{
	*this = src;
}

Vec4::Vec4(float xVal, float yVal, float zVal, float wVal) :
	x(xVal),
	y(yVal),
	z(zVal),
	w(wVal)
{}

Vec4::Vec4(const Vec3 & src, float w) :
	x(src.x),
	y(src.y),
	z(src.z),
	w(w)
{}

Vec4 &	Vec4::operator=(const Vec4 & rhs)
{
	if (this == &rhs)
		return *this;

	w = rhs.w;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

Vec4 &	Vec4::operator=(float scalar)
{
	w = scalar;
	x = scalar;
	y = scalar;
	z = scalar;

	return *this;
}

Vec4	Vec4::operator+(const Vec4 & rhs) const
{
	Vec4	vec(*this);

	vec += rhs;

	return vec;
}

Vec4	Vec4::operator-(const Vec4 & rhs) const
{
	Vec4	vec(*this);

	vec -= rhs;

	return vec;
}

Vec4	Vec4::operator*(const Vec4 & rhs) const
{
	Vec4	vec(*this);

	vec *= rhs;

	return vec;
}


Vec4	Vec4::operator*(float factor) const
{
	Vec4	vec(*this);

	vec *= factor;

	return vec;
}

Vec4	Vec4::operator/(const Vec4 & rhs) const
{
	Vec4	vec(*this);

	vec /= rhs;

	return vec;
}

Vec4	Vec4::operator/(float factor) const
{
	Vec4	vec(*this);

	vec /= factor;

	return vec;
}

Vec4 &	Vec4::operator+=(const Vec4 & rhs)
{
	w += rhs.w;
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Vec4 &	Vec4::operator-=(const Vec4 & rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

Vec4 &	Vec4::operator*=(const Vec4 & rhs)
{
	w *= rhs.w;
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

Vec4 &	Vec4::operator*=(float factor)
{
	w *= factor;
	x *= factor;
	y *= factor;
	z *= factor;

	return *this;
}

Vec4 &	Vec4::operator/=(const Vec4 & rhs)
{
	w /= rhs.w;
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;

	return *this;
}

Vec4 &	Vec4::operator/=(float factor)
{
	w /= factor;
	x /= factor;
	y /= factor;
	z /= factor;

	return *this;
}

bool	Vec4::operator==(const Vec4 & rhs) const
{
	return (w == rhs.w && x == rhs.x && y == rhs.y && z == rhs.z);
}

bool	Vec4::operator!=(const Vec4 & rhs) const
{
	return (w != rhs.w || x != rhs.x || y != rhs.y || z != rhs.z);
}

void	Vec4::set(float wVal, float xVal, float yVal, float zVal)
{
	this->w = wVal;
	this->x = xVal;
	this->y = yVal;
	this->z = zVal;
}

bool	Vec4::isNull() const
{
	return (w == 0 && x == 0 && y == 0 && z == 0);
}

std::ostream &	operator<<(std::ostream & os, const Vec4 & rhs)
{
	os
		<< "Vec4("
		<< "x: " << rhs.x << ", "
		<< "y: " << rhs.y << ", "
		<< "z: " << rhs.z << ", "
		<< "w: " << rhs.w << ")";

	return os;
}
