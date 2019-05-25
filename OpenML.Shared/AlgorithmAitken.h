#pragma once

#include "OpenML.h"

namespace OpenML
{

	template <typename T>
	class AlgorithmAitken
	{
	public:

		///<summary>
		/// Find the value of the function, given a value: F(x) = x
		/// It means: Given an X, the result of the function is X
		/// Find all values where x = y in the functions
		/// If the functions is optiomize using Newton concepts, it finds Zeros in function efficiently
		///</summary>
		API_INTERFACE T solve(T approximation, T functor(T), int maxOfInteration = 100);

	};

}