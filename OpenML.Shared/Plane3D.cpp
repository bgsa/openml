#pragma once

#include "Plane3D.h"

template <typename T>
Plane3D<T>::Plane3D() {	};

template <typename T>
Plane3D<T>::Plane3D(const Vec3<T>& point, const Vec3<T>& vector)
{
	this->point = point;
	this->normalVector = vector;
}

template <typename T>
Plane3D<T>::Plane3D(const Vec3<T>& point1, const Vec3<T>& point2, const Vec3<T>& point3)
{
	Vec3<T> ab = point1 - point2;
	Vec3<T> ac = point1 - point3;

	point = point2;

	normalVector = Vec3<T>{
		ab[1] * ac[2] - (ab[2] * ac[1]),
		ab[2] * ac[0] - (ab[0] * ac[2]),
		ab[0] * ac[1] - (ab[1] * ac[0])
	}.normalize();
}

template <typename T>
Vec4<T> Plane3D<T>::getEquation() const
{
	T value = (normalVector * T(-1)).dot(point);

	return Vec4<T>(
		normalVector[0],
		normalVector[1],
		normalVector[2],
		value
		);
}

template <typename T>
Vec3<T>* Plane3D<T>::findIntersection(const Line3D<T>& line) const
{
	Vec3<T> lineAsVector = line.point2 - line.point1;

	T angle = normalVector.dot(lineAsVector);

	if (angle == T(0))
		return nullptr;

	Vec4<T> planeEquation = getEquation();

	T numerator = -(planeEquation[0] * line.point1[0] + planeEquation[1] * line.point1[1] + planeEquation[2] * line.point1[2] + planeEquation[3]);
	T denominator = planeEquation[0] * lineAsVector[0] + planeEquation[1] * lineAsVector[1] + planeEquation[2] * lineAsVector[2];

	T t = numerator / denominator;

	Vec3<T>* intersection = new Vec3<T>(
		line.point1[0] + lineAsVector[0] * t,
		line.point1[1] + lineAsVector[1] * t,
		line.point1[2] + lineAsVector[2] * t
		);

	return intersection;
}


namespace OpenML
{
	template class Plane3D<int>;
	template class Plane3D<float>;
	template class Plane3D<double>;
}