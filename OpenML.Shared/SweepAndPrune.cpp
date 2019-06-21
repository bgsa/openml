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
	size_t* aabbIndexes1 = new size_t[count * 100];
	size_t* aabbIndexes2 = new size_t[count * 100];
	size_t aabbIndex = 0;

	size_t* candidates = new size_t[count];
	size_t candidatesCount = 0;
	
	size_t* activeListIndex = new size_t[count];
	size_t activeListIndexIndex = 0;
	
	AlgorithmSorting::quickSortNative(aabbs, count, sizeof(AABB<T>), comparatorXAxisForQuickSort);
	
	for (size_t i = 0; i < count; i++)
	{
		AABB<T> currentAABB = aabbs[i];
		bool hasCollision = false;

		for (size_t j = activeListIndexIndex; j > 0; j--)
		{
			if (aabbs[activeListIndex[j - 1]].maxPoint.x < currentAABB.minPoint.x)
			{
				erase_element(activeListIndex, count, j - 1); //remove from active list
				activeListIndexIndex --;
			}
			else
			{
				if (currentAABB.colisionStatus(aabbs[activeListIndex[j - 1]]) == ColisionStatus::INSIDE)
				{
					aabbIndexes1[aabbIndex] = i;
					aabbIndexes2[aabbIndex] = j - 1;
					aabbIndex ++;
				}

				/*
				aabbIndexes1[aabbIndex1++] = i;
				aabbIndexes2[aabbIndex2++] = j - 1;

				if (!hasCollision)
				{
					hasCollision = true;
					candidates[candidatesCount++] = i;
				}
				*/
			}
		}

		activeListIndex[activeListIndexIndex++] = i;
	}

	delete[] candidates, activeListIndex;
	
	return SweepAndPruneResult(aabbIndexes1, aabbIndexes2, aabbIndex);
}

template SweepAndPruneResult SweepAndPrune::findCollisions<int>(AABB<int>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisions<float>(AABB<float>*, size_t);
template SweepAndPruneResult SweepAndPrune::findCollisions<double>(AABB<double>*, size_t);