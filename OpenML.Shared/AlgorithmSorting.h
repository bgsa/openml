#pragma once

#include "OpenML.h"
#include <algorithm>
#include <functional>
#include <numeric>

#include <AABB.h>

namespace OpenML
{

	class AlgorithmSorting
	{
	public:

		///<summary>
		///Fast sorting of numbers array using Radix method
		///Complexity O(n)
		///</summary>
		API_INTERFACE static float* radix(float* vector, size_t count);

		///<summary>
		///Fast sorting of numbers array using Radix method
		///Complexity O(n)
		///</summary>
		API_INTERFACE static void radix(int* vetor, size_t count);

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

	};

}