#include "AlgorithmFalsePosition.h"

template <typename T>
T AlgorithmFalsePosition<T>::solve(T approximation1, T approximation2, T functor(T), int maxOfInteration)
{
	T valueApproximation1 = functor(approximation1);
	T valueApproximation2 = functor(approximation2);

	while (maxOfInteration != 0)
	{
		T newApproximation = approximation2 - valueApproximation2 * (approximation2 - approximation1) / (valueApproximation2 - valueApproximation1);

		if (isCloseEnough(newApproximation - approximation2, T(0)))
			return newApproximation;

		T newValueApproximation = functor(newApproximation);

		if (sign(newValueApproximation) * sign(valueApproximation2) < 0)
		{
			approximation1 = approximation2;
			valueApproximation1 = valueApproximation2;
		}

		approximation2 = newApproximation;
		valueApproximation2 = newValueApproximation;

		maxOfInteration--;
	}

	return T(NAN);
}

namespace OpenML
{
	template class AlgorithmFalsePosition<int>;
	template class AlgorithmFalsePosition<float>;
	template class AlgorithmFalsePosition<double>;
}