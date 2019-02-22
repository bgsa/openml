#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include "Line3D.h"
#include "Orientation.h"

namespace OpenML
{
	template <typename T>
	class Plane3D
	{
	private:

		/// <summary>
		/// Get "D" components from plane equation: ax + by + cz + D = 0
		/// </summary>
		inline T getDcomponent() const;

	public:
		Vec3<T> point;
		Vec3<T> normalVector;

		API_INTERFACE inline Plane3D();

		/// <summary>
		/// Build a plane from a point and normal vector (NORMALIZED!)
		/// </summary>
		API_INTERFACE inline Plane3D(const Vec3<T>& point, const Vec3<T>& vector);

		/// <summary>
		/// Build a plane from 3 points, making a face
		/// </summary>
		API_INTERFACE inline Plane3D(const Vec3<T>& point1, const Vec3<T>& point2, const Vec3<T>& point3);

		/// <summary>
		/// Build a plane from equation
		/// </summary>
		API_INTERFACE inline Plane3D(T a, T b, T c, T d);

		/// <summary>
		/// Get the equation of the plane
		/// </summary>
		API_INTERFACE inline Vec4<T> getEquation() const;

		/// <summary>
		/// Test if the line cross the plane
		/// </summary>
		API_INTERFACE inline Vec3<T>* findIntersection(const Line3D<T>& line) const;

		/// <summary>
		/// Get the line intersection between the planes
		/// </summary>
		API_INTERFACE inline Line3D<T>* findIntersection(const Plane3D<T>& plane) const;
		
		/// <summary>
		/// Get the angle of two planes
		/// </summary>
		API_INTERFACE T angle(const Plane3D<T>& plane) const;

		/// <summary>
		/// Get the distance from the plane to the point
		/// </summary>
		API_INTERFACE T distance(const Vec3<T>& point) const;

		/// <summary>
		/// Indicate whether the point is on the left, right fo the plane OR the point lies on the plane
		/// </summary>
		API_INTERFACE Orientation orientation(const Vec3<T>& point) const;

		/// <summary>
		/// Check if the planes are parallel each other
		/// </summary>
		API_INTERFACE inline bool isParallel(const Plane3D<T>& plane) const;

		/// <summary>
		/// Check if the planes are perpendicular each other
		/// </summary>
		API_INTERFACE inline bool isPerpendicular(const Plane3D<T>& plane) const;

		/// <summary>
		/// Given an arbitrary point, find the closest point on the plane
		/// </summary>
		API_INTERFACE inline Vec3<T> closestPointOnThePlane(const Vec3<T> &target) const;

	};

	typedef Plane3D<int> Plane3Di;
	typedef Plane3D<float> Plane3Df;
	typedef Plane3D<double> Plane3Dd;
}