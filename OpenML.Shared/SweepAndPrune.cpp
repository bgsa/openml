#include "SweepAndPrune.h"

#include <list>
#include <forward_list>

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
	size_t activeListIndexIndex = 0;
	size_t activeListAABBIndex = 0;
	
	AlgorithmSorting::quickSortNative(aabbs, count, sizeof(AABB<T>), comparatorXAxisForQuickSort);
	
	for (size_t i = 0; i < count; i++)
	{
		Vec3<T> currentMaxPoint = aabbs[i].maxPoint;
		Vec3<T> currentMinPoint = aabbs[i].minPoint;

		for (size_t j = activeListIndexIndex; j > 0; j--)
		{
			activeListAABBIndex = activeListIndex[j - 1];

			if (aabbs[activeListAABBIndex].maxPoint.x < currentMinPoint.x)
			{
				erase_element(activeListIndex, activeListIndexIndex + 1, j - 1); //remove from active list
				activeListIndexIndex --;
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

		activeListIndex[activeListIndexIndex++] = i;
	}

	delete[] activeListIndex;
	
	return SweepAndPruneResult(aabbIndexes1, aabbIndexes2, aabbIndex);
}

template SweepAndPruneResult SweepAndPrune::findCollisions<int>(AABB<int>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisions<float>(AABB<float>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisions<double>(AABB<double>*, size_t);