#include "Mat4.h"

using namespace OpenML;

template <typename T>
Mat4<T>::Mat4(T defaultValue)
{
	static T emptyMatrix[MAT4_SIZE] = {
		defaultValue, defaultValue, defaultValue, defaultValue,
		defaultValue, defaultValue, defaultValue, defaultValue,
		defaultValue, defaultValue, defaultValue, defaultValue,
		defaultValue, defaultValue, defaultValue, defaultValue
	};

	memcpy(&values, emptyMatrix, sizeof(values));
}

template <typename T>
Mat4<T>::Mat4(T* values)
{
	memcpy(&this->values, values, sizeof(this->values));
}

template <typename T>
Mat4<T>::Mat4(T value11, T value21, T value31, T value41,
	T value12, T value22, T value32, T value42,
	T value13, T value23, T value33, T value43,
	T value14, T value24, T value34, T value44)
{
	values[0] = value11;
	values[1] = value21;
	values[2] = value31;
	values[3] = value41;

	values[4] = value12;
	values[5] = value22;
	values[6] = value32;
	values[7] = value42;

	values[8] = value13;
	values[9] = value23;
	values[10] = value33;
	values[11] = value43;

	values[12] = value14;
	values[13] = value24;
	values[14] = value34;
	values[15] = value44;
}

template <typename T>
T* Mat4<T>::getValues()
{
	return values;
}

template <typename T>
T Mat4<T>::getValue(int x, int y)
{
	x--;
	y--;

	return values[y * MAT4_ROWSIZE + x];
}

template <typename T>
Vec4<T> Mat4<T>::xAxis() const
{
#if MAJOR_COLUMN_ORDER
	return Vec4<T> {
		values[0 * MAT4_ROWSIZE + 0],
			values[1 * MAT4_ROWSIZE + 0],
			values[2 * MAT4_ROWSIZE + 0],
			values[3 * MAT4_ROWSIZE + 0]
	};
#else
	return Vec4<T> {
		values[0 * MAT4_ROWSIZE + 0],
			values[0 * MAT4_ROWSIZE + 1],
			values[0 * MAT4_ROWSIZE + 2],
			values[0 * MAT4_ROWSIZE + 3]
	};
#endif
}

template <typename T>
Vec4<T> Mat4<T>::yAxis() const
{
#if MAJOR_COLUMN_ORDER
	return Vec4<T> {
		values[0 * MAT4_ROWSIZE + 1],
			values[1 * MAT4_ROWSIZE + 1],
			values[2 * MAT4_ROWSIZE + 1],
			values[3 * MAT4_ROWSIZE + 1]
	};
#else
	return Vec4<T> {
		values[1 * MAT4_ROWSIZE + 0],
			values[1 * MAT4_ROWSIZE + 1],
			values[1 * MAT4_ROWSIZE + 2],
			values[1 * MAT4_ROWSIZE + 3]
	};
#endif
}

template <typename T>
Vec4<T> Mat4<T>::zAxis() const
{
#if MAJOR_COLUMN_ORDER
	return Vec4<T> {
		values[0 * MAT4_ROWSIZE + 2],
			values[1 * MAT4_ROWSIZE + 2],
			values[2 * MAT4_ROWSIZE + 2],
			values[3 * MAT4_ROWSIZE + 2]
	};
#else
	return Vec4<T> {
		values[2 * MAT4_ROWSIZE + 0],
			values[2 * MAT4_ROWSIZE + 1],
			values[2 * MAT4_ROWSIZE + 2],
			values[2 * MAT4_ROWSIZE + 3]
	};
#endif
}

template <typename T>
Vec4<T> Mat4<T>::wAxis() const
{
#if MAJOR_COLUMN_ORDER
	return Vec4<T> {
		values[0 * MAT4_ROWSIZE + 3],
			values[1 * MAT4_ROWSIZE + 3],
			values[2 * MAT4_ROWSIZE + 3],
			values[3 * MAT4_ROWSIZE + 3]
	};
#else
	return Vec4<T> {
		values[3 * MAT4_ROWSIZE + 0],
			values[3 * MAT4_ROWSIZE + 1],
			values[3 * MAT4_ROWSIZE + 2],
			values[3 * MAT4_ROWSIZE + 3]
	};
#endif
}

template <typename T>
Vec4<T> Mat4<T>::primaryDiagonal() const
{
	return Vec4<T> {
		values[0],
			values[5],
			values[10],
			values[15]
	};
}

template <typename T>
Vec4<T> Mat4<T>::secondaryDiagonal() const
{
	return Vec4<T> {
		values[3],
			values[6],
			values[9],
			values[12]
	};
}

template <typename T>
Mat4<T> Mat4<T>::identity()
{
	static T identityMatrix[MAT4_SIZE] = {
		T(1), T(0), T(0), T(0),
		T(0), T(1), T(0), T(0),
		T(0), T(0), T(1), T(0),
		T(0), T(0), T(0), T(1)
	};

	Mat4<T> result;
	memcpy(&result, identityMatrix, sizeof(values));

	return result;
}

template <typename T>
Mat4<T> Mat4<T>::transpose() const
{
	Mat4<T> result;

	//copy principal diagonal
	result[0] = values[0];
	result[5] = values[5];
	result[10] = values[10];
	result[15] = values[15];

	//swap others numbers
	T temp = values[1];
	result[1] = values[4];
	result[4] = temp;

	temp = values[2];
	result[2] = values[8];
	result[8] = temp;

	temp = values[3];
	result[3] = values[12];
	result[12] = temp;

	temp = values[6];
	result[6] = values[9];
	result[9] = temp;

	temp = values[7];
	result[7] = values[13];
	result[13] = temp;

	temp = values[11];
	result[11] = values[14];
	result[14] = temp;

	return result;
}

template <typename T>
T Mat4<T>::determinantIJ(int i, int j) const
{
	int x, y, ii, jj;
	T ret, mat[3][3];

	x = 0;
	for (ii = 0; ii < 4; ii++)
	{
		if (ii == i)
			continue;

		y = 0;

		for (jj = 0; jj < 4; jj++)
		{
			if (jj == j)
				continue;

			mat[x][y] = values[(ii * 4) + jj];
			y++;
		}

		x++;
	}

	ret = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]);
	ret -= mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]);
	ret += mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);

	return ret;
}

template <typename T>
T Mat4<T>::cofactorIJ(int i, int j) const
{
	T determinantIJValue = determinantIJ(i, j);

	if (OpenML::isOdd(i + j))
		determinantIJValue *= -1;

	return determinantIJValue;
}

template <typename T>
T Mat4<T>::determinant() const
{
	T det = T(0);

	for (int i = 0; i < MAT4_ROWSIZE; i++)
	{
		det += (i & 0x1) ? (-values[i] * determinantIJ(0, i)) : (values[i] * determinantIJ(0, i));
	}

	return det;
}

template <typename T>
Mat4<T> Mat4<T>::multiply(const Mat4<T> &matrixB) const
{
	Mat4<T> result;

#if MAJOR_COLUMN_ORDER
	for (int line = 0; line < MAT4_ROWSIZE; line++)
	{
		const T ai0 = values[(0 * MAT4_ROWSIZE) + line];
		const T ai1 = values[(1 * MAT4_ROWSIZE) + line];
		const T ai2 = values[(2 * MAT4_ROWSIZE) + line];
		const T ai3 = values[(3 * MAT4_ROWSIZE) + line];

		T a = matrixB[0];

		result[(0 * MAT4_ROWSIZE) + line] = ai0 * matrixB[(0 * MAT4_ROWSIZE) + 0] + ai1 * matrixB[(0 * MAT4_ROWSIZE) + 1] + ai2 * matrixB[(0 * MAT4_ROWSIZE) + 2] + ai3 * matrixB[(0 * MAT4_ROWSIZE) + 3];
		result[(1 * MAT4_ROWSIZE) + line] = ai0 * matrixB[(1 * MAT4_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT4_ROWSIZE) + 1] + ai2 * matrixB[(1 * MAT4_ROWSIZE) + 2] + ai3 * matrixB[(1 * MAT4_ROWSIZE) + 3];
		result[(2 * MAT4_ROWSIZE) + line] = ai0 * matrixB[(2 * MAT4_ROWSIZE) + 0] + ai1 * matrixB[(2 * MAT4_ROWSIZE) + 1] + ai2 * matrixB[(2 * MAT4_ROWSIZE) + 2] + ai3 * matrixB[(2 * MAT4_ROWSIZE) + 3];
		result[(3 * MAT4_ROWSIZE) + line] = ai0 * matrixB[(3 * MAT4_ROWSIZE) + 0] + ai1 * matrixB[(3 * MAT4_ROWSIZE) + 1] + ai2 * matrixB[(3 * MAT4_ROWSIZE) + 2] + ai3 * matrixB[(3 * MAT4_ROWSIZE) + 3];
	}
#else 
	for (int column = 0; column < MAT4_ROWSIZE; column++)
	{
		T ai0 = values[(column * MAT4_ROWSIZE) + 0];
		T ai1 = values[(column * MAT4_ROWSIZE) + 1];
		T ai2 = values[(column * MAT4_ROWSIZE) + 2];
		T ai3 = values[(column * MAT4_ROWSIZE) + 3];

		result[(column * MAT4_ROWSIZE) + 0] = ai0 * matrixB[(0 * MAT4_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT4_ROWSIZE) + 0] + ai2 * matrixB[(2 * MAT4_ROWSIZE) + 0] + ai3 * matrixB[(3 * MAT4_ROWSIZE) + 0];
		result[(column * MAT4_ROWSIZE) + 1] = ai0 * matrixB[(0 * MAT4_ROWSIZE) + 1] + ai1 * matrixB[(1 * MAT4_ROWSIZE) + 1] + ai2 * matrixB[(2 * MAT4_ROWSIZE) + 1] + ai3 * matrixB[(3 * MAT4_ROWSIZE) + 1];
		result[(column * MAT4_ROWSIZE) + 2] = ai0 * matrixB[(0 * MAT4_ROWSIZE) + 2] + ai1 * matrixB[(1 * MAT4_ROWSIZE) + 2] + ai2 * matrixB[(2 * MAT4_ROWSIZE) + 2] + ai3 * matrixB[(3 * MAT4_ROWSIZE) + 2];
		result[(column * MAT4_ROWSIZE) + 3] = ai0 * matrixB[(0 * MAT4_ROWSIZE) + 3] + ai1 * matrixB[(1 * MAT4_ROWSIZE) + 3] + ai2 * matrixB[(2 * MAT4_ROWSIZE) + 3] + ai3 * matrixB[(3 * MAT4_ROWSIZE) + 3];
	}
#endif

	return result;
}

template <typename T>
Vec4<T> Mat4<T>::multiply(const Vec4<T> &vector) const
{
	Vec4<T> result;

#if MAJOR_COLUMN_ORDER
	result[0]
		= vector[0] * values[0 * MAT4_ROWSIZE + 0]
		+ vector[1] * values[1 * MAT4_ROWSIZE + 0]
		+ vector[2] * values[2 * MAT4_ROWSIZE + 0]
		+ vector[3] * values[3 * MAT4_ROWSIZE + 0];

	result[1]
		= vector[0] * values[0 * MAT4_ROWSIZE + 1]
		+ vector[1] * values[1 * MAT4_ROWSIZE + 1]
		+ vector[2] * values[2 * MAT4_ROWSIZE + 1]
		+ vector[3] * values[3 * MAT4_ROWSIZE + 1];

	result[2]
		= vector[0] * values[0 * MAT4_ROWSIZE + 2]
		+ vector[1] * values[1 * MAT4_ROWSIZE + 2]
		+ vector[2] * values[2 * MAT4_ROWSIZE + 2]
		+ vector[3] * values[3 * MAT4_ROWSIZE + 2];

	result[3]
		= vector[0] * values[0 * MAT4_ROWSIZE + 3]
		+ vector[1] * values[1 * MAT4_ROWSIZE + 3]
		+ vector[2] * values[2 * MAT4_ROWSIZE + 3]
		+ vector[3] * values[3 * MAT4_ROWSIZE + 3];

#else

	result[0]
		= values[0 * MAT4_ROWSIZE + 0] * vector[0]
		+ values[0 * MAT4_ROWSIZE + 1] * vector[1]
		+ values[0 * MAT4_ROWSIZE + 2] * vector[2]
		+ values[0 * MAT4_ROWSIZE + 3] * vector[3];

	result[1]
		= values[1 * MAT4_ROWSIZE + 0] * vector[0]
		+ values[1 * MAT4_ROWSIZE + 1] * vector[1]
		+ values[1 * MAT4_ROWSIZE + 2] * vector[2]
		+ values[1 * MAT4_ROWSIZE + 3] * vector[3];

	result[2]
		= values[2 * MAT4_ROWSIZE + 0] * vector[0]
		+ values[2 * MAT4_ROWSIZE + 1] * vector[1]
		+ values[2 * MAT4_ROWSIZE + 2] * vector[2]
		+ values[2 * MAT4_ROWSIZE + 3] * vector[3];

	result[3]
		= values[3 * MAT4_ROWSIZE + 0] * vector[0]
		+ values[3 * MAT4_ROWSIZE + 1] * vector[1]
		+ values[3 * MAT4_ROWSIZE + 2] * vector[2]
		+ values[3 * MAT4_ROWSIZE + 3] * vector[3];
#endif

	return result;
}

template <typename T>
Mat4<T> Mat4<T>::invert() const
{
	Mat4<T> mInverse;

	int i, j;
	T det = T(0);
	T detij;

	// calculate 4x4 determinant
	for (i = 0; i < 4; i++)
	{
		det += (i & 0x1) ? (-values[i] * determinantIJ(0, i)) : (values[i] * determinantIJ(0, i));
	}
	det = T(1) / det;

	// calculate inverse
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			detij = determinantIJ(j, i);
			mInverse[(i * 4) + j] = ((i + j) & 0x1) ? (-detij * det) : (detij *det);
		}
	}

	return mInverse;
}

template <typename T>
Mat4<T> Mat4<T>::createScale(T xScale, T yScale, T zScale)
{
	Mat4<T> result = Mat4<T>::identity();

	result.scale(xScale, yScale, zScale);

	return result;
}

template <typename T>
void Mat4<T>::scale(T xScale, T yScale, T zScale)
{
	values[0] *= xScale;
	values[5] *= yScale;
	values[10] *= zScale;
}

template <typename T>
Mat4<T> Mat4<T>::createRotate(T angleRadians, T x, T y, T z)
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

template <typename T>
Mat4<T> Mat4<T>::createTranslate(T x, T y, T z)
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

template <typename T>
Mat4<T> Mat4<T>::createOrthographicMatrix(T xMin, T xMax, T yMin, T yMax, T zMin, T zMax)
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

template <typename T>
size_t Mat4<T>::sizeInBytes() const
{
	return MAT4_SIZE * sizeof(T);
}

template <typename T>
Mat4<T> Mat4<T>::clone() const
{
	Mat4<T> result;

	memcpy(&result, this, sizeof(Mat4<T>));

	return result;
}

template <typename T>
Mat4<T> Mat4<T>::operator*(T value)  const
{
	Mat4<T> result;

	for (int i = 0; i < MAT4_SIZE; i++)
		result[i] = values[i] * value;

	return result;
}

template <typename T>
void Mat4<T>::operator*=(const Mat4<T> &matrix)
{
	memcpy(&this->values, multiply(matrix).values, sizeof(this->values));
}

template <typename T>
Mat4<T> Mat4<T>::operator*(const Mat4<T> &matrix) const
{
	return multiply(matrix);
}

template <typename T>
Vec4<T> Mat4<T>::operator*(const Vec4<T> &vector) const
{
	return multiply(vector);
}

template <typename T>
Mat4<T> Mat4<T>::operator/(T value)
{
	return Mat4<T> {
		values[0] / value, values[1] / value, values[2] / value, values[3] / value,
		values[4] / value, values[5] / value, values[6] / value, values[7] / value,
		values[8] / value, values[9] / value, values[10] / value, values[11] / value,
		values[12] / value, values[13] / value, values[14] / value, values[15] / value
	};
}

template <typename T>
void Mat4<T>::operator/=(T value)
{
	for (size_t i = 0; i < MAT4_SIZE; i++)
		values[i] /= value;
}

template <typename T>
Mat4<T> Mat4<T>::operator-() const
{
	Mat4<T> result;

	for (int i = 0; i < MAT4_SIZE; i++)
		result[i] = -values[i];

	return result;
}

template <typename T>
Mat4<T> Mat4<T>::operator+(const Mat4<T>& matrix) const
{
	Mat4<T> result;

	for (int i = 0; i < MAT4_SIZE; i++)
		result[i] = values[i] + matrix[i];

	return result;
}

template <typename T>
Mat4<T> Mat4<T>::operator+(T value) const
{
	Mat4<T> result;

	for (int i = 0; i < MAT4_SIZE; i++)
		result[i] = values[i] + value;

	return result;
}

template <typename T>
Mat4<T> Mat4<T>::operator-(const Mat4<T>& matrix) const
{
	Mat4<T> result;

	for (int i = 0; i < MAT4_SIZE; i++)
		result[i] = values[i] - matrix[i];

	return result;
}

template <typename T>
Mat4<T> Mat4<T>::operator-(T value) const
{
	Mat4<T> result;

	for (int i = 0; i < MAT4_SIZE; i++)
		result[i] = values[i] - value;

	return result;
}

template <typename T>
bool Mat4<T>::operator==(const Mat4<T>& matrix) const
{
	for (int i = 0; i < MAT4_SIZE; i++)
		if (values[i] != matrix[i])
			return false;

	return true;
}

template <typename T>
bool Mat4<T>::operator==(T value) const
{
	for (int i = 0; i < MAT4_SIZE; i++)
		if (values[i] != value)
			return false;

	return true;
}

template <typename T>
bool Mat4<T>::operator!=(const Mat4<T>& matrix) const
{
	for (int i = 0; i < MAT4_SIZE; i++)
		if (values[i] != matrix[i])
			return true;

	return false;
}

template <typename T>
T& Mat4<T>::operator[](int index)
{
	assert(index >= 0 && index < MAT4_SIZE);

	return values[index];
}

template <typename T>
T Mat4<T>::operator[](int index) const
{
	assert(index >= 0 && index < MAT4_SIZE);

	return values[index];
}

template <typename T>
Mat4<T>::operator void*() const
{
	return (void*) values;
}

template <typename T>
Mat4<T>::operator T*()
{
	return values;
}

template <typename T>
Mat3<T> Mat4<T>::toMat3() const
{
	return Mat3<T> {
		values[0], values[1], values[2],
			values[4], values[5], values[6],
			values[8], values[9], values[10]
	};
}

template <typename T>
string Mat4<T>::toString()
{
	return Mat<T>::toString(values, MAT4_SIZE);
}

template <typename T>
Mat4<T>* Mat4<T>::decomposeLU() const
{
	Mat4<T> lowerMatrix = Mat4<T>::identity();
	Mat4<T> upperMatrix = this->clone();
	Mat4<T>* result = new Mat4<T>[2];

	vector<Mat4<T>> elementarInverseMatrixes;
	Mat4<T> elementarInverseMatrix;

	int rowSize = MAT4_ROWSIZE;
	int colSize = MAT4_ROWSIZE;

#if MAJOR_COLUMN_ORDER
	int pivotRowIndex = 0;

	for (int column = 0; column < colSize; column++)
	{
		T pivot = upperMatrix[pivotRowIndex * rowSize + column];
		T pivotOperator = 1 / pivot;

		for (int row = 0; row < rowSize; row++)
			upperMatrix[row * rowSize + column] *= pivotOperator;

		elementarInverseMatrix = Mat4<T>::identity();
		elementarInverseMatrix[pivotRowIndex * rowSize + column] = pivot;
		elementarInverseMatrixes.push_back(elementarInverseMatrix);

		for (int lowerColumns = column + 1; lowerColumns < rowSize; lowerColumns++)
		{
			pivot = upperMatrix[pivotRowIndex * rowSize + lowerColumns];
			pivotOperator = -pivot;

			for (int row = 0; row < rowSize; row++)
				upperMatrix[row * rowSize + lowerColumns] += pivotOperator * upperMatrix[row * rowSize + column];

			elementarInverseMatrix = Mat4<T>::identity();
			elementarInverseMatrix[pivotRowIndex * rowSize + lowerColumns] = pivot;
			elementarInverseMatrixes.push_back(elementarInverseMatrix);
		}

		pivotRowIndex++;
	}

	for (int i = 0; size_t(i) < elementarInverseMatrixes.size(); i++)
		lowerMatrix *= elementarInverseMatrixes[i];
#else
	int pivotColumnIndex = 0;

	for (int line = 0; line < rowSize; line++)
	{
		T pivot = upperMatrix[line * rowSize + pivotColumnIndex];
		T pivotOperator = 1 / pivot;

		for (int column = 0; column < colSize; column++)
			upperMatrix[line * rowSize + column] *= pivotOperator;

		elementarInverseMatrix = Mat4<T>::identity();
		elementarInverseMatrix[line * rowSize + pivotColumnIndex] = pivot;
		elementarInverseMatrixes.push_back(elementarInverseMatrix);

		for (int lowerLines = line + 1; lowerLines < rowSize; lowerLines++)
		{
			pivot = upperMatrix[lowerLines * rowSize + pivotColumnIndex];
			pivotOperator = -pivot;

			for (int column = 0; column < colSize; column++)
				upperMatrix[lowerLines * rowSize + column] += pivotOperator * upperMatrix[line * rowSize + column];

			elementarInverseMatrix = Mat4<T>::identity();
			elementarInverseMatrix[lowerLines * rowSize + pivotColumnIndex] = pivot;
			elementarInverseMatrixes.push_back(elementarInverseMatrix);
		}

		pivotColumnIndex++;
	}

	for (int i = 0; size_t(i) < elementarInverseMatrixes.size(); i++)
		lowerMatrix *= elementarInverseMatrixes[i];
#endif

	result[0] = lowerMatrix;
	result[1] = upperMatrix;

	return result;
}

template <typename T>
Mat4<T>* Mat4<T>::decomposeLDU() const
{
	Mat4<T> diagonalMatrix = Mat4<T>::identity();
	Mat4<T>* result = new Mat4<T>[3];

	Mat4<T>* lowerAndUpperMatrixes = decomposeLU();

	Mat4<T> upperMatrix = lowerAndUpperMatrixes[1];
	unsigned short diagonalIndex = 0;

#if MAJOR_COLUMN_ORDER
	for (int column = 0; column < MAT4_ROWSIZE; column++)
	{
		T pivot = upperMatrix[diagonalIndex * MAT4_ROWSIZE + column];

		diagonalMatrix[column * MAT4_ROWSIZE + diagonalIndex] = pivot;

		for (int row = column; row < MAT4_ROWSIZE; row++)
			upperMatrix[column * MAT4_ROWSIZE + row] /= pivot;

		diagonalIndex++;
	}
#else
	for (size_t row = 0; row < MAT4_ROWSIZE; row++)
	{
		T pivot = upperMatrix[row * MAT4_ROWSIZE + diagonalIndex];

		diagonalMatrix[row * MAT4_ROWSIZE + diagonalIndex] = pivot;

		for (size_t column = row; column < MAT4_ROWSIZE; column++)
			upperMatrix[row * MAT4_ROWSIZE + column] /= pivot;

		diagonalIndex++;
	}
#endif

	result[0] = lowerAndUpperMatrixes[0];
	result[1] = diagonalMatrix;
	result[2] = upperMatrix;

	delete[] lowerAndUpperMatrixes;

	return result;
}

template <typename T>
AutovalueAutovector4<T> Mat4<T>::getAutovalueAndAutovector(const unsigned short maxIteration) const
{
	Mat4<T> matrix = *this;
	Vec4<T> autovector = { T(1), T(1), T(1), T(1) };
	T autovalue;

	for (unsigned short iterationIndex = 0; iterationIndex < maxIteration; iterationIndex++)
	{
		Vec4<T> ax = matrix * autovector;
		autovalue = ax.maximum();
		autovector = ax / autovalue;
	}

	return AutovalueAutovector4<T>{ autovalue, autovector };
}

/*
template <typename T>
Mat3<T> Mat4<T>::toNormalMatrix()
{
	return toMat3().transpose().invert();
}
*/

namespace OpenML
{
	template class Mat4<int>;
	template class Mat4<float>;
	template class Mat4<double>;
}