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
	size_t* aabbIndexes1 = ALLOC_ARRAY(size_t, count);
	size_t* aabbIndexes2 = ALLOC_ARRAY(size_t, count);
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
					aabbIndexes1[aabbIndex] = i;
					aabbIndexes2[aabbIndex] = activeListAABBIndex;
					++aabbIndex;
				}
			}
		}

		activeListIndex[activeListIndexCount++] = i;
	}

	ALLOC_RELEASE(activeListIndex);
	return SweepAndPruneResult(aabbIndexes1, aabbIndexes2, aabbIndex);
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

	IFileManager* fileManager = Factory::getFileManagerInstance();

	std::string source = fileManager->readTextFile("SweepAndPrune.cl");

	sapProgramIndex = gpu->commandManager->cacheProgram(source.c_str(), sizeof(char) * source.length());

	delete fileManager;
}

template <typename T>
SweepAndPruneResult SweepAndPrune::findCollisionsGPU(GpuDevice* gpu, AABB<T>* aabbs, size_t count)
{
	size_t globalIndex = 0;
	size_t globalWorkSize[3] = { nextPowOf2(count), 0, 0 };
	size_t localWorkSize[3] = { 64, 0, 0 };
	
	const size_t outputCount = count * 3 * 2;

	AlgorithmSorting::quickSortNative(aabbs, count, sizeof(AABB<T>), comparatorXAxisForQuickSort);

	T* points = ALLOC_ARRAY(T, outputCount);
	size_t index = 0;
	for (size_t i = 0; i < count; i++)
	{
		points[index + 0] = aabbs[i].minPoint.x;
		points[index + 1] = aabbs[i].minPoint.y;
		points[index + 2] = aabbs[i].minPoint.z;

		points[index + 3] = aabbs[i].maxPoint.x;
		points[index + 4] = aabbs[i].maxPoint.y;
		points[index + 5] = aabbs[i].maxPoint.z;

		index += 6;
	}

	GpuCommand* command = gpu->commandManager->createCommand();

	size_t* output = command
		->setInputParameter(points, sizeof(T) * outputCount, CL_MEM_READ_ONLY)
		->setInputParameter(&count, sizeof(size_t), CL_MEM_READ_ONLY)
		->setInputParameter(&globalIndex, sizeof(size_t), CL_MEM_READ_WRITE)
		->setOutputParameter(sizeof(size_t) * count * 2)
		->buildFromProgram(gpu->commandManager->cachedPrograms[sapProgramIndex], "sweepAndPrune")
		->execute(1, globalWorkSize, localWorkSize)
		->fetch<size_t>();
	
	globalIndex = *command->fetchInOutParameter<size_t>(2) >> 1; //divide by 2

	size_t* aabbIndex1 = ALLOC_ARRAY(size_t, globalIndex);
	size_t* aabbIndex2 = ALLOC_ARRAY(size_t, globalIndex);
	for (size_t i = 0; i < globalIndex; i++)
	{
		aabbIndex1[i] = output[i * 2];
		aabbIndex2[i] = output[i * 2 + 1];
	}

	command->~GpuCommand();
	return SweepAndPruneResult(aabbIndex1, aabbIndex2, globalIndex);
}
template SweepAndPruneResult SweepAndPrune::findCollisionsGPU<int>(GpuDevice* gpuCommandManager, AABB<int>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisionsGPU<float>(GpuDevice* gpuCommandManager, AABB<float>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisionsGPU<double>(GpuDevice* gpuCommandManager, AABB<double>*, size_t);

#endif