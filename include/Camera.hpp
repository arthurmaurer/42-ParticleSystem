
#pragma once

#include "Matrix4.hpp"
#include "Vec3.hpp"
#include "Quaternion.hpp"

class Camera
{
public:
	Camera();

	void		update();
	void		reset();

	Matrix4		matrix;
	Quaternion	rotation;
	Vec3		linearVelocity;
	Vec3		angularVelocity;
};
