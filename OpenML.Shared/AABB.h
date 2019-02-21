#pragma once

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
		AABB(Vec3<T> minPoint, Vec3<T> maxPoint);

		///<summary>
		///Constructur using min points and distances from this point in the axis
		///</summary>
		AABB(Vec3<T> minPoint, T width, T height, T depth);
	};

	typedef AABB<int> AABBi;
	typedef AABB<float> AABBf;
	typedef AABB<double> AABBd;

}