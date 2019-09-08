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

	float* output = ALLOC_ARRAY(float, n);
	size_t* digitsCache = ALLOC_ARRAY(size_t, n);
	const size_t bucketCount = 10;
	size_t bucket[bucketCount];
	size_t bucketIndex;

	for (size_t digitIndex = 0; digitIndex < maxDigitMantissa; digitIndex++)
	{
		std::memset(bucket, 0, SIZEOF_UINT * bucketCount);

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

		std::memcpy(vector, output, SIZEOF_FLOAT * n);
	}

	for (int digitIndex = 0; digitIndex < maxDigitExpoent; digitIndex++)
	{
		std::memset(bucket, 0, SIZEOF_UINT * bucketCount);

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

		std::memcpy(vector, output, SIZEOF_FLOAT * n);
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
		std::memset(bucket, 0, SIZEOF_UINT * bucketCount);

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

		std::memcpy(vector, output, SIZEOF_UINT * n);
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
		std::memset(bucket, 0, SIZEOF_INT * bucketCount);

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

		std::memcpy(vector, output, SIZEOF_INT * n);
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

static size_t radixSortProgramIndex = UINT_MAX;

void AlgorithmSorting::init(GpuDevice* gpu)
{
	if (radixSortProgramIndex != UINT_MAX)
		return;

	gpuCommands_init(gpu);

	IFileManager* fileManager = Factory::getFileManagerInstance();

	std::string sourceRadixSort = fileManager->readTextFile("RadixSorting.cl");
	radixSortProgramIndex = gpu->commandManager->cacheProgram(sourceRadixSort.c_str(), SIZEOF_CHAR * sourceRadixSort.length());

	delete fileManager;
}

cl_mem* AlgorithmSorting::radixGPUBuffer(GpuDevice* gpu, float* input, size_t n, size_t strider, size_t offsetParameter)
{
	const float* minMaxValues = gpuCommands_findMinMaxGPU(gpu, input, n, strider, offsetParameter);
	float minValue = minMaxValues[0];

	const size_t countAsPowOf2 = nextPowOf2(n); //required for OpenCL
	size_t elementsPerWorkItem = countAsPowOf2 / gpu->maxWorkGroupSize;
	const size_t threadsCount = countAsPowOf2 / elementsPerWorkItem;
	const size_t globalWorkSize[3] = { threadsCount, 0 , 0 };
	const size_t localWorkSize[3] = { elementsPerWorkItem, 0, 0 };

	const size_t inputBufferSize = SIZEOF_FLOAT * n * strider;
	const size_t offsetTableSize = SIZEOF_UINT * 10 * threadsCount;
	size_t maxDigits = MAX_DIGITS_MANTISSA - 1;
	bool useExpoent = false;
	size_t digitIndex = 0;
	size_t offset = 10;

	const cl_mem inputBuffer = gpu->createBuffer(inputBufferSize, CL_MEM_READ_ONLY);
	const cl_mem outputBuffer = gpu->createBuffer(inputBufferSize, CL_MEM_READ_ONLY);
	const cl_mem offsetTable1 = gpu->createBuffer(offsetTableSize, CL_MEM_READ_ONLY);
	const cl_mem offsetTable2 = gpu->createBuffer(offsetTableSize, CL_MEM_READ_ONLY);
	const cl_mem offsetBuffer = gpu->createBuffer(SIZEOF_UINT, CL_MEM_READ_ONLY);
	const cl_mem digitIndexBuffer = gpu->createBuffer(SIZEOF_UINT, CL_MEM_READ_ONLY);
	cl_mem indexesInputBuffer = gpu->createBuffer(SIZEOF_UINT * n, CL_MEM_READ_ONLY);
	cl_mem indexesOutputBuffer = gpu->createBuffer(SIZEOF_UINT * n, CL_MEM_READ_ONLY);
	cl_mem offsetTableResult = NULL;

	gpu->commandManager->createCommand()
		->setInputParameter(&elementsPerWorkItem, SIZEOF_UINT, CL_MEM_READ_ONLY, false)
		->setInputParameter(indexesInputBuffer, SIZEOF_UINT * n)
		->buildFromProgram(gpu->commandManager->cachedPrograms[radixSortProgramIndex], "initIndexes")
		->execute(1, globalWorkSize, localWorkSize)
		->~GpuCommand();

	GpuCommand* commandCount = gpu->commandManager
		->createCommand()
		->setInputParameter(inputBuffer, inputBufferSize)
		->setInputParameter(&elementsPerWorkItem, SIZEOF_UINT, CL_MEM_READ_ONLY, false)  //store on GPU
		->setInputParameter(digitIndexBuffer, SIZEOF_UINT)
		->setInputParameter(&useExpoent, SIZEOF_BOOL, CL_MEM_READ_ONLY, false)
		->setInputParameter(&minValue, SIZEOF_FLOAT)
		->setInputParameter(offsetTable1, offsetTableSize)
		->setInputParameter(&strider, SIZEOF_UINT)
		->setInputParameter(&offsetParameter, SIZEOF_UINT)
		->buildFromProgram(gpu->commandManager->cachedPrograms[radixSortProgramIndex], "count")
		->updateInputParameterValue(0, input)
		->updateInputParameterValue(2, &digitIndex)
		->execute(1, globalWorkSize, localWorkSize);

	const cl_mem elementsPerWorkItemBuffer = commandCount->getInputParameter(1);
	const cl_mem useExpoentBuffer = commandCount->getInputParameter(3);
	const cl_mem minValueBuffer = commandCount->getInputParameter(4);
	const cl_mem striderBuffer = commandCount->getInputParameter(6);
	const cl_mem offsetParameterBuffer = commandCount->getInputParameter(7);

	GpuCommand* commandPrefixScan = gpu->commandManager
		->createCommand()
		->setInputParameter(offsetTable1, offsetTableSize)  //use buffer hosted GPU
		->setInputParameter(offsetTable2, offsetTableSize)
		->setInputParameter(offsetBuffer, SIZEOF_UINT)
		->buildFromProgram(gpu->commandManager->cachedPrograms[radixSortProgramIndex], "prefixScan")
		->updateInputParameterValue(2, &offset)
		->execute(1, globalWorkSize, localWorkSize);

	GpuCommand* commandReorder = gpu->commandManager
		->createCommand()
		->setInputParameter(inputBuffer, inputBufferSize)   //use buffer hosted GPU
		->setInputParameter(elementsPerWorkItemBuffer, SIZEOF_UINT)
		->setInputParameter(digitIndexBuffer, SIZEOF_UINT)
		->setInputParameter(useExpoentBuffer, SIZEOF_BOOL)
		->setInputParameter(offsetTableResult, offsetTableSize)
		->setInputParameter(minValueBuffer, SIZEOF_FLOAT)
		->setInputParameter(indexesOutputBuffer, SIZEOF_UINT * n)
		->setInputParameter(indexesInputBuffer, SIZEOF_UINT * n)
		->setInputParameter(outputBuffer, inputBufferSize)
		->setInputParameter(striderBuffer, SIZEOF_UINT)
		->setInputParameter(offsetParameterBuffer, SIZEOF_UINT)
		->buildFromProgram(gpu->commandManager->cachedPrograms[radixSortProgramIndex], "reorder");

	bool offsetChanged = false;

	do  // for each digit in one element
	{
		offsetChanged = false;

		do  // prefix scan
		{
			offset <<= 1;

			commandPrefixScan
				->swapInputParameter(0, 1)
				->updateInputParameterValue(2, &offset)
				->execute(1, globalWorkSize, localWorkSize);

			offsetChanged = !offsetChanged;

		} while (offset < (threadsCount * 10) >> 1);

		offsetTableResult = offsetChanged ? offsetTable1 : offsetTable2;

		commandReorder
			->updateInputParameter(4, offsetTableResult)
			->swapInputParameter(6,7)
			->execute(1, globalWorkSize, localWorkSize);

		if (++digitIndex > maxDigits)  // check the algorithm reach the result
		{
			if (useExpoent)
				break;

			useExpoent = true;
			digitIndex = 0;
			maxDigits = digitCount((int) (minMaxValues[1] + minValue));  // MAX_DIGITS_EXPOENT - 1;
			commandCount->updateInputParameterValue(3, &useExpoent);
		}

		commandCount
			->copyParameters(0, outputBuffer)
			->updateInputParameterValue(2, &digitIndex)
			->execute(1, globalWorkSize, localWorkSize);

		if (offsetTableResult)
			commandPrefixScan->swapInputParameter(0, 1);

		offset = 10;
		commandPrefixScan
			->updateInputParameterValue(2, &offset)
			->execute(1, globalWorkSize, localWorkSize);

	} while (true);

	gpu->releaseBuffer(digitIndexBuffer);
	gpu->releaseBuffer(offsetBuffer);
	gpu->releaseBuffer(offsetTable2);
	gpu->releaseBuffer(offsetTable1);
	//gpu->releaseBuffer(outputBuffer); //this parameter will be returned !
	//gpu->releaseBuffer(indexesOutputBuffer); //this parameter will be returned !
	gpu->releaseBuffer(indexesInputBuffer); //this parameter will be returned !
	gpu->releaseBuffer(inputBuffer);

	commandReorder->~GpuCommand();
	commandPrefixScan->~GpuCommand();
	commandCount->~GpuCommand();

	cl_mem* result = ALLOC_ARRAY(cl_mem, 2);
	result[0] = outputBuffer;
	result[1] = indexesOutputBuffer;

	return result;
}

float* AlgorithmSorting::radixGPU(GpuDevice* gpu, float* input, size_t n, size_t strider, size_t offset)
{
	cl_mem* buffers = radixGPUBuffer(gpu, input, n, strider, offset);
	cl_mem elementsBuffer = buffers[0];
	cl_mem indexesBuffer = buffers[1];

	gpu->commandManager->executeReadBuffer(elementsBuffer, SIZEOF_FLOAT * n, input, true);

	gpu->releaseBuffer(indexesBuffer);
	gpu->releaseBuffer(elementsBuffer);

	return input;
}

size_t* AlgorithmSorting::radixGPUIndexes(GpuDevice* gpu, float* input, size_t n, size_t strider, size_t offset)
{
	cl_mem* buffers = radixGPUBuffer(gpu, input, n, strider, offset);
	cl_mem elementsBuffer = buffers[0];
	cl_mem indexesBuffer = buffers[1];

	size_t* indexes = ALLOC_ARRAY(size_t, n);
	gpu->commandManager->executeReadBuffer(indexesBuffer, SIZEOF_UINT * n, indexes, true);

	gpu->releaseBuffer(indexesBuffer);
	gpu->releaseBuffer(elementsBuffer);

	return indexes;
}

#endif