#include "AABB.h"

AABB::AABB()
{
	this->minPoint = Vec3f(-0.5f);
	this->maxPoint = -this->minPoint;
}

AABB::AABB(Vec3f minPoint, Vec3f maxPoint)
{
	this->minPoint = minPoint;
	this->maxPoint = maxPoint;
}

AABB::AABB(Vec3f minPoint, float width, float height, float depth)
{
	this->minPoint = minPoint;

	maxPoint = Vec3f(
		minPoint.x + width,
		minPoint.y + height,
		minPoint.z + depth
		);
}

Vec3f AABB::center()
{
	return (maxPoint + minPoint) * 0.5f;
}

Vec3f AABB::center() const
{
	return (maxPoint + minPoint) * 0.5f;
}

Vec3f AABB::centerOfBoundingVolume()
{
	return center();
}

float AABB::squaredDistance(const Vec3f& target)
{
	float result = 0.0f;

	// For each axis count any excess distance outside box extents 
	for (int axis = 0; axis < 3; axis++)
	{
		float v = target[axis];

		if (v < minPoint[axis])
			result += (minPoint[axis] - v) * (minPoint[axis] - v);

		if (v > maxPoint[axis])
			result += (v - maxPoint[axis]) * (v - maxPoint[axis]);
	}

	return result;
}

float AABB::distance(const Vec3f& target)
{
	return float(sqrt(squaredDistance(target)));
}

AABB* AABB::translate(float xAxis, float yAxis, float zAxis)
{
	//Mat3f translation = Mat3f::createTranslate(xAxis, yAxis, zAxis);
	Vec3f translation = Vec3f(xAxis, yAxis, zAxis);

	minPoint += translation;
	maxPoint += translation;

	return this;
}

AABB* AABB::scale(float xAxis, float yAxis, float zAxis)
{
	minPoint = Vec3f(
		minPoint.x * (xAxis * 0.5f),
		minPoint.y * (yAxis * 0.5f),
		minPoint.z * (zAxis * 0.5f)
	);

	maxPoint = Vec3f(
		maxPoint.x * (xAxis * 0.5f),
		maxPoint.y * (yAxis * 0.5f),
		maxPoint.z * (zAxis * 0.5f)
	);

	return this;
}

AABB* AABB::rotate(float angleInRadians, float xAxis, float yAxis, float zAxis)
{
	return this;
}

Mat3f AABB::modelView()
{
	Vec3f midPoint = center();
	Vec3f halfWidth = maxPoint - midPoint;

	return Mat3f::createTranslate(midPoint.x, midPoint.y, midPoint.z)
		* Mat3f::createScale(halfWidth.x, halfWidth.y, halfWidth.z);
}

ColisionStatus AABB::colisionStatus(const AABB& aabb) 
{
	if (maxPoint.x < aabb.minPoint.x || minPoint.x > aabb.maxPoint.x)
		return ColisionStatus::OUTSIDE;

	if (maxPoint.y < aabb.minPoint.y || minPoint.y > aabb.maxPoint.y)
		return ColisionStatus::OUTSIDE;

	if (maxPoint.z < aabb.minPoint.z || minPoint.z > aabb.maxPoint.z)
		return ColisionStatus::OUTSIDE;

	return ColisionStatus::INSIDE;
}

ColisionStatus AABB::colisionStatus(const Plane3D& plane)
{
	Vec3f centerPoint = center(); 
	float d = plane.getDcomponent();
	Vec3f halfDistanceFromCenter = maxPoint - centerPoint;

	// Compute the projection interval radius of AABB onto L(t) = center + t * normalPlane
	double r = 
		  halfDistanceFromCenter.x * std::abs(plane.normalVector.x)
		+ halfDistanceFromCenter.y * std::abs(plane.normalVector.y)
		+ halfDistanceFromCenter.z * std::abs(plane.normalVector.z);
	
	double distanceFromAABB2Plane = std::abs(plane.normalVector.dot(centerPoint) + d);
	
	if (isCloseEnough(distanceFromAABB2Plane, r))
		return ColisionStatus::INLINE;

	// it has intersection when distance falls within [-r,+r] interval 	

	if (distanceFromAABB2Plane <= r)  
		return ColisionStatus::INSIDE;

	return ColisionStatus::OUTSIDE;
}

ColisionStatus AABB::colisionStatus(const Sphere& sphere)
{
	float distanceToSphere = squaredDistance(sphere.center);
	float squaredRay = sphere.ray * sphere.ray;
	
	if (isCloseEnough(distanceToSphere, squaredRay))
		return ColisionStatus::INLINE;

	if (distanceToSphere < squaredRay)
		return ColisionStatus::INSIDE;

	return ColisionStatus::OUTSIDE;
}

Vec3f AABB::closestPointInAABB(const Vec3f& target)
{
	Vec3f result;

	for (int axis = 0; axis < 3; axis++)
	{
		float v = target[axis];
				
		v = std::max(v, minPoint[axis]);
		v = std::min(v, maxPoint[axis]);
		
		result[axis] = v;
	}

	return result;
}

Vec3f AABB::closestPointInAABB(const Sphere& sphere)
{
	return closestPointInAABB(sphere.center);
}

AABB AABB::buildFrom(const Vec3List<float>& pointList)
{
	int* indexes = pointList.findExtremePointsAlongAxisXYZ();

	return AABB(
		Vec3f(
			pointList.points[indexes[0]].x,
			pointList.points[indexes[2]].y,
			pointList.points[indexes[4]].z
			), 
		Vec3f(
			pointList.points[indexes[1]].x,
			pointList.points[indexes[3]].y,
			pointList.points[indexes[5]].z
		)
	);
}

AABB AABB::buildFrom(const Sphere& sphere)
{	
	return AABB(
		Vec3f(
			sphere.center.x - sphere.ray,
			sphere.center.y - sphere.ray,
			sphere.center.z - sphere.ray
			),
		Vec3f(
			sphere.center.x + sphere.ray,
			sphere.center.y + sphere.ray,
			sphere.center.z + sphere.ray
			)
		);
}

AABB AABB::enclose(const AABB& aabb)
{
	return AABB(
		Vec3f(
			std::min(this->minPoint.x, aabb.minPoint.x),
			std::min(this->minPoint.y, aabb.minPoint.y),
			std::min(this->minPoint[2], aabb.minPoint.z)
		),
		Vec3f(
			std::max(this->maxPoint.x, aabb.maxPoint.x),
			std::max(this->maxPoint.y, aabb.maxPoint.y),
			std::max(this->maxPoint.z, aabb.maxPoint.z)
		)
	);
}

AABB AABB::enclose(const Sphere& sphere)
{
	return enclose(AABB::buildFrom(sphere));
}

bool AABB::operator==(const AABB& aabb) const
{
	return this->minPoint == aabb.minPoint 
		&& this->maxPoint == aabb.maxPoint;
}

bool AABB::operator!=(const AABB& aabb) const
{
	return ! (*this == aabb);
}

bool AABB::operator<(const AABB& aabb) const
{
	if (this->minPoint.x < aabb.minPoint.x)
		return true;

	if (this->minPoint.y < aabb.minPoint.y)
		return true;

	if (this->minPoint.z < aabb.minPoint.z)
		return true;

	return false;
}

bool AABB::operator>(const AABB& aabb) const
{
	if (this->maxPoint.x > aabb.maxPoint.x)
		return true;

	if (this->maxPoint.y > aabb.maxPoint.y)
		return true;

	if (this->maxPoint.z > aabb.maxPoint.z)
		return true;

	return false;
}

size_t AABB::operator()(const AABB& aabb) const
{
	float hash = 1.0f;
	const float constant = 3.0f;

	hash = constant * hash + aabb.minPoint.x;
	hash = constant * hash + aabb.minPoint.y;
	hash = constant * hash + aabb.minPoint.z;
	hash = constant * hash + aabb.maxPoint.x;
	hash = constant * hash + aabb.maxPoint.y;
	hash = constant * hash + aabb.maxPoint.z;

	return size_t(hash);
}

bool AABB::operator()(const AABB& aabb1, const AABB& aabb2) const
{
	return aabb1 == aabb2;
}
