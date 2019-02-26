#include "Sphere.h"

template <typename T>
Sphere<T>::Sphere()
{
	this->center = Vec3<T>(T(0));
	this->ray = T(1);
}

template <typename T>
Sphere<T>::Sphere(const Vec3<T> &center, T ray)
{
	this->center = center;
	this->ray = ray;
}

template <typename T>
Sphere<T>::Sphere(const Vec3<T> &point1, const Vec3<T> &point2)
{
	Line3D<T> line = Line3D<T>(point1, point2);
	this->center = line.centerOfSegment();
	this->ray = line.lengthOfSegment() / T(2);
}

template <typename T>
Sphere<T>::Sphere(const Vec3<T> &point1, const Vec3<T> &point2, const Vec3<T> &point3)
{
	// triangle "edges"
	const Vec3<T> edge1 = point2 - point1;
	const Vec3<T> edge2 = point3 - point1;
	const Vec3<T> edge3 = point3 - point2;

	// triangle normal
	const Vec3<T> normal = edge1.cross(edge2);
	const T normalLength = normal.length();

	if (normalLength < 10e-14)
		return; // area of the triangle is too small (you may additionally check the points for colinearity if you are paranoid)

	// helpers
	const T iwsl2 = T(1) / ( T(2) * normalLength);
	const T tt = edge1.dot(edge1);
	const T uu = edge2.dot(edge2);

	// result circle
	this->center = point1 + (edge2 * tt * (edge2.dot(edge3)) - edge1 * uu * (edge1.dot(edge3))) * iwsl2;
	this->ray = T(std::sqrt(tt * uu * edge3.dot(edge3) * iwsl2 * T(0.5)));
	//this->ray = w / sqrt(wsl);
}
template <typename T>
Sphere<T>::Sphere(const Vec3<T> &point1, const Vec3<T> &point2, const Vec3<T> &point3, const Vec3<T> &point4)
{
	Mat4<T> m = Mat4<T>(
		Vec4<T>(point1, T(1)),
		Vec4<T>(point2, T(1)),
		Vec4<T>(point3, T(1)),
		Vec4<T>(point4, T(1))
		);

	T invertedDeterminant = T(1) / m.determinant();

	T t1 = -(point1.dot(point1));
	T t2 = -(point2.dot(point2));
	T t3 = -(point3.dot(point3));
	T t4 = -(point4.dot(point4));

	m = Mat4<T>(
		Vec4<T>(t1, point1[1], point1[2], T(1)),
		Vec4<T>(t2, point2[1], point2[2], T(1)),
		Vec4<T>(t3, point3[1], point3[2], T(1)),
		Vec4<T>(t4, point4[1], point4[2], T(1))
		);
	T a = m.determinant() * invertedDeterminant;
	T x = a * T(-0.5);

	m = Mat4<T>(
		Vec4<T>(point1[0], t1, point1[2], T(1)),
		Vec4<T>(point2[0], t2, point2[2], T(1)),
		Vec4<T>(point3[0], t3, point3[2], T(1)),
		Vec4<T>(point4[0], t4, point4[2], T(1))
		);
	T b = m.determinant() * invertedDeterminant;
	T y = b * T(-0.5);

	m = Mat4<T>(
		Vec4<T>(point1[0], point1[1], t1, T(1)),
		Vec4<T>(point2[0], point2[1], t2, T(1)),
		Vec4<T>(point3[0], point3[1], t3, T(1)),
		Vec4<T>(point4[0], point4[1], t4, T(1))
		);
	T c = m.determinant() * invertedDeterminant;
	T z = c * T(-0.5);

	m = Mat4<T>(
		Vec4<T>(point1[0], point1[1], point1[2], t1),
		Vec4<T>(point2[0], point2[1], point2[2], t2),
		Vec4<T>(point3[0], point3[1], point3[2], t3),
		Vec4<T>(point4[0], point4[1], point4[2], t4)
		);
	T d = m.determinant() * invertedDeterminant;

	center = { x, y, z };
	ray = T(std::sqrt(a * a + b * b + c * c - 4 * d)) / T(2);
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