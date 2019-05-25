#include "AlgorithmNewton.h"

template <typename T>
T AlgorithmNewton<T>::solve(T approximation, T functor(T), T derivedFunctor(T), int maxOfInteration)
{
	while (maxOfInteration != 0)
	{
		T newApproximation = approximation - (functor(approximation) / derivedFunctor(approximation));

		if (isCloseEnough(newApproximation, approximation))
			return newApproximation;

		approximation = newApproximation;

		maxOfInteration--;
	}

	return T(NAN);
}

namespace OpenML
{
	template class AlgorithmNewton<int>;
	template class AlgorithmNewton<float>;
	template class AlgorithmNewton<double>;
}