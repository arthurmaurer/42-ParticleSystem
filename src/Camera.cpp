
#include "Camera.hpp"
#include "Ray.hpp"

Camera::Camera(const Vec2 & resolution) :
	resolution(resolution),
	matrix(Matrix4::identity)
{
	updateProjectionMatrix();
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

Ray	Camera::screenPointToRay(const Vec2 & screenPosition) const
{
	Vec3	camForward = rotation * Vec3::forward;
	Vec3	camRight = rotation * Vec3::right;
	Vec3	camUp = rotation * Vec3::up;
	Vec3	camPosition = matrix * Vec3::zero;

	Vec2	renderPlaneSize;
	renderPlaneSize.y = tan(fovY / 2.f) * nearPlane;
	renderPlaneSize.x = renderPlaneSize.y * (resolution.x / resolution.y);

	camRight *= renderPlaneSize.x;
	camUp *= renderPlaneSize.y;

	Vec2	viewportPosition = (screenPosition - resolution / 2.f) / (resolution / 2.f);
	viewportPosition.y *= -1.f;
	Vec3	rayOnNearPlane = camPosition + camForward * nearPlane + camRight * viewportPosition.x + camUp * viewportPosition.y;

	Ray		ray(camPosition, Vec3::zero);
	ray.direction = rayOnNearPlane - camPosition;
	ray.direction = ray.direction.normalize();

	return ray;
}

void				Camera::updateProjectionMatrix()
{
	projectionMatrix = Matrix4::getPerspective(
		fovY,
		resolution.x / resolution.y,
		nearPlane,
		farPlane
	);
}
