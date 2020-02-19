#ifdef OPENCL_ENABLED

#include "GpuCommands.h"

namespace OpenML
{

	static size_t findMinMaxProgramIndex = UINT_MAX;
	static size_t basicProgramIndex = UINT_MAX;

	void GpuCommands::init(GpuDevice* gpu, const char* buildOptions)
	{
		if (findMinMaxProgramIndex != UINT_MAX)
			return;

		IFileManager* fileManager = Factory::getFileManagerInstance();

		std::string sourceFindMinMax = fileManager->readTextFile("FindMinMax.cl");
		findMinMaxProgramIndex = gpu->commandManager->cacheProgram(sourceFindMinMax.c_str(), SIZEOF_CHAR * sourceFindMinMax.length(), buildOptions);

		std::string sourceBasic = fileManager->readTextFile("BasicCommands.cl");
		basicProgramIndex = gpu->commandManager->cacheProgram(sourceBasic.c_str(), SIZEOF_CHAR * sourceBasic.length(), buildOptions);

		delete fileManager;
	}

	cl_mem GpuCommands::creteIndexes(GpuDevice* gpu, size_t length)
	{
		const size_t globalWorkSize[3] = { nextPowOf2(std::min(gpu->maxWorkGroupSize, length)), 0 , 0 };
		const size_t localWorkSize[3] = { std::max(nextPowOf2(length) / gpu->maxWorkGroupSize, size_t(1)), 0, 0 };
		const size_t groupCount = globalWorkSize[0] / localWorkSize[0];

		GpuCommand* commandInitIndexes = gpu->commandManager->createCommand();

		size_t indexesSize = length * SIZEOF_UINT;
		cl_mem indexesBuffer = gpu->createBuffer(indexesSize, CL_MEM_READ_WRITE);

		commandInitIndexes
			->setInputParameter(&length, SIZEOF_UINT)
			->setInputParameter(indexesBuffer, indexesSize)
			->buildFromProgram(gpu->commandManager->cachedPrograms[basicProgramIndex], "initIndexes")
			->execute(1, globalWorkSize, localWorkSize);

		commandInitIndexes->~GpuCommand();

		return indexesBuffer;
	}

	cl_mem GpuCommands::findMaxGPUBuffer(GpuDevice* gpu, float* input, size_t n, size_t strider, size_t offset)
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

	float* GpuCommands::findMinMaxGPU(GpuDevice* gpu, float* input, size_t n, size_t strider, size_t offset)
	{
		float* output = ALLOC_ARRAY(float, 2);
		const size_t globalWorkSize[3] = { nextPowOf2(std::min(gpu->maxWorkGroupSize, n)), 0 , 0 };
		const size_t localWorkSize[3] = { std::max(nextPowOf2(n) / gpu->maxWorkGroupSize, size_t(1)), 0, 0 };
		const size_t groupCount = globalWorkSize[0] / localWorkSize[0];

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
		for (size_t i = 0; i < groupCount - 1; i++)   // check the remaining itens provided from GPU
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

	void GpuCommands::findMinMaxIndexesGPU(GpuDevice* gpu, cl_mem elements, cl_mem indexes, cl_mem indexesLength, cl_mem offset, size_t indexesLengthCpu, size_t striderCpu, cl_mem output)
	{
		const size_t globalWorkSize[3] = { nextPowOf2(std::min(gpu->maxWorkGroupSize, indexesLengthCpu)), 0 , 0 };
		const size_t localWorkSize[3] = { gpu->getLocalWorkSize(indexesLengthCpu) , 0, 0 };
		const size_t threadLength = gpu->getThreadLength(indexesLengthCpu);
		
		GpuCommand* commandFindMinMax = gpu->commandManager->createCommand();

		commandFindMinMax
			->setInputParameter(elements, SIZEOF_FLOAT * indexesLengthCpu * striderCpu)
			->setInputParameter(indexes, SIZEOF_UINT * indexesLengthCpu)
			->setInputParameter(indexesLength, SIZEOF_UINT)
			->setInputParameter(offset, SIZEOF_UINT)
			->setInputParameter(output, threadLength * 2 * SIZEOF_FLOAT)
			->buildFromProgram(gpu->commandManager->cachedPrograms[findMinMaxProgramIndex], "findMinMaxIndexes")
			->execute(1, globalWorkSize, localWorkSize);

		commandFindMinMax->~GpuCommand();
	}

	float GpuCommands::findMaxGPU(GpuDevice* gpu, float* input, size_t n, size_t strider, size_t offset)
	{
		float* output = ALLOC_ARRAY(float, 1);
		cl_mem outputBuffer = GpuCommands::findMaxGPUBuffer(gpu, input, n, strider, offset);

		gpu->commandManager->executeReadBuffer(outputBuffer, SIZEOF_FLOAT, output, true);

		gpu->releaseBuffer(outputBuffer);

		return output[0];
	}

}

#endif // ! OPENCL_ENABLED