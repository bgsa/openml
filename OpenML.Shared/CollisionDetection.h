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
		API_INTERFACE std::vector<std::pair<AABB, AABB>> bruteForce(AABB* boundingVolumes, size_t count);

	};

}