#include "Vec3.h"

using namespace OpenML;

template <typename T>
Vec3<T>::Vec3(T defaultValue) {
	x = defaultValue;
	y = defaultValue;
	z = defaultValue;
}

template <typename T>
Vec3<T>::Vec3(T x, T y, T z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

template <typename T>
Vec3<T>::Vec3(const Vec3<T>& value)
{
	x = value.x;
	y = value.y;
	z = value.z;
}

template <typename T>
Vec3<T>::Vec3(Vec2<T> vector2D, T z) {
	x = vector2D[0];
	y = vector2D[1];
	z = z;
}

template <typename T>
T* Vec3<T>::getValues()
{
	return reinterpret_cast<T*>(this);
}

template <typename T>
Vec3<T> Vec3<T>::abs() const
{
	return Vec3<T>(
		(T)std::abs(x),
		(T)std::abs(y),
		(T)std::abs(z)
	);
}

template <typename T>
T Vec3<T>::squaredLength() const
{
	return (x * x) + (y * y) + (z * z);
}

template <typename T>
T Vec3<T>::length() const
{
	return T(sqrt(squaredLength()));
}

template <typename T>
T Vec3<T>::maximum() const
{
	T value = x;

	if (y > value)
		value = y;

	if (z > value)
		value = z;

	return value;
}

template <typename T>
T Vec3<T>::minimum() const
{
	T value = x;

	if (y < value)
		value = y;

	if (z < value)
		value = z;

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
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

template <typename T>
Vec3<T> Vec3<T>::subtract(const Vec3<T>& vector)
{
	return Vec3<T>(
		x -= vector.x,
		y -= vector.y,
		z -= vector.z
		);
}

template <typename T>
Vec3<T> Vec3<T>::multiply(const Vec3<T>& vector) const
{
	return Vec3<T>(
		x * vector.x,
		y * vector.y,
		z * vector.z
		);
}

template <typename T>
void Vec3<T>::scale(T scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
}

template <typename T>
Vec3<T> Vec3<T>::rotateX(float angle)
{
	return Vec3<T>(
			x,
			T(y * cosf(angle) - z * sinf(angle)),
			T(y * sinf(angle) + z * cosf(angle))
		);
}

template <typename T>
Vec3<T> Vec3<T>::rotateX(float angle, Vec3<T> referencePoint)
{
	Vec3<T> direction = this->subtract(referencePoint);
	angle *= -1.0f;

	return Vec3<T>(
		x,
		T(referencePoint[1] + direction[1] * cosf(angle) + (referencePoint[2] - z) * sinf(angle)),
		T(referencePoint[2] + direction[1] * sinf(angle) + direction[2] * cosf(angle))
	);
}

template <typename T>
Vec3<T> Vec3<T>::rotateY(float angle)
{
	return Vec3<T>(
		T(x * cosf(angle) + z * sinf(angle)),
		y,
		T(z * cosf(angle) - x * sinf(angle))
	);
}

template <typename T>
Vec3<T> Vec3<T>::rotateY(float angle, Vec3<T> referencePoint)
{
	Vec3<T> direction = this->subtract(referencePoint);
	angle *= -1.0f;

	return Vec3<T>(
		x,
			T(referencePoint[1] + direction[1] * cosf(angle) + (referencePoint[2] - z) * sinf(angle)),
			T(referencePoint[2] + direction[1] * sinf(angle) + direction[2] * cosf(angle))
		);
}

template <typename T>
Vec3<T> Vec3<T>::rotateZ(float angle)
{
	return Vec3<T>(
			T(x * cosf(angle) - y * sinf(angle)),
			T(x * sinf(angle) + y * cosf(angle)),
			z
		);
}

template <typename T>
Vec3<T> Vec3<T>::rotateZ(float angle, Vec3<T> referencePoint)
{
	Vec3<T> direction = this->subtract(referencePoint);

	return Vec3<T>(
			T(referencePoint.x + direction.x * cosf(angle) + (referencePoint[1] - y) * sinf(angle)),
			T(referencePoint[1] + direction.x * sinf(angle) + direction[1] * cosf(angle)),
			z
		);
}

template <typename T>
Vec3<T> Vec3<T>::cross(const Vec3<T>& vector) const
{
	Vec3<T> result = Vec3<T>(
		y * vector[2] - vector[1] * z,
		-x * vector[2] + vector[0] * z,
		x * vector[1] - vector[0] * y
	);

	return result;
}

template <typename T>
T Vec3<T>::dot(const Vec3<T>& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z;
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
		x * vectorLengthInverted,
		y * vectorLengthInverted,
		z * vectorLengthInverted
	};
}

template <typename T>
void Vec3<T>::transformToUnit()
{
	scale(T(1) / length());
}

template <typename T>
T Vec3<T>::squaredDistance(const Vec3<T>& vector) const
{
	T xTemp = x - vector.x;
	xTemp = xTemp * xTemp;

	T yTemp = y - vector.y;
	yTemp = yTemp * yTemp;

	T zTemp = z - vector.z;
	zTemp = zTemp * zTemp;

	return xTemp + yTemp + zTemp;
}

template <typename T>
T Vec3<T>::distance(const Vec3<T>& vector) const
{
	T xTemp = x - vector.x;
	T yTemp = y - vector.y;
	T zTemp = z - vector.z;

	return T(std::sqrt(xTemp *xTemp + yTemp * yTemp + zTemp * zTemp));
}

template <typename T>
T Vec3<T>::signedDistance(const Vec3<T>& point) const
{
	return (*this - point).dot(point);
}

template <typename T>
Vec3<T> Vec3<T>::fractional()
{
	return Vec3<T> {
		T(x - floor(x)),
		T(y - floor(y)),
		T(z - floor(z))
	};
}

template <typename T>
Vec3<T> Vec3<T>::clone() const
{
	return Vec3<T>(x, y, z);
}

template <typename T>
Vec3<T> Vec3<T>::operator/(T value) const
{
	return Vec3<T>(
		x / value,
		y / value,
		z / value
		);
}

template <typename T>
Vec3<T> Vec3<T>::operator/(Vec3<T> vector) const
{
	return Vec3<T>(
		x / vector.x,
		y / vector.y,
		z / vector.z
	);
}

template <typename T>
Vec3<T> Vec3<T>::operator*(T value) const
{
	return Vec3<T>(
		x * value,
		y * value,
		z * value
		);
}

template <typename T>
void Vec3<T>::operator*=(T value)
{
	x *= value;
	y *= value;
	z *= value;
}

template <typename T>
Vec3<T> Vec3<T>::operator*(const Vec3<T>& vector) const
{
	return multiply(vector);
}

template <typename T>
Vec3<T> Vec3<T>::operator+(const Vec3<T>& vector)
{
	return Vec3<T>(
		x + vector.x,
		y + vector.y,
		z + vector.z
		);
}

template <typename T>
Vec3<T> Vec3<T>::operator+(const Vec3<T>& vector) const
{
	return Vec3<T>(
		x + vector.x,
		y + vector.y,
		z + vector.z
		);
}

template <typename T>
Vec3<T> Vec3<T>::operator+=(Vec3<T>& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

template <typename T>
Vec3<T> Vec3<T>::operator+(T value)
{
	return Vec3<T>(
		x + value,
		y + value,
		z + value
		);
}

template <typename T>
Vec3<T> Vec3<T>::operator+(T value) const
{
	return Vec3<T>(
		x + value,
		y + value,
		z + value
		);
}

template <typename T>
Vec3<T> Vec3<T>::operator-(const Vec3<T>& vector)
{
	return Vec3<T>(
		x - vector.x,
		y - vector.y,
		z - vector.z
		);
}

template <typename T>
Vec3<T> Vec3<T>::operator-(const Vec3<T>& vector) const
{
	return Vec3<T>(
		x - vector.x,
		y - vector.y,
		z - vector.z
		);
}

template <typename T>
void Vec3<T>::operator-=(const Vec3<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
}

template <typename T>
Vec3<T> Vec3<T>::operator-=(const Vec3<T>& vector) const
{
	return Vec3<T>(
		x - vector.x,
		y - vector.y,
		z - vector.z
	);
}

template <typename T>
Vec3<T> Vec3<T>::operator-(T value)
{
	return Vec3<T>(
		x - value,
		y - value,
		z - value
		);
}

template <typename T>
Vec3<T> Vec3<T>::operator-()
{
	return Vec3<T>(
		-x,
		-y,
		-z
		);
}

template <typename T>
Vec3<T> Vec3<T>::operator-() const
{
	return Vec3<T>(
		-x,
		-y,
		-z
		);
}

template <typename T>
bool Vec3<T>::operator==(const Vec3<T>& vector) const
{
	return x == vector.x
		&& y == vector.y
		&& z == vector.z;
}

template <typename T>
bool Vec3<T>::operator==(T value) const
{
	return x == value
		&& y == value
		&& z == value;
}

template <typename T>
bool Vec3<T>::operator!=(const Vec3<T>& vector) const
{
	return x != vector.x
		|| y != vector.y
		|| z != vector.z;
}

template <typename T>
bool Vec3<T>::operator!=(T value) const
{
	return x != value
		|| y != value
		|| z != value;
}

template <typename T>
T& Vec3<T>::operator[](int index)
{
	assert(index >= 0 && index < VEC3_SIZE);

	return reinterpret_cast<T*>(this)[index];
}

template <typename T>
T Vec3<T>::operator[](int index) const
{
	assert(index >= 0 && index < VEC3_SIZE);

	return reinterpret_cast<const T*>(this)[index];
}

template <typename T>
Vec3<T>::operator void*() const
{
	return (void*)(this);
}

template <typename T>
Vec3<T>::operator void*()
{
	return reinterpret_cast<void*>(this);
}

template <typename T>
Vec3<T>::operator T*()
{
	return reinterpret_cast<T*>(this);
}

template <typename T>
Vec3<T> Vec3<T>::operator+=(T value) 
{
	return Vec3<T>(
		x + value,
		y + value,
		z + value
		);
}

template <typename T>
Vec3<T> Vec3<T>::operator-=(T value)  const
{
	return Vec3<T>(
		x - value,
		y - value,
		z - value
		);
}

template <typename T>
Vec3<T>& Vec3<T>::operator=(const Vec3<T>& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;

	return *this;
}

namespace OpenML
{
	template class Vec3<int>;
	template class Vec3<float>;
	template class Vec3<double>;
}