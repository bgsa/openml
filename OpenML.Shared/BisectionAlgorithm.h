#pragma once

#include "OpenML.h"

namespace OpenML 
{

	template <typename T>
	class BisectionAlgorithm
	{
	public:
	
		API_INTERFACE T solve(T intervalA, T intervalB, T functor(T) );

		API_INTERFACE int maxNumberOfIteration();

	};

}