#include "AlgorithmSorting.h"

/*
// ---- utils for accessing 11-bit quantities
#define _0(x)	(x & 0x7FF)
#define _1(x)	(x >> 11 & 0x7FF)
#define _2(x)	(x >> 22 )

#if PREFETCH
#include <xmmintrin.h>	// for prefetch
#define pfval	64
#define pfval2	128
#define pf(x)	_mm_prefetch(cpointer(x + i + pfval), 0)
#define pf2(x)	_mm_prefetch(cpointer(x + i + pfval2), 0)
#else
#define pf(x)
#define pf2(x)
#endif

// ================================================================================================
// flip a float for sorting
//  finds SIGN of fp number.
//  if it's 1 (negative float), it flips all bits
//  if it's 0 (positive float), it flips the sign only
// ================================================================================================
inline size_t FloatFlip(size_t f)
{
	size_t mask = -int(f >> 31) | 0x80000000;
	return f ^ mask;
}

inline void FloatFlipX(size_t &f)
{
	size_t mask = -int(f >> 31) | 0x80000000;
	f ^= mask;
}

// ================================================================================================
// flip a float back (invert FloatFlip)
//  signed was flipped from above, so:
//  if sign is 1 (negative), it flips the sign bit back
//  if sign is 0 (positive), it flips all bits back
// ================================================================================================
inline size_t IFloatFlip(size_t f)
{
	size_t mask = ((f >> 31) - 1) | 0x80000000;
	return f ^ mask;
}

float* AlgorithmSorting::radix(float* vector, size_t count)
{
	float* sorted = new float[count];

	size_t i;
	size_t *sort = (size_t*)sorted;
	size_t *array = (size_t*)vector;

	// 3 histograms on the stack:
	const size_t kHist = 2048;
	size_t b0[kHist * 3];

	size_t *b1 = b0 + kHist;
	size_t *b2 = b1 + kHist;

	for (i = 0; i < kHist * 3; i++)
		b0[i] = 0;
	//memset(b0, 0, kHist * 12);
	 
	// 1.  parallel histogramming pass
	for (i = 0; i < count; i++) 
	{
		pf(array);

		size_t fi = FloatFlip((size_t&)array[i]);

		b0[_0(fi)] ++;
		b1[_1(fi)] ++;
		b2[_2(fi)] ++;
	}

	// 2.  Sum the histograms -- each histogram entry records the number of values preceding itself.
	{
		size_t sum0 = 0, sum1 = 0, sum2 = 0;
		size_t tsum;
		for (i = 0; i < kHist; i++) 
		{
			tsum = b0[i] + sum0;
			b0[i] = sum0 - 1;
			sum0 = tsum;

			tsum = b1[i] + sum1;
			b1[i] = sum1 - 1;
			sum1 = tsum;

			tsum = b2[i] + sum2;
			b2[i] = sum2 - 1;
			sum2 = tsum;
		}
	}

	// byte 0: floatflip entire value, read/write histogram, write out flipped
	for (i = 0; i < count; i++) 
	{
		size_t fi = array[i];
		FloatFlipX(fi);
		size_t pos = _0(fi);

		pf2(array);
		sort[++b0[pos]] = fi;
	}

	// byte 1: read/write histogram, copy sorted -> array
	for (i = 0; i < count; i++) 
	{
		size_t si = sort[i];
		size_t pos = _1(si);
		pf2(sort);
		array[++b1[pos]] = si;
	}

	// byte 2: read/write histogram, copy & flip out array -> sorted
	for (i = 0; i < count; i++) 
	{
		size_t ai = array[i];
		size_t pos = _2(ai);

		pf2(array);

		sort[++b2[pos]] = IFloatFlip(ai);
	}

	return sorted;
}
*/

void AlgorithmSorting::radix(float* vector, size_t n)
{
	const size_t maxDigitMantissa = 4;
	int tempExp;
	int minElement = INT_MAX;
	int maxElement = 0;
	size_t exp;
	
	for (size_t i = 0; i < n; i++)
	{
		tempExp = (int)vector[i];

		if (tempExp > maxElement)
			maxElement = tempExp;

		if (tempExp < minElement)
			minElement = tempExp;
	}
	minElement = std::abs(minElement);
	int maxDigitExpoent = (int) digitCount(std::max(minElement, maxElement));

	float* output = new float[n];
	size_t* digitsCache = new size_t[n];
	const size_t bucketCount = 10;
	size_t bucket[bucketCount];
	size_t bucketIndex;

	for (size_t digitIndex = 0; digitIndex < maxDigitMantissa; digitIndex++)
	{
		std::memset(bucket, 0, sizeof(size_t) * bucketCount);

		for (size_t j = 0; j < n; j++)    //make histogram
		{
			bucketIndex = digitsCache[j] = digit(floatParts(vector[j], &exp), digitIndex);
			bucket[bucketIndex]++;
		}

		for (size_t j = 1; j < bucketCount; j++)
			bucket[j] += bucket[j - 1];

		for (int j = n - 1; j >= 0; j--)
		{
			bucketIndex = digitsCache[j];

			output[bucket[bucketIndex] - 1] = vector[j];
			bucket[bucketIndex]--;
		}

		std::memcpy(vector, output, sizeof(float) * n);
	}

	for (int digitIndex = 0; digitIndex < maxDigitExpoent; digitIndex++)
	{
		std::memset(bucket, 0, sizeof(size_t) * bucketCount);

		for (size_t j = 0; j < n; j++)    //make histogram
		{
			bucketIndex = digitsCache[j] = digit((int)vector[j] + minElement, digitIndex);
			bucket[bucketIndex]++;
		}

		for (size_t j = 1; j < bucketCount; j++)
			bucket[j] += bucket[j - 1];

		for (int j = n - 1; j >= 0; j--)
		{
			bucketIndex = digitsCache[j];

			output[bucket[bucketIndex] - 1] = vector[j];
			bucket[bucketIndex]--;
		}

		std::memcpy(vector, output, sizeof(float) * n);
	}

	delete[] output, digitsCache;
}

void AlgorithmSorting::radix(size_t *vector, size_t n)
{
	size_t maxElement = 0;

	for (size_t i = 0; i < n; i++)
		if (vector[i] > maxElement)
			maxElement = vector[i];

	size_t maxDigit = digitCount(maxElement);

	size_t* output = new size_t[n];
	size_t* digitsCache = new size_t[n];
	const size_t bucketCount = 10;
	size_t bucket[bucketCount];
	size_t bucketIndex;

	for (size_t digitIndex = 0; digitIndex < maxDigit; digitIndex++)
	{
		std::memset(bucket, 0, sizeof(size_t) * bucketCount);

		for (size_t j = 0; j < n; j++)    //make histogram
		{
			bucketIndex = digitsCache[j] = digit(vector[j], digitIndex);
			bucket[bucketIndex]++;
		}

		for (size_t j = 1; j < bucketCount; j++)
			bucket[j] += bucket[j - 1];

		for (int j = n - 1; j >= 0; j--)
		{
			bucketIndex = digitsCache[j];

			output[bucket[bucketIndex] - 1] = vector[j];
			bucket[bucketIndex]--;
		}

		std::memcpy(vector, output, sizeof(size_t) * n);
	}

	delete[] output, digitsCache;
}

void AlgorithmSorting::radix(int* vector, size_t n)
{
	int maxElement = INT_MIN;
	int minElement = INT_MAX;

	for (size_t i = 0; i < n; i++) 
	{
		if (vector[i] > maxElement)
			maxElement = vector[i];

		if (vector[i] < minElement)
			minElement = vector[i];
	}

	size_t maxDigit = digitCount(maxElement);
	maxDigit = std::max(maxDigit, digitCount(minElement));

	if (minElement > 0)
		minElement = 0;
	else
		minElement *= -1;

	int* output = new int[n];
	int* digitsCache = new int[n];
	const size_t bucketCount = 10;
	int bucket[bucketCount];
	size_t bucketIndex;

	for (size_t digitIndex = 0; digitIndex < maxDigit; digitIndex++)
	{
		std::memset(bucket, 0, sizeof(int) * bucketCount);

		for (size_t j = 0; j < n; j++)    //make histogram
		{
			bucketIndex = digitsCache[j] = digit(size_t(vector[j] + minElement), digitIndex);
			bucket[bucketIndex]++;
		}

		for (size_t j = 1; j < bucketCount; j++)
			bucket[j] += bucket[j - 1];

		for (int j = n - 1; j >= 0; j--)
		{
			bucketIndex = digitsCache[j];

			output[bucket[bucketIndex] - 1] = vector[j];
			bucket[bucketIndex]--;
		}

		std::memcpy(vector, output, sizeof(int) * n);
	}

	delete[] output, digitsCache;
}

void AlgorithmSorting::native(float* vector, size_t count)
{
	std::sort(vector, vector + count, std::less<float>());
}

bool compare(int a, int b, float* data)
{
	return data[a] < data[b];
}

size_t* AlgorithmSorting::nativeIndex(float* vector, size_t count)
{
	size_t* index = new size_t[count];

	std::iota(index, index + count, 0); // fill index with {0,1,2,...} This only needs to happen once

	std::sort(index, index + count, std::bind(compare, std::placeholders::_1, std::placeholders::_2, vector));

	return index;
}

template <typename T>
size_t* AlgorithmSorting::nativeIndex(T* vector, size_t count, bool(*comparator)(int, int, T*))
{
	size_t* index = new size_t[count];

	std::iota(index, index + count, 0); // fill index with {0,1,2,...} This only needs to happen once

	std::sort(index, index + count, std::bind(comparator, std::placeholders::_1, std::placeholders::_2, vector));
		
	return index;
}
template size_t* AlgorithmSorting::nativeIndex(AABB<int>* vector, size_t count, bool(*comparator)(int, int, AABB<int>*));
template size_t* AlgorithmSorting::nativeIndex(AABB<float>* vector, size_t count, bool(*comparator)(int, int, AABB<float>*));
template size_t* AlgorithmSorting::nativeIndex(AABB<double>* vector, size_t count, bool(*comparator)(int, int, AABB<double>*));


void AlgorithmSorting::quickSortNative(void* vector, size_t count, size_t sizeOfOneElement, int(*comparator)(const void*, const void*))
{
	std::qsort(vector, count, sizeOfOneElement, comparator);
}

#ifdef OPENCL_ENABLED

void AlgorithmSorting::radixGPU(GpuDevice* gpu, float* input, size_t n)
{
	IFileManager* fileManager = Factory::getFileManagerInstance();
	
	// 2^17 elementos
	// Total de 1024 threads executando
	// 8 grupos
	// 128 threads em cada grupo
	// cada thread processa 128 elementos
	const size_t countAsPowOf2 = nextPowOf2(n); //required for OpenCL
	size_t elementsPerWorkItem = countAsPowOf2 / gpu->maxWorkGroupSize;
	const size_t threadsCount = countAsPowOf2 / elementsPerWorkItem; 
	size_t globalWorkSize[3] = { threadsCount, 0 , 0 };
	size_t localWorkSize[3] = { elementsPerWorkItem, 0, 0 };
	const size_t groupCount = threadsCount / elementsPerWorkItem;
	size_t elementsPerGroup = elementsPerWorkItem * elementsPerWorkItem;
	size_t iteraions = ((size_t) std::log(groupCount)) + 1;
	size_t inputBufferSize = sizeof(float) * n;

	std::string sourceRadixSort = fileManager->readTextFile("RadixSortingByGroup.cl");
	sourceRadixSort = sourceRadixSort.insert(0, "#define ELEMENTS_PER_WORKITEM (" + StringHelper::toString(elementsPerWorkItem) + ")   \n");
	std::string sourceBitonicSort = fileManager->readTextFile("BitonicSorting2Groups.cl");

	size_t bitonicSortProgramIndex = gpu->commandManager->cacheProgram(sourceBitonicSort.c_str(), sizeof(char) * sourceBitonicSort.length());
	size_t radixSortProgramIndex = gpu->commandManager->cacheProgram(sourceRadixSort.c_str(), sizeof(char) * sourceRadixSort.length());

	GpuCommand* command = gpu->commandManager->createCommand();
	command
		->setInputParameter(input, inputBufferSize, CL_MEM_READ_WRITE, true)
		->setInputParameter(&n, sizeof(float), CL_MEM_READ_ONLY, true)
		->setOutputParameter(inputBufferSize)
		->buildFromProgram(gpu->commandManager->cachedPrograms[radixSortProgramIndex], "sort")
		->execute(1, globalWorkSize, localWorkSize);
	cl_mem inputBuffer = command->getInputParameter(0);
	cl_mem inputMemBufferSize = command->getInputParameter(1);
	delete command;

	do
	{
		localWorkSize[0] = elementsPerWorkItem;

		command = gpu->commandManager->createCommand();
		command
			->setInputParameter(inputBuffer, inputBufferSize)
			->setInputParameter(inputMemBufferSize, sizeof(float))
			->buildFromProgram(gpu->commandManager->cachedPrograms[bitonicSortProgramIndex], "sort")
			->execute(1, globalWorkSize, localWorkSize);
		delete command;

		command = gpu->commandManager->createCommand();
		command
			->setInputParameter(inputBuffer, inputBufferSize)
			->setInputParameter(inputMemBufferSize, sizeof(float))
			->setOutputParameter(inputBufferSize)
			->buildFromProgram(gpu->commandManager->cachedPrograms[radixSortProgramIndex], "sort")
			->execute(1, globalWorkSize, localWorkSize);
		delete command;

		/*
		// check the command is correct ! (TEST)
		for (size_t groups = 1; groups < n; groups += 2 * elementsPerGroup)
			for (size_t i = groups; i < groups + 2 * elementsPerGroup - 1; i++)
				assert(input[i - 1] <= input[i]);
		*/

		elementsPerWorkItem *= 2;
		elementsPerGroup *= 2;
		--iteraions;
	} while (iteraions > 0);


	/*
	for (size_t i = 1; i < n; ++i)
		assert(input[i - 1] <= input[i]);
	*/

	gpu->commandManager->executeReadBuffer(inputBuffer, inputBufferSize, input, true);
	HANDLE_OPENCL_ERROR(clReleaseMemObject(inputBuffer));
	HANDLE_OPENCL_ERROR(clReleaseMemObject(inputMemBufferSize));
	delete fileManager;
}

#endif