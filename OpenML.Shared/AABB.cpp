#include "AABB.h"

template <typename T>
AABB<T>::AABB()
{
	this->minPoint = Vec3<T>(T(-0.5f));
	this->maxPoint = -this->minPoint;
}

template <typename T>
AABB<T>::AABB(Vec3<T> minPoint, Vec3<T> maxPoint)
{
	this->minPoint = minPoint;
	this->maxPoint = maxPoint;
}

template <typename T>
AABB<T>::AABB(Vec3<T> minPoint, T width, T height, T depth) 
{
	this->minPoint = minPoint;

	maxPoint = Vec3<T>(
		minPoint.x + width,
		minPoint.y + height,
		minPoint.z + depth
		);
}

template <typename T>
Vec3<T> AABB<T>::center() const
{
	return (maxPoint + minPoint) * T(0.5);
}

template <typename T>
Vec3<T> AABB<T>::centerOfBoundingVolume() const
{
	return center();
}

template <typename T>
T AABB<T>::squaredDistance(const Vec3<T>& target)
{
	T result = T(0);

	// For each axis count any excess distance outside box extents 
	for (int axis = 0; axis < 3; axis++)
	{
		T v = target[axis];

		if (v < minPoint[axis])
			result += (minPoint[axis] - v) * (minPoint[axis] - v);

		if (v > maxPoint[axis])
			result += (v - maxPoint[axis]) * (v - maxPoint[axis]);
	}

	return result;
}

template <typename T>
T AABB<T>::distance(const Vec3<T>& target)
{
	return T(sqrt(squaredDistance(target)));
}

template <typename T>
ColisionStatus AABB<T>::colisionStatus(const AABB<T>& aabb) 
{
	if (maxPoint.x < aabb.minPoint.x || minPoint.x > aabb.maxPoint.x)
		return ColisionStatus::OUTSIDE;

	if (maxPoint.y < aabb.minPoint.y || minPoint.y > aabb.maxPoint.y)
		return ColisionStatus::OUTSIDE;

	if (maxPoint.z < aabb.minPoint.z || minPoint.z > aabb.maxPoint.z)
		return ColisionStatus::OUTSIDE;

	return ColisionStatus::INSIDE;
}

template <typename T>
ColisionStatus AABB<T>::colisionStatus(const Plane3D<T>& plane)
{
	Vec3<T> centerPoint = center(); 
	T d = plane.getDcomponent();	
	Vec3<T> halfDistanceFromCenter = maxPoint - centerPoint;

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

template <typename T>
ColisionStatus AABB<T>::colisionStatus(const Sphere<T>& sphere)
{
	T distanceToSphere = squaredDistance(sphere.center);
	T squaredRay = sphere.ray * sphere.ray;
	
	if (isCloseEnough(distanceToSphere, squaredRay))
		return ColisionStatus::INLINE;

	if (distanceToSphere < squaredRay)
		return ColisionStatus::INSIDE;

	return ColisionStatus::OUTSIDE;
}

template <typename T>
Vec3<T> AABB<T>::closestPointInAABB(const Vec3<T>& target)
{
	Vec3<T> result;

	for (int axis = 0; axis < 3; axis++)
	{
		T v = target[axis];
				
		v = std::max(v, minPoint[axis]);
		v = std::min(v, maxPoint[axis]);
		
		result[axis] = v;
	}

	return result;
}

template <typename T>
Vec3<T> AABB<T>::closestPointInAABB(const Sphere<T>& sphere)
{
	return closestPointInAABB(sphere.center);
}

template <typename T>
AABB<T> AABB<T>::buildFrom(const Vec3List<T>& pointList)
{
	int* indexes = pointList.findExtremePointsAlongAxisXYZ();

	return AABB<T>(
		Vec3<T>(
			pointList.points[indexes[0]].x,
			pointList.points[indexes[2]].y,
			pointList.points[indexes[4]].z
			), 
		Vec3<T>(
			pointList.points[indexes[1]].x,
			pointList.points[indexes[3]].y,
			pointList.points[indexes[5]].z
		)
	);
}

template <typename T>
AABB<T> AABB<T>::buildFrom(const Sphere<T>& sphere)
{	
	return AABB<T>(
		Vec3<T>(
			sphere.center.x - sphere.ray,
			sphere.center.y - sphere.ray,
			sphere.center.z - sphere.ray
			),
		Vec3<T>(
			sphere.center.x + sphere.ray,
			sphere.center.y + sphere.ray,
			sphere.center.z + sphere.ray
			)
		);
}

template <typename T>
AABB<T> AABB<T>::enclose(const AABB<T>& aabb)
{
	return AABB<T>(
		Vec3<T>(
			std::min(this->minPoint.x, aabb.minPoint.x),
			std::min(this->minPoint.y, aabb.minPoint.y),
			std::min(this->minPoint[2], aabb.minPoint.z)
		),
		Vec3<T>(
			std::max(this->maxPoint.x, aabb.maxPoint.x),
			std::max(this->maxPoint.y, aabb.maxPoint.y),
			std::max(this->maxPoint.z, aabb.maxPoint.z)
		)
	);
}

template <typename T>
AABB<T> AABB<T>::enclose(const Sphere<T>& sphere)
{
	return enclose(AABB<T>::buildFrom(sphere));
}

template <typename T>
bool AABB<T>::operator==(const AABB<T>& aabb) const
{
	return this->minPoint == aabb.minPoint 
		&& this->maxPoint == aabb.maxPoint;
}

template <typename T>
bool AABB<T>::operator!=(const AABB<T>& aabb) const
{
	return ! (*this == aabb);
}

template <typename T>
bool AABB<T>::operator<(const AABB<T>& aabb) const
{
	if (this->minPoint.x < aabb.minPoint.x)
		return true;

	if (this->minPoint.y < aabb.minPoint.y)
		return true;

	if (this->minPoint.z < aabb.minPoint.z)
		return true;

	return false;
}

template <typename T>
bool AABB<T>::operator>(const AABB<T>& aabb) const
{
	if (this->maxPoint.x > aabb.maxPoint.x)
		return true;

	if (this->maxPoint.y > aabb.maxPoint.y)
		return true;

	if (this->maxPoint.z > aabb.maxPoint.z)
		return true;

	return false;
}

template <typename T>
size_t AABB<T>::operator()(const AABB<T>& aabb) const
{
	T hash = T(1);
	const T constant = T(3);

	hash = constant * hash + aabb.minPoint.x;
	hash = constant * hash + aabb.minPoint.y;
	hash = constant * hash + aabb.minPoint.z;
	hash = constant * hash + aabb.maxPoint.x;
	hash = constant * hash + aabb.maxPoint.y;
	hash = constant * hash + aabb.maxPoint.z;

	return size_t(hash);
}

template <typename T>
bool AABB<T>::operator()(const AABB<T>& aabb1, const AABB<T>& aabb2) const
{
	return aabb1 == aabb2;
}

namespace OpenML
{
	template class AABB<int>;
	template class AABB<float>;
	template class AABB<double>;
}
