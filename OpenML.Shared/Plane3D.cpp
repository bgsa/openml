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
Plane3D<T>::Plane3D(T a, T b, T c, T d)
{
	point = Vec3<T>(
		T(0),
		T(0),
		-d / c
		);

	normalVector = Vec3<T>(a, b, c).normalize();
}

template <typename T>
T Plane3D<T>::getDcomponent() const
{
	return (normalVector * T(-1)).dot(point);
}

template <typename T>
Vec4<T> Plane3D<T>::getEquation() const
{
	return Vec4<T>(
		normalVector[0],
		normalVector[1],
		normalVector[2],
		getDcomponent()
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

template <typename T>
Line3D<T>* Plane3D<T>::findIntersection(const Plane3D<T>& plane) const
{
	if (isParallel(plane))
		return nullptr;

	Vec3<T> lineDirection = normalVector.cross(plane.normalVector);
	
	T d1 = getDcomponent();
	T d2 = plane.getDcomponent();

	// find a point on the line, which is also on both planes
	T dot = lineDirection.dot(lineDirection);					// V dot V
	Vec3<T> u1 = normalVector * d2;								// d2 * normalVector
	Vec3<T> u2 = plane.normalVector * -d1;					    //-d1 * plane.normalVector
	Vec3<T> point1 = (u1 + u2).cross(lineDirection) / dot;      // (d2*N1-d1*N2) X V / V dot V

	// find another point on the line
	Vec3<T> point2 = point1 + lineDirection;

	return new Line3D<T>(point1, point2);
}

template <typename T>
T Plane3D<T>::distance(const Vec3<T>& target)
{
	Vec3<T> rayToTarget = target - point;

	T numerator = normalVector.dot(rayToTarget);
	T length = normalVector.length();

	return numerator / length;
}

template <typename T>
T Plane3D<T>::angle(const Plane3D<T>& plane)
{
	T angle = normalVector.dot(plane.normalVector);
	T length = normalVector.length() * plane.normalVector.length();

	return angle / length;
}

template <typename T>
Orientation Plane3D<T>::orientation(const Vec3<T>& point)
{
	T distanceToPoint =  distance(point);

	if (distanceToPoint == T(0))
		return Orientation::NONE;
	else if (distanceToPoint > T(0))
		return Orientation::LEFT;
	
	return Orientation::RIGHT;
}

template <typename T>
bool Plane3D<T>::isParallel(const Plane3D<T>& plane) const
{
	return normalVector.cross(plane.normalVector) == T(0);
}

template <typename T>
bool Plane3D<T>::isPerpendicular(const Plane3D<T>& plane) const
{
	return normalVector.dot(plane.normalVector) == T(0);
}

namespace OpenML
{
	template class Plane3D<int>;
	template class Plane3D<float>;
	template class Plane3D<double>;
}