#include "AlgorithmSteffensen.h"

template <typename T>
T AlgorithmSteffensen<T>::solve(T approximation, T functor(T), int maxOfInteration)
{
	while (maxOfInteration != 0)
	{
		T aproximation1 = functor(approximation);
		T aproximation2 = functor(aproximation1);

		T divisor = (aproximation2 - (2 * aproximation1) + approximation);

		if (divisor == T(0))
			return aproximation2;

		T newAproximation = T(approximation - std::pow(aproximation1 - approximation, 2) / divisor);

		if (isCloseEnough(newAproximation, approximation))
			return approximation;

		approximation = newAproximation;

		maxOfInteration--;
	}

	return T(NAN);
}

namespace OpenML
{
	template class AlgorithmSteffensen<int>;
	template class AlgorithmSteffensen<float>;
	template class AlgorithmSteffensen<double>;
}