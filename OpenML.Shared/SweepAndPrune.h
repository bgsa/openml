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
		size_t* aabbIndexes;
		size_t count;

		SweepAndPruneResult(size_t* aabbIndexes,  size_t count)
		{
			this->aabbIndexes = aabbIndexes;
			this->count = count;
		}

		~SweepAndPruneResult()
		{
			ALLOC_RELEASE(aabbIndexes);
		}
	};

	class SweepAndPrune
	{
	public:

		///<summary>
		/// Init Sweep And Prune Algorithm on GPU
		///</summary>
		static void init(GpuDevice* gpu);

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
		API_INTERFACE static SweepAndPruneResult findCollisionsGPU(GpuDevice* gpuCommandManager, AABB<T>* aabbs, size_t count);

#endif

	};

}