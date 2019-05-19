#pragma once

#include "OpenML.h"

namespace OpenML
{

	template <typename T>
	class AlgorithmFixedPoint
	{
	public:

		API_INTERFACE T solve(T approximation, T functor(T), int maxOfInteration = 100);

	};

}