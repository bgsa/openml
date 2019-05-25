#pragma once

#include "OpenML.h"

namespace OpenML
{

	template <typename T>
	class AlgorithmSteffensen
	{
	public:

		///<summary>
		/// Find Zero in function using Steffensen Method
		/// This method accelerate the conversion from linear to quadratic conversion
		/// Ex.: Convert the polynomial to fixed point method and use Seteffensen Method to solve
		///</summary>
		API_INTERFACE T solve(T approximation1, T functor(T), int maxOfInteration = 100);

	};

}
