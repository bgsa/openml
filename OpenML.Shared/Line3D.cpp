#pragma once

#include "Line3D.h"

Line3D::Line3D() {	};

Line3D::Line3D(const Vec3f& point1, const Vec3f& point2)
{
	assert(point1 != point2);

	this->point1 = point1;
	this->point2 = point2;
}

Line3D::Line3D(Vec3f* points)
{
	assert(points[0] != points[1]);

	this->point1 = points[0];
	this->point2 = points[1];
}

Line3D::Line3D(float* point1, float* point2)
{
	assert(point1 != point2);

	this->point1 = Vec3f(point1[0], point1[1], point1[2]);
	this->point2 = Vec3f(point2[0], point2[1], point2[2]);
}

Vec3f Line3D::direction() const
{
	return (point2 - point1).normalize();
}

Vec3f Line3D::centerOfSegment() const
{
	return (point1 + point2) * 0.5f;
}

float Line3D::lengthOfSegment() const
{
	return point1.distance(point2);
}

bool Line3D::isOnLine(const Vec3f& point) const
{
	Vec3f lineDirection = point2 - point1;

	bool isOnTheLine = lineDirection.cross(point) == 0.0f;

	return isOnTheLine;
}

bool Line3D::isOnSegment(const Vec3f& point) const
{
	Vec3f lineDirection = point2 - point1;

	bool isOnTheLine = lineDirection.cross(point) == 0.0f;

	if (!isOnTheLine)
		return false;
	
	float ab = lineDirection.dot(lineDirection);
	float ac = lineDirection.dot(point - point1);
	
	if (ac < 0.0f || ac > ab)
		return false;

	return (0.0f <= ac && ac <= ab);
}

Vec3f* Line3D::findIntersection(const Line3D& line2) const
{
	Vec3f da = point2 - point1;
	Vec3f db = line2.point2 - line2.point1;
	Vec3f dc = line2.point1 - point1;

	Vec3f dAcrossB = da.cross(db);

	float value = dc.dot(dAcrossB);

	if (value != 0.0f)
		return nullptr;

	float numerador = dc.cross(db).dot(dAcrossB);
	float denominador = dAcrossB.squaredLength();

	float s = numerador / denominador;

	if (s >= 0 && s <= 1)
		return ALLOC_NEW(Vec3f)(da * s + point1);

	return nullptr;
}

Vec3f Line3D::closestPointOnTheLine(const Vec3f& target) const
{
	Vec3f lineDirection = point2 - point1;
	
	// Project target onto lineDirection, computing parameterized position closestPoint(t) = point1 + t*(point2 – point1) 
	float t = (target - point1).dot(lineDirection) / lineDirection.dot(lineDirection);

	// If outside segment, clamp t (and therefore d) to the closest endpoint 
	t = clamp(t, 0.0f, 1.0f); // clamp t from 0.0 to 1.0
	
	//closestPoint(t) = point1 + t * (point2 – point1)
	Vec3f closestPoint = point1 + t*lineDirection;

	return closestPoint;
}

bool Line3D::hasIntersectionOnRay(const Sphere& sphere) const
{	
	Vec3f m = point1 - sphere.center; 
	float c = m.dot(m) - sphere.ray * sphere.ray;
	
	// If there is definitely at least one real root, there must be an intersection 
	if (c <= 0.0f) 
		return true; 
	
	Vec3f d = point2 - point1;

	float b = m.dot(d);
	
	// Early exit if ray origin outside sphere and ray pointing away from sphere 
	if (b > 0.0f) 
		return false; 
	
	float disc = b*b - c;
	
	// A negative discriminant corresponds to ray missing sphere 
	if (disc < 0.0f) 
		return false; // Now ray must hit sphere 
	
	return true;
}

Vec3f* Line3D::findIntersectionOnSegment(const Plane3D& plane) const
{
	Vec3f lineDirection = point2 - point1;
	float d = plane.getDcomponent();

	// Segment = Poin1 + t . (Point2 - Point1)
	// Plane: (n . X) = d
	// put the line on the plane, Compute the t value for the directed line ab intersecting the plane.
	float t = (d - plane.normalVector.dot(point1)) / plane.normalVector.dot(lineDirection);
	
	// If t in [0..1] compute and return intersection point 
	if (t >= 0.0f && t <= 1.0f) 
	{
		Vec3f intersectionPoint = point1 + t * lineDirection;
		return ALLOC_NEW(Vec3f)(intersectionPoint);
	}

	return nullptr;
}

DetailedColisionStatus<float> Line3D::findIntersectionOnRay(const Sphere& sphere) const
{
	Vec3f lineDirection = direction();
	Vec3f point1ToSphere = point1 - sphere.center;

	float b = point1ToSphere.dot(lineDirection);
	float c = point1ToSphere.dot(point1ToSphere) - (sphere.ray * sphere.ray);
	
	// Exit if r’s origin outside sphere (c > 0) and ray pointing away from sphere (b > 0) 
	if (c > 0.0f && b > 0.0f)
		return DetailedColisionStatus<float>(ColisionStatus::OUTSIDE);
	
	float discriminant = b * b - c;    // d = b^2 - c
	
	// A negative discriminant corresponds to ray missing sphere 
	if (discriminant < 0.0f) // the quadratic equation has not real root
		return DetailedColisionStatus<float>(ColisionStatus::OUTSIDE);

	float sqrtDisctiminant = std::sqrtf(discriminant);

	// Ray now found to intersect sphere, compute smallest t value of intersection 
	float t1 = -b - sqrtDisctiminant;   // -b - sqrt(b^2 - c)

	// If t is negative, ray started inside sphere so clamp t to zero 	
	if (t1 < 0.0f)
		t1 = 0.0f;

	Vec3f intersectionPoint1 = point1 + t1 * lineDirection;
	
	if (isCloseEnough(discriminant, 0.0f)) 
		return DetailedColisionStatus<float>(ColisionStatus::INLINE, intersectionPoint1);

	// discriminant > T(0)  =>  the quadratic equation has 2 real root, then the ray intersect in 2 points

	// Ray now found to intersect sphere in 2 points, compute bigger t value of intersection 
	float t2 = -b + sqrtDisctiminant;   // -b + sqrt(b^2 - c)
	
	Vec3f intersectionPoint2 = point1 + t2 * lineDirection;

	return DetailedColisionStatus<float>(ColisionStatus::INSIDE, intersectionPoint1, intersectionPoint2);
}

DetailedColisionStatus<float> Line3D::findIntersectionOnSegment(const Sphere& sphere) const
{
	DetailedColisionStatus<float> colision = findIntersectionOnRay(sphere);

	if (colision.status == ColisionStatus::OUTSIDE)
		return colision;

	if (!isOnSegment(colision.points[0]))
		return DetailedColisionStatus<float>(ColisionStatus::OUTSIDE);

	if (!isOnSegment(colision.points[1]))
		return DetailedColisionStatus<float>(ColisionStatus::INSIDE, colision.points[0]);

	return colision;
}

DetailedColisionStatus<float> Line3D::findIntersectionOnRay(const AABB& aabb) const
{
	float tmin = 0.0f;
	float tmax = std::numeric_limits<float>().max();
	Vec3f lineDirection = direction();

	// For all three slabs (planes on AABB)
	for (int i = 0; i < 3; i++) 
	{ 
		if (std::abs(lineDirection[i]) < DBL_EPSILON)
		{ 
			// Ray is parallel to slab! No hit if origin not within slab 
			if (point1[i] < aabb.minPoint[i] || point1[i] > aabb.maxPoint[i])
				return DetailedColisionStatus<float>(ColisionStatus::OUTSIDE);
		} 
		else 
		{ 
			// Compute intersection t value of ray with near and far plane of slab 
			float ood = 1.0f / lineDirection[i];
			float t1 = (aabb.minPoint[i] - point1[i]) * ood;
			float t2 = (aabb.maxPoint[i] - point1[i]) * ood;
			
			// Make t1 be intersection with near plane, t2 with far plane 
			if (t1 > t2) 
				std::swap(t1, t2); 
			
			// Compute the intersection of slab intersection intervals 
			tmin = std::max(tmin, t1); 
			tmax = std::min(tmax, t2); 
			
			// Exit with no collision as soon as slab intersection becomes empty 
			if (tmin > tmax) 
				return DetailedColisionStatus<float>(ColisionStatus::OUTSIDE);
		} 	
	} 
	
	// Ray intersects all 3 slabs. Return point (q) and intersection t value (tmin) 
	return DetailedColisionStatus<float>(ColisionStatus::INSIDE, point1 + tmin * lineDirection, point1 + tmax * lineDirection);
}

ColisionStatus Line3D::hasIntersectionOnSegment(const AABB& aabb) const
{
	float epsilon = std::numeric_limits<float>().epsilon();

	/*
	Vec3<T> c = (aabb.minPoint + aabb.maxPoint) * T(0.5);	// Box center-point
	Vec3<T> e = aabb.maxPoint - c; 	// Box halflength extents 
	Vec3<T> m = (point1 + point2) * T(0.5); 	// Segment midpoint 
	Vec3<T> d = point2 - m;	// Segment halflength vector 
	m = m - c; 
	*/
	
	Vec3f halfLengthExtends = aabb.maxPoint - aabb.minPoint;
	Vec3f halfLengthVector = point2 - point1;
	Vec3f lineCenterPoint = point1 + point2 - aabb.minPoint - aabb.maxPoint;


	// Translate box and segment to origin 	
	// Try world coordinate axes as separating axes 
	float adx = std::abs(halfLengthVector[0]);
	if (std::abs(lineCenterPoint[0]) > halfLengthExtends[0] + adx)
		return ColisionStatus::OUTSIDE;
	
	float ady = std::abs(halfLengthVector[1]);
	if (std::abs(lineCenterPoint[1]) > halfLengthExtends[1] + ady)
		return ColisionStatus::OUTSIDE;
	
	float adz = std::abs(halfLengthVector[2]);
	if (std::abs(lineCenterPoint[2]) > halfLengthExtends[2] + adz)
		return ColisionStatus::OUTSIDE;
	
	// Add in an epsilon term to counteract arithmetic errors when segment is 
	// (near) parallel to a coordinate axis (see text for detail) 
	adx += epsilon;
	ady += epsilon;
	adz += epsilon;

	// Try cross products of segment direction vector with coordinate axes 
	if (std::abs(lineCenterPoint[1] * halfLengthVector[2] - lineCenterPoint[2] * halfLengthVector[1]) > halfLengthExtends[1] * adz + halfLengthExtends[2] * ady)
		return ColisionStatus::OUTSIDE;
	
	if (std::abs(lineCenterPoint[2] * halfLengthVector[0] - lineCenterPoint[0] * halfLengthVector[2]) > halfLengthExtends[0] * adz + halfLengthExtends[2] * adx)
		return ColisionStatus::OUTSIDE;
	
	if (std::abs(lineCenterPoint[0] * halfLengthVector[1] - lineCenterPoint[1] * halfLengthVector[0]) > halfLengthExtends[0] * ady + halfLengthExtends[1] * adx)
		return ColisionStatus::OUTSIDE;
	
	// No separating axis found; segment must be overlapping AABB 
	return ColisionStatus::INSIDE;
}

float Line3D::squaredDistance(const Vec3f& target) const
{
	//Returns the squared distance between point and segment point1-point2

	Vec3f ab = point2 - point1;
	Vec3f ac = target - point1;
	Vec3f bc = target - point2;
	
	float e = ac.dot(ab); // Handle cases where point projects outside the line segment
	
	if (e <= 0.0f) 
		return ac.dot(ac); 
	
	float f = ab.dot(ab);

	if (e >= f) 		
		return bc.dot(bc); // Handle cases where point projects onto line segment
	
	return ac.dot(ac) - e * e / f;
}

float Line3D::distance(const Vec3f& target) const
{
	return std::sqrtf(squaredDistance(target));
}
