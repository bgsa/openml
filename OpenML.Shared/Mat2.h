#pragma once

#include "OpenML.h"

namespace OpenML
{
#define MAT2_SIZE 4
#define MAT2_ROWSIZE 2

	template <typename T>
	struct AutovalueAutovector2 {
		T autovalue;
		Vec2<T> autovector;
	};

	template <typename T>
	class Mat2 : public Mat<T>
	{
	private:
		T values[MAT2_SIZE];

	public:

		/// <summary>
		/// Default constructor
		/// Load a empty matrix = 0
		/// </summary>
		API_INTERFACE inline Mat2(T defaultValue = T(0));

		/// <summary>
		/// Constructor with initialized values
		/// </summary>
		API_INTERFACE inline Mat2(T* values);

		/// <summary>
		/// Constructor with initialized values - COL ORDER
		/// </summary>
		API_INTERFACE inline Mat2(T value11, T value12, T value21, T value22);

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
		API_INTERFACE inline Vec2<T> xAxis() const;

		/// <summary>
		/// Get the Y axis
		/// COLUMN MAJOR ORDER
		/// </summary>
		API_INTERFACE inline Vec2<T> yAxis() const;

		/// <summary>
		/// Get the main / principal / major / primary diagonal from matrix
		/// </summary>
		API_INTERFACE inline Vec2<T> primaryDiagonal() const;

		/// <summary>
		/// Get the antidiagonal / counter / minor / secondary diagonal from matrix
		/// </summary>
		API_INTERFACE inline Vec2<T> secondaryDiagonal() const;

		/// <summary>
		/// Load a identity matrix
		/// </summary>
		API_INTERFACE static Mat2<T> identity();

		/// <summary>
		/// Transpose matrix - swap rows by columns
		/// </summary>
		API_INTERFACE inline Mat2<T> transpose() const;

		/// <summary>
		/// Multiply this matrix with the parametrized matrix => AxB
		/// </summary>
		API_INTERFACE inline Mat2<T> multiply(const Mat2<T>& matrixB) const;

		/// <summary>
		/// Multiply this matrix with the parametrized vector => AxB
		/// </summary>
		API_INTERFACE inline Vec2<T> multiply(const Vec2<T>& vector) const;

		/// <summary>
		/// Create a scaled matrix
		/// </summary>
		API_INTERFACE static Mat2<T> createScale(T xScale, T yScale);

		/// <summary>
		/// Scale the current matrix
		/// </summary>
		API_INTERFACE inline void scale(T xScale, T yScale);

		/// <summary>
		/// Craete a translation matrix
		/// </summary>
		API_INTERFACE static Mat2<T> createTranslate(T x, T y);

		/// <summary>
		/// Get the deeterminant of the Matrix
		/// </summary>
		API_INTERFACE inline T determinant() const;

		/// <summary>
		/// Get the autovalue of the matrix
		/// </summary>
		API_INTERFACE inline AutovalueAutovector2<T> getAutovalueAndAutovector(const unsigned short maxIteration = 5) const;

		/// <summary>
		/// Get the size in Bytes of Mat3
		/// </summary>
		API_INTERFACE inline size_t sizeInBytes() const;

		/// <summary>
		/// Clone this matrix
		/// </summary>
		API_INTERFACE inline Mat2<T> clone() const;

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
		/// Get the negative matrix
		/// </summary>
		API_INTERFACE inline Mat2<T> operator-() const;

		/// <summary>
		/// Subtract a matrix to another one
		/// </summary>
		API_INTERFACE inline Mat2<T> operator-(const Mat2<T>& matrix) const;

		/// <summary>
		/// Sum a matrix to another one
		/// </summary>
		API_INTERFACE inline Mat2<T> operator+(const Mat2<T>& matrix) const;

		/// <summary>
		/// Multiply the matrix to another one
		/// </summary>
		API_INTERFACE inline Mat2<T> operator*(const Mat2<T>& matrix) const;

		/// <summary>
		/// Multiply the matrix to 2D vector
		/// </summary>
		API_INTERFACE inline Vec2<T> operator*(const Vec2<T>& matrix) const;

		/// <summary>
		/// Multiply the matrix to another one
		/// </summary>
		API_INTERFACE inline void operator*=(const Mat2<T>& matrix);

		/// <summary>
		/// Divide the matrix by a scalar value
		/// </summary>
		API_INTERFACE inline Mat2<T> operator/(T value);

		/// <summary>
		/// Divide the matrix by a scalar value
		/// </summary>
		API_INTERFACE inline void operator/=(T value);

		/// <summary>
		/// Get the matrix content as string
		/// </summary>
		API_INTERFACE inline string toString();

	};

	typedef Mat2<int>	 Mat2i;
	typedef Mat2<float>  Mat2f;
	typedef Mat2<double> Mat2d;

}