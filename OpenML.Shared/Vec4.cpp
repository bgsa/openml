#include "Vec4.h"

using namespace OpenML;

template <typename T>
Vec4<T>::Vec4(T defaultValue)
{
	values[0] = defaultValue;
	values[1] = defaultValue;
	values[2] = defaultValue;
	values[3] = defaultValue;
}

template <typename T>
Vec4<T>::Vec4(Vec2<T> xyComponents, Vec2<T> zwComponents)
{
	values[0] = xyComponents[0];
	values[1] = xyComponents[1];
	values[2] = zwComponents[0];
	values[3] = zwComponents[1];
}

template <typename T>
Vec4<T>::Vec4(const Vec3<T>& vector, T w) 
{
	values[0] = vector[0];
	values[1] = vector[1];
	values[2] = vector[2];
	values[3] = w;
}

template <typename T>
Vec4<T>::Vec4(T x, T y, T z, T w) 
{
	values[0] = x;
	values[1] = y;
	values[2] = z;
	values[3] = w;
}

template <typename T>
T Vec4<T>::x() const
{
	return values[0];
}

template <typename T>
T Vec4<T>::y() const
{
	return values[1];
}

template <typename T>
T Vec4<T>::z() const
{
	return values[2];
}

template <typename T>
T Vec4<T>::w() const
{
	return values[3];
}

template <typename T>
T* Vec4<T>::getValues() 
{
	return values;
}

template <typename T>
T Vec4<T>::length() const
{
	return T(sqrt(squared()));
}

template <typename T>
T Vec4<T>::squared() const
{
	return (values[0] * values[0]) + (values[1] * values[1]) + (values[2] * values[2]) + (values[3] * values[3]);
}

template <typename T>
T Vec4<T>::maximum() const
{
	T value = values[0];

	for (size_t i = 1; i < 4; i++)
		if (values[i] > value)
			value = values[i];

	return value;
}

template <typename T>
T Vec4<T>::minimum() const
{
	T value = values[0];

	for (size_t i = 1; i < 4; i++)
		if (values[i] < value)
			value = values[i];

	return value;
}

template <typename T>
void Vec4<T>::add(const Vec4<T>& vector)
{
	values[0] += vector[0];
	values[1] += vector[1];
	values[2] += vector[2];
	values[3] += vector[3];
}

template <typename T>
void Vec4<T>::subtract(const Vec4<T>& vector)
{
	values[0] -= vector[0];
	values[1] -= vector[1];
	values[2] -= vector[2];
	values[3] -= vector[3];
}

template <typename T>
void Vec4<T>::scale(T scale)
{
	values[0] *= scale;
	values[1] *= scale;
	values[2] *= scale;
	values[3] *= scale;
}

template <typename T>
T Vec4<T>::dot(const Vec4<T>& vector) const
{
	return values[0] * vector[0] + values[1] * vector[1] + values[2] * vector[2] + values[3] * vector[3];
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
		values[0] * vectorLengthInverted,
		values[1] * vectorLengthInverted,
		values[2] * vectorLengthInverted,
		values[3] * vectorLengthInverted
	};
}

template <typename T>
T Vec4<T>::distance(const Vec4<T>& vector) const
{
	T x = values[0] - vector[0];
	x = x*x;

	T y = values[1] - vector[1];
	y = y*y;

	T z = values[2] - vector[2];
	z = z*z;

	T w = values[3] - vector[3];
	w = w*w;

	return T(sqrt(x + y + z + w));
}

template <typename T>
Vec4<T> Vec4<T>::fractional()
{
	return Vec4<T> {
		T(values[0] - floor(values[0])),
		T(values[1] - floor(values[1])),
		T(values[2] - floor(values[2])),
		T(values[3] - floor(values[3]))
	};
}

template <typename T>
Vec4<T> Vec4<T>::clone() const
{
	return Vec4<T>(values[0], values[1], values[2], values[3]);
}

template <typename T>
Vec3<T> Vec4<T>::toVec3() 
{
	return Vec3<T>(values[0], values[1], values[2]);
}

template <typename T>
Vec4<T> Vec4<T>::operator*(T value)
{
	Vec4<T> result;

	result[0] = values[0] * value;
	result[1] = values[1] * value;
	result[2] = values[2] * value;
	result[3] = values[3] * value;

	return result;
}

template <typename T>
Vec4<T> Vec4<T>::operator*(T value) const
{
	Vec4<T> result;

	result[0] = values[0] * value;
	result[1] = values[1] * value;
	result[2] = values[2] * value;
	result[3] = values[3] * value;

	return result;
}

template <typename T>
Vec4<T> Vec4<T>::operator/(T value) const
{
	Vec4<T> result;

	result[0] = values[0] / value;
	result[1] = values[1] / value;
	result[2] = values[2] / value;
	result[3] = values[3] / value;

	return result;
}

template <typename T>
void Vec4<T>::operator/=(T value)
{
	values[0] = values[0] / value;
	values[1] = values[1] / value;
	values[2] = values[2] / value;
	values[3] = values[3] / value;
}

template <typename T>
Vec4<T> Vec4<T>::operator+(const Vec4<T>& vector) const
{
	Vec4<T> result;

	result[0] = values[0] + vector[0];
	result[1] = values[1] + vector[1];
	result[2] = values[2] + vector[2];
	result[3] = values[3] + vector[3];

	return result;
}

template <typename T>
Vec4<T> Vec4<T>::operator+(T value) const
{
	Vec4<T> result;

	result[0] = values[0] + value;
	result[1] = values[1] + value;
	result[2] = values[2] + value;
	result[3] = values[3] + value;

	return result;
}

template <typename T>
Vec4<T> Vec4<T>::operator-(const Vec4<T>& vector) const
{
	Vec4<T> result;

	result[0] = values[0] - vector[0];
	result[1] = values[1] - vector[1];
	result[2] = values[2] - vector[2];
	result[3] = values[3] - vector[3];

	return result;
}

template <typename T>
Vec4<T> Vec4<T>::operator-(T value) const
{
	Vec4<T> result;

	result[0] = values[0] - value;
	result[1] = values[1] - value;
	result[2] = values[2] - value;
	result[3] = values[3] - value;

	return result;
}

template <typename T>
Vec4<T> Vec4<T>::operator-() const
{
	return Vec4<T>(
		-values[0],
		-values[1],
		-values[2],
		-values[3]
		);
}

template <typename T>
Vec4<T> Vec4<T>::operator*(const Mat4<T>& matrix4x4) const
{
	Vec4<T> result;

#if MAJOR_COLUMN_ORDER

	result[0]
		= matrix4x4[0 * MAT4_ROWSIZE + 0] * values[0]
		+ matrix4x4[0 * MAT4_ROWSIZE + 1] * values[1]
		+ matrix4x4[0 * MAT4_ROWSIZE + 2] * values[2]
		+ matrix4x4[0 * MAT4_ROWSIZE + 3] * values[3];

	result[1]
		= matrix4x4[1 * MAT4_ROWSIZE + 0] * values[0]
		+ matrix4x4[1 * MAT4_ROWSIZE + 1] * values[1]
		+ matrix4x4[1 * MAT4_ROWSIZE + 2] * values[2]
		+ matrix4x4[1 * MAT4_ROWSIZE + 3] * values[3];

	result[2]
		= matrix4x4[2 * MAT4_ROWSIZE + 0] * values[0]
		+ matrix4x4[2 * MAT4_ROWSIZE + 1] * values[1]
		+ matrix4x4[2 * MAT4_ROWSIZE + 2] * values[2]
		+ matrix4x4[2 * MAT4_ROWSIZE + 3] * values[3];

	result[3]
		= matrix4x4[3 * MAT4_ROWSIZE + 0] * values[0]
		+ matrix4x4[3 * MAT4_ROWSIZE + 1] * values[1]
		+ matrix4x4[3 * MAT4_ROWSIZE + 2] * values[2]
		+ matrix4x4[3 * MAT4_ROWSIZE + 3] * values[3];

#else

	result[0]
		= values[0] * matrix4x4[0 * MAT4_ROWSIZE + 0]
		+ values[1] * matrix4x4[1 * MAT4_ROWSIZE + 0]
		+ values[2] * matrix4x4[2 * MAT4_ROWSIZE + 0]
		+ values[3] * matrix4x4[3 * MAT4_ROWSIZE + 0];

	result[1]
		= values[0] * matrix4x4[0 * MAT4_ROWSIZE + 0]
		+ values[1] * matrix4x4[1 * MAT4_ROWSIZE + 0]
		+ values[2] * matrix4x4[2 * MAT4_ROWSIZE + 0]
		+ values[3] * matrix4x4[3 * MAT4_ROWSIZE + 0];

	result[2]
		= values[0] * matrix4x4[0 * MAT4_ROWSIZE + 0]
		+ values[1] * matrix4x4[1 * MAT4_ROWSIZE + 0]
		+ values[2] * matrix4x4[2 * MAT4_ROWSIZE + 0]
		+ values[3] * matrix4x4[3 * MAT4_ROWSIZE + 0];

	result[3]
		= values[0] * matrix4x4[0 * MAT4_ROWSIZE + 0]
		+ values[1] * matrix4x4[1 * MAT4_ROWSIZE + 0]
		+ values[2] * matrix4x4[2 * MAT4_ROWSIZE + 0]
		+ values[3] * matrix4x4[3 * MAT4_ROWSIZE + 0];
#endif

	return result;
}

template <typename T>
bool Vec4<T>::operator==(const Vec4<T>& vector) const
{
	return values[0] == vector[0]
		&& values[1] == vector[1]
		&& values[2] == vector[2]
		&& values[3] == vector[3];
}

template <typename T>
bool Vec4<T>::operator==(T value) const
{
	return values[0] == value
		&& values[1] == value
		&& values[2] == value
		&& values[3] == value;
}

template <typename T>
bool Vec4<T>::operator!=(const Vec4<T>& vector) const
{
	return values[0] != vector[0]
		|| values[1] != vector[1]
		|| values[2] != vector[2]
		|| values[3] != vector[3];
}

template <typename T>
T& Vec4<T>::operator[](int index)
{
	assert(index >= 0 && index < VEC4_SIZE);

	return values[index];
}

template <typename T>
T Vec4<T>::operator[](int index) const
{
	assert(index >= 0 && index < VEC4_SIZE);

	return values[index];
}

template <typename T>
Vec4<T>::operator void*() const
{
	return (void*)values;
}

template <typename T>
Vec4<T>::operator void*()
{
	return (void*)values;
}

template <typename T>
Vec4<T>::operator T*()
{
	return values;
}

template <typename T>
Vec3<T> Vec4<T>::toVec3() const {
	return Vec3<T> { values[0], values[1], values[2] };
}

namespace OpenML
{
	template class Vec4<int>;
	template class Vec4<float>;
	template class Vec4<double>;
}