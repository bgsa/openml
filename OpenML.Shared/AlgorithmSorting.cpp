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

// ================================================================================================
// Main radix sort
// ================================================================================================
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

class RadixIntComparator
{
private:
	const int bit; // bit position [0..31] to examine

public:
	RadixIntComparator(int offset) : bit(offset) {} // constructor

	bool operator()(int value) const // function call operator
	{
		if (bit == 31) // sign bit
			return value < 0; // negative int to left partition
		else
			return !(value & (1 << bit)); // 0 bit to left partition
	}
};

// Least significant digit radix sort
void lsd_radix_sort(int *first, int *last)
{
	for (int lsb = 0; lsb < 32; ++lsb) // least-significant-bit
	{
		std::stable_partition(first, last, RadixIntComparator(lsb));
	}
}

// Most significant digit radix sort (recursive)
void msd_radix_sort(int *first, int *last, int msb = 31)
{
	if (first != last && msb >= 0)
	{
		int *mid = std::partition(first, last, RadixIntComparator(msb));
		msb--; // decrement most-significant-bit
		msd_radix_sort(first, mid, msb); // sort left partition
		msd_radix_sort(mid, last, msb); // sort right partition
	}
}

void AlgorithmSorting::radix(int *data, size_t n)
{
	msd_radix_sort(data, data + n);
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