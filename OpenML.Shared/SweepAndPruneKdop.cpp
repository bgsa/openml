#include "SweepAndPruneKdop.h"

std::mutex sapMutex;
DOP18* kdopsGlobal = NULL;
size_t axisToSweep = 0;
size_t axisToSweep2= 0;

int comparatorAlignedAxisForQuickSortKdop(const void* a, const void* b)
{
	DOP18 obj1 = kdopsGlobal[*(size_t*)a];
	DOP18 obj2 = kdopsGlobal[*(size_t*)b];
	
	if (obj1.min[axisToSweep] < obj2.min[axisToSweep])
		return -1;
	else
		if (obj1.min[axisToSweep] > obj2.min[axisToSweep])
			return 1;

	return 0;
}

int comparatorPlaneAxisForQuickSortKdop(const void* a, const void* b)
{
	DOP18 obj1 = kdopsGlobal[*(size_t*)a];
	DOP18 obj2 = kdopsGlobal[*(size_t*)b];

	Vec3f centerObj1 = obj1.centerOfBoundingVolume();
	Vec3f centerObj2 = obj2.centerOfBoundingVolume();

	float translateXYObj1 = std::sqrt(centerObj1[axisToSweep] * centerObj1[axisToSweep] + centerObj1[axisToSweep2] * centerObj1[axisToSweep2]);
	float translateXYObj2 = std::sqrt(centerObj2[axisToSweep] * centerObj2[axisToSweep] + centerObj2[axisToSweep2] * centerObj2[axisToSweep2]);

	if (obj1.min[2] + translateXYObj1 < obj2.min[2] + translateXYObj2)
		return -1;
	else
		if (obj1.min[2] + translateXYObj1 > obj2.min[2] + translateXYObj2)
			return 1;

	return 0;
}

size_t* sortAndSweep(size_t* indixes, size_t& count, int swaapIndex, int(*comparator)(const void*, const void*))
{
#define CURRENT_ELEMENT kdopsGlobal[indixes[i]]
#define NEXT_ELEMENT kdopsGlobal[indixes[j]]
	axisToSweep = swaapIndex;

	size_t newActiveListIndex = 0;
	size_t* activeList = ALLOC_ARRAY(size_t, count * 10);

	AlgorithmSorting::quickSortNative(indixes, count, sizeof(size_t), comparator);

	for (size_t i = 0; i < count; i++)
	{
		for (size_t j = i+1; j < count 
			&& CURRENT_ELEMENT.max[swaapIndex] > NEXT_ELEMENT.min[swaapIndex]
			&& CURRENT_ELEMENT.min[swaapIndex] < NEXT_ELEMENT.max[swaapIndex]; j++)
		{
			activeList[newActiveListIndex++] = indixes[i];
			activeList[newActiveListIndex++] = indixes[j];
		}
	}

	count = newActiveListIndex;
	return activeList;

#undef CURRENT_ELEMENT
#undef NEXT_ELEMENT
}

size_t* sortAndSweepOriented(size_t* indixes, size_t& count, int swaapIndex, int axis1, int axis2, int(*comparator)(const void*, const void*))
{
#define CURRENT_ELEMENT kdopsGlobal[indixes[i]]
#define NEXT_ELEMENT kdopsGlobal[indixes[j]]
	axisToSweep = axis1;
	axisToSweep2 = axis2;

	size_t newActiveListIndex = 0;
	size_t* activeList = ALLOC_ARRAY(size_t, count * 10);

	AlgorithmSorting::quickSortNative(indixes, count, sizeof(size_t), comparatorPlaneAxisForQuickSortKdop);

	for (size_t i = 0; i < count; i++)
	{
		Vec3f centerObj1 = CURRENT_ELEMENT.centerOfBoundingVolume();
		float translateToPlaneObj1 = std::sqrt(centerObj1[axis1] * centerObj1[axis1] + centerObj1[axis2] * centerObj1[axis2]);

		for (size_t j = i + 1; j < count; j++)
		{
			Vec3f centerObj2 = NEXT_ELEMENT.centerOfBoundingVolume();
			float translateToPlaneObj2 = std::sqrt(centerObj2[axis1] * centerObj2[axis1] + centerObj2[axis2] * centerObj2[axis2]);

			if (CURRENT_ELEMENT.max[swaapIndex] + translateToPlaneObj1 > NEXT_ELEMENT.min[swaapIndex] + translateToPlaneObj2
				&& CURRENT_ELEMENT.min[swaapIndex] + translateToPlaneObj1 < NEXT_ELEMENT.max[swaapIndex] + translateToPlaneObj2)
			{
				activeList[newActiveListIndex++] = indixes[i];
				activeList[newActiveListIndex++] = indixes[j];
			}
			else
				break;
		}
	}

	count = newActiveListIndex;
	return activeList;

#undef CURRENT_ELEMENT
#undef NEXT_ELEMENT
}

size_t* removeDuplicatedIndexes(size_t* indexes, size_t& newKdopsCount)
{
	size_t j = 0;

	AlgorithmSorting::radix(indexes, newKdopsCount);

	size_t* newIndexes = ALLOC_ARRAY(size_t, newKdopsCount);
	
	newIndexes[0] = indexes[0];
	for (size_t i = 1; i < newKdopsCount; i++) // remove duplicated elements in par collision
		if (indexes[i] > newIndexes[j])
			newIndexes[++j] = indexes[i];

	newKdopsCount = j + 1;

	return newIndexes;
}

SweepAndPruneResult SweepAndPruneKdop::findCollisions(DOP18* kdops, size_t count)
{
	assert(kdops != NULL);
	sapMutex.lock();
	kdopsGlobal = kdops;

	size_t newKdopsCount = count;

	size_t* indexes = ALLOC_ARRAY(size_t, count);
	for (size_t i = 0; i < count; i++)
		indexes[i] = i;

	size_t* newIndexes = sortAndSweep(indexes, newKdopsCount, 0, comparatorAlignedAxisForQuickSortKdop);
	indexes = removeDuplicatedIndexes(newIndexes, newKdopsCount);

	newIndexes = sortAndSweep(indexes, newKdopsCount, 1, comparatorAlignedAxisForQuickSortKdop);
	indexes = removeDuplicatedIndexes(newIndexes, newKdopsCount);

	newIndexes = sortAndSweep(indexes, newKdopsCount, 2, comparatorAlignedAxisForQuickSortKdop);
	indexes = removeDuplicatedIndexes(newIndexes, newKdopsCount);

	// up-left or down-right
	newIndexes = sortAndSweepOriented(indexes, newKdopsCount, 3, 0, 1, comparatorPlaneAxisForQuickSortKdop);
	indexes = removeDuplicatedIndexes(newIndexes, newKdopsCount);

	// up-right or down-left
	newIndexes = sortAndSweepOriented(indexes, newKdopsCount, 4, 0, 1, comparatorPlaneAxisForQuickSortKdop);
	indexes = removeDuplicatedIndexes(newIndexes, newKdopsCount);

	// up-front or down-depth
	newIndexes = sortAndSweepOriented(indexes, newKdopsCount, 5, 1, 2, comparatorPlaneAxisForQuickSortKdop);
	indexes = removeDuplicatedIndexes(newIndexes, newKdopsCount);

	// up-depth or down-front
	newIndexes = sortAndSweepOriented(indexes, newKdopsCount, 6, 1, 2, comparatorPlaneAxisForQuickSortKdop);
	indexes = removeDuplicatedIndexes(newIndexes, newKdopsCount);

	// left-depth or right-front
	newIndexes = sortAndSweepOriented(indexes, newKdopsCount, 7, 0, 2, comparatorPlaneAxisForQuickSortKdop);
	indexes = removeDuplicatedIndexes(newIndexes, newKdopsCount);

	// right-depth or left-front
	newIndexes = sortAndSweepOriented(indexes, newKdopsCount, 8, 0, 2, comparatorPlaneAxisForQuickSortKdop);
	//indexes = removeDuplicatedIndexes(newIndexes, newKdopsCount);

	ALLOC_RELEASE(indexes);
	kdopsGlobal = NULL;
	sapMutex.unlock();
	return SweepAndPruneResult(newIndexes, divideBy2(newKdopsCount));
}

#if OPENCL_ENABLED

static size_t sapKdopProgramIndex = UINT_MAX;

void SweepAndPruneKdop::init(GpuDevice* gpu)
{
	if (sapKdopProgramIndex != UINT_MAX)
		return;

	AlgorithmSorting::init(gpu);

	IFileManager* fileManager = Factory::getFileManagerInstance();

	std::string source = fileManager->readTextFile("SweepAndPruneKdop.cl");

	sapKdopProgramIndex = gpu->commandManager->cacheProgram(source.c_str(), sizeof(char) * source.length());

	delete fileManager;
}

SweepAndPruneResult SweepAndPruneKdop::findCollisions(GpuDevice* gpu, DOP18* kdops, size_t count)
{
	const size_t globalWorkSize[3] = { gpu->maxWorkGroupSize, 0, 0 };
	const size_t localWorkSize[3] = { nextPowOf2(count) / gpu->maxWorkGroupSize, 0, 0 };
	size_t globalIndex = 0;

	cl_mem* buffers = AlgorithmSorting::radixGPUBuffer(gpu, (float*)&kdops[0], count, 20, 2);
	cl_mem elementsBuffer = buffers[0];
	cl_mem indexesBuffer = buffers[1];

	GpuCommand* command = gpu->commandManager->createCommand();
	size_t* indexes = command
		->setInputParameter((float*)kdops, sizeof(DOP18) * count)
		->setInputParameter(&count, SIZEOF_UINT)
		->setInputParameter(&globalIndex, SIZEOF_UINT)
		->setInputParameter(buffers[1], SIZEOF_UINT * count)
		->setOutputParameter(SIZEOF_UINT * count * 2)
		->buildFromProgram(gpu->commandManager->cachedPrograms[sapKdopProgramIndex], "sweepAndPrune")
		->execute(1, globalWorkSize, localWorkSize)
		->fetch<size_t>();

	globalIndex = divideBy2(*command->fetchInOutParameter<size_t>(2));

	command->~GpuCommand();
	gpu->releaseBuffer(indexesBuffer);
	gpu->releaseBuffer(elementsBuffer);
	return SweepAndPruneResult(indexes, globalIndex);

	return SweepAndPruneResult(NULL, 0);
}

#endif