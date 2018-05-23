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
		API_INTERFACE inline static Mat3<T> identity() 
		{
			static T identityMatrix[MAT3_SIZE] = {
				T(1), T(0), T(0),
				T(0), T(1), T(0),
				T(0), T(0), T(1)
			};

			Mat3<T> result;
			memcpy(&result, identityMatrix, sizeof(values));

			return result;
		}

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
		API_INTERFACE inline static Mat3<T> createScale(T xScale, T yScale, T zScale)
		{
			Mat3<T> result = Mat3<T>::identity();

			result.scale(xScale, yScale, zScale);

			return result;
		}

		/// <summary>
		/// Scale the current matrix
		/// </summary>
		API_INTERFACE inline void scale(T xScale, T yScale, T zScale);

		/// <summary>
		/// Create a rotation matrix
		/// Example: x = 1.0 to rotate over X axis; x = 0.0 to not rotate over X axis
		/// </summary>
		API_INTERFACE inline static Mat3<T> createRotate(T angleRadians, T x, T y, T z)
		{
			T mag, sine, cosine;
			T xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

			sine = T(sin(angleRadians));
			cosine = T(cos(angleRadians));

			mag = T(sqrt(x*x + y * y + z * z));

			if (mag == 0.0f)
				return Mat3::identity();

			// Rotation matrix is normalized
			x /= mag;
			y /= mag;
			z /= mag;

			xx = x * x;
			yy = y * y;
			zz = z * z;
			xy = x * y;
			yz = y * z;
			zx = z * x;
			xs = x * sine;
			ys = y * sine;
			zs = z * sine;
			one_c = T(1) - cosine;

			Mat3<T> result;

			result[0 * MAT3_ROWSIZE + 0] = (one_c * xx) + cosine;
			result[1 * MAT3_ROWSIZE + 0] = (one_c * xy) - zs;
			result[2 * MAT3_ROWSIZE + 0] = (one_c * zx) + ys;

			result[0 * MAT3_ROWSIZE + 1] = (one_c * xy) + zs;
			result[1 * MAT3_ROWSIZE + 1] = (one_c * yy) + cosine;
			result[2 * MAT3_ROWSIZE + 1] = (one_c * yz) - xs;

			result[0 * MAT3_ROWSIZE + 2] = (one_c * zx) - ys;
			result[1 * MAT3_ROWSIZE + 2] = (one_c * yz) + xs;
			result[2 * MAT3_ROWSIZE + 2] = (one_c * zz) + cosine;

			return result;
		}

		/// <summary>
		/// Craete a translation matrix
		/// </summary>
		API_INTERFACE inline static Mat3<T> createTranslate(T x, T y, T z)
		{
			Mat3<T> result = Mat3<T>::identity();

#if MAJOR_COLUMN_ORDER
			result[6] = x;
			result[7] = y;
			result[8] = z;
#else
			result[2] = x;
			result[5] = y;
			result[8] = z;
#endif

			return result;
		}

		/// <summary>
		/// Get the determinant of the matrix
		/// </summary>
		API_INTERFACE inline T determinant() const;

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