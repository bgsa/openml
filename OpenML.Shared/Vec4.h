#pragma once

#include "OpenML.h"

namespace OpenML
{
#define VEC4_SIZE 4

	template <typename T>
	class Vec4
	{
	private:
		T values[VEC4_SIZE];

	public:

		/// <summary>
		/// Default constructor
		/// Optional default value 0.0
		/// </summary>
		API_INTERFACE inline Vec4(T defaultValue = T(0));
		/// <summary>
		/// Constructor with a vector and a W homogeneous coordinate
		/// </summary>
		API_INTERFACE inline Vec4(const Vec3<T>& vector, T w);
		/// <summary>
		/// Constructor with scalar values
		/// </summary>
		API_INTERFACE inline Vec4(T x, T y, T z, T w);
		
		/// <summary>
		/// First value in the vector / X coordinate
		/// </summary>
		API_INTERFACE inline T x() const;

		/// <summary>
		/// Second value in the vector / Y coordinate
		/// </summary>
		API_INTERFACE inline T y() const;

		/// <summary>
		/// Third value in the vector / Z coordinate
		/// </summary>
		API_INTERFACE inline T z() const;

		/// <summary>
		/// Fourth value in the vector / W coordinate
		/// </summary>
		API_INTERFACE inline T w() const;

		/// <summary>
		/// Get the component values in the vector
		/// </summary>
		API_INTERFACE inline T* getValues();

		/// <summary>
		/// Get the length / norma from the vector -> ||v||
		/// </summary>
		API_INTERFACE inline T length() const;

		/// <summary>
		/// Get the squared of the vector. It means the Vector Pow2 -> x^2 + y^2 + z^2 + w^2
		/// </summary>
		API_INTERFACE inline T squared() const;

		/// <summary>
		/// Get the maximun value in the vector
		/// </summary>
		API_INTERFACE inline T maximum() const;

		/// <summary>
		/// Get the min value in the vector
		/// </summary>
		API_INTERFACE inline T minimum() const;

		/// <summary>
		/// Add a vector from current vector
		/// </summary>
		API_INTERFACE inline void add(const Vec4<T>& vector);

		/// <summary>
		/// Subtract a vector from current vector
		/// </summary>
		API_INTERFACE inline void subtract(const Vec4<T>& vector);

		/// <summary>
		/// Scale the vector from a scalar => v * scalar
		/// </summary>
		API_INTERFACE inline void scale(T scale);

		/// <summary>
		/// Dot Product / Scalar Product - return the angle between two vectors: A . B
		/// return u dot v
		/// <summary>
		API_INTERFACE inline T dot(const Vec4<T>& vector) const;

		/// <summary>
		/// Get the andle in radians between the vectors
		/// <summary>
		API_INTERFACE inline T angleRandians(const Vec4<T>& vectorB) const;

		/// <summary>
		/// Get the andle in radians between the vectors
		/// <summary>
		API_INTERFACE inline T angleDegree(const Vec4<T>& vectorB) const;

		/// <summary>
		/// Get a normalized vector
		/// <summary>
		API_INTERFACE inline Vec4<T> normalize() const;

		/// <summary>
		/// Calculate the distance (Euclidean) from this vector to another one
		/// <summary>
		API_INTERFACE inline T distance(const Vec4<T>& vector) const;

		/// <summary>
		/// Clone the vector to a new instance
		/// <summary>
		API_INTERFACE inline Vec4<T> clone() const;

		/// <summary>
		/// Multiply the vector to a scalar
		/// <summary>
		API_INTERFACE inline Vec4<T> operator*(T value);
		/// <summary>
		/// Multiply the vector to a scalar
		/// <summary>
		API_INTERFACE inline Vec4<T> operator*(T value) const;

		/// <summary>
		/// Multiply this vector to a matrix
		/// <summary>
		API_INTERFACE inline Vec4<T> operator*(const Mat4<T>& matrix4x4) const;

		/// <summary>
		/// Divide the vector to a scalar
		/// <summary>
		API_INTERFACE inline Vec4<T> operator/(T value) const;

		/// <summary>
		/// Divide the vector to a scalar
		/// <summary>
		API_INTERFACE inline void operator/=(T value);

		/// <summary>
		/// Sum this vector to another one
		/// <summary>
		API_INTERFACE inline Vec4<T> operator+(const Vec4<T>& vector) const;

		/// <summary>
		/// Sum a scalar to this vector
		/// <summary>
		API_INTERFACE inline Vec4<T> operator+(T value) const;

		/// <summary>
		/// Subtract this vector to another one
		/// <summary>
		API_INTERFACE inline Vec4<T> operator-(const Vec4<T>& vector) const;

		/// <summary>
		/// Subtract a scalar from this vector
		/// <summary>
		API_INTERFACE inline Vec4<T> operator-(T value) const;

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE inline bool operator==(const Vec4<T>& vector) const;

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE inline bool operator==(T value) const;

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE inline bool operator!=(const Vec4<T>& vector) const;

		/// <summary>
		/// Get a index from the vector
		/// <summary>
		API_INTERFACE inline T& operator[](int index);
		/// <summary>
		/// Get a index from the vector
		/// <summary>
		API_INTERFACE inline T operator[](int index) const;
		
		/// <summary>
		/// Auto convertion to void *
		/// </summary>
		API_INTERFACE inline operator void*() const;
		/// <summary>
		/// Auto convertion to void *
		/// </summary>
		API_INTERFACE inline operator void*();

		/// <summary>
		/// Auto convertion to T *
		/// It is the same of convertion to float* or int* or double*, whatever T is.
		/// </summary>
		API_INTERFACE inline operator T*();

		/// <summary>
		/// Convert to Vec3 - ignore the W component
		/// <summary>
		API_INTERFACE inline Vec3<T> toVec3() const;

	};

	typedef Vec4<int> Vec4i;
	typedef Vec4<float> Vec4f;
	typedef Vec4<double> Vec4d;

}