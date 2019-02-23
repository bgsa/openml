#pragma once

#include <algorithm>
#include "Vec3.h"
#include "Plane3D.h"

namespace OpenML
{

	template <typename T>
	class AABB
	{
	public:
		Vec3<T> minPoint;
		Vec3<T> maxPoint;

		///<summary>
		///Default constructur using min and max points
		///</summary>
		API_INTERFACE inline AABB(Vec3<T> minPoint, Vec3<T> maxPoint);

		///<summary>
		///Constructur using min points and distances from this point in the axis
		///</summary>
		API_INTERFACE inline AABB(Vec3<T> minPoint, T width, T height, T depth);

		///<summary>
		///Get the center of AABB
		///</summary>
		API_INTERFACE inline Vec3<T> center();

		///<summary>
		///Check whether the AABBs are in contact each other
		///</summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const AABB<T>& aabb);

		///<summary>
		///Check whether the AABB intersect the plane
		///</summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const Plane3D<T>& plane);

		///<summary>
		///Given a point, find the closest point in AABB
		///</summary>
		API_INTERFACE inline Vec3<T> closestPointInAABB(const Vec3<T>& target);

		///<summary>
		///Get the SQUARED distance from a point and AABB
		///</summary>
		API_INTERFACE inline T squaredDistance(const Vec3<T>& target);

		///<summary>
		///Get the distance from a point and AABB
		///</summary>
		API_INTERFACE inline T distance(const Vec3<T>& target);

	};

	typedef AABB<int> AABBi;
	typedef AABB<float> AABBf;
	typedef AABB<double> AABBd;

}