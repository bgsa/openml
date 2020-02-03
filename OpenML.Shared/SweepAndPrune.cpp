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

void SweepAndPrune::init(GpuDevice* gpu)
{
	if (sapProgramIndex != UINT_MAX)
		return;

	radixSorting = ALLOC_NEW(GpuRadixSorting)();
	radixSorting->init(gpu);

	IFileManager* fileManager = Factory::getFileManagerInstance();

	std::string source = fileManager->readTextFile("SweepAndPrune.cl");

	sapProgramIndex = gpu->commandManager->cacheProgram(source.c_str(), sizeof(char) * source.length());

	delete fileManager;
}

SweepAndPruneResult SweepAndPrune::findCollisionsGPU(GpuDevice* gpu, AABB* aabbs, size_t count)
{
	const size_t globalWorkSize[3] = { gpu->maxWorkGroupSize, 0, 0 };
	const size_t localWorkSize[3] = { nextPowOf2(count) / gpu->maxWorkGroupSize, 0, 0 };
	size_t globalIndex = 0;

	//cl_mem* buffers = AlgorithmSorting::radixGPUBuffer(gpu, (float*) aabbs, count, 8, 2);
	radixSorting->setParameters((float*)aabbs, count, 8, 2);
	cl_mem indexesBuffer = radixSorting->execute();

	GpuCommand* command = gpu->commandManager->createCommand();
	size_t* indexes = command
		->setInputParameter((float*)aabbs, sizeof(AABB) * count)
		->setInputParameter(&count, SIZEOF_UINT)
		->setInputParameter(&globalIndex, SIZEOF_UINT)
		->setInputParameter(indexesBuffer, SIZEOF_UINT * count)
		->setOutputParameter(SIZEOF_UINT * count * 2)
		->buildFromProgram(gpu->commandManager->cachedPrograms[sapProgramIndex], "sweepAndPrune")
		->execute(1, globalWorkSize, localWorkSize)
		->fetch<size_t>();
	
	globalIndex = *command->fetchInOutParameter<size_t>(2) >> 1; //divide by 2

	command->~GpuCommand();
	gpu->releaseBuffer(indexesBuffer);
	return SweepAndPruneResult(indexes, globalIndex);
}

#endif

SweepAndPrune::~SweepAndPrune()
{
#if OPENCL_ENABLED
	ALLOC_DELETE(radixSorting, GpuRadixSorting);
#endif
}