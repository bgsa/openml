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
int* Vec3List<T>::findExtremePointsAlongAxisXYZ() const
{
	T maxValue = T(std::numeric_limits<double>().max());

	T minProjectionX = maxValue;
	T maxProjectionX = -maxValue;

	T minProjectionY = maxValue;
	T maxProjectionY = -maxValue;

	T minProjectionZ = maxValue;
	T maxProjectionZ = -maxValue;

	Vec3<T> directionX = Vec3<T>(T(1), T(0), T(0));
	Vec3<T> directionY = Vec3<T>(T(0), T(1), T(0));
	Vec3<T> directionZ = Vec3<T>(T(0), T(0), T(1));

	int* result = new int[6];

	for (int i = 0; i < count; i++)
	{
		T projectionX = points[i].dot(directionX);
		T projectionY = points[i].dot(directionY);
		T projectionZ = points[i].dot(directionZ);

		if (projectionX < minProjectionX)
		{
			minProjectionX = projectionX;
			result[0] = i;
		}
		if (projectionX > maxProjectionX)
		{
			maxProjectionX = projectionX;
			result[1] = i;
		}

		if (projectionY < minProjectionY)
		{
			minProjectionY = projectionY;
			result[2] = i;
		}
		if (projectionY > maxProjectionY)
		{
			maxProjectionY = projectionY;
			result[3] = i;
		}

		if (projectionZ < minProjectionZ)
		{
			minProjectionZ = projectionZ;
			result[4] = i;
		}
		if (projectionZ > maxProjectionZ)
		{
			maxProjectionZ = projectionZ;
			result[5] = i;
		}
	}

	return result;
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