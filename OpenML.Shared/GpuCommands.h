#ifdef OPENCL_ENABLED

#ifndef GPU_COMMANDS
#define GPU_COMMANDS

#include "OpenML.h"
#include <algorithm>
#include "GpuContext.h"
#include "GpuCommand.h"
#include "IFileManager.h"
#include "Factory.h"

namespace OpenML
{

	class GpuCommands
	{
	public:

		/// <summary>
		/// Init algorithms for GPU
		/// </summary>
		API_INTERFACE static void init(GpuDevice* gpu);

		/// <summary>
		/// Create Indexes buffer ( 0, 1, 2, ... , length ) on GPU
		/// </summary>
		API_INTERFACE static cl_mem creteIndexes(GpuDevice * gpu, size_t length);

		/// <summary>
		/// Find minimum and maximum value from an array of elements
		/// </summary>
		API_INTERFACE static float* findMinMaxGPU(GpuDevice* gpu, float* input, size_t n, size_t offsetMultiplier = 1, size_t offsetSum = 0);

		/// <summary>
		/// Find maximum value from an array of elements
		/// </summary>
		/// <returns>
		/// GPU Buffer Memory
		/// </returns>
		API_INTERFACE static cl_mem findMaxGPUBuffer(GpuDevice* gpu, float* input, size_t n, size_t offsetMultiplier = 1, size_t offsetSum = 0);

		/// <summary>
		/// Find maximum value from an array of elements
		/// </summary>
		API_INTERFACE static float findMaxGPU(GpuDevice* gpu, float* input, size_t n, size_t offsetMultiplier = 1, size_t offsetSum = 0);

		/// <summary>
		/// Find minimum and maximum value from an array of elements using indexes
		/// Elements and indexes should be on GPU memory
		/// </summary>
		API_INTERFACE static void findMinMaxIndexesGPU(GpuDevice* gpu, cl_mem elements, cl_mem indexes, cl_mem indexesLength, cl_mem strider, cl_mem offset, size_t indexesLengthCpu, size_t striderCpu, cl_mem output);

	};
}


#endif // ! GPU_COMMANDS

#endif // ! OPENCL_ENABLED