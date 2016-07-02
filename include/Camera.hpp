
#pragma once

#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Quaternion.hpp"
#include "Matrix4.hpp"
#include "Ray.hpp"

class Camera
{
public:
	Camera(const Vec2 & resolution);

	void		update();
	void		reset();
	Ray			screenPointToRay(const Vec2 & screenPosition) const;
	void		updateProjectionMatrix();

	Matrix4		matrix;
	Matrix4		projectionMatrix;
	Vec2		resolution;
	Quaternion	rotation;
	Vec3		linearVelocity;
	Vec3		angularVelocity;
	float		fovY = M_PI / 2.f;
	float		nearPlane = 0.001f;
	float		farPlane = 100.f;
};
