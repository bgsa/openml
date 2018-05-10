#pragma once

#include "OpenML.h"

namespace OpenML
{
#define VEC3_SIZE 3

	template <typename T>
	class Vec3
	{
	private:
		T values[VEC3_SIZE];

	public:

		/// <summary>
		/// Default construct
		/// </summary>
		API_INTERFACE
			Vec3();

		/// <summary>
		/// Construct with args
		/// </summary>
		API_INTERFACE
			Vec3(T x, T y, T z);

		/// <summary>
		/// First value in the vector
		/// </summary>
		API_INTERFACE
			T x();

		/// <summary>
		/// Second value in the vector
		/// </summary>
		API_INTERFACE
			T y();

		/// <summary>
		/// Third value in the vector
		/// </summary>
		API_INTERFACE
			T z();

		/// <summary>
		/// Get the component values in the vector
		/// </summary>
		API_INTERFACE
			T* getValues();

		/// <summary>
		/// Get the length / norma from the vector -> ||v||
		/// </summary>
		API_INTERFACE
			T length();

		/// <summary>
		/// Get the squared of the vector. It means the Vector Pow2 -> x^2 + y^2 + z^2
		/// </summary>
		API_INTERFACE
			T squared();

		/// <summary>
		/// Get the maximun value in the vector
		/// </summary>
		API_INTERFACE T maximum();

		/// <summary>
		/// Get the min value in the vector
		/// </summary>
		API_INTERFACE T minimum();

		/// <summary>
		/// Add a vector from current vector
		/// </summary>
		API_INTERFACE
			void add(Vec3<T> vector);

		/// <summary>
		/// Subtract a vector from current vector
		/// </summary>
		API_INTERFACE
			void subtract(Vec3<T> vector);

		/// <summary>
		/// Scale the vector from a scalar => v * scalar
		/// </summary>
		API_INTERFACE
			void scale(T scale);

		/// <summary>
		/// Cross Product - return a perpendicular vector, regards two vectors => u x v
		/// </summary>
		API_INTERFACE
			Vec3<T> cross(Vec3<T> vector);

		/// <summary>
		/// Dot Product / Scalar Product - between two vectors: A . B
		/// return u dot v
		/// </summary>
		API_INTERFACE
			T dot(Vec3<T> vector);

		/// <summary>
		/// Get the andle in radians between the vectors
		/// Obs.: if the vectors are normalized, can use: acosf(dot(vectorB));
		/// </summary>
		API_INTERFACE
			T angleRandians(Vec3<T> vectorB);

		/// <summary>
		/// Get the andle in radians between the vectors
		/// Obs.: if the vectors are normalized, can use: acosf(dot(vectorB));
		/// </summary>
		API_INTERFACE
			T angleDegree(Vec3<T> vectorB);

		/// <summary>
		/// Get a normalized vector
		/// </summary>
		API_INTERFACE
			Vec3<T> normalize();

		/// <summary>
		/// Normalize the current vector - change to unit vector
		/// </summary>
		API_INTERFACE
			void transformToUnit();

		/// <summary>
		/// Calculate the distance (Euclidean) from this vector to another one
		/// </summary>
		API_INTERFACE
			T distance(Vec3<T> vector);

		/// <summary>
		/// Clone the vector to a new instance
		/// </summary>
		API_INTERFACE
			Vec3<T> clone();

		/// <summary>
		/// Set new value to the vector
		/// </summary>
		API_INTERFACE void operator=(Vec3<T> value);

		/// <summary>
		/// Multiply the vector to a scalar
		/// </summary>
		API_INTERFACE Vec3<T> operator/(T value);

		/// <summary>
		/// Multiply the vector to a scalar
		/// </summary>
		API_INTERFACE
			Vec3<T> operator*(T value);

		/// <summary>
		/// Multiply the vector to another one using Cross Product
		/// </summary>
		API_INTERFACE
			Vec3<T> operator*(Vec3<T> vector);

		/// <summary>
		/// Sum this vector to another one
		/// </summary>
		API_INTERFACE
			Vec3<T> operator+(Vec3<T> vector);

		/// <summary>
		/// Sum this vector to another one
		/// </summary>
		API_INTERFACE
			void operator+=(Vec3<T> vector);

		/// <summary>
		/// Sum a scalar to this vector
		/// </summary>
		API_INTERFACE
			Vec3<T> operator+(T value);

		/// <summary>
		/// Subtract this vector to another one
		/// </summary>
		API_INTERFACE
			Vec3<T> operator-(Vec3<T> vector);

		/// <summary>
		/// Subtract this vector to another one
		/// </summary>
		API_INTERFACE
			void operator-=(Vec3<T> vector);

		/// <summary>
		/// Subtract a scalar from this vector
		/// </summary>
		API_INTERFACE
			Vec3<T> operator-(T value);

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// </summary>
		API_INTERFACE
			bool operator==(Vec3<T> vector);

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// </summary>
		API_INTERFACE
			bool operator==(T value);

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// </summary>
		API_INTERFACE
			bool operator!=(Vec3<T> vector);

		/// <summary>
		/// Get a index from the vector
		/// </summary>
		T& operator[](int index);

		/// <summary>
		/// Auto convertion to void *
		/// </summary>
		API_INTERFACE operator void*() const;

		/// <summary>
		/// Auto convertion to T *
		/// It is the same of convertion to float* or int* or double*, whatever T is.
		/// </summary>
		API_INTERFACE operator T*();

	};

	typedef Vec3<int> Vec3i;
	typedef Vec3<float> Vec3f;
	typedef Vec3<double> Vec3d;

}