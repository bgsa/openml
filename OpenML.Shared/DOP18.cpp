#include "DOP18.h"

DOP18::DOP18()
{
	min[0] = -0.5f;
	min[1] = -0.5f;
	min[2] = -0.5f;
	min[3] = -0.5f;
	min[4] = -0.5f;
	min[5] = -0.5f;
	min[6] = -0.5f;
	min[7] = -0.5f;
	min[8] = -0.5f;

	max[0] = 0.5f;
	max[1] = 0.5f;
	max[2] = 0.5f;
	max[3] = 0.5f;
	max[4] = 0.5f;
	max[5] = 0.5f;
	max[6] = 0.5f;
	max[7] = 0.5f;
	max[8] = 0.5f;
}

Vec3f DOP18::centerOfBoundingVolume()
{
	return Vec3f(
		(max[0] + min[0]) * 0.5f,
		(max[1] + min[1]) * 0.5f,
		(max[2] + min[2]) * 0.5f
	);
}

DOP18* DOP18::translate(float xAxis, float yAxis, float zAxis)
{
	min[0] += xAxis;
	max[0] += xAxis;

	min[1] += yAxis;
	max[1] += yAxis;

	min[2] += zAxis;
	max[2] += zAxis;

	float xyAxis = std::sqrtf(xAxis * xAxis + yAxis * yAxis);
	min[3] += xyAxis;
	max[3] += xyAxis;
	min[4] += xyAxis;
	max[4] += xyAxis;

	float yzAxis = std::sqrtf(yAxis * yAxis + zAxis * zAxis);
	min[5] += yzAxis;
	max[5] += yzAxis;
	min[6] += yzAxis;
	max[6] += yzAxis;

	float xzAxis = std::sqrtf(xAxis * xAxis + zAxis * zAxis);
	min[7] += xzAxis;
	max[7] += xzAxis;
	min[8] += xzAxis;
	max[8] += xzAxis;

	return this;
}

DOP18* DOP18::rotate(float angleInRadians, float xAxis, float yAxis, float zAxis)
{
	return this;
}

CollisionStatus DOP18::collisionStatus(const DOP18& kDop)
{
	for (int i = 0; i < DOP18_ORIENTATIONS; i++) 
		if (this->min[i] > kDop.max[i] || this->max[i] < kDop.min[i])
			return CollisionStatus::OUTSIDE;

	return CollisionStatus::INSIDE;
}

DOP18* DOP18::scale(float xAxis, float yAxis, float zAxis)
{
	min[0] *= xAxis;
	max[0] *= xAxis;

	min[1] *= yAxis;
	max[1] *= yAxis;

	min[2] *= zAxis;
	max[2] *= zAxis;

	float xyAxis = std::sqrtf(xAxis * xAxis + yAxis * yAxis);
	min[3] *= xyAxis;
	max[3] *= xyAxis;
	min[4] *= xyAxis;
	max[4] *= xyAxis;

	float yzAxis = std::sqrtf(yAxis * yAxis + zAxis * zAxis);
	min[5] *= yzAxis;
	max[5] *= yzAxis;
	min[6] *= yzAxis;
	max[6] *= yzAxis;

	float xzAxis = std::sqrtf(xAxis * xAxis + zAxis * zAxis);
	min[7] *= xzAxis;
	max[7] *= xzAxis;
	min[8] *= xzAxis;
	max[8] *= xzAxis;

	return this;
}

Mat3f DOP18::modelView()
{
	return Mat3f::identity();
}