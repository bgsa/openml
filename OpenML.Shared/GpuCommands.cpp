#ifdef OPENCL_ENABLED

#include "GpuCommands.h"

size_t findMinMaxProgramIndex;

void gpuCommands_init(GpuDevice* gpu)
{
	IFileManager* fileManager = Factory::getFileManagerInstance();

	std::string sourceFindMinMax = fileManager->readTextFile("FindMinMax.cl");
	findMinMaxProgramIndex = gpu->commandManager->cacheProgram(sourceFindMinMax.c_str(), SIZEOF_CHAR * sourceFindMinMax.length());

	delete fileManager;
}

float* gpuCommands_findMinMaxGPU(GpuDevice* gpu, float* input, size_t n)
{
	float* output = ALLOC_ARRAY(float, 2);
	const size_t globalWorkSize[3] = { gpu->maxWorkGroupSize, 0 , 0 };
	const size_t localWorkSize[3] = { nextPowOf2(n) / gpu->maxWorkGroupSize, 0, 0 };
	const size_t groupCount = gpu->maxWorkGroupSize / localWorkSize[0];

	cl_mem outputBuffer = gpu->createBuffer(SIZEOF_FLOAT * groupCount * 2, CL_MEM_READ_WRITE);

	GpuCommand* commandFindMinMax = gpu->commandManager->createCommand();

	float* outputGPU = commandFindMinMax
		->setInputParameter(input, SIZEOF_FLOAT * n, CL_MEM_READ_ONLY, false)
		->setInputParameter(&n, SIZEOF_UINT)
		->setInputParameter(outputBuffer, SIZEOF_FLOAT * groupCount * 2)
		->buildFromProgram(gpu->commandManager->cachedPrograms[findMinMaxProgramIndex], "findMinMax")
		->execute(1, globalWorkSize, localWorkSize)
		->fetchInOutParameter<float>(2);

	output[0] = FLT_MAX;
	output[1] = FLT_MIN;
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

float gpuCommands_findMaxGPU(GpuDevice* gpu, float* input, size_t n)
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

	float output = FLT_MIN;
	for (size_t i = 0; i < groupCount; i++)   // check the remaining itens provided from GPU
		if (output > outputGPU[i])
			output = outputGPU[i];

	commandFindMinMax->~GpuCommand();
	gpu->releaseBuffer(outputBuffer);
	return output;
}

#endif // ! OPENCL_ENABLED