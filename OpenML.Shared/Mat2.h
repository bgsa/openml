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
		API_INTERFACE Mat2();

		/// <summary>
		/// Constructor with initialized values
		/// </summary>
		API_INTERFACE Mat2(T* values);

		/// <summary>
		/// Constructor with initialized values - COL ORDER
		/// </summary>
		API_INTERFACE Mat2(T value11, T value12,
			T value21, T value22);

		/// <summary>
		/// Get the values from current matrix
		/// </summary>
		API_INTERFACE T* getValues();

		/// <summary>
		/// Get the value from current matrix
		/// COLUMN MAJOR ORDER
		/// X and Y: 1 index base
		/// </summary>
		API_INTERFACE T getValue(int x, int y);

		/// <summary>
		/// Get the X axis
		/// COLUMN MAJOR ORDER
		/// </summary>
		API_INTERFACE Vec2<T> xAxis();

		/// <summary>
		/// Get the Y axis
		/// COLUMN MAJOR ORDER
		/// </summary>
		API_INTERFACE Vec2<T> yAxis();

		/// <summary>
		/// Get the main / principal / major / primary diagonal from matrix
		/// </summary>
		API_INTERFACE Vec2<T> primaryDiagonal();

		/// <summary>
		/// Get the antidiagonal / counter / minor / secondary diagonal from matrix
		/// </summary>
		API_INTERFACE Vec2<T> secondaryDiagonal();

		/// <summary>
		/// Load a identity matrix
		/// </summary>
		API_INTERFACE static Mat2<T> identity()
		{
			static T identityMatrix[MAT2_SIZE] = {
				T(1), T(0),
				T(0), T(1)
			};

			Mat2 result;
			memcpy(&result, identityMatrix, sizeof(values));

			return result;
		}

		/// <summary>
		/// Transpose matrix - swap rows by columns
		/// </summary>
		API_INTERFACE Mat2<T> transpose();

		/// <summary>
		/// Multiply this matrix with the parametrized matrix => AxB
		/// </summary>
		API_INTERFACE Mat2<T> multiply(Mat2<T> matrixB);

		/// <summary>
		/// Multiply this matrix with the parametrized vector => AxB
		/// </summary>
		API_INTERFACE Vec2<T> multiply(Vec2<T> vector);

		/// <summary>
		/// Create a scaled matrix
		/// </summary>
		API_INTERFACE static Mat2<T> createScale(T xScale, T yScale)
		{
			Mat2<T> result = Mat2<T>::identity();

			result.scale(xScale, yScale);

			return result;
		}

		/// <summary>
		/// Scale the current matrix
		/// </summary>
		API_INTERFACE void scale(T xScale, T yScale);

		/// <summary>
		/// Craete a translation matrix
		/// </summary>
		API_INTERFACE static Mat2<T> createTranslate(T x, T y)
		{
			Mat2<T> result = Mat2<T>::identity();

#ifdef MAJOR_COLUMN_ORDER
			result[2] = x;
			result[3] = y;
#else
			result[1] = x;
			result[3] = y;
#endif

			return result;
		}

		/// <summary>
		/// Get the deeterminant of the Matrix
		/// </summary>
		API_INTERFACE T determinant();

		/// <summary>
		/// Get the autovalue of the matrix
		/// </summary>
		API_INTERFACE AutovalueAutovector2<T> getAutovalueAndAutovector(const unsigned short maxIteration = 5);

		/// <summary>
		/// Get the size in Bytes of Mat3
		/// </summary>
		API_INTERFACE size_t sizeInBytes();

		/// <summary>
		/// Clone this matrix
		/// </summary>
		API_INTERFACE Mat2<T> clone();

		/// <summary>
		/// Get a index from the vector
		/// </summary>
		API_INTERFACE T& operator[](int index);

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
		/// Multiply the matrix to another one
		/// </summary>
		API_INTERFACE Mat2<T> operator*(Mat2<T> matrix);

		/// <summary>
		/// Multiply the matrix to 2D vector
		/// </summary>
		API_INTERFACE Vec2<T> operator*(Vec2<T> matrix);

		/// <summary>
		/// Multiply the matrix to another one
		/// </summary>
		API_INTERFACE void operator*=(Mat2<T> matrix);

		/// <summary>
		/// Get the matrix content as string
		/// </summary>
		API_INTERFACE string toString();

	};

	typedef Mat2<int>	 Mat2i;
	typedef Mat2<float>  Mat2f;
	typedef Mat2<double> Mat2d;

}