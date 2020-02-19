#include "SweepAndPrune.h"

bool comparatorXAxisForNativeSort(int index1, int index2, AABB* aabbs)
{
	return aabbs[index1].minPoint[0] < aabbs[index2].minPoint[0];
}

int comparatorXAxisForQuickSort(const void* a, const void* b) 
{
	AABB* obj1 = (AABB*) a;
	AABB* obj2 = (AABB*) b;

	if (obj1->minPoint.x < obj2->minPoint.x)
		return -1;
	else
		if (obj1->minPoint.x > obj2->minPoint.x)
			return 1;

	return 0;
}

template<typename T>
void erase_element(std::vector<T>& vector, size_t index)
{
	std::swap(vector[index], vector.back());

	vector.pop_back();

	if (vector.size() != index)
		std::swap(vector[index], vector.back());
}

template<typename T>
void erase_element(T* array, size_t count, size_t index)
{
	std::memmove(array + index, array + index + 1, (count - index - 1) * sizeof(T));
}

SweepAndPruneResult SweepAndPrune::findCollisions(AABB* aabbs, size_t count)
{
	size_t* indexes = ALLOC_ARRAY(size_t, count*2);
	size_t aabbIndex = 0;

	size_t* activeListIndex = ALLOC_ARRAY(size_t, count);
	size_t activeListIndexCount = 0;
	size_t activeListAABBIndex = 0;
	
	AlgorithmSorting::quickSortNative(aabbs, count, sizeof(AABB), comparatorXAxisForQuickSort);
	
	for (size_t i = 0; i < count; ++i)
	{
		for (size_t j = activeListIndexCount; j > 0; --j)
		{
			activeListAABBIndex = activeListIndex[j - 1];

			if (aabbs[activeListAABBIndex].maxPoint.x < aabbs[i].minPoint.x)
			{
				erase_element(activeListIndex, activeListIndexCount, j - 1); //remove from active list
				--activeListIndexCount;
			}
			else
			{
				//check collision AABB x AABB
				if (  (aabbs[i].maxPoint.x >= aabbs[activeListAABBIndex].minPoint.x && aabbs[i].minPoint.x <= aabbs[activeListAABBIndex].maxPoint.x)
					&&(aabbs[i].maxPoint.y >= aabbs[activeListAABBIndex].minPoint.y && aabbs[i].minPoint.y <= aabbs[activeListAABBIndex].maxPoint.y)
					&&(aabbs[i].maxPoint.z >= aabbs[activeListAABBIndex].minPoint.z && aabbs[i].minPoint.z <= aabbs[activeListAABBIndex].maxPoint.z))
				{
					indexes[aabbIndex++] = i;
					indexes[aabbIndex++] = activeListAABBIndex;
				}
			}
		}

		activeListIndex[activeListIndexCount++] = i;
	}

	ALLOC_RELEASE(activeListIndex);
	return SweepAndPruneResult(indexes, aabbIndex >> 1);
}

#ifdef OPENCL_ENABLED

static size_t sapProgramIndex = UINT_MAX;

void SweepAndPrune::init(GpuDevice* gpu, const char* buildOptions)
{
	if (sapProgramIndex != UINT_MAX)
		return;

	this->gpu = gpu;

	radixSorting = ALLOC_NEW(GpuRadixSorting)();
	radixSorting->init(gpu, buildOptions);

	IFileManager* fileManager = Factory::getFileManagerInstance();

	std::string source = fileManager->readTextFile("SweepAndPruneKdop.cl");

	sapProgramIndex = gpu->commandManager->cacheProgram(source.c_str(), sizeof(char) * source.length(), buildOptions);

	delete fileManager;
}

SweepAndPruneResult SweepAndPrune::findCollisionsGPU(float* input, size_t inputLength, size_t strider, size_t offset, size_t minPointIndex, size_t maxPointIndex)
{
	const size_t globalWorkSize[3] = { gpu->maxWorkGroupSize, 0, 0 };
	const size_t localWorkSize[3] = { nextPowOf2(inputLength) / gpu->maxWorkGroupSize, 0, 0 };
	size_t globalIndex = 0;

	size_t outputSize = inputLength * 2 * SIZEOF_UINT;
	size_t* outputIndexes = ALLOC_ARRAY(size_t, inputLength * 2);
	cl_mem output = gpu->createBuffer(outputIndexes, outputSize, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, false);

	radixSorting->setParameters(input, inputLength, strider, offset);
	cl_mem indexes = radixSorting->execute();

	size_t* in = ALLOC_ARRAY(size_t, inputLength);
	gpu->commandManager->executeReadBuffer(indexes, inputLength * SIZEOF_UINT, in, true);

	GpuCommand* command = gpu->commandManager->createCommand();
	command
		->setInputParameter(radixSorting->inputGpu, inputLength * strider * SIZEOF_FLOAT)
		->setInputParameter(radixSorting->indexesLengthGpu, SIZEOF_UINT)
		->setInputParameter(indexes, inputLength * SIZEOF_UINT)
		->setInputParameter(radixSorting->offsetGpu, SIZEOF_UINT)
		->setInputParameter(&minPointIndex, SIZEOF_UINT, CL_MEM_READ_ONLY)
		->setInputParameter(&maxPointIndex, SIZEOF_UINT, CL_MEM_READ_ONLY)
		->setInputParameter(&globalIndex, SIZEOF_UINT, CL_MEM_READ_WRITE)
		->setInputParameter(output, outputSize)
		->buildFromProgram(gpu->commandManager->cachedPrograms[sapProgramIndex], "sweepAndPrune")
		->execute(1, globalWorkSize, localWorkSize);

	gpu->commandManager->executeReadBuffer(output, outputSize, outputIndexes, true);

	globalIndex = *command->fetchInOutParameter<size_t>(7) >> 1; //divide by 2

	command->~GpuCommand();
	gpu->releaseBuffer(indexes);
	return SweepAndPruneResult(outputIndexes, globalIndex);
}

#endif

SweepAndPrune::~SweepAndPrune()
{
#if OPENCL_ENABLED
	ALLOC_DELETE(radixSorting, GpuRadixSorting);
#endif
}