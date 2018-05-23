#pragma once

#include "OpenML.h"

namespace OpenML
{
#define VEC2_SIZE 2

	template <typename T>
	class Vec2
	{
	private:
		T values[VEC2_SIZE];

	public:

		/// <summary>
		/// Default constructor
		/// </summary>
		API_INTERFACE inline Vec2(T value = T(0));

		/// <summary>
		/// Constructor with parameters
		/// </summary>
		API_INTERFACE inline Vec2(T x, T y);

		/// <summary>
		/// First value in the vector
		/// </summary>
		API_INTERFACE inline T x() const;

		/// <summary>
		/// Second value in the vector
		/// </summary>
		API_INTERFACE inline T y() const;

		/// <summary>
		/// Get the component values in the vector
		/// </summary>
		API_INTERFACE inline T* getValues();

		/// <summary>
		/// Scale the current matrix
		/// </summary>
		API_INTERFACE inline T maximum() const;

		/// <summary>
		/// Scale the current matrix
		/// </summary>
		API_INTERFACE inline T minimum() const;

		/// <summary>
		/// Get the length / norma from the vector -> ||v||
		/// </summary>
		API_INTERFACE inline T length() const;

		/// <summary>
		/// Get the squared of the vector. It means the Vector Pow2 -> x^2 + y^2
		/// </summary>
		API_INTERFACE inline T squared() const;

		/// <summary>
		/// Add a vector from current vector
		/// </summary>
		API_INTERFACE inline void add(const Vec2<T>& vector);

		/// <summary>
		/// Subtract a vector from current vector
		/// </summary>
		API_INTERFACE inline void subtract(const Vec2<T>& vector);

		/// <summary>
		/// Scale the vector from a scalar => v * scalar
		/// </summary>
		API_INTERFACE inline void scale(T scale);

		/// <summary>
		/// Dot Product / Scalar Product between two vectors
		/// return u dot v
		/// <summary>
		API_INTERFACE inline T dot(const Vec2<T>& vector) const;

		/// <summary>
		/// Get the angle in radians between two vectors: A . B
		/// <summary>
		API_INTERFACE inline T angleRandians(const Vec2<T>& vectorB) const;

		/// <summary>
		/// Get the andle in radians between the vectors
		/// <summary>
		API_INTERFACE inline T angleDegree(const Vec2<T>& vectorB) const;

		/// <summary>
		/// Get a normalized vector
		/// <summary>
		API_INTERFACE inline Vec2<T> normalize() const;

		/// <summary>
		/// Normalize the current vector - change to unit vector
		/// <summary>
		API_INTERFACE inline void transformToUnit();

		/// <summary>
		/// Calculate the distance (Euclidean) from this vector to another one
		/// <summary>
		API_INTERFACE inline T distance(const Vec2<T>& vector) const;

		/// <summary>
		/// Find a orthogonal projection between two vectors
		/// Return Two vectors
		/// <summary>
		API_INTERFACE inline Vec2<T>* orthogonalProjection(const Vec2<T>& vector) const;

		/// <summary>
		/// Clone the vector to a new instance
		/// <summary>
		API_INTERFACE inline Vec2<T> clone() const;

		/// <summary>
		/// Multiply the vector to a scalar
		/// <summary>
		API_INTERFACE inline Vec2<T> operator*(T value) const;

		/// <summary>
		/// Multiply the vector to a scalar
		/// </summary>
		API_INTERFACE inline Vec2<T> operator/(T value) const;

		/// <summary>
		/// Sum this vector to another one
		/// <summary>
		API_INTERFACE inline Vec2<T> operator+(const Vec2<T>& vector) const;

		/// <summary>
		/// Sum a scalar to this vector
		/// <summary>
		API_INTERFACE inline Vec2<T> operator+(T value) const;

		/// <summary>
		/// Subtract this vector to another one
		/// <summary>
		API_INTERFACE inline Vec2<T> operator-(const Vec2<T>& vector) const;

		/// <summary>
		/// Subtract a scalar from this vector
		/// <summary>
		API_INTERFACE inline Vec2<T> operator-(T value) const;

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE inline bool operator==(const Vec2<T>& vector) const;

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE inline bool operator==(T value) const;

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE inline bool operator!=(const Vec2<T>& vector) const;

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
		API_INTERFACE inline operator T*() const;

	};

	typedef Vec2<int> Vec2i;
	typedef Vec2<float> Vec2f;
	typedef Vec2<double> Vec2d;

}