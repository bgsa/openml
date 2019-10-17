#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include "Line3D.h"
#include "Orientation.h"

namespace OpenML
{

	class Plane3D
	{

	public:
		Vec3f point;
		Vec3f normalVector;

		API_INTERFACE inline Plane3D();

		/// <summary>
		/// Build a plane from a point and normal vector (NORMALIZED!)
		/// </summary>
		API_INTERFACE inline Plane3D(const Vec3f& point, const Vec3f& vector);

		/// <summary>
		/// Build a plane from 3 points, making a face
		/// </summary>
		API_INTERFACE inline Plane3D(const Vec3f& point1, const Vec3f& point2, const Vec3f& point3);

		/// <summary>
		/// Build a plane from equation
		/// </summary>
		API_INTERFACE inline Plane3D(float a, float b, float c, float d);

		/// <summary>
		/// Get "D" components from plane equation: ax + by + cz + D = 0
		/// </summary>
		API_INTERFACE inline float getDcomponent() const;

		/// <summary>
		/// Get the equation of the plane
		/// </summary>
		API_INTERFACE inline Vec4f getEquation() const;

		/// <summary>
		/// Test if the line cross the plane
		/// </summary>
		API_INTERFACE inline Vec3f* findIntersection(const Line3D& line) const;

		/// <summary>
		/// Get the line intersection between the planes
		/// </summary>
		API_INTERFACE inline Line3D* findIntersection(const Plane3D& plane) const;
		
		/// <summary>
		/// Get the angle of two planes
		/// </summary>
		API_INTERFACE float angle(const Plane3D& plane) const;

		/// <summary>
		/// Get the distance from the plane to the point
		/// </summary>
		API_INTERFACE float distance(const Vec3f& point) const;

		/// <summary>
		/// Indicate whether the point is on the left, right fo the plane OR the point lies on the plane
		/// </summary>
		API_INTERFACE Orientation orientation(const Vec3f& point) const;

		/// <summary>
		/// Check if the planes are parallel each other
		/// </summary>
		API_INTERFACE inline bool isParallel(const Plane3D& plane) const;

		/// <summary>
		/// Check if the planes are perpendicular each other
		/// </summary>
		API_INTERFACE inline bool isPerpendicular(const Plane3D& plane) const;

		/// <summary>
		/// Given an arbitrary point, find the closest point on the plane
		/// </summary>
		API_INTERFACE inline Vec3f closestPointOnThePlane(const Vec3f &target) const;

	};

}