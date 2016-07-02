
#pragma once

#include <iostream>

class Quaternion;
class Vec4;

class Vec3
{
public:
	float	x;
	float	y;
	float	z;

	static Vec3	zero;
	static Vec3	up;
	static Vec3	down;
	static Vec3	left;
	static Vec3	right;
	static Vec3	forward;
	static Vec3	back;

	Vec3();
	Vec3(const Vec3 & src);
	Vec3(float x, float y, float z);
	Vec3(const Vec4 & src);

	Vec3 &	operator=(const Vec3 & rhs);
	Vec3 &	operator=(float scalar);
	Vec3	operator+(const Vec3 & rhs) const;
	Vec3	operator-(const Vec3 & rhs) const;
	Vec3	operator*(const Vec3 & rhs) const;
	Vec3	operator*(float factor) const;
	Vec3	operator/(const Vec3 & rhs) const;
	Vec3	operator/(float factor) const;
	Vec3 &	operator+=(const Vec3 & rhs);
	Vec3 &	operator-=(const Vec3 & rhs);
	Vec3 &	operator*=(const Vec3 & rhs);
	Vec3 &	operator*=(float factor);
	Vec3 &	operator/=(const Vec3 & rhs);
	Vec3 &	operator/=(float factor);
	bool	operator==(const Vec3 & rhs) const;
	bool	operator!=(const Vec3 & rhs) const;

	void	set(float xVal, float yVal, float zVal);
	bool	isNull() const;
	float	magnitude() const;
	Vec3	normalize() const;
	float	dot(const Vec3 & vec) const;
	Vec3	cross(const Vec3 & vec) const;
};

std::ostream &	operator<<(std::ostream & os, const Vec3 & rhs);
