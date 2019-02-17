#pragma once

#include "Line3D.h"

template <typename T>
Line3D<T>::Line3D() {	};

template <typename T>
Line3D<T>::Line3D(const Vec3<T>& point1, const Vec3<T>& point2)
{
	assert(point1 != point2);

	this->point1 = point1;
	this->point2 = point2;
}

template <typename T>
Line3D<T>::Line3D(Vec3<T>* points)
{
	assert(points[0] != points[1]);

	this->point1 = points[0];
	this->point2 = points[1];
}

template <typename T>
Line3D<T>::Line3D(T* point1, T* point2)
{
	assert(point1 != point2);

	this->point1 = Vec3<T>(point1[0], point1[1], point1[2]);
	this->point2 = Vec3<T>(point2[0], point2[1], point2[2]);
}

template <typename T>
Vec3<T>* Line3D<T>::findIntersection(const Line3D<T>& line2) const
{
	Vec3<T> da = point2 - point1;
	Vec3<T> db = line2.point2 - line2.point1;
	Vec3<T> dc = line2.point1 - point1;

	Vec3<T> dAcrossB = da.cross(db);

	T value = dc.dot(dAcrossB);

	if (value != T(0))
		return nullptr;

	T numerador = dc.cross(db).dot(dAcrossB);
	T denominador = dAcrossB.squared();

	T s = numerador / denominador;

	if (s >= 0 && s <= 1)
		return new Vec3<T>(da * s + point1);

	return nullptr;
}

namespace OpenML
{
	template class Line3D<int>;
	template class Line3D<float>;
	template class Line3D<double>;
}