#include "AlgorithmBisection.h"

template <typename T>
T AlgorithmBisection<T>::solve(T intervalA, T intervalB, T functor(T), int maxOfInteration)
{
	const T closesTo = T(0);
	
	T midPoint = intervalA + ((intervalB - intervalA) * T(0.5));
	T valueMidPoint = functor(midPoint);
	T valueA = functor(intervalA);
	
	while (maxOfInteration != 0)
	{
		if (isCloseEnough(valueMidPoint, closesTo))
			return midPoint;

		if (sign(valueA) * sign(valueMidPoint) > 0)
		{
			intervalA = midPoint;
			valueA = valueMidPoint;
		}
		else
			intervalB = midPoint;

		midPoint = intervalA + ((intervalB - intervalA) * T(0.5));
		valueMidPoint = functor(midPoint);

		maxOfInteration--;
	}

	return T(NAN);
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