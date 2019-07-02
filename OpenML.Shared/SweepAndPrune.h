#pragma once

#include "OpenML.h"
#include "AABB.h"
#include "AlgorithmSorting.h"

#if OPENCL_ENABLED
	#include "GpuCommand.h"
	#include "GpuContext.h"
	#include "Factory.h"
	#include "IFileManager.h"
#endif

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

		~SweepAndPruneResult()
		{
			delete[] aabbIndexes1, aabbIndexes2;
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

#if OPENCL_ENABLED

		///<summary>
		/// Find the collisions using Sweep and Prune method in GPU
		/// Returns the pair indexes
		///</summary>
		template <typename T>
		API_INTERFACE static SweepAndPruneResult findCollisionsGPU(GpuCommandManager* gpuCommandManager, AABB<T>* aabbs, size_t count);

#endif

	};

}