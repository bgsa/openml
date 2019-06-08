#pragma once

#include "OpenML.h"
#include <iostream>
#include <sstream>

namespace OpenML
{

	template <typename T>
	class AlgorithmInterpolation
	{
	public:

		///<summary>
		///Given a function by ordered points ("points" parameter), 
		///find the interpolation on "x" (first parameter)
		///This algorithm uses Neville Method
		///</summary>
		API_INTERFACE T findInterpolation(T x, Vec2<T>* points, size_t pointsCount);

		///<summary>
		///Given a function by ordered points ("points" parameter), 
		///find the interpolation polynomial
		///This algorithm uses Newton Difference Divided Method
		///</summary>
		API_INTERFACE T* getInterpolationPolynomial(Vec2<T>* points, size_t pointsCount);

		///<summary>
		///Given a function by ordered points ("points" parameter), 
		///find the description (formula) interpolation polynomial
		///This algorithm uses Newton Difference Divided Method
		///</summary>
		API_INTERFACE std::string getInterpolationPolynomialDescription(Vec2<T>* points, size_t pointsCount);

	};

}