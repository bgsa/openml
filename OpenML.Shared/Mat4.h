#pragma once

#include "GlobalHeader.h"
#include "Mat.h"
#include "Mat3.h"
#include "Vec4.h"

namespace OpenML
{
#define MAT4_SIZE 16
#define MAT4_ROWSIZE 4

	template <typename T>
	class AutovalueAutovector4
	{
	public:
		T autovalue;
		Vec4<T> autovector;
	};

	template <typename T>
	class Mat4 : public Mat<T>
	{
	private:
		T values[MAT4_SIZE];

	public:

		/// <summary>
		/// Default constructor
		/// Load a empty matrix = 0
		/// </summary>
		API_INTERFACE Mat4(T defaultValue = T(0));

		/// <summary>
		/// Constructor with initialized values
		/// </summary>
		API_INTERFACE Mat4(T* values);

		/// <summary>
		/// Constructor with initialized values - COL ORDER
		/// </summary>
		API_INTERFACE Mat4(
			T value11, T value21, T value31, T value41,
			T value12, T value22, T value32, T value42,
			T value13, T value23, T value33, T value43,
			T value14, T value24, T value34, T value44);

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
		API_INTERFACE Vec4<T> xAxis() const;

		/// <summary>
		/// Get the Y axis
		/// COLUMN MAJOR ORDER
		/// <summary>
		API_INTERFACE Vec4<T> yAxis() const;

		/// <summary>
		/// Get the Z axis
		/// COLUMN MAJOR ORDER
		/// </summary>
		API_INTERFACE Vec4<T> zAxis() const;

		/// <summary>
		/// Get the Z axis
		/// COLUMN MAJOR ORDER
		/// </summary>
		API_INTERFACE Vec4<T> wAxis() const;

		/// <summary>
		/// Get the main / principal / major / primary diagonal from matrix
		/// </summary>
		API_INTERFACE Vec4<T> primaryDiagonal() const;

		/// <summary>
		/// Get the antidiagonal / counter / minor / secondary diagonal from matrix
		/// </summary>
		API_INTERFACE Vec4<T> secondaryDiagonal() const;

		/// <summary>
		/// Load a identity matrix
		/// </summary>
		API_INTERFACE static Mat4<T> identity();

		/// <summary>
		/// Transpose matrix - swap rows by columns
		/// </summary>
		API_INTERFACE Mat4<T> transpose() const;

		/// <summary>
		/// Get the determinant from index i,j
		/// Zero-Index based
		/// </summary>
		API_INTERFACE T determinantIJ(int i, int j) const;

		/// <summary>
		/// Get the cofactor of the index i,j
		/// Zero-Index based
		/// </summary>
		API_INTERFACE T cofactorIJ(int i, int j) const;

		/// <summary>
		/// Get the determinant from matrix
		/// </summary>
		API_INTERFACE T determinant() const;

		/// <summary>
		/// Multiply this matrix with the parametrized matrix => AxB
		/// <summary>
		API_INTERFACE Mat4<T> multiply(const Mat4<T> &matrixB) const;

		/// <summary>
		/// Multiply this matrix with the parametrized vector => AxB
		/// </summary>
		API_INTERFACE Vec4<T> multiply(const Vec4<T> &vector) const;

		/// <summary>
		/// Get the inverse matrix from current matrix => A^-1
		/// <summary>
		API_INTERFACE Mat4<T> invert() const;

		/// <summary>
		/// Create a scaled matrix
		/// </summary>
		API_INTERFACE static Mat4<T> createScale(T xScale, T yScale, T zScale);

		/// <summary>
		/// Scale the current matrix
		/// </summary>
		API_INTERFACE void scale(T xScale, T yScale, T zScale);

		/// <summary>
		/// Create a rotation matrix
		/// Example: x = 1.0 to rotate over X axis; x = 0.0 to not rotate over X axis
		/// </summary>
		API_INTERFACE static Mat4<T> createRotate(T angleRadians, T x, T y, T z);

		/// <summary>
		/// Craete a translation matrix
		/// </summary>
		API_INTERFACE static Mat4<T> createTranslate(T x, T y, T z);

		/// <summary>
		/// Craete a orthographic matrix projection
		/// </summary>
		API_INTERFACE static Mat4<T> createOrthographicMatrix(T xMin, T xMax, T yMin, T yMax, T zMin, T zMax);

		/// <summary>
		/// Get the size in Bytes of Mat4
		/// </summary>
		API_INTERFACE size_t sizeInBytes() const;

		/// <summary>
		/// Clone this matrix
		/// </summary>
		API_INTERFACE Mat4<T> clone() const;

		/// <summary>
		/// Multiply the vector to a scalar
		/// </summary>
		API_INTERFACE Mat4<T> operator*(T value) const;

		/// <summary>
		/// Multiply the matrix to another one
		/// </summary>
		API_INTERFACE void operator*=(const Mat4<T>& matrix);

		/// <summary>
		/// Multiply the matrix to another one
		/// </summary>
		API_INTERFACE Mat4<T> operator*(const Mat4<T>& matrix) const;

		/// <summary>
		/// Multiply the matrix to a vector
		/// </summary>
		API_INTERFACE Vec4<T> operator*(const Vec4<T> &vector) const;
		
		/// <summary>
		/// Sum this matrix to another one
		/// </summary>
		API_INTERFACE Mat4<T> operator+(const Mat4<T> &matrix) const;

		/// <summary>
		/// Sum a scalar to this matrix
		/// </summary>
		API_INTERFACE Mat4<T> operator+(T value) const;

		/// <summary>
		/// Subtract this matrix to another one
		/// </summary>
		API_INTERFACE Mat4<T> operator-(const Mat4<T>& matrix) const;

		/// <summary>
		/// Subtract a scalar from this matrix
		/// </summary>
		API_INTERFACE Mat4<T> operator-(T value) const;

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// </summary>
		API_INTERFACE bool operator==(const Mat4<T>& matrix) const;

		/// <summary>
		/// Compare this matrix to another one. Compare each component.
		/// </summary>
		API_INTERFACE bool operator==(T value) const;

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// </summary>
		API_INTERFACE bool operator!=(const Mat4<T>& matrix) const;

		/// <summary>
		/// Get a index from the vector
		/// </summary>
		API_INTERFACE T& operator[](int index);

		/// <summary>
		/// Get a index from the vector
		/// </summary>
		API_INTERFACE T operator[](int index) const;

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
		/// Convert the matrix to Matrix 3x3
		/// Returns the first 3 components of x-Axis, y-Axis, z-Axis
		/// </summary>
		API_INTERFACE Mat3<T> toMat3() const;

		/// <summary>
		/// Get the matrix content as string
		/// </summary>
		API_INTERFACE string toString();

		/// <summary>
		/// Decompose the matrix to Lower and Upper matrix
		/// </summary>
		API_INTERFACE Mat4<T>* decomposeLU() const;

		/// <summary>
		/// Decompose the matrix to Lower, Diagonal Matrix and Upper matrix
		/// </summary>
		API_INTERFACE Mat4<T>* decomposeLDU() const;

		/// <summary>
		/// Get the autovalue of the matrix
		/// </summary>
		API_INTERFACE AutovalueAutovector4<T> getAutovalueAndAutovector(const unsigned short maxIteration = 5) const;

		/*
		/// <summary>
		/// Get the normal matrix
		/// </summary>
		API_INTERFACE Mat3<T> toNormalMatrix();
		*/
	};

	typedef Mat4<int> Mat4i;
	typedef Mat4<float> Mat4f;
	typedef Mat4<double> Mat4d;

}