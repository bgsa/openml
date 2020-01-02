#pragma once

#include "Vec3.h"
#include "Plane3D.h"
#include "Sphere.h"
#include "AABB.h"

namespace OpenML 
{
	class Line3D
	{
	public:
		Vec3f point1;
		Vec3f point2;

		///<summary>
		/// Empty constructor 
		///</summary>
		API_INTERFACE inline Line3D();

		///<summary>
		/// Build a line from 2 points
		///</summary>
		API_INTERFACE inline Line3D(const Vec3f& point1, const Vec3f& point2);

		///<summary>
		/// Build a line from 2 points as vector
		///</summary>
		API_INTERFACE inline Line3D(Vec3f* points);

		///<summary>
		/// Build a line from 2 points (3 numbers for each point)
		///</summary>
		API_INTERFACE inline Line3D(float* point1, float* point2);

		///<summary>
		/// Get the direction of line
		///</summary>
		API_INTERFACE inline Vec3f direction() const;

		///<summary>
		/// Get the SQUARED distance from SEGMENT of line and an arbitrary point
		///</summary>
		API_INTERFACE float squaredDistance(const Vec3f& target) const;

		///<summary>
		/// Get the SQUARED distance from SEGMENT of line and an arbitrary point
		///</summary>
		API_INTERFACE float distance(const Vec3f& target) const;

		///<summary>
		///Returns the center of the segment of line
		///</summary>
		API_INTERFACE inline Vec3f centerOfSegment() const;

		///<summary>
		///Returns the center of the segment of line
		///</summary>
		API_INTERFACE inline float lengthOfSegment() const;

		///<summary>
		/// Check the point is on the line
		///</summary>
		API_INTERFACE bool isOnLine(const Vec3f& point) const;

		///<summary>
		/// Check the point is on segment
		///</summary>
		API_INTERFACE bool isOnSegment(const Vec3f& point) const;
		
		///<summary>
		/// Check the ray has intersection with the sphere
		///</summary>
		API_INTERFACE bool hasIntersectionOnRay(const Sphere& sphere) const;

		///<summary>
		/// Find intersection of line against another one
		///</summary>
		API_INTERFACE Vec3f* findIntersection(const Line3D& line2) const;

		///<summary>
		/// Find intersection of line against a phere
		///</summary>
		API_INTERFACE DetailedCollisionStatus<float> findIntersectionOnRay(const Sphere& sphere) const;

		///<summary>
		/// Find intersection of SEGMENT of line against a phere
		///</summary>
		API_INTERFACE DetailedCollisionStatus<float> findIntersectionOnSegment(const Sphere& sphere) const;

		///<summary>
		/// Find intersection of ray against a AABB
		///</summary>
		API_INTERFACE DetailedCollisionStatus<float> findIntersectionOnRay(const AABB& aabb) const;

		///<summary>
		/// Find intersection of SEGMENT of line against a AABB
		///</summary>
		API_INTERFACE CollisionStatus hasIntersectionOnSegment(const AABB& aabb) const;

		///<summary>
		/// Find intersection SEGMENT of line against a plane
		///</summary>
		API_INTERFACE Vec3f* findIntersectionOnSegment(const Plane3D& plane) const;

		///<summary>
		/// Get the closest point in the SEGMENT of line, given an arbitrary point
		///</summary>
		API_INTERFACE Vec3f closestPointOnTheLine(const Vec3f& target) const;

	};

}