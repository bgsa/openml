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

		Vec4();

		Vec4(Vec3<T> vector, T w);

		Vec4(T x, T y, T z, T w);

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
		/// Fourth value in the vector
		/// </summary>
		API_INTERFACE
			T w();

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
		/// Get the squared of the vector. It means the Vector Pow2 -> x^2 + y^2 + z^2 + w^2
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
			void add(Vec4<T> vector);

		/// <summary>
		/// Subtract a vector from current vector
		/// </summary>
		API_INTERFACE
			void subtract(Vec4<T> vector);

		/// <summary>
		/// Scale the vector from a scalar => v * scalar
		/// </summary>
		API_INTERFACE
			void scale(T scale);

		/// <summary>
		/// Dot Product / Scalar Product - return the angle between two vectors: A . B
		/// return u dot v
		/// <summary>
		API_INTERFACE
			T dot(Vec4<T> vector);

		/// <summary>
		/// Get the andle in radians between the vectors
		/// <summary>
		API_INTERFACE
			T angleRandians(Vec4<T> vectorB);

		/// <summary>
		/// Get the andle in radians between the vectors
		/// <summary>
		API_INTERFACE
			T angleDegree(Vec4<T> vectorB);

		/// <summary>
		/// Get a normalized vector
		/// <summary>
		API_INTERFACE
			Vec4<T> normalize();

		/// <summary>
		/// Calculate the distance (Euclidean) from this vector to another one
		/// <summary>
		API_INTERFACE
			T distance(Vec4<T> vector);

		/// <summary>
		/// Clone the vector to a new instance
		/// <summary>
		API_INTERFACE
			Vec4<T> clone();

		/// <summary>
		/// Multiply the vector to a scalar
		/// <summary>
		API_INTERFACE
			Vec4<T> operator*(T value);

		/// <summary>
		/// Multiply this vector to a matrix
		/// <summary>
		API_INTERFACE
			Vec4<T> operator*(OpenML::Mat4<T> matrix4x4);

		/// <summary>
		/// Divide the vector to a scalar
		/// <summary>
		API_INTERFACE
			Vec4<T> operator/(T value);

		/// <summary>
		/// Divide the vector to a scalar
		/// <summary>
		API_INTERFACE
			void operator/=(T value);

		/// <summary>
		/// Sum this vector to another one
		/// <summary>
		API_INTERFACE
			Vec4<T> operator+(Vec4<T> vector);

		/// <summary>
		/// Sum a scalar to this vector
		/// <summary>
		API_INTERFACE
			Vec4<T> operator+(T value);

		/// <summary>
		/// Subtract this vector to another one
		/// <summary>
		API_INTERFACE
			Vec4<T> operator-(Vec4<T> vector);

		/// <summary>
		/// Subtract a scalar from this vector
		/// <summary>
		API_INTERFACE
			Vec4<T> operator-(T value);

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE
			bool operator==(Vec4<T> vector);

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE
			bool operator==(T value);

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// <summary>
		API_INTERFACE
			bool operator!=(Vec4<T> vector);

		/// <summary>
		/// Get a index from the vector
		/// <summary>
		API_INTERFACE
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

		/// <summary>
		/// Convert to Vec3 - ignore the W component
		/// <summary>
		API_INTERFACE
			Vec3<T> toVec3();

	};

	typedef Vec4<int> Vec4i;
	typedef Vec4<float> Vec4f;
	typedef Vec4<double> Vec4d;

}