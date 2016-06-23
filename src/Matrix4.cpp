
#include <cmath>
#include <cstring>
#include <iostream>

#include "Matrix4.hpp"
#include "Quaternion.hpp"
#include "Vec3.hpp"

const Matrix4		Matrix4::zero(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
const Matrix4		Matrix4::identity(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

Matrix4::Matrix4()
{
	setIdentity();
}

Matrix4::Matrix4(const Matrix4 & src)
{
	*this = src;
}

Matrix4::Matrix4(const Quaternion & quat)
{
	setFromQuaternion(quat);
}

Matrix4::Matrix4(float d0, float d1, float d2, float d3, float d4, float d5,
	float d6, float d7, float d8, float d9, float d10, float d11, float d12,
	float d13, float d14, float d15)
{
	data[0] = d0;
	data[1] = d1;
	data[2] = d2;
	data[3] = d3;
	data[4] = d4;
	data[5] = d5;
	data[6] = d6;
	data[7] = d7;
	data[8] = d8;
	data[9] = d9;
	data[10] = d10;
	data[11] = d11;
	data[12] = d12;
	data[13] = d13;
	data[14] = d14;
	data[15] = d15;
}

Matrix4 &	Matrix4::operator=(const Matrix4 & rhs)
{
	if (&rhs == this)
		return *this;

	memcpy(data, rhs.data, sizeof(data));
	return *this;
}

Matrix4		Matrix4::operator*(const Matrix4 & rhs) const
{
	Matrix4		result;
	unsigned	i;
	unsigned	j;

	i = 0;
	while (i < 16)
	{
		result.data[i] = 0;
		j = 0;
		while (j < 4)
		{
			result.data[i] += data[((i / 4) * 4 + j)] * rhs.data[(j * 4 + i % 4)];
			j++;
		}
		i++;
	}

	return result;
}

Matrix4 &	Matrix4::operator*=(const Matrix4 & rhs)
{
	if (&rhs == this)
		return *this;

	*this = *this * rhs;
	return *this;
}

Matrix4		Matrix4::translate(const Vec3 & amount) const
{
	Matrix4	trans;

	trans.data[3] = amount.x;
	trans.data[7] = amount.y;
	trans.data[11] = amount.z;

	return (*this * trans);
}

Matrix4		Matrix4::scale(const Vec3 & amount) const
{
	return scale(amount.x, amount.y, amount.z);
}

Matrix4		Matrix4::scale(float amount) const
{
	return scale(amount, amount, amount);
}

Matrix4		Matrix4::scale(float amountX, float amountY, float amountZ) const
{
	Matrix4	trans;

	trans.data[0] = amountX;
	trans.data[5] = amountY;
	trans.data[10] = amountZ;

	return (*this * trans);
}

Matrix4		Matrix4::rotateX(float amount) const
{
	Matrix4	rot;

	rot.data[5] = cosf(amount);
	rot.data[6] = sinf(amount) * -1;
	rot.data[9] = sinf(amount);
	rot.data[10] = cosf(amount);

	return (*this * rot);
}

Matrix4		Matrix4::rotateY(float amount) const
{
	Matrix4	rot;

	rot.data[0] = cosf(amount);
	rot.data[2] = sinf(amount);
	rot.data[8] = sinf(amount) * -1;
	rot.data[10] = cosf(amount);

	return (*this * rot);
}

Matrix4		Matrix4::rotateZ(float amount) const
{
	Matrix4	rot;

	rot.data[0] = cosf(amount);
	rot.data[1] = sinf(amount) * -1;
	rot.data[4] = sinf(amount);
	rot.data[5] = cosf(amount);

	return (*this * rot);
}

Matrix4		Matrix4::inverse() const
{
	Matrix4		inversed;
	Matrix4		out;
	float		determinant;

	inversed.data[0] = data[5] * data[10] * data[15] -
		data[5] * data[11] * data[14] -
		data[9] * data[6] * data[15] +
		data[9] * data[7] * data[14] +
		data[13] * data[6] * data[11] -
		data[13] * data[7] * data[10];

	inversed.data[4] = -data[4] * data[10] * data[15] +
		data[4] * data[11] * data[14] +
		data[8] * data[6] * data[15] -
		data[8] * data[7] * data[14] -
		data[12] * data[6] * data[11] +
		data[12] * data[7] * data[10];

	inversed.data[8] = data[4] * data[9] * data[15] -
		data[4] * data[11] * data[13] -
		data[8] * data[5] * data[15] +
		data[8] * data[7] * data[13] +
		data[12] * data[5] * data[11] -
		data[12] * data[7] * data[9];

	inversed.data[12] = -data[4] * data[9] * data[14] +
		data[4] * data[10] * data[13] +
		data[8] * data[5] * data[14] -
		data[8] * data[6] * data[13] -
		data[12] * data[5] * data[10] +
		data[12] * data[6] * data[9];

	inversed.data[1] = -data[1] * data[10] * data[15] +
		data[1] * data[11] * data[14] +
		data[9] * data[2] * data[15] -
		data[9] * data[3] * data[14] -
		data[13] * data[2] * data[11] +
		data[13] * data[3] * data[10];

	inversed.data[5] = data[0] * data[10] * data[15] -
		data[0] * data[11] * data[14] -
		data[8] * data[2] * data[15] +
		data[8] * data[3] * data[14] +
		data[12] * data[2] * data[11] -
		data[12] * data[3] * data[10];

	inversed.data[9] = -data[0] * data[9] * data[15] +
		data[0] * data[11] * data[13] +
		data[8] * data[1] * data[15] -
		data[8] * data[3] * data[13] -
		data[12] * data[1] * data[11] +
		data[12] * data[3] * data[9];

	inversed.data[13] = data[0] * data[9] * data[14] -
		data[0] * data[10] * data[13] -
		data[8] * data[1] * data[14] +
		data[8] * data[2] * data[13] +
		data[12] * data[1] * data[10] -
		data[12] * data[2] * data[9];

	inversed.data[2] = data[1] * data[6] * data[15] -
		data[1] * data[7] * data[14] -
		data[5] * data[2] * data[15] +
		data[5] * data[3] * data[14] +
		data[13] * data[2] * data[7] -
		data[13] * data[3] * data[6];

	inversed.data[6] = -data[0] * data[6] * data[15] +
		data[0] * data[7] * data[14] +
		data[4] * data[2] * data[15] -
		data[4] * data[3] * data[14] -
		data[12] * data[2] * data[7] +
		data[12] * data[3] * data[6];

	inversed.data[10] = data[0] * data[5] * data[15] -
		data[0] * data[7] * data[13] -
		data[4] * data[1] * data[15] +
		data[4] * data[3] * data[13] +
		data[12] * data[1] * data[7] -
		data[12] * data[3] * data[5];

	inversed.data[14] = -data[0] * data[5] * data[14] +
		data[0] * data[6] * data[13] +
		data[4] * data[1] * data[14] -
		data[4] * data[2] * data[13] -
		data[12] * data[1] * data[6] +
		data[12] * data[2] * data[5];

	inversed.data[3] = -data[1] * data[6] * data[11] +
		data[1] * data[7] * data[10] +
		data[5] * data[2] * data[11] -
		data[5] * data[3] * data[10] -
		data[9] * data[2] * data[7] +
		data[9] * data[3] * data[6];

	inversed.data[7] = data[0] * data[6] * data[11] -
		data[0] * data[7] * data[10] -
		data[4] * data[2] * data[11] +
		data[4] * data[3] * data[10] +
		data[8] * data[2] * data[7] -
		data[8] * data[3] * data[6];

	inversed.data[11] = -data[0] * data[5] * data[11] +
		data[0] * data[7] * data[9] +
		data[4] * data[1] * data[11] -
		data[4] * data[3] * data[9] -
		data[8] * data[1] * data[7] +
		data[8] * data[3] * data[5];

	inversed.data[15] = data[0] * data[5] * data[10] -
		data[0] * data[6] * data[9] -
		data[4] * data[1] * data[10] +
		data[4] * data[2] * data[9] +
		data[8] * data[1] * data[6] -
		data[8] * data[2] * data[5];

	determinant = data[0] * inversed.data[0] + data[1] * inversed.data[4] + data[2] * inversed.data[8] + data[3] * inversed.data[12];

	determinant = 1.f / determinant;

	for (unsigned i = 0; i < 16; i++)
		out.data[i] = inversed.data[i] * determinant;

	return out;
}

Matrix4		Matrix4::transpose() const
{
	Matrix4		transposed;
	unsigned	i;
	unsigned	j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			transposed.data[i * 4 + j] = data[j * 4 + i];
		}
	}

	return transposed;
}

Matrix4		Matrix4::getPerspective(float fov, float aspect, float nearPlane, float farPlane)
{
	Matrix4	matrix;
	float	tanHalfFov;

	tanHalfFov = tanf(fov / 2.f);
	memset(matrix.data, 0, sizeof(matrix.data));
	matrix.data[0] = 1.f / (aspect * tanHalfFov);
	matrix.data[5] = 1.f / (tanHalfFov);
	matrix.data[10] = (farPlane + nearPlane) / (farPlane - nearPlane) * -1.f;
	matrix.data[11] = (2.f * farPlane * nearPlane) / (farPlane - nearPlane) * -1.f;
	matrix.data[14] = -1.f;

	return matrix;
}

void	Matrix4::setIdentity()
{
	memset(data, 0, sizeof(data));
	data[0] = 1.0f;
	data[5] = 1.0f;
	data[10] = 1.0f;
	data[15] = 1.0f;
}

void	Matrix4::setFromQuaternion(const Quaternion & quat)
{
	setIdentity();

	float xx = quat.x * quat.x;
	float xy = quat.x * quat.y;
	float xz = quat.x * quat.z;
	float xw = quat.x * quat.w;

	float yy = quat.y * quat.y;
	float yz = quat.y * quat.z;
	float yw = quat.y * quat.w;

	float zz = quat.z * quat.z;
	float zw = quat.z * quat.w;

	data[0] = 1.0f - 2.0f * (yy + zz);
	data[1] = 2.0f * (xy - zw);
	data[2] = 2.0f * (xz + yw);
	data[3] = 0;

	data[4] = 2.0f * (xy + zw);
	data[5] = 1.0f - 2.0f * (xx + zz);
	data[6] = 2.0f * (yz - xw);
	data[7] = 0;

	data[8] = 2.0f * (xz - yw);
	data[9] = 2.0f * (yz + xw);
	data[10] = 1.0f - 2.0f * (xx + yy);
	data[11] = 0;

	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1.0f;
}

std::ostream &	operator<<(std::ostream & os, const Matrix4 & rhs)
{
	os
		<< "Matrix4("
		<< rhs.data[0] << ", "
		<< rhs.data[1] << ", "
		<< rhs.data[2] << ", "
		<< rhs.data[3] << ", " << std::endl
		<< "        " << rhs.data[4] << ", "
		<< rhs.data[5] << ", "
		<< rhs.data[6] << ", "
		<< rhs.data[7] << ", " << std::endl
		<< "        " << rhs.data[8] << ", "
		<< rhs.data[9] << ", "
		<< rhs.data[10] << ", "
		<< rhs.data[11] << ", " << std::endl
		<< "        " << rhs.data[12] << ", "
		<< rhs.data[13] << ", "
		<< rhs.data[14] << ", "
		<< rhs.data[15] << ")" << std::endl
		;

	return os;
}
