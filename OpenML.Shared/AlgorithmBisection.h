#pragma once

#include "OpenML.h"

namespace OpenML 
{

	template <typename T>
	class AlgorithmBisection
	{
	public:
	
		API_INTERFACE T solve(T intervalA, T intervalB, T functor(T), int maxOfInteration = 100);

		API_INTERFACE int maxNumberOfIteration();

	};

}