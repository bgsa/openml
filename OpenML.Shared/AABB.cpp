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

namespace OpenML
{
	template class AABB<int>;
	template class AABB<float>;
	template class AABB<double>;
}
