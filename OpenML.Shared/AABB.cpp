#include "AABB.h"

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
		minPoint[0] + width,
		minPoint[1] + height,
		minPoint[2] + depth
		);
}

template <typename T>
Vec3<T> AABB<T>::center()
{
	return (maxPoint + minPoint) * T(0.5);
}

template <typename T>
ColisionStatus AABB<T>::colisionStatus(const AABB<T>& aabb) 
{
	if (maxPoint[0] < aabb.minPoint[0] || minPoint[0] > aabb.maxPoint[0])
		return ColisionStatus::OUTSIDE;

	if (maxPoint[1] < aabb.minPoint[1] || minPoint[1] > aabb.maxPoint[1])
		return ColisionStatus::OUTSIDE;

	if (maxPoint[2] < aabb.minPoint[2] || minPoint[2] > aabb.maxPoint[2])
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
		  halfDistanceFromCenter[0] * std::abs(plane.normalVector[0])
		+ halfDistanceFromCenter[1] * std::abs(plane.normalVector[1])
		+ halfDistanceFromCenter[2] * std::abs(plane.normalVector[2]);
	
	double distanceFromAABB2Plane = std::abs(plane.normalVector.dot(centerPoint) + d);
	
	if (isCloseEnough(distanceFromAABB2Plane, r))
		return ColisionStatus::INLINE;

	// it has intersection when distance falls within [-r,+r] interval 	

	if (distanceFromAABB2Plane <= r)  
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

namespace OpenML
{
	template class AABB<int>;
	template class AABB<float>;
	template class AABB<double>;
}
