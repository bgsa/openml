#include "AlgorithmLagrange.h"

template <typename T>
T AlgorithmLagrange<T>::polynomialApproximation(Vec2<T>* points, size_t pointsCount, T x)
{
	T result = T(0);

	for (size_t i = 0; i < pointsCount; i++)
	{
		T li = T(1);

		for (size_t j = 0; j < pointsCount; j++)
		{
			if (i == j)
				continue;

			li *= (x - points[j][0]) / (points[i][0] - points[j][0]);			
		}

		result += points[i][1] * li;
	}

	return result;
}

namespace OpenML
{
	template class AlgorithmLagrange<int>;
	template class AlgorithmLagrange<float>;
	template class AlgorithmLagrange<double>;
}