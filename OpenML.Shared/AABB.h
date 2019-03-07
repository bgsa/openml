#pragma once

#include <algorithm>
#include "Vec3.h"
#include "Vec3List.h"
#include "Plane3D.h"
#include "Sphere.h"

namespace OpenML
{

	template <typename T>
	class AABB
	{
	public:
		Vec3<T> minPoint;
		Vec3<T> maxPoint;

		///<summary>
		///Default constructur - build a unit AABB with the center in the origin
		///</summary>
		API_INTERFACE inline AABB();

		///<summary>
		///Constructor using min and max points
		///</summary>
		API_INTERFACE inline AABB(Vec3<T> minPoint, Vec3<T> maxPoint);

		///<summary>
		///Constructur using min points and distances from this point in the axis
		///</summary>
		API_INTERFACE inline AABB(Vec3<T> minPoint, T width, T height, T depth);

		///<summary>
		///Get the center of AABB
		///</summary>
		API_INTERFACE inline Vec3<T> center() const;

		///<summary>
		///Get the SQUARED distance from a point and AABB
		///</summary>
		API_INTERFACE inline T squaredDistance(const Vec3<T>& target);

		///<summary>
		///Get the distance from a point and AABB
		///</summary>
		API_INTERFACE inline T distance(const Vec3<T>& target);

		///<summary>
		///Check whether the AABBs are in contact each other
		///</summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const AABB<T>& aabb);

		///<summary>
		///Check whether the AABB intersect the plane
		///</summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const Plane3D<T>& plane);

		///<summary>
		///Check whether the AABB intersect the sphere
		///</summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const Sphere<T>& sphere);
		
		///<summary>
		///Given a point, find the closest point in AABB
		///</summary>
		API_INTERFACE inline Vec3<T> closestPointInAABB(const Vec3<T>& target);

		///<summary>
		///Given a point, find the closest point in AABB
		///</summary>
		API_INTERFACE inline Vec3<T> closestPointInAABB(const Sphere<T>& sphgere);

		///<summary>
		///Given a list of point (mesh), build the AABB
		///</summary>
		API_INTERFACE static AABB<T> buildFrom(const Vec3List<T>& pointList);

		///<summary>
		///Given a sphere, build the AABB to enclose the sphere
		///</summary>
		API_INTERFACE static AABB<T> buildFrom(const Sphere<T>& sphere);

		///<summary>
		///Ecnlose/add a new bounding volume with AABB in parameter
		///</summary>
		API_INTERFACE inline AABB<T> enclose(const AABB<T>& aabb);

		///<summary>
		///Ecnlose/add a new bounding volume with Sphere in parameter
		///</summary>
		API_INTERFACE AABB<T> enclose(const Sphere<T>& sphere);

	};

	typedef AABB<int> AABBi;
	typedef AABB<float> AABBf;
	typedef AABB<double> AABBd;

}