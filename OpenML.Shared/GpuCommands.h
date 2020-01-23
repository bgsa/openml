#ifdef OPENCL_ENABLED

#ifndef GPU_COMMANDS
#define GPU_COMMANDS

#include "OpenML.h"
#include <algorithm>
#include "GpuContext.h"
#include "GpuCommand.h"
#include "IFileManager.h"
#include "Factory.h"

#ifdef __cplusplus
//extern "C"
//{
#endif

	/// <summary>
	/// Init algorithms for GPU
	/// </summary>
	API_INTERFACE void gpuCommands_init(GpuDevice* gpu);

	/// <summary>
	/// Find minimum and maximum value from an array of elements
	/// </summary>
	API_INTERFACE float* gpuCommands_findMinMaxGPU(GpuDevice* gpu, float* input, size_t n, size_t offsetMultiplier = 1, size_t offsetSum = 0);

	/// <summary>
	/// Find maximum value from an array of elements
	/// </summary>
	/// <returns>
	/// GPU Buffer Memory
	/// </returns>
	API_INTERFACE cl_mem gpuCommands_findMaxGPUBuffer(GpuDevice* gpu, float* input, size_t n, size_t offsetMultiplier = 1, size_t offsetSum = 0);

	/// <summary>
	/// Find maximum value from an array of elements
	/// </summary>
	API_INTERFACE float gpuCommands_findMaxGPU(GpuDevice* gpu, float* input, size_t n, size_t offsetMultiplier = 1, size_t offsetSum = 0);

#ifdef __cplusplus
//}
#endif

#endif // ! GPU_COMMANDS

#endif // ! OPENCL_ENABLED