#pragma once

#include "OpenML.h"

namespace OpenML
{

	template <typename T>
	class AlgorithmInterpolation
	{
	public:

		///<summary>
		///Given a function by points ordered ("points" parameter), 
		///find the interpolation on "x" (first parameter)
		///This algorithm uses Neville Method
		///</summary>
		API_INTERFACE T findInterpolation(T x, Vec2<T>* points, size_t pointsCount);

	};

}