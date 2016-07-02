
#include <cmath>

#include "Vec2.hpp"

Vec2	Vec2::zero = Vec2(0, 0);
Vec2	Vec2::up = Vec2(0, 1.0f);
Vec2	Vec2::down = Vec2(0, -1.0f);
Vec2	Vec2::right = Vec2(1.0f, 0);
Vec2	Vec2::left = Vec2(-1.0f, 0);

Vec2::Vec2() :
	x(0),
	y(0)
{}

Vec2::Vec2(const Vec2 & src)
{
	*this = src;
}

Vec2::Vec2(float xVal, float yVal) :
	x(xVal),
	y(yVal)
{}

Vec2 &	Vec2::operator=(const Vec2 & rhs)
{
	if (this == &rhs)
		return *this;

	x = rhs.x;
	y = rhs.y;

	return *this;
}

Vec2 &	Vec2::operator=(float scalar)
{
	x = scalar;
	y = scalar;

	return *this;
}

Vec2	Vec2::operator+(const Vec2 & rhs) const
{
	Vec2	vec(*this);

	vec += rhs;

	return vec;
}

Vec2	Vec2::operator-(const Vec2 & rhs) const
{
	Vec2	vec(*this);

	vec -= rhs;

	return vec;
}

Vec2	Vec2::operator*(const Vec2 & rhs) const
{
	Vec2	vec(*this);

	vec *= rhs;

	return vec;
}


Vec2	Vec2::operator*(float factor) const
{
	Vec2	vec(*this);

	vec *= factor;

	return vec;
}

Vec2	Vec2::operator/(const Vec2 & rhs) const
{
	Vec2	vec(*this);

	vec /= rhs;

	return vec;
}

Vec2	Vec2::operator/(float factor) const
{
	Vec2	vec(*this);

	vec /= factor;

	return vec;
}

Vec2 &	Vec2::operator+=(const Vec2 & rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

Vec2 &	Vec2::operator-=(const Vec2 & rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

Vec2 &	Vec2::operator*=(const Vec2 & rhs)
{
	x *= rhs.x;
	y *= rhs.y;

	return *this;
}

Vec2 &	Vec2::operator*=(float factor)
{
	x *= factor;
	y *= factor;

	return *this;
}

Vec2 &	Vec2::operator/=(const Vec2 & rhs)
{
	x /= rhs.x;
	y /= rhs.y;

	return *this;
}

Vec2 &	Vec2::operator/=(float factor)
{
	x /= factor;
	y /= factor;

	return *this;
}

bool	Vec2::operator==(const Vec2 & rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

bool	Vec2::operator!=(const Vec2 & rhs) const
{
	return (x != rhs.x || y != rhs.y);
}

void	Vec2::set(float xVal, float yVal)
{
	this->x = xVal;
	this->y = yVal;
}

bool	Vec2::isNull() const
{
	return (x == 0 && y == 0);
}

float	Vec2::magnitude() const
{
	return sqrt(x * x + y * y);
}

Vec2	Vec2::normalize() const
{
	return (Vec2(*this) / magnitude());
}

float	Vec2::dot(const Vec2 & vec) const
{
	return (x * vec.x + y * vec.y);
}

std::ostream &	operator<<(std::ostream & os, const Vec2 & rhs)
{
	os
		<< "Vec2("
		<< rhs.x << ", "
		<< rhs.y << ")"
		;

	return os;
}
