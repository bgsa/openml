#pragma once

#include "OpenML.h"
#include "AABB.h"

namespace OpenML
{

	class CollisionDetection
	{
	public:

		///<summary>
		/// Find the collision using brute force algorithm O(n^2)
		///</summary>
		template <typename T>
		API_INTERFACE std::vector<std::pair<AABB<T>, AABB<T>>> bruteForce(AABB<T>* boundingVolumes, size_t count);

	};

}