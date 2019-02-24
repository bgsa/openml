#include "Vec3List.h"

template <typename T>
Vec3List<T>::Vec3List(Vec3<T>* points, size_t count)
{
	this->points = points;
	this->count = count;
}

template <typename T>
int* Vec3List<T>::findExtremePointsAlongDirection(const Vec3<T>& direction) const
{
	T minProjection = T(std::numeric_limits<double>().max());
	T maxProjection = -minProjection;

	int* result = new int[2];
		
	for (int i = 0; i < count; i++) 
	{ 
		// Project vector from origin to point onto direction vector 
		T projection = points[i].dot(direction);
		
		if (projection < minProjection)
		{ 
			minProjection = projection;
			result[0] = i;
		} 
		
		if (projection > maxProjection)
		{ 
			maxProjection = projection;
			result[1] = i;
		} 
	}
	
	return result;
}

template <typename T>
int* Vec3List<T>::findExtremePointsAlongAxisX() const
{
	return findExtremePointsAlongDirection(Vec3<T>(T(1), T(0), T(0)));
}

template <typename T>
int* Vec3List<T>::findExtremePointsAlongAxisY() const
{
	return findExtremePointsAlongDirection(Vec3<T>(T(0), T(1), T(0)));
}

template <typename T>
int* Vec3List<T>::findExtremePointsAlongAxisZ() const
{
	return findExtremePointsAlongDirection(Vec3<T>(T(0), T(0), T(1)));
}


template <typename T>
Vec3List<T>::~Vec3List()
{
	if (points != nullptr)
	{
		delete[] points;
		points = nullptr;
		count = 0;
	}
}

namespace OpenML
{
	template class Vec3List<int>;
	template class Vec3List<float>;
	template class Vec3List<double>;
}