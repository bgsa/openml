#include "Vec2.h"

using namespace OpenML;

template <typename T>
Vec2<T>::Vec2(T value)
{
	x = value;
	y = value;
}

template <typename T>
Vec2<T>::Vec2(T x, T y)
{
	this->x = x;
	this->y = y;
}

template <typename T>
T* Vec2<T>::getValues()
{
	return reinterpret_cast<T*>(this);
}

template <typename T>
T Vec2<T>::maximum() const
{
	if (x > y)
		return x;
	else
		return y;
}

template <typename T>
T Vec2<T>::minimum() const
{
	if (x < y)
		return x;
	else
		return y;
}

template <typename T>
T Vec2<T>::length() const
{
	return T(sqrt(squared()));
}

template <typename T>
T Vec2<T>::squared() const
{
	return (x * x) + (y * y);
}

template <typename T>
void Vec2<T>::add(const Vec2<T>& vector)
{
	x += vector.x;
	y += vector.y;
}

template <typename T>
void Vec2<T>::subtract(const Vec2<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
}

template <typename T>
void Vec2<T>::scale(T scale)
{
	x *= scale;
	y *= scale;
}

template <typename T>
T Vec2<T>::dot(const Vec2<T>& vector) const
{
	return x * vector.x + y * vector.y;
}

template <typename T>
T Vec2<T>::angle(const Vec2<T>& vectorB) const
{
	T vec1Len = length();
	T vec2Len = vectorB.length();

	if (vec1Len == T(0)) // vec-Len == 0 means division by zero and return "nan" (not a number)
		vec1Len = T(0.000001);

	if (vec2Len == T(0)) // vec-Len == 0 means division by zero and return "nan" (not a number)
		vec2Len = T(0.000001);

	return dot(vectorB) / (vec1Len * vec2Len);
}

template <typename T>
Vec2<T> Vec2<T>::normalize() const
{
	T vectorLength = length();

	return Vec2<T> {
		x / vectorLength,
			y / vectorLength
	};
}

template <typename T>
void Vec2<T>::transformToUnit()
{
	scale(T(1) / length());
}

template <typename T>
T Vec2<T>::distance(const Vec2<T>& vector) const
{
	T xTemp = x - vector.x;
	T yTemp = y - vector.y;

	return T(sqrt(xTemp * xTemp + yTemp * yTemp));
}

template <typename T>
Vec2<T> Vec2<T>::fractional()
{
	return Vec2<T> {
		T(x - floor(x)),
		T(y - floor(y))
	};
}

template <typename T>
Vec2<T>* Vec2<T>::orthogonalProjection(const Vec2<T>& vector) const
{
	T value = dot(vector) / vector.squared();

	Vec2<T> v1 = vector * value;
	Vec2<T> v2 = {
		vector.x - v1.x,
		vector.y - v1.y
	};

	Vec2<T>* result = new Vec2<T>[2];
	result[0] = v1;
	result[1] = v2;

	return result;
}

template <typename T>
Vec2<T> Vec2<T>::clone() const
{
	return Vec2<T>(x, y);
}

template <typename T>
Vec2<T> Vec2<T>::operator*(T value) const
{
	return Vec2<T>(
		x * value,
		y * value
		);
}

template <typename T>
Vec2<T> Vec2<T>::operator/(T value) const
{
	return Vec2<T> (
		x / value,
		y / value
		);
}

template <typename T>
Vec2<T> Vec2<T>::operator+(const Vec2<T>& vector) const
{
	return Vec2<T> (
		x + vector.x,
		y + vector.y
		);
}

template <typename T>
Vec2<T> Vec2<T>::operator+(T value) const
{
	return Vec2<T>(
		x + value,
		y + value
		);
}

template <typename T>
Vec2<T> Vec2<T>::operator-(const Vec2<T>& vector) const
{
	return Vec2<T>(
		x - vector.x,
		y - vector.y
		);
}

template <typename T>
Vec2<T> Vec2<T>::operator-(T value) const
{
	return Vec2<T> (
		x - value,
		y - value
		);
}

template <typename T>
Vec2<T> Vec2<T>::operator-() const
{
	return Vec2<T>(
		-x,
		-y
		);
}

template <typename T>
bool Vec2<T>::operator==(const Vec2<T>& vector) const
{
	return x == vector.x
		&& y == vector.y;
}

template <typename T>
bool Vec2<T>::operator==(T value) const
{
	return x == value 
		&& y == value;
}

template <typename T>
bool Vec2<T>::operator!=(const Vec2<T>& vector) const
{
	return x != vector.x
		|| y != vector.y;
}

template <typename T>
bool Vec2<T>::operator!=(T value) const
{
	return x != value
		|| y != value;
}

template <typename T>
T& Vec2<T>::operator[](int index)
{
	assert(index >= 0 && index < VEC2_SIZE);

	return reinterpret_cast<T*>(this)[index];
}

template <typename T>
T Vec2<T>::operator[](int index) const
{
	assert(index >= 0 && index < VEC2_SIZE);

	return reinterpret_cast<const T*>(this)[index];
}

template <typename T>
Vec2<T>::operator T*()
{
	return reinterpret_cast<T*>(this);
}

template <typename T>
std::ostream& operator<<(std::ostream& outputStream, const Vec2<T>& vector)
{
	return outputStream << vector.x << "," << vector.y;
}

template <typename T>
std::istream& operator>>(std::istream& inputStream, Vec2<T>& vector)
{
	char separator;
	return inputStream >> vector.x >> separator >> vector.y;
}

template <typename T>
std::ostream& Vec2<T>::serialize(std::ostream& outputStream) const
{
	return outputStream << *this;
}

template <typename T>
std::istream& Vec2<T>::deserialize(std::istream& inputStream)
{
	inputStream >> *this;
	return inputStream;
}

namespace OpenML
{
	template class Vec2<int>;
	template class Vec2<float>;
	template class Vec2<double>;
}