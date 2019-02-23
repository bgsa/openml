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
Vec3<T> Line3D<T>::direction() const
{
	return (point2 - point1).normalize();
}

template <typename T>
bool Line3D<T>::isOnLine(const Vec3<T>& point) const
{
	Vec3<T> lineDirection = point2 - point1;

	bool isOnTheLine = lineDirection.cross(point) == T(0);

	return isOnTheLine;
}

template <typename T>
bool Line3D<T>::isOnSegment(const Vec3<T>& point) const
{
	Vec3<T> lineDirection = point2 - point1;

	bool isOnTheLine = lineDirection.cross(point) == T(0);

	if (!isOnTheLine)
		return false;
	
	T ab = lineDirection.dot(lineDirection);
	T ac = lineDirection.dot(point - point1);
	
	if (ac < T(0) || ac > ab)
		return false;

	return (T(0) <= ac && ac <= ab);
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
	T denominador = dAcrossB.squaredLength();

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
bool Line3D<T>::hasIntersectionOnRay(const Sphere<T>& sphere) const
{	
	Vec3<T> m = point1 - sphere.center; 
	T c = m.dot(m) - sphere.ray * sphere.ray;
	
	// If there is definitely at least one real root, there must be an intersection 
	if (c <= T(0)) 
		return true; 
	
	Vec3<T> d = point2 - point1;

	T b = m.dot(d); 
	
	// Early exit if ray origin outside sphere and ray pointing away from sphere 
	if (b > T(0)) 
		return false; 
	
	T disc = b*b - c; 
	
	// A negative discriminant corresponds to ray missing sphere 
	if (disc < T(0)) 
		return false; // Now ray must hit sphere 
	
	return true;
}

template <typename T>
Vec3<T>* Line3D<T>::findIntersectionOnSegment(const Plane3D<T>& plane) const 
{
	Vec3<T> lineDirection = point2 - point1;
	T d = plane.getDcomponent();

	// Segment = Poin1 + t . (Point2 - Point1)
	// Plane: (n . X) = d
	// put the line on the plane, Compute the t value for the directed line ab intersecting the plane.
	T t = (d - plane.normalVector.dot(point1)) / plane.normalVector.dot(lineDirection);
	
	// If t in [0..1] compute and return intersection point 
	if (t >= T(0) && t <= T(1)) 
	{
		Vec3<T> intersectionPoint = point1 + t * lineDirection;
		return new Vec3<T>(intersectionPoint);
	}

	return nullptr;
}

template <typename T>
DetailedColisionStatus<T> Line3D<T>::findIntersectionOnRay(const Sphere<T>& sphere) const
{
	Vec3<T> lineDirection = direction();
	Vec3<T> point1ToSphere = point1 - sphere.center;

	T b = point1ToSphere.dot(lineDirection);
	T c = point1ToSphere.dot(point1ToSphere) - (sphere.ray * sphere.ray);
	
	// Exit if r’s origin outside sphere (c > 0) and ray pointing away from sphere (b > 0) 
	if (c > T(0) && b > T(0))
		return DetailedColisionStatus<T>(ColisionStatus::OUTSIDE); 
	
	T discriminant = b * b - c;    // d = b^2 - c
	
	// A negative discriminant corresponds to ray missing sphere 
	if (discriminant < T(0)) // the quadratic equation has not real root
		return DetailedColisionStatus<T>(ColisionStatus::OUTSIDE);

	T sqrtDisctiminant = T(std::sqrt(discriminant));

	// Ray now found to intersect sphere, compute smallest t value of intersection 
	T t1 = -b - sqrtDisctiminant;   // -b - sqrt(b^2 - c)

	// If t is negative, ray started inside sphere so clamp t to zero 	
	if (t1 < T(0))
		t1 = T(0);

	Vec3<T> intersectionPoint1 = point1 + t1 * lineDirection;
	
	if (isCloseEnough(discriminant, T(0))) 
		return DetailedColisionStatus<T>(ColisionStatus::INLINE, intersectionPoint1);

	// discriminant > T(0)  =>  the quadratic equation has 2 real root, then the ray intersect in 2 points

	// Ray now found to intersect sphere in 2 points, compute bigger t value of intersection 
	T t2 = -b + sqrtDisctiminant;   // -b + sqrt(b^2 - c)
	
	Vec3<T> intersectionPoint2 = point1 + t2 * lineDirection;

	return DetailedColisionStatus<T>(ColisionStatus::INSIDE, intersectionPoint1, intersectionPoint2);
}

template <typename T>
DetailedColisionStatus<T> Line3D<T>::findIntersectionOnSegment(const Sphere<T>& sphere) const
{
	DetailedColisionStatus<T> colision = findIntersectionOnRay(sphere);

	if (colision.status == ColisionStatus::OUTSIDE)
		return colision;

	if (!isOnSegment(colision.points[0]))
		return DetailedColisionStatus<T>(ColisionStatus::OUTSIDE);

	if (!isOnSegment(colision.points[1]))
		return DetailedColisionStatus<T>(ColisionStatus::INSIDE, colision.points[0]);

	return colision;
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