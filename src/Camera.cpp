
#include "Camera.hpp"

Camera::Camera() :
	matrix(Matrix4::identity)
{
}

void	Camera::update()
{
	rotation *= Quaternion(angularVelocity);

	matrix = matrix
		.rotateX(angularVelocity.x)
		.rotateY(angularVelocity.y)
		.rotateZ(angularVelocity.z)
		.translate(linearVelocity);
}

void	Camera::reset()
{
	matrix = Matrix4::identity;
}
