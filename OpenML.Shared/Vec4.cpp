#include "Vec4.h"

using namespace OpenML;

template <typename T>
Vec4<T>::Vec4(T defaultValue)
{
	x = defaultValue;
	y = defaultValue;
	z = defaultValue;
	w = defaultValue;
}

template <typename T>
Vec4<T>::Vec4(Vec2<T> xyComponents, Vec2<T> zwComponents)
{
	x = xyComponents.x;
	y = xyComponents.y;
	z = zwComponents.x;
	w = zwComponents.y;
}

template <typename T>
Vec4<T>::Vec4(const Vec3<T>& vector, T w) 
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	this->w = w;
}

template <typename T>
Vec4<T>::Vec4(T x, T y, T z, T w) 
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

template <typename T>
T* Vec4<T>::getValues() 
{
	return reinterpret_cast<T*>(this);
}

template <typename T>
T Vec4<T>::length() const
{
	return T(sqrt(squared()));
}

template <typename T>
T Vec4<T>::squared() const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

template <typename T>
T Vec4<T>::maximum() const
{
	T value = x;

	if (y > value)
		value = y;

	if (z > value)
		value = z;

	if (w > value)
		value = w;

	return value;
}

template <typename T>
T Vec4<T>::minimum() const
{
	T value = x;

	if (y < value)
		value = y;

	if (z < value)
		value = z;

	if (w < value)
		value = w;

	return value;
}

template <typename T>
void Vec4<T>::add(const Vec4<T>& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;
}

template <typename T>
void Vec4<T>::subtract(const Vec4<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;
}

template <typename T>
void Vec4<T>::scale(T scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	w *= scale;
}

template <typename T>
T Vec4<T>::dot(const Vec4<T>& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
}

template <typename T>
T Vec4<T>::angle(const Vec4<T>& vectorB) const
{
	return dot(vectorB) / (length() * vectorB.length());
}

template <typename T>
Vec4<T> Vec4<T>::normalize() const
{
	T vectorLengthInverted = T(1) / length();

	return Vec4<T> {
		x * vectorLengthInverted,
		y * vectorLengthInverted,
		z * vectorLengthInverted,
		w * vectorLengthInverted
	};
}

template <typename T>
T Vec4<T>::distance(const Vec4<T>& vector) const
{
	T xTemp = x - vector.x;
	T yTemp = y - vector.y;
	T zTemp = z - vector.z;
	T wTemp = w - vector.w;

	return T(sqrt(xTemp * xTemp + yTemp * yTemp + zTemp * zTemp + wTemp * wTemp));
}

template <typename T>
Vec4<T> Vec4<T>::fractional()
{
	return Vec4<T> {
		T(x - floor(x)),
		T(y - floor(y)),
		T(z - floor(z)),
		T(w - floor(w))
	};
}

template <typename T>
Vec4<T> Vec4<T>::clone() const
{
	return Vec4<T>(x, y, z, w);
}

template <typename T>
Vec3<T> Vec4<T>::toVec3() 
{
	return Vec3<T>(x, y, z);
}

template <typename T>
Vec4<T> Vec4<T>::operator*(T value)
{
	return Vec4<T>(
		x * value,
		y * value,
		z * value,
		w * value
		);
}

template <typename T>
Vec4<T> Vec4<T>::operator*(T value) const
{
	return Vec4<T>(
		x * value,
		y * value,
		z * value,
		w * value
		);
}

template <typename T>
Vec4<T> Vec4<T>::operator/(T value) const
{
	return Vec4<T> (
		x / value,
		y / value,
		z / value,
		w / value
		);
}

template <typename T>
void Vec4<T>::operator/=(T value)
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;
}

template <typename T>
Vec4<T> Vec4<T>::operator+(const Vec4<T>& vector) const
{
	return Vec4<T>(
		x + vector.x,
		y + vector.y,
		z + vector.z,
		w + vector.w
		);
}

template <typename T>
Vec4<T> Vec4<T>::operator+(T value) const
{
	return Vec4<T>(
		x + value,
		y + value,
		z + value,
		w + value
		);
}

template <typename T>
Vec4<T> Vec4<T>::operator-(const Vec4<T>& vector) const
{
	return Vec4<T>(
		x - vector.x,
		y - vector.y,
		z - vector.z,
		w - vector.w
		);
}

template <typename T>
Vec4<T> Vec4<T>::operator-(T value) const
{
	return Vec4<T>(
		x - value,
		y - value,
		z - value,
		w - value
		);
}

template <typename T>
Vec4<T> Vec4<T>::operator-() const
{
	return Vec4<T>(
		-x,
		-y,
		-z,
		-w
		);
}

template <typename T>
Vec4<T> Vec4<T>::operator*(const Mat4<T>& matrix4x4) const
{
	Vec4<T> result;

#if MAJOR_COLUMN_ORDER

	result[0]
		= matrix4x4[0 * MAT4_ROWSIZE + 0] * x
		+ matrix4x4[0 * MAT4_ROWSIZE + 1] * y
		+ matrix4x4[0 * MAT4_ROWSIZE + 2] * z
		+ matrix4x4[0 * MAT4_ROWSIZE + 3] * w;

	result[1]
		= matrix4x4[1 * MAT4_ROWSIZE + 0] * x
		+ matrix4x4[1 * MAT4_ROWSIZE + 1] * y
		+ matrix4x4[1 * MAT4_ROWSIZE + 2] * z
		+ matrix4x4[1 * MAT4_ROWSIZE + 3] * w;

	result[2]
		= matrix4x4[2 * MAT4_ROWSIZE + 0] * x
		+ matrix4x4[2 * MAT4_ROWSIZE + 1] * y
		+ matrix4x4[2 * MAT4_ROWSIZE + 2] * z
		+ matrix4x4[2 * MAT4_ROWSIZE + 3] * w;

	result[3]
		= matrix4x4[3 * MAT4_ROWSIZE + 0] * x
		+ matrix4x4[3 * MAT4_ROWSIZE + 1] * y
		+ matrix4x4[3 * MAT4_ROWSIZE + 2] * z
		+ matrix4x4[3 * MAT4_ROWSIZE + 3] * w;

#else

	result[0]
		= x * matrix4x4[0 * MAT4_ROWSIZE + 0]
		+ y * matrix4x4[1 * MAT4_ROWSIZE + 0]
		+ z * matrix4x4[2 * MAT4_ROWSIZE + 0]
		+ w * matrix4x4[3 * MAT4_ROWSIZE + 0];

	result[1]
		= x * matrix4x4[0 * MAT4_ROWSIZE + 0]
		+ y * matrix4x4[1 * MAT4_ROWSIZE + 0]
		+ z * matrix4x4[2 * MAT4_ROWSIZE + 0]
		+ w * matrix4x4[3 * MAT4_ROWSIZE + 0];

	result[2]
		= x * matrix4x4[0 * MAT4_ROWSIZE + 0]
		+ y * matrix4x4[1 * MAT4_ROWSIZE + 0]
		+ z * matrix4x4[2 * MAT4_ROWSIZE + 0]
		+ w * matrix4x4[3 * MAT4_ROWSIZE + 0];

	result[3]
		= x * matrix4x4[0 * MAT4_ROWSIZE + 0]
		+ y * matrix4x4[1 * MAT4_ROWSIZE + 0]
		+ z * matrix4x4[2 * MAT4_ROWSIZE + 0]
		+ w * matrix4x4[3 * MAT4_ROWSIZE + 0];
#endif

	return result;
}

template <typename T>
bool Vec4<T>::operator==(const Vec4<T>& vector) const
{
	return x == vector.x
		&& y == vector.y
		&& z == vector.z
		&& w == vector.w;
}

template <typename T>
bool Vec4<T>::operator==(T value) const
{
	return x == value
		&& y == value
		&& z == value
		&& w == value;
}

template <typename T>
bool Vec4<T>::operator!=(const Vec4<T>& vector) const
{
	return x != vector.x
		|| y != vector.y
		|| z != vector.z
		|| w != vector.w;
}

template <typename T>
T& Vec4<T>::operator[](int index)
{
	assert(index >= 0 && index < VEC4_SIZE);

	return reinterpret_cast<T*>(this)[index];
}

template <typename T>
T Vec4<T>::operator[](int index) const
{
	assert(index >= 0 && index < VEC4_SIZE);

	return reinterpret_cast<const T*>(this)[index];
}

template <typename T>
Vec4<T>::operator void*() const
{
	return (void*)(this);
}

template <typename T>
Vec4<T>::operator void*()
{
	return (void*)(this);
}

template <typename T>
Vec4<T>::operator T*()
{
	return reinterpret_cast<T*>(this);
}

template <typename T>
Vec3<T> Vec4<T>::toVec3() const 
{
	return Vec3<T>(x, y, z);
}

namespace OpenML
{
	template class Vec4<int>;
	template class Vec4<float>;
	template class Vec4<double>;
}