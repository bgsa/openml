#pragma once

#include "OpenML.h"

template <typename T>
class AlgorithmNewton
{
public:

	///<summary>
	/// Find Zero in function using Newton Method: F(x) = 0
	///</summary>
	API_INTERFACE T solve(T approximation, T functor(T), T derivedFunctor(T), int maxOfInteration = 100);

};

