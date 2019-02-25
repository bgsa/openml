#include "Sphere.h"

template <typename T>
Sphere<T>::Sphere(const Vec3<T> &center, T ray)
{
	this->center = center;
	this->ray = ray;
}

template <typename T>
ColisionStatus Sphere<T>::colisionStatus(const Vec3<T> &point)  const
{
	T distanceToPoint = center.distance(point);
	
	if (isCloseEnough(distanceToPoint, ray))
		return ColisionStatus::INLINE;

	if (distanceToPoint > ray)
		return ColisionStatus::OUTSIDE;

	return ColisionStatus::INSIDE;
}

template <typename T>
ColisionStatus Sphere<T>::colisionStatus(const Sphere<T>& sphere)  const
{
	Vec3<T> rayToSphere = center - sphere.center; 
	T squaredDistance = rayToSphere.dot(rayToSphere);

	// Spheres intersect if squared distance is less than squared sum of radius 
	T diameter = ray + sphere.ray;
	T squaredDiameter = diameter * diameter;

	if (isCloseEnough(squaredDistance, squaredDiameter))
		return ColisionStatus::INLINE;

	if (squaredDistance > squaredDiameter)
		return ColisionStatus::OUTSIDE;

	return ColisionStatus::INSIDE;
}

template <typename T>
ColisionStatus Sphere<T>::colisionStatus(const Plane3D<T> &plane)  const
{
	/*
	Implementation "1"
	T distanceToPlane = plane.distance(center);

	if (isCloseEnough(distanceToPlane, ray))
		return ColisionStatus::INLINE;

	if (distanceToPlane > ray)
		return ColisionStatus::OUTSIDE;

	return ColisionStatus::INSIDE;
	*/

	// optimized implementation

	T d = plane.getDcomponent();
	T distanceToPlane = center.dot(plane.normalVector) + d;

	if (isCloseEnough(distanceToPlane, ray))
		return ColisionStatus::INLINE;

	if (distanceToPlane > ray)
		return ColisionStatus::OUTSIDE;

	return ColisionStatus::INSIDE;
}

template <typename T>
Sphere<T> Sphere<T>::buildFrom(const AABB<T> &aabb)
{
	T maxDistance = aabb.maxPoint[0] - aabb.minPoint[0];

	maxDistance = std::max(maxDistance, aabb.maxPoint[1] - aabb.minPoint[1]);

	maxDistance = std::max(maxDistance, aabb.maxPoint[2] - aabb.minPoint[2]);

	return Sphere<T>(
		aabb.center(),
		maxDistance / T(2)
		);
}

namespace OpenML
{
	template class Sphere<int>;
	template class Sphere<float>;
	template class Sphere<double>;
}