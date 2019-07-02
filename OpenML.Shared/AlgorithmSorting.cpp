#include "AlgorithmSorting.h"

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
size_t FloatFlip(size_t f)
{
	size_t mask = -int(f >> 31) | 0x80000000;
	return f ^ mask;
}

void FloatFlipX(size_t &f)
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

void AlgorithmSorting::radix(size_t *vector, size_t n)
{
	size_t maxElement = 0;

	for (size_t i = 0; i < n; i++)
		if (vector[i] > maxElement)
			maxElement = vector[i];

	size_t maxDigit = digitCount(maxElement);

	size_t* output = new size_t[n];
	const size_t bucketCount = 10;
	size_t bucket[bucketCount];
	size_t value;

	for (size_t digitIndex = 0; digitIndex < maxDigit; digitIndex++)
	{
		std::memset(bucket, 0, sizeof(size_t) * bucketCount);

		for (size_t j = 0; j < n; j++)    //make histogram
		{
			value = digit(vector[j], digitIndex);
			bucket[value]++;
		}

		for (size_t j = 1; j < bucketCount; j++)
			bucket[j] += bucket[j - 1];

		for (int j = n - 1; j >= 0; j--)
		{
			value = digit(vector[j], digitIndex);

			output[bucket[value] - 1] = vector[j];
			bucket[value]--;
		}

		std::memcpy(vector, output, sizeof(size_t) * n);
	}

	delete[] output;
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
