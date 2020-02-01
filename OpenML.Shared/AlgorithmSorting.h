#pragma once

#include "OpenML.h"
#include <algorithm>
#include <functional>
#include <numeric>

#include "AABB.h"

#ifdef OPENCL_ENABLED
	#include "GpuCommands.h"
	#include "IFileManager.h"
	#include "Factory.h"
	#undef max
	#undef min
#endif

namespace OpenML
{

	class AlgorithmSorting
	{
	public:

		///<summary>
		///Fast sorting of numbers array using Counting method
		///Complexity O(n)
		///</summary>
		API_INTERFACE static void radix(int* vector, size_t count);

		///<summary>
		///Fast sorting of numbers array using Counting method
		///Complexity O(n)
		///</summary>
		API_INTERFACE static void radix(size_t* vector, size_t count);

		///<summary>
		///Fast sorting of numbers array using Radix method
		///Complexity O(n)
		///</summary>
		API_INTERFACE static void radix(float* vector, size_t count);

		///<summary>
		///Fast sorting of numbers array using "C" native method
		///Faster than radix sorting when large dataset >= 500k
		///</summary>
		API_INTERFACE static void native(float* vetor, size_t count);

		///<summary>
		///Fast sorting of numbers array using "C" native method
		///Faster than radix sorting when large dataset >= 500k
		///Returns the index of sorted vector
		///</summary>
		API_INTERFACE static size_t* nativeIndex(float* vector, size_t count);

		///<summary>
		///Fast native sorting of custom type array using "C" native method
		///Faster than radix sorting when large dataset >= 500k
		///Returns the index of sorted vector
		///</summary>
		template <typename T>
		API_INTERFACE static size_t* nativeIndex(T* vector, size_t count, bool(*comparator)(int, int, T*));

		///<summary>
		///Fast native Quick Sorting of custom type array using "C" native method
		///</summary>
		API_INTERFACE static void quickSortNative(void* vector, size_t count, size_t sizeOfOneElement, int(*comparator)(const void*, const  void*));

#ifdef OPENCL_ENABLED

		///<summary>
		///Init algorithms for GPU
		///</summary>
		API_INTERFACE static void init(GpuDevice* gpu);

		/// <summary>
		/// Fast sorting of numbers array using Radix method in GPU
		/// Complexity O(log n)
		/// </summary>
		/// <return>
		/// Sorted array
		/// </return>
		API_INTERFACE static float* radixGPU(GpuDevice* gpu, float* input, size_t count, size_t strider = 1, size_t offset = 0);

		/// <summary>
		/// Fast sorting of numbers array using Radix method in GPU
		/// Complexity O(log n)
		/// </summary>
		/// <return>
		/// Indexes with sorted elements
		/// </return>
		API_INTERFACE static size_t* radixGPUIndexes(GpuDevice* gpu, float* input, size_t n, size_t strider = 1, size_t offset = 0);

		/// <summary>
		/// Fast sorting of numbers array using Radix method in GPU
		/// Complexity O(log n)
		/// </summary>
		/// <return>
		/// Memory Buffer elements and indexes from GPU where the sorted numbers and its indexes are stored
		/// </return>
		API_INTERFACE static cl_mem* radixGPUBuffer(GpuDevice* gpu, float* input, size_t n, size_t strider = 1, size_t offset = 0);

		/// <summary>
		/// Fast sorting of numbers array using Radix method in GPU
		/// Complexity O(log n)
		/// </summary>
		/// <return>
		/// Memory Buffer elements and indexes from GPU where the sorted numbers and its indexes are stored
		/// </return>
		API_INTERFACE static void radixGPUBufferIndexed(GpuDevice* gpu, cl_mem input, cl_mem indexes, cl_mem indexesLength, cl_mem strider, cl_mem offset, size_t indexesLengthCpu, size_t striderCpu, size_t offsetCpu, cl_mem outputMinMax, cl_mem outputIndexes);
		
		
#endif

	};

}