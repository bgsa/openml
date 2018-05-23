#pragma once

#include "Plane3D.h"

template <typename T>
Plane3D<T>::Plane3D() {	};

template <typename T>
Plane3D<T>::Plane3D(const Point3D<T>& point, const Vec3<T>& vector)
{
	this->point = point;
	this->normalVector = vector;
}

template <typename T>
Plane3D<T>::Plane3D(const Point3D<T>& point1, const Point3D<T>& point2, const Point3D<T>& point3)
{
	Vec3<T> point1AsVec3 = point1.toVec3();
	Vec3<T> ab = point1AsVec3 - point2.toVec3();
	Vec3<T> ac = point1AsVec3 - point3.toVec3();

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
	T value = (normalVector * T(-1)).dot(point.toVec3());

	return Vec4<T>(
		normalVector[0],
		normalVector[1],
		normalVector[2],
		value
		);
}

template <typename T>
Point3D<T>* Plane3D<T>::findIntersection(const Line3D<T>& line) const
{
	Vec3<T> point1AsVec3 = line.point1.toVec3();
	Vec3<T> lineAsVector = line.point2.toVec3() - point1AsVec3;

	T angle = normalVector.dot(lineAsVector);

	if (angle == T(0))
		return nullptr;

	Vec4<T> planeEquation = getEquation();

	T numerator = -(planeEquation[0] * point1AsVec3[0] + planeEquation[1] * point1AsVec3[1] + planeEquation[2] * point1AsVec3[2] + planeEquation[3]);
	T denominator = planeEquation[0] * lineAsVector[0] + planeEquation[1] * lineAsVector[1] + planeEquation[2] * lineAsVector[2];

	T t = numerator / denominator;

	Point3D<T>* intersection = new Point3D<T>(
		point1AsVec3[0] + lineAsVector[0] * t,
		point1AsVec3[1] + lineAsVector[1] * t,
		point1AsVec3[2] + lineAsVector[2] * t
		);

	return intersection;
}


namespace OpenML
{
	template class Plane3D<int>;
	template class Plane3D<float>;
	template class Plane3D<double>;
}