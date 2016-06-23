
#pragma once

#include <iostream>

class Vec4
{
public:
	float	w;
	float	x;
	float	y;
	float	z;

	Vec4();
	Vec4(const Vec4 & src);
	Vec4(float w, float x, float y, float z);

	Vec4 &	operator=(const Vec4 & rhs);
	Vec4 &	operator=(float scalar);
	Vec4	operator+(const Vec4 & rhs) const;
	Vec4	operator-(const Vec4 & rhs) const;
	Vec4	operator*(const Vec4 & rhs) const;
	Vec4	operator*(float factor) const;
	Vec4	operator/(const Vec4 & rhs) const;
	Vec4	operator/(float factor) const;
	Vec4 &	operator+=(const Vec4 & rhs);
	Vec4 &	operator-=(const Vec4 & rhs);
	Vec4 &	operator*=(const Vec4 & rhs);
	Vec4 &	operator*=(float factor);
	Vec4 &	operator/=(const Vec4 & rhs);
	Vec4 &	operator/=(float factor);
	bool	operator==(const Vec4 & rhs) const;
	bool	operator!=(const Vec4 & rhs) const;

	void	set(float wVal, float xVal, float yVal, float zVal);
	bool	isNull() const;
};

std::ostream &	operator<<(std::ostream & os, const Vec4 & rhs);
