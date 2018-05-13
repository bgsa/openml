#include "Point3D.h"

using namespace OpenML;

template<typename T>
Point3D<T>::Point3D() {
}

template<typename T>
Point3D<T>::Point3D(T x, T y, T z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

template<typename T>
Point3D<T>::Point3D(Vec3<T> vector) {
	this->x = vector[0];
	this->y = vector[1];
	this->z = vector[2];
}

template<typename T>
Point3D<T>::Point3D(T* values) {
	this->x = values[0];
	this->y = values[1];
	this->z = values[2];
}

template<typename T>
T Point3D<T>::distance(Point3D<T> otherPoint)
{
	T distance = toVec3().distance(otherPoint.toVec3());
	return distance;
}

template<typename T>
Vec3<T> Point3D<T>::toVec3()
{
	return Vec3<T>(x, y, z);
}

template<typename T>
bool Point3D<T>::operator==(const Point3D<T> &other) const
{
	return x == other.x
		&& y == other.y
		&& z == other.z;
}

template<typename T>
bool Point3D<T>::operator!=(const Point3D<T> &other) const
{
	return x != other.x
		|| y != other.y
		|| z != other.z;
}

template<typename T>
Point3D<T> API_INTERFACE Point3D<T>::findMinX(Point3D<T>* points, size_t pointsCount) 
{
	Point3D<T> minXValue = points[0];

	for (size_t i = 1; i < pointsCount; i++)
		if (points[i].x < minXValue.x)
			minXValue = points[i];

	return minXValue;
}

template<typename T>
Point3D<T> API_INTERFACE Point3D<T>::findMinY(Point3D<T>* points, size_t pointsCount)
{
	Point3D<T> minYValue = points[0];

	for (size_t i = 1; i < pointsCount; i++)
		if (points[i].y < minYValue.y)
			minYValue = points[i];

	return minYValue;
}

template<typename T>
Point3D<T> API_INTERFACE Point3D<T>::findMinZ(Point3D<T>* points, size_t pointsCount)
{
	Point3D<T> minZValue = points[0];

	for (size_t i = 1; i < pointsCount; i++)
		if (points[i].z < minZValue.z)
			minZValue = points[i];

	return minZValue;
}

template<typename T>
Point3D<T> API_INTERFACE Point3D<T>::findMaxX(Point3D<T>* points, size_t pointsCount)
{
	Point3D<T> maxXValue = points[0];

	for (size_t i = 1; i < pointsCount; i++)
		if (points[i].x > maxXValue.x)
			maxXValue = points[i];

	return maxXValue;
}

template<typename T>
Point3D<T> API_INTERFACE Point3D<T>::findMaxY(Point3D<T>* points, size_t pointsCount)
{
	Point3D<T> maxYValue = points[0];

	for (size_t i = 1; i < pointsCount; i++)
		if (points[i].y > maxYValue.y)
			maxYValue = points[i];

	return maxYValue;
}

template<typename T>
Point3D<T> API_INTERFACE Point3D<T>::findMaxZ(Point3D<T>* points, size_t pointsCount)
{
	Point3D<T> maxZValue = points[0];

	for (size_t i = 1; i < pointsCount; i++)
		if (points[i].z > maxZValue.z)
			maxZValue = points[i];

	return maxZValue;
}


template class Point3D<int>;
template class Point3D<float>;
template class Point3D<double>;