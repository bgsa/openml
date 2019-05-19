#include "AlgorithmBisection.h"

template <typename T>
T AlgorithmBisection<T>::solve(T intervalA, T intervalB, T functor(T) )
{
	const T closesTo = T(0);
	
	T midPoint = intervalA + ((intervalB - intervalA) * T(0.5));
	T valueMidPoint = functor(midPoint);
	T valueA = functor(intervalA);
	
	while ( ! isCloseEnough(valueMidPoint, closesTo) )
	{
		if (sign(valueA) * sign(valueMidPoint) > 0) 
		{			
			intervalA = midPoint;
			valueA = valueMidPoint;
		}
		else
			intervalB = midPoint;

 		midPoint = intervalA + ((intervalB - intervalA) * T(0.5));
		valueMidPoint = functor(midPoint);
	}

	return midPoint;
}

template <typename T>
int AlgorithmBisection<T>::maxNumberOfIteration()
{
	const double log2 = log10(2);
	const double v = log10(DefaultErrorMargin);	
	const int maxIteration = (int) ceil(-v / log2);

	return maxIteration;
}

namespace OpenML
{
	template class AlgorithmBisection<int>;
	template class AlgorithmBisection<float>;
	template class AlgorithmBisection<double>;
}