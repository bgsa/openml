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
T** AlgorithmInterpolation<T>::naturalSpline(Vec2<T>* points, size_t pointsCount)
{
	T** result = new T*[pointsCount - 1];

	T* h = new T[pointsCount];
	h[pointsCount - 1] = T(0);

	for (size_t i = 0; i < pointsCount - 1; i++)
		h[i] = points[i + 1][0] - points[i][0];

	T* alpha = new T[pointsCount];
	alpha[0] = T(0);
	alpha[pointsCount - 1] = T(0);

	T* l = new T[pointsCount];
	T* u = new T[pointsCount];
	T* z = new T[pointsCount];
	T* c = new T[pointsCount];
	T* b = new T[pointsCount];
	T* d = new T[pointsCount];

	b[pointsCount - 1] = T(0);
	d[pointsCount - 1] = T(0);

	l[0] = T(1);
	l[pointsCount - 1] = T(1);

	u[0] = T(0);

	z[0] = T(0);	
	z[pointsCount - 1] = T(0);

	c[pointsCount - 1] = T(0);
	
	for (size_t i = 1; i < pointsCount - 1; i++)
	{
		alpha[i] = ((T(3) / h[i]) * (points[i + 1][1] - points[i][1])) - ((T(3) / h[i - 1]) * (points[i][1] - points[i - 1][1]));

		l[i] = (2 * (points[i + 1][0] - points[i-1][0])) - (h[i - 1] * u[i - 1]);
		u[i] = h[i] / l[i];
		z[i] = (alpha[i] - (h[i - 1] * z[i - 1])) / l[i];
	}

	for (int j = pointsCount - 2; j >= T(0); j--)
	{
		c[j] = z[j] - u[j] * c[j + 1];
		b[j] = (points[j + 1][1] - points[j][1]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
		d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
	}

	for (size_t i = 0; i < pointsCount - 1; i++)
	{
		result[i] = new T[4];
		result[i][0] = points[i][1];
		result[i][1] = b[i];
		result[i][2] = c[i];
		result[i][3] = d[i];
	}

	delete[] h, alpha, l, u, z, c, b, d;
	return result;
}

template <typename T>
std::string AlgorithmInterpolation<T>::naturalSplineDescription(Vec2<T>* points, size_t pointsCount)
{
	std::ostringstream output;

	T** spline = naturalSpline(points, pointsCount);

	for (size_t i = 0; i < pointsCount - 1; i++)
	{
		T diff = points[i][0] - points[0][0];

		output << "(" << spline[i][0] << ") + (" 
			<< spline[i][1] << ")(x - " << diff << ") + (" 
			<< spline[i][2] << ")(x - " << diff << ")^2 + (" 
			<< spline[i][3] << ")(x - " << diff << ")^3 "
			<< std::endl;
	}
	
	delete[] spline;
	return output.str();
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
T** AlgorithmInterpolation<T>::fixedSpline(Vec2<T>* points, size_t pointsCount, T derivedFx0, T derivedFxn)
{
	T** result = new T*[pointsCount - 1];
	size_t n = pointsCount - 1;

	T* h = new T[pointsCount];
	h[n] = T(0);

	for (size_t i = 0; i < n; i++)
		h[i] = points[i + 1][0] - points[i][0];

	T* alpha = new T[pointsCount];
	alpha[0] = T(3) * ((points[1][1] - points[0][1]) / h[0]) - (T(3) * derivedFx0);
	alpha[n] = T(3) * derivedFxn - (T(3) * (points[n][1] - points[n - 1][1])) / h[n - 1];

	T* l = new T[pointsCount];
	T* u = new T[pointsCount];
	T* z = new T[pointsCount];
	T* c = new T[pointsCount];
	T* b = new T[pointsCount];
	T* d = new T[pointsCount];

	b[n] = T(0);
	d[n] = T(0);

	l[0] = T(2) * h[0];
	u[0] = T(0.5);
	z[0] = alpha[0] / l[0];

	for (size_t i = 1; i < n; i++)
	{
		alpha[i] = ((T(3) / h[i]) * (points[i + 1][1] - points[i][1])) - ((T(3) / h[i - 1]) * (points[i][1] - points[i - 1][1]));

		l[i] = (T(2) * (points[i + 1][0] - points[i - 1][0])) - (h[i - 1] * u[i - 1]);
		u[i] = h[i] / l[i];
		z[i] = (alpha[i] - (h[i - 1] * z[i - 1])) / l[i];
	}

	l[n] = h[n - 1] * (T(2) - u[n - 1]);
	z[n] = (alpha[n] - h[n - 1] * z[n - 1] ) / l[n];
	c[n] = z[n];

	for (int j = n - 1; j >= T(0); j--)
	{
		c[j] = z[j] - u[j] * c[j + 1];
		b[j] = (points[j + 1][1] - points[j][1]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / T(3);
		d[j] = (c[j + 1] - c[j]) / (T(3) * h[j]);
	}

	for (size_t i = 0; i < n; i++)
	{
		result[i] = new T[4];
		result[i][0] = points[i][1];
		result[i][1] = b[i];
		result[i][2] = c[i];
		result[i][3] = d[i];
	}

	delete[] h, alpha, l, u, z, c, b, d;
	return result;
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