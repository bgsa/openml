#include "Sphere.h"

Sphere WelzlSphere(Vec3f* points, int numPts, Vec3f suportPoints[], int suportPointsCount)
{
	// if no input points, the recursion has bottomed out. Now compute an 
	// exact sphere based on points in set of support (zero through four points) 

	if (numPts == 0)
	{
		switch (suportPointsCount)
		{
		case 0:
			return Sphere();
		case 1:
			return Sphere(suportPoints[0]);
		case 2:
			return Sphere(suportPoints[0], suportPoints[1]);
		case 3:
			return Sphere(suportPoints[0], suportPoints[1], suportPoints[2]);
		case 4:
			return Sphere(suportPoints[0], suportPoints[1], suportPoints[2], suportPoints[3]);
		}
	}

	// Pick a point at "random" (here just the last point of the input set) 	
	int index = numPts - 1;

	// Recursively compute the smallest bounding sphere of the remaining points 
	Sphere smallestSphere = WelzlSphere(points, numPts - 1, suportPoints, suportPointsCount); // (*) 

	bool isPointInsideTheSphere = smallestSphere.colisionStatus(points[index]) == ColisionStatus::INSIDE;
	if (isPointInsideTheSphere)
		return smallestSphere;

	// Otherwise, update set of support to additionally contain the new point 
	suportPoints[suportPointsCount] = points[index];

	// Recursively compute the smallest sphere of remaining points with new s.o.s. 
	return WelzlSphere(points, numPts - 1, suportPoints, suportPointsCount + 1);
}

Sphere::Sphere()
{
	this->center = Vec3f(0.0f);
	this->ray = 1.0f;

	initParticleSystem();
}

Sphere::Sphere(const Vec3f &center, float ray)
{
	this->center = center;
	this->ray = ray;

	initParticleSystem();
}

Sphere::Sphere(const Vec3f &point1)
{
	this->center = point1;
	this->ray = 1.0f;

	initParticleSystem();
}

Sphere::Sphere(const Vec3f &point1, const Vec3f &point2)
{
	Line3D line = Line3D(point1, point2);
	this->center = line.centerOfSegment();
	this->ray = line.lengthOfSegment() / 2.0f;

	initParticleSystem();
}

Sphere::Sphere(const Vec3f &point1, const Vec3f &point2, const Vec3f &point3)
{
	Vec3f ac = point3 - point1;
	Vec3f ab = point2 - point1;
	Vec3f abXac = ab.cross(ac);

	// this is the vector from a TO the circumsphere center
	Vec3f toCircumsphereCenter = (abXac.cross(ab) * ac.squaredLength() + ac.cross(abXac) * ab.squaredLength()) / (2.0f*abXac.squaredLength());
	
	// The 3 space coords of the circumsphere center then:
	this->center = point1 + toCircumsphereCenter; // now this is the actual 3space location
	this->ray = toCircumsphereCenter.length();

	initParticleSystem();
}

Sphere::Sphere(const Vec3f &point1, const Vec3f &point2, const Vec3f &point3, const Vec3f &point4)
{
	Mat4f m = Mat4f(
		Vec4f(point1, 1.0f),
		Vec4f(point2, 1.0f),
		Vec4f(point3, 1.0f),
		Vec4f(point4, 1.0f)
		);

	float invertedDeterminant = 1.0f / m.determinant();

	float t1 = -(point1.dot(point1));
	float t2 = -(point2.dot(point2));
	float t3 = -(point3.dot(point3));
	float t4 = -(point4.dot(point4));

	m = Mat4f(
		Vec4f(t1, point1[1], point1[2], 1.0f),
		Vec4f(t2, point2[1], point2[2], 1.0f),
		Vec4f(t3, point3[1], point3[2], 1.0f),
		Vec4f(t4, point4[1], point4[2], 1.0f)
		);
	float a = m.determinant() * invertedDeterminant;
	float x = a * -0.5f;

	m = Mat4f(
		Vec4f(point1[0], t1, point1[2], 1.0f),
		Vec4f(point2[0], t2, point2[2], 1.0f),
		Vec4f(point3[0], t3, point3[2], 1.0f),
		Vec4f(point4[0], t4, point4[2], 1.0f)
		);
	float b = m.determinant() * invertedDeterminant;
	float y = b * -0.5f;

	m = Mat4f(
		Vec4f(point1[0], point1[1], t1, 1.0f),
		Vec4f(point2[0], point2[1], t2, 1.0f),
		Vec4f(point3[0], point3[1], t3, 1.0f),
		Vec4f(point4[0], point4[1], t4, 1.0f)
		);
	float c = m.determinant() * invertedDeterminant;
	float z = c * -0.5f;

	m = Mat4f(
		Vec4f(point1[0], point1[1], point1[2], t1),
		Vec4f(point2[0], point2[1], point2[2], t2),
		Vec4f(point3[0], point3[1], point3[2], t3),
		Vec4f(point4[0], point4[1], point4[2], t4)
		);
	float d = m.determinant() * invertedDeterminant;

	center = { x, y, z };
	ray = std::sqrt(a * a + b * b + c * c - 4 * d) / 2.0f;

	initParticleSystem();
}

ColisionStatus Sphere::colisionStatus(const Vec3f &point)  const
{
	float distanceToPoint = center.distance(point);
	
	if (isCloseEnough(distanceToPoint, ray))
		return ColisionStatus::INLINE;

	if (distanceToPoint > ray)
		return ColisionStatus::OUTSIDE;

	return ColisionStatus::INSIDE;
}

ColisionStatus Sphere::colisionStatus(const Sphere& sphere)  const
{
	Vec3f rayToSphere = center - sphere.center; 
	float squaredDistance = rayToSphere.dot(rayToSphere);

	// Spheres intersect if squared distance is less than squared sum of radius 
	float diameter = ray + sphere.ray;
	float squaredDiameter = diameter * diameter;

	if (isCloseEnough(squaredDistance, squaredDiameter))
		return ColisionStatus::INLINE;

	if (squaredDistance > squaredDiameter)
		return ColisionStatus::OUTSIDE;

	return ColisionStatus::INSIDE;
}

ColisionStatus Sphere::colisionStatus(const Plane3D& plane)  const
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

	float d = plane.getDcomponent();
	float distanceToPlane = center.dot(plane.normalVector) + d;

	if (isCloseEnough(distanceToPlane, ray))
		return ColisionStatus::INLINE;

	if (distanceToPlane > ray)
		return ColisionStatus::OUTSIDE;

	return ColisionStatus::INSIDE;
}

Sphere Sphere::buildFrom(const AABB &aabb)
{
	float maxDistance = aabb.maxPoint[0] - aabb.minPoint[0];

	maxDistance = std::max(maxDistance, aabb.maxPoint[1] - aabb.minPoint[1]);

	maxDistance = std::max(maxDistance, aabb.maxPoint[2] - aabb.minPoint[2]);

	return Sphere(
		aabb.center(),
		maxDistance / 2.0f
		);
}

Sphere Sphere::buildFrom(const Vec3List<float>& pointList)
{
	Vec3f* suportPoints = ALLOC_ARRAY(Vec3f, pointList.count);

	Sphere result = WelzlSphere(pointList.points, pointList.count, suportPoints, 0);

	ALLOC_RELEASE(suportPoints);
	return result;
}

Sphere Sphere::enclose(const Sphere& sphere)
{
	Sphere result;

	Vec3f d = sphere.center - center;
	float squaredDistance = d.dot(d);  	// Compute the squared distance between the sphere centers 

	if (std::pow(double(sphere.ray - ray), 2) >= squaredDistance)
	{
		// The sphere with the larger radius encloses the other; 
		// just set s to be the larger of the two spheres
		if (sphere.ray >= this->ray)
			result = sphere;
		else
			result = *this;
	}
	else
	{
		// Spheres partially overlapping or disjoint 
		float distance = std::sqrtf(squaredDistance);

		result.ray = (distance + ray + sphere.ray) * 0.5f;
		result.center = center;

		if (distance > DefaultErrorMargin)
			result.center += ((result.ray - ray) / distance) * d;
	}

	return result;
}

Sphere Sphere::enclose(const AABB& aabb)
{
	Sphere sphere = Sphere::buildFrom(aabb);	

	return enclose(sphere);
}

void Sphere::initParticleSystem()
{
	particleSystem = ALLOC_NEW(ParticleSystem)(1);
	particleSystem->particles[0].position = center;
	particleSystem->particles[0].previousPosition = center;
}