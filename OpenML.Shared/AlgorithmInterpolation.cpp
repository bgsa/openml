#include "AlgorithmInterpolation.h"

template <typename T>
T AlgorithmInterpolation<T>::findInterpolation(T x, Vec2<T>* points, size_t pointsCount)
{
	T* q = new T[pointsCount * pointsCount];

	std::memset(q, 0, pointsCount * pointsCount * sizeof(T)); //initialize array with Zeros
	
	for (size_t row = 0; row < pointsCount; row++)
		q[row * pointsCount] = points[row][1];


	for (size_t row = 1; row < pointsCount; row++)
		for (size_t column = 1; column <= row; column++)
		{
			T x0 = points[row - column][0];
			T x1 = points[row][0];
			T q00 = q[(row - 1) * pointsCount + column - 1];
			T q10 = q[row * pointsCount + column - 1];

			q[row * pointsCount + column] = ((x - x0) * q10 - (x - x1) * q00) / (x1 - x0);
		}
	
	T result = q[pointsCount * pointsCount - 1];

	delete[] q;

	return result;
}

namespace OpenML
{
	template class AlgorithmInterpolation<int>;
	template class AlgorithmInterpolation<float>;
	template class AlgorithmInterpolation<double>;
}