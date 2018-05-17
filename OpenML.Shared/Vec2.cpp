#include "Vec2.h"

using namespace OpenML;

template <typename T>
Vec2<T>::Vec2() { }

template <typename T>
Vec2<T>::Vec2(T x, T y)
{
	values[0] = x;
	values[1] = y;
}

template <typename T>
T Vec2<T>::x()
{
	return values[0];
}

template <typename T>
T Vec2<T>::y()
{
	return values[1];
}

template <typename T>
T* Vec2<T>::getValues()
{
	return values;
}

template <typename T>
T Vec2<T>::maximum()
{
	if (values[0] > values[1])
		return values[0];
	else
		return values[1];
}

template <typename T>
T Vec2<T>::minimum()
{
	if (values[0] < values[1])
		return values[0];
	else
		return values[1];
}

template <typename T>
T Vec2<T>::length()
{
	return T(sqrt(squared()));
}

template <typename T>
T Vec2<T>::squared()
{
	return (values[0] * values[0]) + (values[1] * values[1]);
}

template <typename T>
void Vec2<T>::add(Vec2<T> vector)
{
	values[0] += vector[0];
	values[1] += vector[1];
}

template <typename T>
void Vec2<T>::subtract(Vec2<T> vector)
{
	values[0] -= vector[0];
	values[1] -= vector[1];
}

template <typename T>
void Vec2<T>::scale(T scale)
{
	values[0] *= scale;
	values[1] *= scale;
}

template <typename T>
T Vec2<T>::dot(Vec2<T> vector)
{
	return values[0] * vector[0] + values[1] * vector[1];
}

template <typename T>
T Vec2<T>::angleRandians(Vec2<T> vectorB)
{
	T vec1Len = length();
	T vec2Len = vectorB.length();

	if (vec1Len == T(0)) // vec-Len == 0 means division by zero and return "nan" (not a number)
		vec1Len = T(0.01);

	if (vec2Len == T(0)) // vec-Len == 0 means division by zero and return "nan" (not a number)
		vec2Len = T(0.01);

	return dot(vectorB) / (vec1Len * vec2Len);
}

template <typename T>
T Vec2<T>::angleDegree(Vec2<T> vectorB)
{
	T angleRadians = dot(vectorB) / (length() * vectorB.length());

	return (T)radiansToDegrees(angleRadians);
}

template <typename T>
Vec2<T> Vec2<T>::normalize()
{
	T vectorLength = length();

	return Vec2<T> {
		values[0] / vectorLength,
			values[1] / vectorLength
	};
}

template <typename T>
void Vec2<T>::transformToUnit()
{
	scale(T(1) / length());
}

template <typename T>
T Vec2<T>::distance(Vec2<T> vector)
{
	T x = values[0] - vector[0];
	x = x*x;

	T y = values[1] - vector[1];
	y = y*y;

	return T(sqrt(x + y));
}

template <typename T>
Vec2<T>* Vec2<T>::orthogonalProjection(Vec2<T> vector)
{
	T value = dot(vector) / vector.squared();

	Vec2<T> v1 = vector * value;
	Vec2<T> v2 = {
		vector[0] - v1[0],
		vector[1] - v1[1]
	};

	Vec2<T>* result = new Vec2<T>[2];
	result[0] = v1;
	result[1] = v2;

	return result;
}

template <typename T>
Vec2<T> Vec2<T>::clone()
{
	return Vec2<T>(values[0], values[1]);
}

template <typename T>
Vec2<T> Vec2<T>::operator*(T value)
{
	Vec2<T> result;

	result[0] = values[0] * value;
	result[1] = values[1] * value;

	return result;
}

template <typename T>
Vec2<T> Vec2<T>::operator/(T value)
{
	Vec2<T> result;

	result[0] = values[0] / value;
	result[1] = values[1] / value;

	return result;
}

template <typename T>
Vec2<T> Vec2<T>::operator+(Vec2<T> vector)
{
	Vec2<T> result;

	result[0] = values[0] + vector[0];
	result[1] = values[1] + vector[1];

	return result;
}

template <typename T>
Vec2<T> Vec2<T>::operator+(T value)
{
	Vec2<T> result;

	result[0] = values[0] + value;
	result[1] = values[1] + value;

	return result;
}

template <typename T>
Vec2<T> Vec2<T>::operator-(Vec2<T> vector)
{
	Vec2<T> result;

	result[0] = values[0] - vector[0];
	result[1] = values[1] - vector[1];

	return result;
}

template <typename T>
Vec2<T> Vec2<T>::operator-(T value)
{
	Vec2<T> result;

	result[0] = values[0] - value;
	result[1] = values[1] - value;

	return result;
}

template <typename T>
bool Vec2<T>::operator==(Vec2<T> vector)
{
	return values[0] == vector[0]
		&& values[1] == vector[1];
}

template <typename T>
bool Vec2<T>::operator==(T value)
{
	return values[0] == value
		&& values[1] == value;
}

template <typename T>
bool Vec2<T>::operator!=(Vec2<T> vector)
{
	return values[0] != vector[0]
		|| values[1] != vector[1];
}

template <typename T>
T& Vec2<T>::operator[](int index)
{
	assert(index >= 0 && index < VEC2_SIZE);

	return values[index];
}

template <typename T>
Vec2<T>::operator T*() const
{
	return (T*)values;
}

template <typename T>
Vec2<T>::operator T*()
{
	return values;
}

namespace OpenML
{
	template class Vec2<int>;
	template class Vec2<float>;
	template class Vec2<double>;
}