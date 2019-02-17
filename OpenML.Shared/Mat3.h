#pragma once

#include "OpenML.h"
#include <cstring>
#include <vector>

namespace OpenML
{
#define MAT3_SIZE 9
#define MAT3_ROWSIZE 3

	template <typename T>
	struct AutovalueAutovector3 {
		T autovalue;
		Vec3<T> autovector;
	};

	template <typename T>
	class Mat3 : public Mat<T>
	{
	private:
		T values[MAT3_SIZE];

	public:

		/// <summary>
		/// Default constructor
		/// Load a empty matrix = 0
		/// </summary>
		API_INTERFACE inline Mat3(T defaultValue = T(0));

		/// <summary>
		/// Constructor with initialized values
		/// </summary>
		API_INTERFACE inline Mat3(T* values);

		/// <summary>
		/// Constructor with initialized values - COL ORDER
		/// </summary>
		API_INTERFACE inline Mat3(
			T value11, T value21, T value31,
			T value12, T value22, T value32,
			T value13, T value23, T value33);

		/// <summary>
		/// Get the values from current matrix
		/// </summary>
		API_INTERFACE inline T* getValues();

		/// <summary>
		/// Get the value from current matrix
		/// COLUMN MAJOR ORDER
		/// X and Y: 1 index base
		/// </summary>
		API_INTERFACE inline T getValue(int x, int y);

		/// <summary>
		/// Get the X axis
		/// COLUMN MAJOR ORDER
		/// </summary>
		API_INTERFACE inline Vec3<T> xAxis() const;

		/// <summary>
		/// Get the Y axis
		/// COLUMN MAJOR ORDER
		/// </summary>
		API_INTERFACE inline Vec3<T> yAxis() const;

		/// <summary>
		/// Get the Z axis
		/// COLUMN MAJOR ORDER
		/// </summary>
		API_INTERFACE inline Vec3<T> zAxis() const;

		/// <summary>
		/// Get the main / principal / major / primary diagonal from matrix
		/// </summary>
		API_INTERFACE inline Vec3<T> primaryDiagonal() const;

		/// <summary>
		/// Get the antidiagonal / counter / minor / secondary diagonal from matrix
		/// </summary>
		API_INTERFACE inline Vec3<T> secondaryDiagonal() const;

		/// <summary>
		/// Load a identity matrix
		/// </summary>
		API_INTERFACE static Mat3<T> identity();

		/// <summary>
		/// Transpose matrix - swap rows by columns
		/// </summary>
		API_INTERFACE inline Mat3<T> transpose() const;

		/// <summary>
		/// Multiply this matrix with the parametrized matrix => AxB
		/// </summary>
		API_INTERFACE inline Mat3<T> multiply(const Mat3<T>& matrixB) const;

		/// <summary>
		/// Multiply this matrix with the parametrized vector => AxB
		/// </summary>
		API_INTERFACE inline Vec3<T> multiply(const Vec3<T>& vector) const;

		/// <summary>
		/// Get the determinant from index i,j
		/// Zero-Index based
		/// </summary>
		API_INTERFACE inline T determinantIJ(size_t i, size_t j) const;

		/// <summary>
		/// Get the cofactor of the index i,j
		/// Zero-Index based
		/// </summary>
		API_INTERFACE inline T cofactorIJ(size_t i, size_t j) const;

		/// <summary>
		/// Create a scaled matrix
		/// </summary>
		API_INTERFACE static Mat3<T> createScale(T xScale, T yScale, T zScale);

		/// <summary>
		/// Scale the current matrix
		/// </summary>
		API_INTERFACE inline void scale(T xScale, T yScale, T zScale);

		/// <summary>
		/// Create a rotation matrix
		/// Example: x = 1.0 to rotate over X axis; x = 0.0 to not rotate over X axis
		/// </summary>
		API_INTERFACE static Mat3<T> createRotate(T angleRadians, T x, T y, T z);

		/// <summary>
		/// Craete a translation matrix
		/// </summary>
		API_INTERFACE static Mat3<T> createTranslate(T x, T y, T z);

		/// <summary>
		/// Get the determinant of the matrix
		/// </summary>
		API_INTERFACE inline T determinant() const;
		
		/// <summary>
		/// Get the inverse matrix from current matrix => A^-1
		/// <summary>
		API_INTERFACE Mat3<T> invert();

		/// <summary>
		/// Get the size in Bytes of Mat3
		/// </summary>
		inline API_INTERFACE size_t sizeInBytes() const;

		/// <summary>
		/// Clone this matrix
		/// </summary>
		API_INTERFACE inline Mat3<T> clone() const;

		/// <summary>
		/// Get a index from the vector
		/// </summary>
		API_INTERFACE inline T& operator[](int index);

		/// <summary>
		/// Get a index from the vector
		/// </summary>
		API_INTERFACE inline T operator[](int index) const;

		/// <summary>
		/// Auto convertion to void *
		/// </summary>
		API_INTERFACE inline operator void*() const;

		/// <summary>
		/// Auto convertion to T *
		/// It is the same of convertion to float* or int* or double*, whatever T is.
		/// </summary>
		API_INTERFACE inline operator T*();

		/// <summary>
		/// Multiply the matrix to another one
		/// </summary>
		API_INTERFACE inline Mat3<T> operator*(const Mat3<T>& matrix) const;

		/// <summary>
		/// Multiply the matrix to 3D vector
		/// </summary>
		API_INTERFACE inline Vec3<T> operator*(const Vec3<T>& matrix) const;

		/// <summary>
		/// Multiply the matrix to another one
		/// </summary>
		API_INTERFACE inline void operator*=(const Mat3<T>& matrix);

		/// <summary>
		/// Divide the matrix by a scalar value
		/// </summary>
		API_INTERFACE inline Mat3<T> operator/(T value);

		/// <summary>
		/// Divide the matrix by a scalar value
		/// </summary>
		API_INTERFACE inline void operator/=(T value);

		/// <summary>
		/// Get the matrix content as string
		/// </summary>
		API_INTERFACE inline string toString();

		/// <summary>
		/// Decompose the matrix to Lower and Upper matrix
		/// </summary>
		API_INTERFACE inline Mat3<T>* decomposeLU() const;

		/// <summary>
		/// Decompose the matrix to Lower, Diagonal Matrix and Upper matrix
		/// </summary>
		API_INTERFACE inline Mat3<T>* decomposeLDU() const;

		/// <summary>
		/// Get the autovalue of the matrix
		/// </summary>
		API_INTERFACE AutovalueAutovector3<T> getAutovalueAndAutovector(const unsigned short maxIteration = 5) const;

	};

	typedef Mat3<int> Mat3i;
	typedef Mat3<float> Mat3f;
	typedef Mat3<double> Mat3d;

}