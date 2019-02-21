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
ColisionStatus Sphere<T>::colisionStatus(const Plane3D<T> &plane)  const
{
	T distanceToPlane = plane.distance(center);

	if (isCloseEnough(distanceToPlane, ray))
		return ColisionStatus::INLINE;

	if (distanceToPlane > ray)
		return ColisionStatus::OUTSIDE;

	return ColisionStatus::INSIDE;
}

namespace OpenML
{
	template class Sphere<int>;
	template class Sphere<float>;
	template class Sphere<double>;
}