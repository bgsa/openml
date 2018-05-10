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

template class Point3D<int>;
template class Point3D<float>;
template class Point3D<double>;