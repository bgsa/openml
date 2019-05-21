#pragma once

#include "OpenML.h"

template <typename T>
class AlgorithmSecant
{
public:

	///<summary>
	/// Find Zero in function using Secant Method: F(x) = 0
	///</summary>
	API_INTERFACE T solve(T approximation1, T approximation2, T functor(T), int maxOfInteration = 100);

};

