#ifndef SWEEP_AND_PRUNE_KDOP_HEADER
#define SWEEP_AND_PRUNE_KDOP_HEADER

#include "SweepAndPrune.h"
#include "DOP18.h"

namespace OpenML
{
	class SweepAndPruneKdop
		: public SweepAndPrune
	{
	public:

		/// <summary>
		/// Find the collisions using Sweep and Prune method
		/// Returns the pair indexes
		/// </summary>
		API_INTERFACE static SweepAndPruneResult findCollisions(DOP18* kdops, size_t count);

#if OPENCL_ENABLED

		/// <summary>
		/// Init Sweep And Prune Algorithm on GPU
		/// </summary>
		API_INTERFACE static void init(GpuDevice* gpu);

		/// <summary>
		/// Find the collisions using Sweep and Prune method On GPU
		/// Returns the pair indexes
		/// </summary>
		API_INTERFACE static SweepAndPruneResult findCollisions(GpuDevice* gpu, DOP18* aabbs, size_t count);

#endif

	};
}
#endif // !SWEEP_AND_PRUNE_KDOP_HEADER