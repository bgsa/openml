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

template <typename T>
void getInterpolationPolynomialRecursive(Vec2<T>* points, size_t pointsCount, T x0, T* result, size_t iteration)
{
	if (pointsCount == 1)
		return;

	Vec2<T>* newPoints = new Vec2<T>[pointsCount - 1];

	for (size_t i = 0; i < pointsCount - 1; i++)
	{
		T value = iteration != 0 ? points[1][0] - x0 : points[i + 1][0] - points[i][0];

		newPoints[i][0] = points[i + 1][0];
		newPoints[i][1] = (points[i + 1][1] - points[i][1]) / value;
	}

	iteration++;

	result[iteration] = newPoints[0][1];

	getInterpolationPolynomialRecursive(newPoints, pointsCount - 1, x0, result, iteration);

	delete[] newPoints;
}

template <typename T>
T* AlgorithmInterpolation<T>::getInterpolationPolynomial(Vec2<T>* points, size_t pointsCount)
{
	T* result = new T[pointsCount];

	result[0] = points[0][1];

	getInterpolationPolynomialRecursive(points, pointsCount, points[0][0], result, 0);

	return result;
}

template <typename T>
std::string AlgorithmInterpolation<T>::getInterpolationPolynomialDescription(Vec2<T>* points, size_t pointsCount)
{
	T* result = new T[pointsCount];
	result[0] = points[0][1];
	getInterpolationPolynomialRecursive(points, pointsCount, points[0][0], result, 0);

	std::stringstream output;

	output << "P" << (pointsCount -1) << "(x) = " << result[0];

	for (size_t i = 1; i < pointsCount; i++)
	{
		if (result[i] < T(0))
			output << " - " << (result[i] * T(-1));
		else
			output << " + " << result[i];
		
		for (size_t j = 0; j < i; j++)
			output << "(x - " << points[j][0] << ")";
	}

	delete[] result;

	return output.str();
}

namespace OpenML
{
	template class AlgorithmInterpolation<int>;
	template class AlgorithmInterpolation<float>;
	template class AlgorithmInterpolation<double>;
}