#include "Vec3.h"

using namespace OpenML;

template <typename T>
Vec3<T>::Vec3(T defaultValue) {
	values[0] = defaultValue;
	values[1] = defaultValue;
	values[2] = defaultValue;
}

template <typename T>
Vec3<T>::Vec3(T x, T y, T z) {
	values[0] = x;
	values[1] = y;
	values[2] = z;
}

template <typename T>
Vec3<T>::Vec3(Vec2<T> vector2D, T z) {
	values[0] = vector2D[0];
	values[1] = vector2D[1];
	values[2] = z;
}

template <typename T>
T Vec3<T>::x() const
{
	return values[0];
}

template <typename T>
T Vec3<T>::y() const
{
	return values[1];
}

template <typename T>
T Vec3<T>::z() const
{
	return values[2];
}

template <typename T>
T* Vec3<T>::getValues()
{
	return values;
}

template <typename T>
T Vec3<T>::length() const
{
	return T(sqrt(squared()));
}

template <typename T>
T Vec3<T>::squared() const
{
	return (values[0] * values[0]) + (values[1] * values[1]) + (values[2] * values[2]);
}

template <typename T>
T Vec3<T>::maximum() const
{
	T value = values[0];

	for (size_t i = 1; i < 3; i++)
		if (values[i] > value)
			value = values[i];

	return value;
}

template <typename T>
T Vec3<T>::minimum() const
{
	T value = values[0];

	for (size_t i = 1; i < 3; i++)
		if (values[i] < value)
			value = values[i];

	return value;
}

template <typename T>
T Vec3<T>::tripleProduct(const Vec3<T> &v, const Vec3<T> &u) const
{
	return this->cross(v).dot(u);
}

template <typename T>
void Vec3<T>::add(const Vec3<T>& vector)
{
	values[0] += vector[0];
	values[1] += vector[1];
	values[2] += vector[2];
}

template <typename T>
Vec3<T> Vec3<T>::subtract(const Vec3<T>& vector)
{
	return Vec3<T>(
			values[0] -= vector[0],
			values[1] -= vector[1],
			values[2] -= vector[2]
		);
}

template <typename T>
Vec3<T> Vec3<T>::multiply(const Vec3<T>& vector) const
{
	return Vec3<T>(
		values[0] * vector[0],
		values[1] * vector[1],
		values[2] * vector[2]
		);
}

template <typename T>
void Vec3<T>::scale(T scale)
{
	values[0] *= scale;
	values[1] *= scale;
	values[2] *= scale;
}

template <typename T>
Vec3<T> Vec3<T>::rotateX(float angle)
{
	return Vec3<T>(
			values[0],
			T(values[1] * cosf(angle) - values[2] * sinf(angle)),
			T(values[1] * sinf(angle) + values[2] * cosf(angle))
		);
}

template <typename T>
Vec3<T> Vec3<T>::rotateX(float angle, Vec3<T> referencePoint)
{
	Vec3<T> direction = this->subtract(referencePoint);
	angle *= -1.0f;

	return Vec3<T>(
		values[0],
		T(referencePoint[1] + direction[1] * cosf(angle) + (referencePoint[2] - values[2]) * sinf(angle)),
		T(referencePoint[2] + direction[1] * sinf(angle) + direction[2] * cosf(angle))
	);
}

template <typename T>
Vec3<T> Vec3<T>::rotateY(float angle)
{
	return Vec3<T>(
		T(values[0] * cosf(angle) + values[2] * sinf(angle)),
		values[1],
		T(values[2] * cosf(angle) - values[0] * sinf(angle))
	);
}

template <typename T>
Vec3<T> Vec3<T>::rotateY(float angle, Vec3<T> referencePoint)
{
	Vec3<T> direction = this->subtract(referencePoint);
	angle *= -1.0f;

	return Vec3<T>(
		values[0],
			T(referencePoint[1] + direction[1] * cosf(angle) + (referencePoint[2] - values[2]) * sinf(angle)),
			T(referencePoint[2] + direction[1] * sinf(angle) + direction[2] * cosf(angle))
		);
}

template <typename T>
Vec3<T> Vec3<T>::rotateZ(float angle)
{
	return Vec3<T>(
			T(values[0] * cosf(angle) - values[1] * sinf(angle)),
			T(values[0] * sinf(angle) + values[1] * cosf(angle)),
			values[2]
		);
}

template <typename T>
Vec3<T> Vec3<T>::rotateZ(float angle, Vec3<T> referencePoint)
{
	Vec3<T> direction = this->subtract(referencePoint);

	return Vec3<T>(
			T(referencePoint[0] + direction[0] * cosf(angle) + (referencePoint[1] - values[1]) * sinf(angle)),
			T(referencePoint[1] + direction[0] * sinf(angle) + direction[1] * cosf(angle)),
			values[2]
		);
}

template <typename T>
Vec3<T> Vec3<T>::cross(const Vec3<T>& vector) const
{
	Vec3<T> result = Vec3<T>(
		result[0] = values[1] * vector[2] - vector[1] * values[2],
		result[1] = -values[0] * vector[2] + vector[0] * values[2],
		result[2] = values[0] * vector[1] - vector[0] * values[1]
	);

	return result;
}

template <typename T>
T Vec3<T>::dot(const Vec3<T>& vector) const
{
	return values[0] * vector[0] + values[1] * vector[1] + values[2] * vector[2];
}

template <typename T>
T Vec3<T>::angle(const Vec3<T>& vectorB) const
{
	return dot(vectorB) / (length() * vectorB.length());
}

template <typename T>
Vec3<T> Vec3<T>::normalize() const
{
	T vectorLengthInverted = T(1) / length();

	return Vec3<T> {
		values[0] * vectorLengthInverted,
		values[1] * vectorLengthInverted,
		values[2] * vectorLengthInverted
	};
}

template <typename T>
void Vec3<T>::transformToUnit()
{
	scale(T(1) / length());
}

template <typename T>
T Vec3<T>::distance(const Vec3<T>& vector) const
{
	T x = values[0] - vector[0];
	x = x*x;

	T y = values[1] - vector[1];
	y = y*y;

	T z = values[2] - vector[2];
	z = z*z;

	return T(sqrt(x + y + z));
}

template <typename T>
Vec3<T> Vec3<T>::fractional()
{
	return Vec3<T> {
		T(values[0] - floor(values[0])),
		T(values[1] - floor(values[1])),
		T(values[2] - floor(values[2]))
	};
}

template <typename T>
Vec3<T> Vec3<T>::clone() const
{
	return Vec3<T>(values[0], values[1], values[2]);
}

template <typename T>
void Vec3<T>::operator=(const Vec3<T>& value)
{
	values[0] = value[0];
	values[1] = value[1];
	values[2] = value[2];
}

template <typename T>
Vec3<T> Vec3<T>::operator/(T value) const
{
	Vec3<T> result;

	result[0] = values[0] / value;
	result[1] = values[1] / value;
	result[2] = values[2] / value;

	return result;
}

template <typename T>
Vec3<T> Vec3<T>::operator/(Vec3<T> vector) const
{
	return Vec3<T>(
		values[0] / vector[0],
		values[1] / vector[1],
		values[2] / vector[2]
	);
}

template <typename T>
Vec3<T> Vec3<T>::operator*(T value) const
{
	Vec3<T> result;

	result[0] = values[0] * value;
	result[1] = values[1] * value;
	result[2] = values[2] * value;

	return result;
}

template <typename T>
void Vec3<T>::operator*=(T value)
{
	values[0] = values[0] * value;
	values[1] = values[1] * value;
	values[2] = values[2] * value;
}

template <typename T>
Vec3<T> Vec3<T>::operator*(const Vec3<T>& vector) const
{
	return multiply(vector);
}

template <typename T>
Vec3<T> Vec3<T>::operator+(const Vec3<T>& vector) const
{
	Vec3<T> result;

	result[0] = values[0] + vector[0];
	result[1] = values[1] + vector[1];
	result[2] = values[2] + vector[2];

	return result;
}

template <typename T>
void Vec3<T>::operator+=(const Vec3<T>& vector)
{
	values[0] = values[0] + vector[0];
	values[1] = values[1] + vector[1];
	values[2] = values[2] + vector[2];
}

template <typename T>
Vec3<T> Vec3<T>::operator+(T value) const
{
	Vec3<T> result;

	result[0] = values[0] + value;
	result[1] = values[1] + value;
	result[2] = values[2] + value;

	return result;
}

template <typename T>
Vec3<T> Vec3<T>::operator-(const Vec3<T>& vector) const
{
	Vec3<T> result;

	result[0] = values[0] - vector[0];
	result[1] = values[1] - vector[1];
	result[2] = values[2] - vector[2];

	return result;
}

template <typename T>
void Vec3<T>::operator-=(const Vec3<T>& vector)
{
	values[0] = values[0] - vector[0];
	values[1] = values[1] - vector[1];
	values[2] = values[2] - vector[2];
}

template <typename T>
Vec3<T> Vec3<T>::operator-(T value) const
{
	Vec3<T> result;

	result[0] = values[0] - value;
	result[1] = values[1] - value;
	result[2] = values[2] - value;

	return result;
}

template <typename T>
Vec3<T> Vec3<T>::operator-() const
{
	return Vec3<T>(
		-values[0],
		-values[1],
		-values[2]
		);
}

template <typename T>
bool Vec3<T>::operator==(const Vec3<T>& vector) const
{
	return values[0] == vector[0]
		&& values[1] == vector[1]
		&& values[2] == vector[2];
}

template <typename T>
bool Vec3<T>::operator==(T value) const
{
	return values[0] == value
		&& values[1] == value
		&& values[2] == value;
}

template <typename T>
bool Vec3<T>::operator!=(const Vec3<T>& vector) const
{
	return values[0] != vector[0]
		|| values[1] != vector[1]
		|| values[2] != vector[2];
}

template <typename T>
T& Vec3<T>::operator[](int index)
{
	assert(index >= 0 && index < VEC3_SIZE);

	return values[index];
}

template <typename T>
T Vec3<T>::operator[](int index) const
{
	assert(index >= 0 && index < VEC3_SIZE);

	return values[index];
}

template <typename T>
Vec3<T>::operator void*() const
{
	return (void*)values;
}

template <typename T>
Vec3<T>::operator void*()
{
	return (void*)values;
}

template <typename T>
Vec3<T>::operator T*()
{
	return values;
}

namespace OpenML
{
	template class Vec3<int>;
	template class Vec3<float>;
	template class Vec3<double>;
}