#ifndef SWEEP_AND_PRUNE_HEADER
#define SWEEP_AND_PRUNE_HEADER

#include "OpenML.h"
#include "AABB.h"
#include "AlgorithmSorting.h"

#if OPENCL_ENABLED
	#include "GpuCommand.h"
	#include "GpuContext.h"
	#include "Factory.h"
	#include "IFileManager.h"
	#include "GpuRadixSorting.h"
#endif

namespace OpenML
{

	class SweepAndPruneResult
	{
	public:
		size_t* indexes;
		size_t count;

		SweepAndPruneResult(size_t* indexes,  size_t count)
		{
			this->indexes = indexes;
			this->count = count;
		}

		~SweepAndPruneResult()
		{
			ALLOC_RELEASE(indexes);
		}
	};

	class SweepAndPrune
	{
	private:

#if OPENCL_ENABLED
		GpuDevice* gpu = NULL;
		GpuRadixSorting* radixSorting;
#endif

	public:

		///<summary>
		/// Find the collisions using Sweep and Prune method
		/// Returns the pair indexes
		///</summary>
		API_INTERFACE static SweepAndPruneResult findCollisions(AABB* aabbs, size_t count);

#ifdef OPENCL_ENABLED

		///<summary>
		/// Init Sweep And Prune Algorithm on GPU
		///</summary>
		API_INTERFACE void init(GpuDevice* gpu);

		///<summary>
		/// Find the collisions using Sweep and Prune method in GPU
		/// Returns the pair indexes
		///</summary>
		API_INTERFACE SweepAndPruneResult findCollisionsGPU(float* input, size_t count, size_t strider = 1, size_t offset = 0, size_t minPointIndex = 0, size_t maxPointIndex = 1);

#endif

		API_INTERFACE ~SweepAndPrune();

	};

}

#endif // SWEEP_AND_PRUNE_HEADER