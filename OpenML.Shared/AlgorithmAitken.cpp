#include "AlgorithmAitken.h"

template <typename T>
T AlgorithmAitken<T>::solve(T approximation, T functor(T), int maxOfInteration)
{
	while (maxOfInteration != 0)
	{
		T newAproximation = functor(approximation);
		T newAproximation1 = functor(newAproximation);
		T newAproximation2 = functor(newAproximation1);

		double divisor = newAproximation2 - 2.0 * newAproximation1 + newAproximation;

		if (divisor == 0.0)
			return newAproximation2;

		newAproximation = T(newAproximation - std::pow(newAproximation1 - newAproximation, 2.0) / divisor);

		if (isCloseEnough(newAproximation, approximation))
			return newAproximation;

		approximation = newAproximation;

		maxOfInteration--;
	}

	return T(NAN);
}

namespace OpenML
{
	template class AlgorithmAitken<int>;
	template class AlgorithmAitken<float>;
	template class AlgorithmAitken<double>;
}