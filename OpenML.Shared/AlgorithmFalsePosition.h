#pragma once

#include "OpenML.h"

namespace OpenML
{

	template <typename T>
	class AlgorithmFalsePosition
	{
	public:

		///<summary>
		/// Find Zero in function using False Position Method: F(x) = 0
		///</summary>
		API_INTERFACE T solve(T approximation1, T approximation2, T functor(T), int maxOfInteration = 100);

	};

}