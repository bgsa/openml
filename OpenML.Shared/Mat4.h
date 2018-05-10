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
		API_INTERFACE Mat4();

		/// <summary>
		/// Constructor with initialized values
		/// </summary>
		API_INTERFACE Mat4(T* values);

		/// <summary>
		/// Constructor with initialized values - COL ORDER
		/// </summary>
		API_INTERFACE Mat4(T value11, T value21, T value31, T value41,
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
		API_INTERFACE Vec4<T> xAxis();

		/// <summary>
		/// Get the Y axis
		/// COLUMN MAJOR ORDER
		/// <summary>
		API_INTERFACE Vec4<T> yAxis();

		/// <summary>
		/// Get the Z axis
		/// COLUMN MAJOR ORDER
		/// </summary>
		API_INTERFACE Vec4<T> zAxis();

		/// <summary>
		/// Get the Z axis
		/// COLUMN MAJOR ORDER
		/// </summary>
		API_INTERFACE Vec4<T> wAxis();

		/// <summary>
		/// Get the main / principal / major / primary diagonal from matrix
		/// </summary>
		API_INTERFACE Vec4<T> primaryDiagonal();

		/// <summary>
		/// Get the antidiagonal / counter / minor / secondary diagonal from matrix
		/// </summary>
		API_INTERFACE Vec4<T> secondaryDiagonal();

		/// <summary>
		/// Load a identity matrix
		/// </summary>
		API_INTERFACE static Mat4<T> identity()
		{
			static T identityMatrix[MAT4_SIZE] = {
				T(1), T(0), T(0), T(0),
				T(0), T(1), T(0), T(0),
				T(0), T(0), T(1), T(0),
				T(0), T(0), T(0), T(1)
			};

			Mat4 result;
			memcpy(&result, identityMatrix, sizeof(values));

			return result;
		}

		/// <summary>
		/// Transpose matrix - swap rows by columns
		/// </summary>
		API_INTERFACE Mat4<T> transpose();

		/// <summary>
		/// Get the determinant from index i,j
		/// Zero-Index based
		/// </summary>
		API_INTERFACE T determinantIJ(int i, int j);

		/// <summary>
		/// Get the cofactor of the index i,j
		/// Zero-Index based
		/// </summary>
		API_INTERFACE T cofactorIJ(int i, int j);

		/// <summary>
		/// Get the determinant from matrix
		/// </summary>
		API_INTERFACE T determinant();

		/// <summary>
		/// Multiply this matrix with the parametrized matrix => AxB
		/// <summary>
		API_INTERFACE Mat4<T> multiply(Mat4<T> matrixB);

		/// <summary>
		/// Multiply this matrix with the parametrized vector => AxB
		/// </summary>
		API_INTERFACE Vec4<T> multiply(Vec4<T> vector);

		/// <summary>
		/// Get the inverse matrix from current matrix => A^-1
		/// <summary>
		API_INTERFACE Mat4<T> invert();

		/// <summary>
		/// Create a scaled matrix
		/// </summary>
		API_INTERFACE static Mat4<T> createScale(T xScale, T yScale, T zScale)
		{
			Mat4<T> result = Mat4<T>::identity();

			result.scale(xScale, yScale, zScale);

			return result;
		}

		/// <summary>
		/// Scale the current matrix
		/// </summary>
		API_INTERFACE void scale(T xScale, T yScale, T zScale);

		/// <summary>
		/// Create a rotation matrix
		/// Example: x = 1.0 to rotate over X axis; x = 0.0 to not rotate over X axis
		/// </summary>
		API_INTERFACE static Mat4<T> createRotate(T angleRadians, T x, T y, T z)
		{
			T mag, sineAngle, cosineAngle;
			T xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

			sineAngle = T(sin(angleRadians));
			cosineAngle = T(cos(angleRadians));

			mag = T(sqrt(x*x + y * y + z * z));

			if (mag == 0.0f)
				return Mat4::identity();

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
			xs = x * sineAngle;
			ys = y * sineAngle;
			zs = z * sineAngle;
			one_c = T(1) - cosineAngle;

			Mat4<T> result;

#define M(row,col)  result[col * MAT4_ROWSIZE + row]
			M(0, 0) = (one_c * xx) + cosineAngle;
			M(0, 1) = (one_c * xy) - zs;
			M(0, 2) = (one_c * zx) + ys;
			M(0, 3) = T(0);

			M(1, 0) = (one_c * xy) + zs;
			M(1, 1) = (one_c * yy) + cosineAngle;
			M(1, 2) = (one_c * yz) - xs;
			M(1, 3) = T(0);

			M(2, 0) = (one_c * zx) - ys;
			M(2, 1) = (one_c * yz) + xs;
			M(2, 2) = (one_c * zz) + cosineAngle;
			M(2, 3) = T(0);

			M(3, 0) = T(0);
			M(3, 1) = T(0);
			M(3, 2) = T(0);
			M(3, 3) = T(1);
#undef M

			return result;
		}

		/// <summary>
		/// Craete a translation matrix
		/// </summary>
		API_INTERFACE static Mat4<T> createTranslate(T x, T y, T z)
		{
			Mat4<T> result = Mat4<T>::identity();

#if MAJOR_COLUMN_ORDER
			result[12] = x;
			result[13] = y;
			result[14] = z;
#else
			result[3] = x;
			result[7] = y;
			result[11] = z;
#endif

			return result;
		}

		/// <summary>
		/// Craete a orthographic matrix projection
		/// </summary>
		API_INTERFACE static Mat4<T> createOrthographicMatrix(T xMin, T xMax, T yMin, T yMax, T zMin, T zMax)
		{
			Mat4<T> projectionMatrix = Mat4<T>::identity();

			projectionMatrix[0] = T(2) / (xMax - xMin);
			projectionMatrix[5] = T(2) / (yMax - yMin);
			projectionMatrix[10] = T(-2) / (zMax - zMin);
			projectionMatrix[12] = -((xMax + xMin) / (xMax - xMin));
			projectionMatrix[13] = -((yMax + yMin) / (yMax - yMin));
			projectionMatrix[14] = -((zMax + zMin) / (zMax - zMin));
			projectionMatrix[15] = T(1);

			return projectionMatrix;
		}

		/// <summary>
		/// Get the size in Bytes of Mat4
		/// </summary>
		API_INTERFACE size_t sizeInBytes();

		/// <summary>
		/// Clone this matrix
		/// </summary>
		API_INTERFACE Mat4<T> clone();

		/// <summary>
		/// Multiply the vector to a scalar
		/// </summary>
		API_INTERFACE Mat4<T> operator*(T value);

		/// <summary>
		/// Multiply the matrix to another one
		/// </summary>
		API_INTERFACE void operator*=(Mat4<T> matrix);

		/// <summary>
		/// Multiply the matrix to another one
		/// </summary>
		API_INTERFACE Mat4<T> operator*(Mat4<T> matrix);

		/// <summary>
		/// Multiply the matrix to a vector
		/// </summary>
		API_INTERFACE Vec4<T> operator*(Vec4<T> vector);

		/// <summary>
		/// Sum this matrix to another one
		/// </summary>
		API_INTERFACE Mat4<T> operator+(Mat4<T> matrix);

		/// <summary>
		/// Sum a scalar to this matrix
		/// </summary>
		API_INTERFACE Mat4<T> operator+(T value);

		/// <summary>
		/// Subtract this matrix to another one
		/// </summary>
		API_INTERFACE Mat4<T> operator-(Mat4<T> matrix);

		/// <summary>
		/// Subtract a scalar from this matrix
		/// </summary>
		API_INTERFACE Mat4<T> operator-(T value);

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// </summary>
		API_INTERFACE bool operator==(Mat4<T> matrix);

		/// <summary>
		/// Compare this matrix to another one. Compare each component.
		/// </summary>
		API_INTERFACE bool operator==(T value);

		/// <summary>
		/// Compare this vector to another one. Compare each component.
		/// </summary>
		API_INTERFACE bool operator!=(Mat4<T> matrix);

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
		/// Convert the matrix to Matrix 3x3
		/// Returns the first 3 components of x-Axis, y-Axis, z-Axis
		/// </summary>
		API_INTERFACE Mat3<T> toMat3();

		/// <summary>
		/// Get the matrix content as string
		/// </summary>
		API_INTERFACE string toString();

		/// <summary>
		/// Decompose the matrix to Lower and Upper matrix
		/// </summary>
		API_INTERFACE Mat4<T>* decomposeLU();

		/// <summary>
		/// Decompose the matrix to Lower, Diagonal Matrix and Upper matrix
		/// </summary>
		API_INTERFACE Mat4<T>* decomposeLDU();

		/// <summary>
		/// Get the autovalue of the matrix
		/// </summary>
		API_INTERFACE AutovalueAutovector4<T> getAutovalueAndAutovector(const unsigned short maxIteration = 5);

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