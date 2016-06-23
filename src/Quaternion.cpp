
#include <cmath>

#include "Quaternion.hpp"
#include "Vec3.hpp"
#include "Utils.hpp"

Quaternion	Quaternion::identity = Quaternion(0, 0, 0, 1.f);

Quaternion::Quaternion() :
	w(1.0f),
	x(0),
	y(0),
	z(0)
{}

Quaternion::Quaternion(const Quaternion & src)
{
	*this = src;
}

Quaternion::Quaternion(float wVal, float xVal, float yVal, float zVal) :
	w(wVal),
	x(xVal),
	y(yVal),
	z(zVal)
{}

Quaternion::Quaternion(const Vec3 & eulerAngles)
{
	setFromEulerAngles(eulerAngles);
}

Quaternion &	Quaternion::operator=(const Quaternion & rhs)
{
	if (&rhs == this)
		return *this;

	w = rhs.w;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

Quaternion		Quaternion::operator*(const Quaternion & rhs) const
{
	Quaternion	quat(*this);

	quat *= rhs;

	return quat;
}

Quaternion &	Quaternion::operator*=(const Quaternion & rhs)
{
	Quaternion	quat(*this);

	quat.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
	quat.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
	quat.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
	quat.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

	w = quat.w;
	x = quat.x;
	y = quat.y;
	z = quat.z;

	return *this;
}

Vec3			Quaternion::operator*(const Vec3 & rhs) const
{
	Quaternion	vec;

	vec.setFromVector(rhs);
	vec = *this * vec * inverse();

	return Vec3(vec.x, vec.y, vec.z);
}

bool			Quaternion::operator==(const Quaternion & rhs) const
{
	return (w == rhs.w && x == rhs.x && y == rhs.y && z == rhs.z);
}

bool			Quaternion::operator!=(const Quaternion & rhs) const
{
	return (w != rhs.w || x != rhs.x || y != rhs.y || z != rhs.z);
}

float			Quaternion::pitch() const
{
	return atan2(2.f * (y * z + w * x), w * w - x * x - y * y + z * z);
}

float			Quaternion::yaw() const
{
	Quaternion	normalized(normalize());
	float		tmp = -2.f * (normalized.x * normalized.z - normalized.w * normalized.y);

	tmp = Utils::clamp(tmp, -1.f, 1.f);

	// TODO: tmp < -1.f even when norm = 1.f. It create "jumps" on certain
	// frames.
	return (asinf(tmp));
}

float			Quaternion::roll() const
{
	return (atan2(2.f * (x * y + w * z), w * w + x * x - y * y - z * z));
}

void			Quaternion::set(float wVal, float xVal, float yVal, float zVal)
{
	this->w = wVal;
	this->x = xVal;
	this->y = yVal;
	this->z = zVal;
}

float			Quaternion::getNorm() const
{
	return sqrtf(dot(*this));
}

Vec3			Quaternion::getEulerAngles() const
{
	return Vec3(pitch(), yaw(), roll());
}

void			Quaternion::setFromEulerAngles(const Vec3 & eulerAngles)
{
	Vec3	cosAngles;
	Vec3	sinAngles;

	cosAngles.x = cosf(eulerAngles.x * 0.5f);
	cosAngles.y = cosf(eulerAngles.y * 0.5f);
	cosAngles.z = cosf(eulerAngles.z * 0.5f);

	sinAngles.x = sinf(eulerAngles.x * 0.5f);
	sinAngles.y = sinf(eulerAngles.y * 0.5f);
	sinAngles.z = sinf(eulerAngles.z * 0.5f);

	w = cosAngles.x * cosAngles.y * cosAngles.z + sinAngles.x * sinAngles.y * sinAngles.z;
	x = sinAngles.x * cosAngles.y * cosAngles.z - cosAngles.x * sinAngles.y * sinAngles.z;
	y = cosAngles.x * sinAngles.y * cosAngles.z + sinAngles.x * cosAngles.y * sinAngles.z;
	z = cosAngles.x * cosAngles.y * sinAngles.z - sinAngles.x * sinAngles.y * cosAngles.z;
}

void			Quaternion::rotateFromAxisAngle(const Vec3 & axis, float angle)
{
	Quaternion	quat;
	float		sinA;

	angle = Utils::deg(angle) / 360.f * (float)M_PI * 2.f;

	sinA = sinf(angle / 2.0f);

	quat.x = axis.x * sinA;
	quat.y = axis.y * sinA;
	quat.z = axis.z * sinA;
	quat.w = cosf(angle / 2.f);

	*this *= quat.normalize();
}

void Quaternion::setFromVector(const Vec3 & vector)
{
	w = 0;
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

void Quaternion::rotateX(float angle)
{
	rotateFromAxisAngle(Vec3::right, angle);
}

void Quaternion::rotateY(float angle)
{
	rotateFromAxisAngle(Vec3::up, angle);
}

void Quaternion::rotateZ(float angle)
{
	rotateFromAxisAngle(Vec3::forward, angle);
}

Quaternion		Quaternion::normalize() const
{
	float	norm;

	norm = getNorm();
	return Quaternion(w / norm, x / norm, y / norm, z / norm);
}

Quaternion		Quaternion::conjugate() const
{
	return Quaternion(w, x * -1.0f, y * -1.0f, z * -1.0f);
}

Quaternion		Quaternion::inverse() const
{
	return Quaternion(w, -x, -y, -z);
}

float			Quaternion::dot(const Quaternion & quat) const
{
	return (x * quat.x + y * quat.y + z * quat.z + w * quat.w);
}

std::ostream &	operator<<(std::ostream & os, const Quaternion & rhs)
{
	os
		<< "Quaternion("
		<< rhs.w << ", "
		<< rhs.x << ", "
		<< rhs.y << ", "
		<< rhs.z << ")"
		;

	return os;
}
