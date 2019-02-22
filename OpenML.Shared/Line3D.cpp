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

template <typename T>
Vec3<T> Line3D<T>::closestPointOnTheLine(const Vec3<T>& target) const
{
	Vec3<T> lineDirection = point2 - point1;
	
	// Project target onto lineDirection, computing parameterized position closestPoint(t) = point1 + t*(point2 – point1) 
	T t = (target - point1).dot(lineDirection) / lineDirection.dot(lineDirection);

	// If outside segment, clamp t (and therefore d) to the closest endpoint 
	t = clamp(t, T(0), T(1)); // clamp t from 0.0 to 1.0
	
	//closestPoint(t) = point1 + t * (point2 – point1)
	Vec3<T> closestPoint = point1 + t*lineDirection;

	return closestPoint;
}

template <typename T>
T Line3D<T>::squaredDistance(const Vec3<T>& target) const
{
	//Returns the squared distance between point and segment point1-point2

	Vec3<T> ab = point2 - point1;
	Vec3<T> ac = target - point1;
	Vec3<T> bc = target - point2;
	
	T e = ac.dot(ab); // Handle cases where point projects outside the line segment
	
	if (e <= T(0)) 
		return ac.dot(ac); 
	
	T f = ab.dot(ab); 

	if (e >= f) 		
		return bc.dot(bc); // Handle cases where point projects onto line segment
	
	return ac.dot(ac) - e * e / f;
}

template <typename T>
T Line3D<T>::distance(const Vec3<T>& target) const
{
	return T(sqrt(squaredDistance(target)));
}

namespace OpenML
{
	template class Line3D<int>;
	template class Line3D<float>;
	template class Line3D<double>;
}