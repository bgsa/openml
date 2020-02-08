#if OPENCL_ENABLED

#ifndef GPU_RADIX_DORTING
#define GPU_RADIX_DORTING

#include "GpuCommands.h"

namespace OpenML
{
	class GpuRadixSorting
	{
	private:
		size_t radixSortProgramIndex;
		GpuDevice* gpu = NULL;
		float minMaxValues[2];
		size_t globalWorkSize[3];
		size_t localWorkSize[3];
		size_t maxDigits = MAX_DIGITS_MANTISSA - 1;
		size_t threadsCount;
		size_t offsetPrefixScanCpu = 10;

		GpuCommand* commandCount;
		GpuCommand* commandPrefixScan;
		GpuCommand* commandPrefixScanSwaped;
		GpuCommand* commandReorder;

		cl_mem outputMinMaxGpu;
		cl_mem offsetTable1;
		cl_mem offsetTable2;
		cl_mem offsetTableResult;
		cl_mem offsetPrefixScanGpu;
		cl_mem digitIndexGpu;
		cl_mem useExpoentGpu;

		cl_mem outputIndexes;

	public:
		cl_mem inputGpu;
		cl_mem indexesGpu;
		cl_mem indexesLengthGpu;
		cl_mem striderGpu;
		cl_mem offsetGpu;

		API_INTERFACE GpuRadixSorting* init(GpuDevice* gpu, const char* buildOptions);

		API_INTERFACE GpuRadixSorting* setParameters(float* input, size_t indexesLengthCpu, size_t striderCpu, size_t offsetCpu);

		API_INTERFACE cl_mem execute();

		API_INTERFACE ~GpuRadixSorting();

	};
}

#endif // ! GPU_RADIX_DORTING

#endif