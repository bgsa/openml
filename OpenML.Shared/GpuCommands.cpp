#ifdef OPENCL_ENABLED

#include "GpuCommands.h"

static size_t findMinMaxProgramIndex = UINT_MAX;

void gpuCommands_init(GpuDevice* gpu)
{
	if (findMinMaxProgramIndex != UINT_MAX)
		return;

	IFileManager* fileManager = Factory::getFileManagerInstance();

	std::string sourceFindMinMax = fileManager->readTextFile("FindMinMax.cl");
	findMinMaxProgramIndex = gpu->commandManager->cacheProgram(sourceFindMinMax.c_str(), SIZEOF_CHAR * sourceFindMinMax.length());

	delete fileManager;
}

cl_mem gpuCommands_findMaxGPUBuffer(GpuDevice* gpu, float* input, size_t n, size_t strider, size_t offset)
{
	const size_t globalWorkSize[3] = { gpu->maxWorkGroupSize, 0 , 0 };
	const size_t localWorkSize[3] = { nextPowOf2(n) / gpu->maxWorkGroupSize, 0, 0 };
	const size_t groupCount = gpu->maxWorkGroupSize / localWorkSize[0];

	cl_mem outputBuffer = gpu->createBuffer(SIZEOF_FLOAT * groupCount, CL_MEM_READ_WRITE);

	GpuCommand* commandFindMinMax = gpu->commandManager->createCommand();

	float* outputGPU = commandFindMinMax
		->setInputParameter(input, SIZEOF_FLOAT * n, CL_MEM_READ_ONLY, false)
		->setInputParameter(&n, SIZEOF_UINT)
		->setInputParameter(outputBuffer, SIZEOF_FLOAT * groupCount)
		->buildFromProgram(gpu->commandManager->cachedPrograms[findMinMaxProgramIndex], "findMax")
		->execute(1, globalWorkSize, localWorkSize)
		->fetchInOutParameter<float>(2);

	commandFindMinMax->~GpuCommand();

	return  outputBuffer;
}

float* gpuCommands_findMinMaxGPU(GpuDevice* gpu, float* input, size_t n, size_t strider, size_t offset)
{
	float* output = ALLOC_ARRAY(float, 2);
	const size_t globalWorkSize[3] = { gpu->maxWorkGroupSize, 0 , 0 };
	const size_t localWorkSize[3] = { nextPowOf2(n) / gpu->maxWorkGroupSize, 0, 0 };
	const size_t groupCount = gpu->maxWorkGroupSize / localWorkSize[0];

	cl_mem outputBuffer = gpu->createBuffer(SIZEOF_FLOAT * groupCount * 2, CL_MEM_READ_WRITE);

	GpuCommand* commandFindMinMax = gpu->commandManager->createCommand();

	float* outputGPU = commandFindMinMax
		->setInputParameter(input, SIZEOF_FLOAT * n * strider, CL_MEM_READ_ONLY, false)
		->setInputParameter(&n, SIZEOF_UINT * strider)
		->setInputParameter(outputBuffer, SIZEOF_FLOAT * groupCount * 2)
		->setInputParameter(&strider, SIZEOF_UINT)
		->setInputParameter(&offset, SIZEOF_UINT)
		->buildFromProgram(gpu->commandManager->cachedPrograms[findMinMaxProgramIndex], "findMinMax")
		->execute(1, globalWorkSize, localWorkSize)
		->fetchInOutParameter<float>(2);

	output[0] = FLT_MAX;
	output[1] = -FLT_MAX;
	for (size_t i = 0; i < groupCount; i++)   // check the remaining itens provided from GPU
	{
		if (output[0] > outputGPU[i])
			output[0] = outputGPU[i];

		if (output[1] < outputGPU[groupCount + i])
			output[1] = outputGPU[groupCount + i];
	}

	commandFindMinMax->~GpuCommand();
	gpu->releaseBuffer(outputBuffer);
	return output;
}

float gpuCommands_findMaxGPU(GpuDevice* gpu, float* input, size_t n, size_t strider, size_t offset)
{
	float* output = ALLOC_ARRAY(float, 1);
	cl_mem outputBuffer = gpuCommands_findMaxGPUBuffer(gpu, input, n, strider, offset);

	gpu->commandManager->executeReadBuffer(outputBuffer, SIZEOF_FLOAT, output, true);

	gpu->releaseBuffer(outputBuffer);

	return output[0];
}

#endif // ! OPENCL_ENABLED