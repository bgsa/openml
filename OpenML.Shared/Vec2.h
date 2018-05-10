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
		API_INTERFACE Vec2();

		/// <summary>
		/// Constructor with parameters
		/// </summary>
		API_INTERFACE Vec2(T x, T y);

		/// <summary>
		/// First value in the vector
		/// </summary>
		API_INTERFACE T x();

		/// <summary>
		/// Second value in the vector
		/// </summary>
		API_INTERFACE T y();

		/// <summary>
		/// Get the component values in the vector
		/// </summary>
		API_INTERFACE T* getValues();

		/// <summary>
		/// Scale the current matrix
		/// </summary>
		API_INTERFACE T maximum();

		/// <summary>
		/// Scale the current matrix
		/// </summary>
		API_INTERFACE T minimum();

		/// <summary>
		/// Get the length / norma from the vector -> ||v||
		/// </summary>
		API_INTERFACE T length();

		/// <summary>
		/// Get the squared of the vector. It means the Vector Pow2 -> x^2 + y^2
		/// </summary>
		API_INTERFACE T squared();

		/// <summary>
		/// Add a vector from current vector
		/// </summary>
		API_INTERFACE void add(Vec2<T> vector);

		/// <summary>
		/// Subtract a vector from current vector
		/// </summary>
		API_INTERFACE void subtract(Vec2<T> vector);

		/// <summary>
		/// Scale the vector from a scalar => v * scalar
		/// </summary>
		API_INTERFACE void scale(T scale);

		/// <summary>
		/// Dot Product / Scalar Product between two vectors
		/// return u dot v
		/// <summary>
		API_INTERFACE T dot(Vec2<T> vector);

		/// <summary>
		/// Get the angle in radians between two vectors: A . B
		/// <summary>
		API_INTERFACE T angleRandians(Vec2<T> vectorB);

		/// <summary>
		/// Get the andle in radians between the vectors
		/// <summary>
		API_INTERFACE T angleDegree(Vec2<T> vectorB);

		/// <summary>
		/// Get a normalized vector
		/// <summary>
		API_INTERFACE Vec2<T> normalize();

		/// <summary>
		/// Normalize the current vector - change to unit vector
		/// <summary>
		API_INTERFACE void transformToUnit();

		/// <summary>
		/// Calculate the distance (Euclidean) from this vector to another one
		/// <summary>
		API_INTERFACE T distance(Vec2<T> vector);

		/// <summary>
		/// Find a orthogonal projection between two vectors
		/// Return Two vectors
		/// <summary>
		API_INTERFACE Vec2<T>* orthogonalProjection(Vec2<T> vector);

		/// <summary>
		/// Clone the vector to a new instance
		/// <summary>
		API_INTERFACE Vec2<T> clone();

		/// <summary>
		/// Multiply the vector to a scalar
		/// <summary>
		API_INTERFACE Vec2<T> operator*(T value);

		/// <summary>
		/// Multiply the vector to a scalar
		/// </summary>
		API_INTERFACE Vec2<T> operator/(T value);

		/// <summary>
		/// Sum this vector to another one
		/// <summary>
		API_INTERFACE Vec2<T> operator+(Vec2<T> vector);

		/// <summary>
		/// Sum a scalar to this vector
		/// <summary>
		API_INTERFACE Vec2<T> operator+(T value);

		/// <summary>
		/// Subtract this vector to another one
		/// <summary>
		API_INTERFACE Vec2<T> operator-(Vec2<T> vector);

		/// <summary>
		/// Subtract a scalar from this vector
		/// <summary>
		API_INTERFACE Vec2<T> operator-(T value);

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE bool operator==(Vec2<T> vector);

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE bool operator==(T value);

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE bool operator!=(Vec2<T> vector);

		/// <summary>
		/// Get a index from the vector
		/// <summary>
		T& operator[](int index);

		/// <summary>
		/// Auto convertion to void *
		/// </summary>
		API_INTERFACE operator T*() const;

		/// <summary>
		/// Auto convertion to T *
		/// It is the same of convertion to float* or int* or double*, whatever T is.
		/// </summary>
		API_INTERFACE operator T*();

	};

	typedef Vec2<float> Vec2f;
	typedef Vec2<double> Vec2d;

}