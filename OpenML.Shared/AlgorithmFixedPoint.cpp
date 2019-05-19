#include "AlgorithmFixedPoint.h"

template <typename T>
T AlgorithmFixedPoint<T>::solve(T approximation, T functor(T), int maxOfInteration)
{
	const T closesTo = T(0);
	
	while (maxOfInteration != 0)
	{
		T f_Aproximation = functor(approximation);

		if (isCloseEnough(f_Aproximation, approximation))
			return approximation;

		approximation = f_Aproximation;

		maxOfInteration--;
	}

	return T(NAN);
}

namespace OpenML
{
	template class AlgorithmFixedPoint<int>;
	template class AlgorithmFixedPoint<float>;
	template class AlgorithmFixedPoint<double>;
}