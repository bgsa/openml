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

namespace OpenML
{
	template class AABB<int>;
	template class AABB<float>;
	template class AABB<double>;
}
