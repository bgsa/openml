#pragma once

#include "OpenML.h"
#include <algorithm>
#include <functional>
#include <numeric>

namespace OpenML
{

	class AlgorithmSorting
	{
	public:

		///<summary>
		///Fast sorting of numbers array using Radix method
		///Complexity O(n)
		///</summary>
		API_INTERFACE float* radix(float* vector, size_t count);

		///<summary>
		///Fast sorting of numbers array using Radix method
		///Complexity O(n)
		///</summary>
		API_INTERFACE void radix(int* vetor, size_t count);

		///<summary>
		///Fast sorting of numbers array using "C" native method
		///Faster than radix sorting when large dataset >= 500k
		///</summary>
		API_INTERFACE void native(float* vetor, size_t count);

		///<summary>
		///Fast sorting of numbers array using "C" native method
		///Faster than radix sorting when large dataset >= 500k
		///Returns the index of sorted vector
		///</summary>
		API_INTERFACE size_t* nativeIndex(float* vector, size_t count);

	};

}