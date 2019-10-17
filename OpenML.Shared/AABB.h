#pragma once

#include <algorithm>
#include "Vec3.h"
#include "Vec3List.h"
#include "BoundingVolume.h"
#include "Plane3D.h"
#include "Sphere.h"

namespace OpenML
{

	class AABB
		: public BoundingVolume
	{
	public:
		Vec3f minPoint;
		Vec3f maxPoint;

		///<summary>
		///Default constructur - build a unit AABB with the center in the origin
		///</summary>
		API_INTERFACE inline AABB();

		///<summary>
		///Constructor using min and max points
		///</summary>
		API_INTERFACE inline AABB(Vec3f minPoint, Vec3f maxPoint);

		///<summary>
		///Constructur using min points and distances from this point in the axis
		///</summary>
		API_INTERFACE inline AABB(Vec3f minPoint, float width, float height, float depth);

		///<summary>
		///Get the center of AABB
		///</summary>
		API_INTERFACE inline Vec3f center() const;

		///<summary>
		///Get the center of bounding volumne (AABB)
		///</summary>
		API_INTERFACE inline Vec3f centerOfBoundingVolume() const override;

		///<summary>
		///Get the SQUARED distance from a point and AABB
		///</summary>
		API_INTERFACE inline float squaredDistance(const Vec3f& target);

		///<summary>
		///Get the distance from a point and AABB
		///</summary>
		API_INTERFACE inline float distance(const Vec3f& target);

		///<summary>
		///Check whether the AABBs are in contact each other
		///</summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const AABB& aabb);

		///<summary>
		///Check whether the AABB intersect the plane
		///</summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const Plane3D& plane);

		///<summary>
		///Check whether the AABB intersect the sphere
		///</summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const Sphere& sphere);
		
		///<summary>
		///Given a point, find the closest point in AABB
		///</summary>
		API_INTERFACE inline Vec3f closestPointInAABB(const Vec3f& target);

		///<summary>
		///Given a point, find the closest point in AABB
		///</summary>
		API_INTERFACE inline Vec3f closestPointInAABB(const Sphere& sphgere);

		///<summary>
		///Given a list of point (mesh), build the AABB
		///</summary>
		API_INTERFACE static AABB buildFrom(const Vec3List<float>& pointList);

		///<summary>
		///Given a sphere, build the AABB to enclose the sphere
		///</summary>
		API_INTERFACE static AABB buildFrom(const Sphere& sphere);

		///<summary>
		///Ecnlose/add a new bounding volume with AABB in parameter
		///</summary>
		API_INTERFACE inline AABB enclose(const AABB& aabb);

		///<summary>
		///Ecnlose/add a new bounding volume with Sphere in parameter
		///</summary>
		API_INTERFACE AABB enclose(const Sphere& sphere);

		/// <summary>
		///Compare this AABB to another one. Compare each minPoint and maxPoint
		/// </summary>
		API_INTERFACE inline bool operator==(const AABB& aabb) const;

		/// <summary>
		///Compare this AABB to another one. Compare each minPoint and maxPoint
		/// </summary>
		API_INTERFACE inline bool operator!=(const AABB& aabb) const;

		/// <summary>
		///Comparator function
		/// </summary>
		API_INTERFACE bool operator<(const AABB& aabb) const;

		/// <summary>
		///Comparator function
		/// </summary>
		API_INTERFACE bool operator>(const AABB& aabb) const;

		/// <summary>
		///Hash code function
		/// </summary>
		API_INTERFACE size_t operator()(const AABB& aabb) const;
		
		/// <summary>
		///Equals function
		/// </summary>
		API_INTERFACE bool operator()(const AABB& aabb1, const AABB& aabb2) const;

	};

}