#pragma once

#include "OpenML.h"

namespace OpenML
{

	template <typename T>
	class AlgorithmLagrange
	{
	public:

		///<summary>
		///Find the value "y" from: F(x) = y where F(x) are function points
		///This method approximate the function by a polynomial where the function F(x) is unknown, 
		///so points (x, F(x)) of the function are given
		///</summary>
		API_INTERFACE T polynomialApproximation(Vec2<T>* points, size_t pointsCount, T x);

	};

}