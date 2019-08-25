#include "AlgorithmHorner.h"

template <typename T>
T* AlgorithmHorner<T>::polynomialDivision(T x0, T* polynomial, int polynomialDegree)
{
	T* result = ALLOC_ARRAY(T, polynomialDegree);
	result[0] = polynomial[0];

	for (int i = 1; i < polynomialDegree; i++)
		result[i] = polynomial[i] + result[i - 1] * x0; //Bk = Ak + Bk + 1 * x0;

	return result;
}

template <typename T>
T solvePolynomial(T* coefficients, int polynomialDegree, T x)
{
	T result = T(0);

	for (int i = polynomialDegree - 1; i >= 0; i--)
		result += T(coefficients[polynomialDegree - i - 1] * std::pow(x, i));

	return result;
}

template <typename T>
T* AlgorithmHorner<T>::findRoots(T x0, T* polynomial, int polynomialDegree)
{
	T* result = ALLOC_ARRAY(T, polynomialDegree);
	result[0] = x0;
	
	for (int i = 0; i < polynomialDegree - 1; i++)
	{
		T* dividedPolynomial = polynomialDivision(result[i], polynomial, polynomialDegree);

		T value = dividedPolynomial[polynomialDegree - 1];

		T valueDerived = solvePolynomial(dividedPolynomial, polynomialDegree - 1, result[i]);
			
		result[i + 1] = result[i] - value / valueDerived;

		ALLOC_RELEASE(dividedPolynomial);
	}
	
	return result;
}

namespace OpenML
{
	template class AlgorithmHorner<int>;
	template class AlgorithmHorner<float>;
	template class AlgorithmHorner<double>;
}