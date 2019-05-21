#include "AlgorithmSecant.h"

template <typename T>
T AlgorithmSecant<T>::solve(T approximation1, T approximation2, T functor(T), int maxOfInteration)
{
	T valueApproximation1 = functor(approximation1);
	T valueApproximation2 = functor(approximation2);

	while (maxOfInteration != 0)
	{
		T newApproximation = approximation2 - valueApproximation2 * (approximation2 - approximation1) / (valueApproximation2 - valueApproximation1);

		if (isCloseEnough(newApproximation - approximation2, T(0)))
			return newApproximation;

		approximation1 = approximation2;
		valueApproximation1 = valueApproximation2;

		approximation2 = newApproximation;
		valueApproximation2 = functor(newApproximation);

		maxOfInteration--;
	}

	return T(NAN);
}

namespace OpenML
{
	template class AlgorithmSecant<int>;
	template class AlgorithmSecant<float>;
	template class AlgorithmSecant<double>;
}