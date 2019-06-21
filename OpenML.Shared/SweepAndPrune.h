#pragma once

#include "OpenML.h"
#include "AABB.h"
#include "AlgorithmSorting.h"

namespace OpenML
{

	class SweepAndPruneResult
	{
	public:
		size_t* aabbIndexes1;
		size_t* aabbIndexes2;
		size_t count;

		SweepAndPruneResult(size_t* aabbIndexes1, size_t* aabbIndexes2, size_t count)
		{
			this->aabbIndexes1 = aabbIndexes1;
			this->aabbIndexes2 = aabbIndexes2;
			this->count = count;
		}
	};

	class SweepAndPrune
	{
	public:

		///<summary>
		/// Find the collisions using Sweep and Prune method
		/// Returns the pair indexes
		///</summary>
		template <typename T>
		API_INTERFACE static SweepAndPruneResult findCollisions(AABB<T>* aabbs, size_t count);

	};

}