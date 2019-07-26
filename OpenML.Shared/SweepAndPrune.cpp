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
	size_t* aabbIndexes1 = new size_t[count];
	size_t* aabbIndexes2 = new size_t[count];
	size_t aabbIndex = 0;
		
	size_t* activeListIndex = new size_t[count];
	size_t activeListIndexCount = 0;
	size_t activeListAABBIndex = 0;
	
	AlgorithmSorting::quickSortNative(aabbs, count, sizeof(AABB<T>), comparatorXAxisForQuickSort);
	
	for (size_t i = 0; i < count; i++)
	{
		Vec3<T> currentMaxPoint = aabbs[i].maxPoint;
		Vec3<T> currentMinPoint = aabbs[i].minPoint;

		for (size_t j = activeListIndexCount; j > 0; j--)
		{
			activeListAABBIndex = activeListIndex[j - 1];

			if (aabbs[activeListAABBIndex].maxPoint.x < currentMinPoint.x)
			{
				erase_element(activeListIndex, activeListIndexCount, j - 1); //remove from active list
				activeListIndexCount --;
			}
			else
			{
				//check collision AABB x AABB
				if (  (currentMaxPoint.x > aabbs[activeListAABBIndex].minPoint.x && currentMinPoint.x < aabbs[activeListAABBIndex].maxPoint.x)
					&&(currentMaxPoint.y > aabbs[activeListAABBIndex].minPoint.y && currentMinPoint.y < aabbs[activeListAABBIndex].maxPoint.y)
					&&(currentMaxPoint.z > aabbs[activeListAABBIndex].minPoint.z && currentMinPoint.z < aabbs[activeListAABBIndex].maxPoint.z))
				{
					aabbIndexes1[aabbIndex] = i;
					aabbIndexes2[aabbIndex] = j - 1;
					aabbIndex ++;
				}
			}
		}

		activeListIndex[activeListIndexCount++] = i;
	}

	delete[] activeListIndex;
	
	return SweepAndPruneResult(aabbIndexes1, aabbIndexes2, aabbIndex);
}
template SweepAndPruneResult SweepAndPrune::findCollisions<int>(AABB<int>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisions<float>(AABB<float>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisions<double>(AABB<double>*, size_t);

#if OPENCL_ENABLED

template <typename T>
SweepAndPruneResult SweepAndPrune::findCollisionsGPU(GpuCommandManager* gpuCommandManager, AABB<T>* aabbs, size_t count)
{
	IFileManager* fileManager = Factory::getFileManagerInstance();
	std::string source = fileManager->readTextFile("SweepAndPrune.cl");
	size_t globalIndex = 0;

	size_t globalWorkSize[3] = { nextPowOf2(count), 0, 0 };
	size_t localWorkSize[3] = { 64, 0, 0 };
	
	const size_t outputCount = count * 3 * 2;

	AlgorithmSorting::quickSortNative(aabbs, count, sizeof(AABB<T>), comparatorXAxisForQuickSort);

	T* points = new T[outputCount];

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

	GpuCommand* command = gpuCommandManager->createCommand();

	T* output = command
		->setInputParameter(points, sizeof(T) * outputCount)
		->setInputParameter(&count, sizeof(size_t))
		->setInputParameter(&globalIndex, sizeof(size_t), CL_MEM_READ_WRITE)
		->setOutputParameter(sizeof(T) * count * 2)
		->build(source.c_str(), sizeof(char) * source.length(), "sweepAndPrune")
		->execute(1, globalWorkSize, localWorkSize)
		->fetch<T>();
	
	globalIndex = *command->fetchInOutParameter<size_t>(2);

	size_t* aabbIndex1 = new size_t[globalIndex / 2];
	size_t* aabbIndex2 = new size_t[globalIndex / 2];
	for (size_t i = 0; i < globalIndex / 2; i++)
	{
		aabbIndex1[i] = size_t(points[i * 2]);
		aabbIndex2[i] = size_t(points[i * 2 + 1]);
	}

	delete fileManager, command;
	delete[] points;
	return SweepAndPruneResult(aabbIndex1, aabbIndex2, globalIndex / 2);
}
template SweepAndPruneResult SweepAndPrune::findCollisionsGPU<int>(GpuCommandManager* gpuCommandManager, AABB<int>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisionsGPU<float>(GpuCommandManager* gpuCommandManager, AABB<float>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisionsGPU<double>(GpuCommandManager* gpuCommandManager, AABB<double>*, size_t);

#endif