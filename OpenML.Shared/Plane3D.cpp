#pragma once

#include "Plane3D.h"

Plane3D::Plane3D() {	};

Plane3D::Plane3D(const Vec3f& point, const Vec3f& vector)
{
	this->point = point;
	this->normalVector = vector;
}

Plane3D::Plane3D(const Vec3f& point1, const Vec3f& point2, const Vec3f& point3)
{
	Vec3f ab = point1 - point2;
	Vec3f ac = point1 - point3;

	point = point2;

	normalVector = Vec3f{
		ab[1] * ac[2] - (ab[2] * ac[1]),
		ab[2] * ac[0] - (ab[0] * ac[2]),
		ab[0] * ac[1] - (ab[1] * ac[0])
	}.normalize();
}

Plane3D::Plane3D(float a, float b, float c, float d)
{
	point = Vec3f(
		0.0f,
		0.0f,
		-d / c
		);

	normalVector = Vec3f(a, b, c).normalize();
}

float Plane3D::getDcomponent() const
{
	return -normalVector.dot(point);
	//return normalVector.dot(point);
}

Vec4f Plane3D::getEquation() const
{
	return Vec4f(
		normalVector[0],
		normalVector[1],
		normalVector[2],
		getDcomponent()
		);
}

Vec3f* Plane3D::findIntersection(const Line3D& line) const
{
	Vec3f lineAsVector = line.point2 - line.point1;

	float angle = normalVector.dot(lineAsVector);

	if (angle == 0.0f)
		return nullptr;

	Vec4f planeEquation = getEquation();

	float numerator = -(planeEquation[0] * line.point1[0] + planeEquation[1] * line.point1[1] + planeEquation[2] * line.point1[2] + planeEquation[3]);
	float denominator = planeEquation[0] * lineAsVector[0] + planeEquation[1] * lineAsVector[1] + planeEquation[2] * lineAsVector[2];

	float t = numerator / denominator;

	Vec3f* intersection = ALLOC_NEW(Vec3f)(
		line.point1[0] + lineAsVector[0] * t,
		line.point1[1] + lineAsVector[1] * t,
		line.point1[2] + lineAsVector[2] * t
		);

	return intersection;
}

Line3D* Plane3D::findIntersection(const Plane3D& plane) const
{
	if (isParallel(plane))
		return nullptr;

	Vec3f lineDirection = normalVector.cross(plane.normalVector);
	
	float d1 = getDcomponent();
	float d2 = plane.getDcomponent();

	// find a point on the line, which is also on both planes
	float dot = lineDirection.dot(lineDirection);					// V dot V
	Vec3f u1 = normalVector * d2;								// d2 * normalVector
	Vec3f u2 = plane.normalVector * -d1;					    //-d1 * plane.normalVector
	Vec3f point1 = (u1 + u2).cross(lineDirection) / dot;      // (d2*N1-d1*N2) X V / V dot V

	// find another point on the line
	Vec3f point2 = point1 + lineDirection;

	return ALLOC_NEW(Line3D)(point1, point2);
}

float Plane3D::distance(const Vec3f& target) const
{
	Vec3f rayToTarget = target - point;

	float numerator = normalVector.dot(rayToTarget);
	float length = normalVector.length();

	return numerator / length;
}

Vec3f Plane3D::closestPointOnThePlane(const Vec3f &target) const
{
	float d = getDcomponent();

	float t = (normalVector.dot(target) - d) / normalVector.dot(normalVector); //t = ((n . p) - d) / (n.n)

	return target - (normalVector * t); //result = point - tn
}

float Plane3D::angle(const Plane3D& plane) const
{
	float angle = normalVector.dot(plane.normalVector);
	float length = normalVector.length() * plane.normalVector.length();

	return angle / length;
}

Orientation Plane3D::orientation(const Vec3f& point) const
{
	float distanceToPoint =  distance(point);

	if (distanceToPoint == 0.0f)
		return Orientation::NONE;
	else if (distanceToPoint > 0.0f)
		return Orientation::LEFT;
	
	return Orientation::RIGHT;
}

bool Plane3D::isParallel(const Plane3D& plane) const
{
	return normalVector.cross(plane.normalVector) == 0.0f;
}

bool Plane3D::isPerpendicular(const Plane3D& plane) const
{
	return normalVector.dot(plane.normalVector) == 0.0f;
}
