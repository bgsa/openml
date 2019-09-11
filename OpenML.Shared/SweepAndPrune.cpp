#include "SweepAndPrune.h"

template <typename T>
bool comparatorXAxisForNativeSort(int index1, int index2, AABB<T>* aabbs)
{
	return aabbs[index1].minPoint[0] < aabbs[index2].minPoint[0];
}
template bool comparatorXAxisForNativeSort(int index1, int index2, AABB<int>* aabbs);
template bool comparatorXAxisForNativeSort(int index1, int index2, AABB<float>* aabbs);
template bool comparatorXAxisForNativeSort(int index1, int index2, AABB<double>* aabbs);


int comparatorXAxisForQuickSort(const void* a, const void* b) 
{
	AABB<float>* obj1 = (AABB<float>*) a;
	AABB<float>* obj2 = (AABB<float>*) b;

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

template <typename T>
SweepAndPruneResult SweepAndPrune::findCollisions(AABB<T>* aabbs, size_t count)
{
	size_t* aabbIndexes = ALLOC_ARRAY(size_t, count*2);
	size_t aabbIndex = 0;

	size_t* activeListIndex = ALLOC_ARRAY(size_t, count);
	size_t activeListIndexCount = 0;
	size_t activeListAABBIndex = 0;
	
	AlgorithmSorting::quickSortNative(aabbs, count, sizeof(AABB<T>), comparatorXAxisForQuickSort);
	
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
					aabbIndexes[aabbIndex++] = i;
					aabbIndexes[aabbIndex++] = activeListAABBIndex;
				}
			}
		}

		activeListIndex[activeListIndexCount++] = i;
	}

	ALLOC_RELEASE(activeListIndex);
	return SweepAndPruneResult(aabbIndexes, aabbIndex >> 1);
}
template SweepAndPruneResult SweepAndPrune::findCollisions<int>(AABB<int>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisions<float>(AABB<float>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisions<double>(AABB<double>*, size_t);

#if OPENCL_ENABLED

static size_t sapProgramIndex = UINT_MAX;

void SweepAndPrune::init(GpuDevice* gpu)
{
	if (sapProgramIndex != UINT_MAX)
		return;

	AlgorithmSorting::init(gpu);

	IFileManager* fileManager = Factory::getFileManagerInstance();

	std::string source = fileManager->readTextFile("SweepAndPrune.cl");

	sapProgramIndex = gpu->commandManager->cacheProgram(source.c_str(), sizeof(char) * source.length());

	delete fileManager;
}

template <typename T>
SweepAndPruneResult SweepAndPrune::findCollisionsGPU(GpuDevice* gpu, AABB<T>* aabbs, size_t count)
{
	const size_t globalWorkSize[3] = { gpu->maxWorkGroupSize, 0, 0 };
	const size_t localWorkSize[3] = { nextPowOf2(count) / gpu->maxWorkGroupSize, 0, 0 };
	size_t globalIndex = 0;

	cl_mem* buffers = AlgorithmSorting::radixGPUBuffer(gpu, (float*) aabbs, count, 7, 1);
	cl_mem elementsBuffer = buffers[0];
	cl_mem indexesBuffer = buffers[1];

	GpuCommand* command = gpu->commandManager->createCommand();
	size_t* aabbIndexes = command
		->setInputParameter((float*)aabbs, sizeof(AABB<T>) * count)
		->setInputParameter(&count, SIZEOF_UINT)
		->setInputParameter(&globalIndex, SIZEOF_UINT)
		->setInputParameter(buffers[1], SIZEOF_UINT * count)
		->setOutputParameter(SIZEOF_UINT * count * 2)
		->buildFromProgram(gpu->commandManager->cachedPrograms[sapProgramIndex], "sweepAndPrune")
		->execute(1, globalWorkSize, localWorkSize)
		->fetch<size_t>();
	
	globalIndex = *command->fetchInOutParameter<size_t>(2) >> 1; //divide by 2

	command->~GpuCommand();
	gpu->releaseBuffer(indexesBuffer);
	gpu->releaseBuffer(elementsBuffer);
	return SweepAndPruneResult(aabbIndexes, globalIndex);
}
template SweepAndPruneResult SweepAndPrune::findCollisionsGPU<int>(GpuDevice* gpuCommandManager, AABB<int>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisionsGPU<float>(GpuDevice* gpuCommandManager, AABB<float>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisionsGPU<double>(GpuDevice* gpuCommandManager, AABB<double>*, size_t);

#endif