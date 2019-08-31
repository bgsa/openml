#include "AlgorithmSorting.h"

static size_t bitonicSortProgramIndex;
static size_t radixSortProgramIndex;

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

	float* output = ALLOC_ARRAY(float, n);
	size_t* digitsCache = ALLOC_ARRAY(size_t, n);
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

	ALLOC_RELEASE(output);
}

void AlgorithmSorting::radix(size_t *vector, size_t n)
{
	size_t maxElement = 0;

	for (size_t i = 0; i < n; i++)
		if (vector[i] > maxElement)
			maxElement = vector[i];

	size_t maxDigit = digitCount(maxElement);

	size_t* output = ALLOC_ARRAY(size_t, n);
	size_t* digitsCache = ALLOC_ARRAY(size_t, n);
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

	ALLOC_RELEASE(output);
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

	int* output = ALLOC_ARRAY(int, n);
	int* digitsCache = ALLOC_ARRAY(int, n);
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

	ALLOC_RELEASE(output);
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
	size_t* index = ALLOC_ARRAY(size_t, count);

	std::iota(index, index + count, 0); // fill index with {0,1,2,...} This only needs to happen once

	std::sort(index, index + count, std::bind(compare, std::placeholders::_1, std::placeholders::_2, vector));

	return index;
}

template <typename T>
size_t* AlgorithmSorting::nativeIndex(T* vector, size_t count, bool(*comparator)(int, int, T*))
{
	size_t* index = ALLOC_ARRAY(size_t, count);

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

void AlgorithmSorting::init(GpuDevice* gpu)
{
	IFileManager* fileManager = Factory::getFileManagerInstance();

	std::string sourceRadixSort = fileManager->readTextFile("RadixSorting.cl");
	radixSortProgramIndex = gpu->commandManager->cacheProgram(sourceRadixSort.c_str(), sizeof(char) * sourceRadixSort.length());

	delete fileManager;
}

void AlgorithmSorting::radixGPU(GpuDevice* gpu, float* input, size_t n)
{
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
	//size_t iteraions = ((size_t)std::log(groupCount)) + 1;
	//size_t iteraions = ((size_t)std::log(elementsPerWorkItem)) + 1;
	size_t iteraions = ((size_t)std::log(gpu->maxWorkGroupSize)) + 1;

	const size_t inputBufferSize = sizeof(float) * n;
	const size_t offsetTableSize = sizeof(size_t) * 10 * threadsCount;
	size_t digitIndex = 3;
	size_t offset = 10;

	const cl_mem offsetTable1 = gpu->createBuffer(offsetTableSize, CL_MEM_READ_WRITE);
	const cl_mem offsetTable2 = gpu->createBuffer(offsetTableSize, CL_MEM_READ_WRITE);
	
	GpuCommand* commandRadix = gpu->commandManager->createCommand();
	commandRadix
		->setInputParameter(input, inputBufferSize, CL_MEM_READ_WRITE, true)
		->setInputParameter(&n, sizeof(size_t), CL_MEM_WRITE_ONLY, true)   //store on GPU
		->setInputParameter(&elementsPerWorkItem, sizeof(size_t), CL_MEM_WRITE_ONLY, true)  //store on GPU
		->setInputParameter(&digitIndex, sizeof(size_t))
		->setInputParameter(offsetTable1, offsetTableSize)
		->buildFromProgram(gpu->commandManager->cachedPrograms[radixSortProgramIndex], "count")
		->execute(1, globalWorkSize, localWorkSize);
	const cl_mem inputBuffer = commandRadix->getInputParameter(0);   //get buffer pointer from GPU
	const cl_mem elementsCount = commandRadix->getInputParameter(1); 
	const cl_mem elementsPerWorkItemBuffer = commandRadix->getInputParameter(2);

	GpuCommand* commandPrefixScan = gpu->commandManager->createCommand();
	commandPrefixScan
		->setInputParameter(offsetTable1, offsetTableSize)  //use buffer hosted GPU
		->setInputParameter(offsetTable2, offsetTableSize)
		->setInputParameter(elementsCount, sizeof(size_t))
		->setInputParameter(&offset, sizeof(size_t), CL_MEM_WRITE_ONLY, true)
		->buildFromProgram(gpu->commandManager->cachedPrograms[radixSortProgramIndex], "prefixScan")
		->execute(1, globalWorkSize, localWorkSize);
	const cl_mem offsetBuffer = commandPrefixScan->getInputParameter(3);

	size_t* o1 = commandRadix->fetchInOutParameter<size_t>(4);
	size_t* o2 = commandPrefixScan->fetchInOutParameter<size_t>(1);

	do
	{
		//TEST PREFIX SCAN INTERATION
		for (size_t i = 0; i < offset; i++)
			assert(o1[i] == o2[i]);
		for (size_t i = offset; i < threadsCount; i++)
			assert(o1[i - offset] + o1[i] == o2[i]);
		// */

		offset <<= 1;

		commandPrefixScan
			->swapInputParameter(0, 1)
			->updateInputParameter(3, &offset)
			->execute(1, globalWorkSize, localWorkSize);

		o1 = commandPrefixScan->fetchInOutParameter<size_t>(0);
		o2 = commandPrefixScan->fetchInOutParameter<size_t>(1);

	} while (offset < (threadsCount*10) >> 1);

	GpuCommand* commandReorder = gpu->commandManager->createCommand();
	commandReorder
		->setInputParameter(inputBuffer, inputBufferSize)   //use buffer hosted GPU
		->setInputParameter(offsetTable2, offsetTableSize)  
		->buildFromProgram(gpu->commandManager->cachedPrograms[radixSortProgramIndex], "reorder")
		->execute(1, globalWorkSize, localWorkSize);
	float* result = commandReorder->fetchInOutParameter<float>(0);

	//gpu->commandManager->executeReadBuffer(inputBuffer, inputBufferSize, input, true);

	/*//TEST ORDER
	for (size_t i = 1; i < n; ++i)
		assert(result[i - 1] <= result[i]);
	*/

	gpu->releaseBuffer(offsetTable2);
	gpu->releaseBuffer(offsetTable1);
	gpu->releaseBuffer(elementsCount);

	commandRadix->~GpuCommand();
	commandPrefixScan->~GpuCommand();
	//commandReorder->~GpuCommand();
}

#endif