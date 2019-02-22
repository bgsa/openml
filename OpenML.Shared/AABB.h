#pragma once

#include <algorithm>
#include "Vec3.h"

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
		///Check whether the AABBs are in contact each other
		///</summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const AABB<T>& aabb);

		///<summary>
		///Given a point, find the closest point in AABB
		///</summary>
		API_INTERFACE inline Vec3<T> closestPointInAABB(const Vec3<T>& target);

	};

	typedef AABB<int> AABBi;
	typedef AABB<float> AABBf;
	typedef AABB<double> AABBd;

}