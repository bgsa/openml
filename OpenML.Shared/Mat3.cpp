#include "Mat3.h"

using namespace OpenML;

template <typename T>
Mat3<T>::Mat3(T defaultValue)
{
	static T emptyMatrix[MAT3_SIZE] = {
		defaultValue, defaultValue, defaultValue,
		defaultValue, defaultValue, defaultValue,
		defaultValue, defaultValue, defaultValue
	};

	memcpy(&values, emptyMatrix, sizeof(values));
}

template <typename T>
Mat3<T>::Mat3(T* values)
{
	memcpy(&this->values, values, sizeof(this->values));
}

template <typename T>
Mat3<T>::Mat3(T value11, T value21, T value31,
	T value12, T value22, T value32,
	T value13, T value23, T value33)
{
	values[0] = value11;
	values[1] = value21;
	values[2] = value31;
	values[3] = value12;
	values[4] = value22;
	values[5] = value32;
	values[6] = value13;
	values[7] = value23;
	values[8] = value33;
}

template <typename T>
T* Mat3<T>::getValues()
{
	return values;
}

template <typename T>
T Mat3<T>::getValue(int x, int y)
{
	x--;
	y--;

	return values[y * MAT3_ROWSIZE + x];
}

template <typename T>
Vec3<T> Mat3<T>::xAxis() const
{
	Vec3<T> result;

#if MAJOR_COLUMN_ORDER
	result = Vec3<T>{
		values[0],
		values[3],
		values[6]
	};
#else
	result = Vec3<T>{
		values[0],
		values[1],
		values[2]
	};
#endif

	return result;
}

template <typename T>
Vec3<T> Mat3<T>::yAxis() const
{
	Vec3<T> result;

#if MAJOR_COLUMN_ORDER
	result = Vec3<T>{
		values[1],
		values[4],
		values[7]
	};
#else
	result = Vec3<T>{
		values[3],
		values[4],
		values[5]
	};
#endif

	return result;
}

template <typename T>
Vec3<T> Mat3<T>::zAxis() const
{
	Vec3<T> result;

#if MAJOR_COLUMN_ORDER
	result = Vec3<T>{
		values[2],
		values[5],
		values[8]
	};
#else
	result = Vec3<T>{
		values[6],
		values[7],
		values[8]
	};
#endif

	return result;
}

template <typename T>
Mat3<T> Mat3<T>::identity()
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

template <typename T>
Vec3<T> Mat3<T>::primaryDiagonal() const
{
	return Vec3<T> {
		values[0],
		values[4],
		values[8]
	};
}

template <typename T>
Vec3<T> Mat3<T>::secondaryDiagonal() const
{
	return Vec3<T> {
		values[2],
			values[4],
			values[6]
	};
}

template <typename T>
Mat3<T> Mat3<T>::transpose() const
{
	Mat3<T> result;

	//copy principal diagonal
	result[0] = values[0];
	result[4] = values[4];
	result[8] = values[8];

	//swap others numbers
	T temp = values[1];
	result[1] = values[3];
	result[3] = temp;

	temp = values[2];
	result[2] = values[6];
	result[6] = temp;

	temp = values[5];
	result[5] = values[7];
	result[7] = temp;

	return result;
}

template <typename T>
Mat3<T> Mat3<T>::multiply(const Mat3<T>& matrixB) const
{
	Mat3<T> result;

#if MAJOR_COLUMN_ORDER
	for (int line = 0; line < MAT3_ROWSIZE; line++)
	{
		T ai0 = values[(0 * MAT3_ROWSIZE) + line];
		T ai1 = values[(1 * MAT3_ROWSIZE) + line];
		T ai2 = values[(2 * MAT3_ROWSIZE) + line];

		result[(0 * MAT3_ROWSIZE) + line] = ai0 * matrixB[(0 * MAT3_ROWSIZE) + 0] + ai1 * matrixB[(0 * MAT3_ROWSIZE) + 1] + ai2 * matrixB[(0 * MAT3_ROWSIZE) + 2];
		result[(1 * MAT3_ROWSIZE) + line] = ai0 * matrixB[(1 * MAT3_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT3_ROWSIZE) + 1] + ai2 * matrixB[(1 * MAT3_ROWSIZE) + 2];
		result[(2 * MAT3_ROWSIZE) + line] = ai0 * matrixB[(2 * MAT3_ROWSIZE) + 0] + ai1 * matrixB[(2 * MAT3_ROWSIZE) + 1] + ai2 * matrixB[(2 * MAT3_ROWSIZE) + 2];
	}
#else
	for (int column = 0; column < MAT3_ROWSIZE; column++)
	{
		T ai0 = values[(column * MAT3_ROWSIZE) + 0];
		T ai1 = values[(column * MAT3_ROWSIZE) + 1];
		T ai2 = values[(column * MAT3_ROWSIZE) + 2];

		result[(column * MAT3_ROWSIZE) + 0] = ai0 * matrixB[(0 * MAT3_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT3_ROWSIZE) + 0] + ai2 * matrixB[(2 * MAT3_ROWSIZE) + 0];
		result[(column * MAT3_ROWSIZE) + 1] = ai0 * matrixB[(0 * MAT3_ROWSIZE) + 1] + ai1 * matrixB[(1 * MAT3_ROWSIZE) + 1] + ai2 * matrixB[(2 * MAT3_ROWSIZE) + 1];
		result[(column * MAT3_ROWSIZE) + 2] = ai0 * matrixB[(0 * MAT3_ROWSIZE) + 2] + ai1 * matrixB[(1 * MAT3_ROWSIZE) + 2] + ai2 * matrixB[(2 * MAT3_ROWSIZE) + 2];
	}
#endif

	return result;
}

template <typename T>
Vec3<T> Mat3<T>::multiply(const Vec3<T>& vector) const
{
	Vec3<T> result;

	result[0] = values[0 * MAT3_ROWSIZE + 0] * vector[0] + values[0 * MAT3_ROWSIZE + 1] * vector[1] + values[0 * MAT3_ROWSIZE + 2] * vector[2];
	result[1] = values[1 * MAT3_ROWSIZE + 0] * vector[0] + values[1 * MAT3_ROWSIZE + 1] * vector[1] + values[1 * MAT3_ROWSIZE + 2] * vector[2];
	result[2] = values[2 * MAT3_ROWSIZE + 0] * vector[0] + values[2 * MAT3_ROWSIZE + 1] * vector[1] + values[2 * MAT3_ROWSIZE + 2] * vector[2];

	return result;
}

template <typename T>
T Mat3<T>::determinantIJ(size_t i, size_t j) const
{
	T* matrixValues = new T[4];
	size_t index = 0;

	for (size_t row = 0; row < MAT3_ROWSIZE; row++)
	{
		if (i == row)
			continue;

		for (size_t column = 0; column < MAT3_ROWSIZE; column++)
		{
			if (j == column)
				continue;

			matrixValues[index] = values[row * MAT3_ROWSIZE + column];
			index++;
		}
	}

	Mat2<T> matrix = Mat2<T>(matrixValues);
	T determinant = matrix.determinant();

	return determinant;
}

template <typename T>
T Mat3<T>::cofactorIJ(size_t i, size_t j) const
{
	T determinantIJValue = determinantIJ(i, j);

	if (OpenML::isOdd(i + j))
		determinantIJValue *= -1;

	return determinantIJValue;
}

template <typename T>
Mat3<T> Mat3<T>::createScale(T xScale, T yScale, T zScale)
{
	Mat3<T> result = Mat3<T>::identity();

	result.scale(xScale, yScale, zScale);

	return result;
}

template <typename T>
void Mat3<T>::scale(T xScale, T yScale, T zScale)
{
	values[0] *= xScale;
	values[4] *= yScale;
	values[8] *= zScale;
}

template <typename T>
Mat3<T> Mat3<T>::createRotate(T angleRadians, T x, T y, T z)
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

template <typename T>
Mat3<T> Mat3<T>::createTranslate(T x, T y, T z)
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

template <typename T>
T Mat3<T>::determinant() const
{
	return
		(values[0] * values[4] * values[8]
			+ values[1] * values[5] * values[6]
			+ values[2] * values[3] * values[7]
			)
		-
		(values[2] * values[4] * values[6]
			+ values[0] * values[5] * values[7]
			+ values[1] * values[3] * values[8]
			);
}

template <typename T>
Mat3<T> Mat3<T>::invert()
{
	Mat3<T> matrixInverse;
	T detij;

	T det = determinant();

	for (int i = 0; i < MAT3_ROWSIZE; i++)
		for (int j = 0; j < MAT3_ROWSIZE; j++)
		{
			detij = determinantIJ(j, i);

			if ((i + j) & 0x1)
				matrixInverse[i * MAT3_ROWSIZE + j] = -detij * det;
			else
				matrixInverse[i * MAT3_ROWSIZE + j] = detij * det;
		}

	return matrixInverse;
}

template <typename T>
size_t Mat3<T>::sizeInBytes() const
{
	return MAT3_SIZE * sizeof(T);
}

template <typename T>
Mat3<T> Mat3<T>::clone() const
{
	Mat3<T> result;

	memcpy(&result, this, sizeof(Mat3<T>));

	return result;
}

template <typename T>
T& Mat3<T>::operator[](int index)
{
	assert(index >= 0 && index < MAT3_SIZE);

	return values[index];
}

template <typename T>
T Mat3<T>::operator[](int index) const
{
	assert(index >= 0 && index < MAT3_SIZE);

	return values[index];
}

template <typename T>
Mat3<T>::operator void*() const
{
	return (void*)values;
}

template <typename T>
Mat3<T>::operator T*()
{
	return values;
}

template <typename T>
Mat3<T> Mat3<T>::operator*(const Mat3<T>& matrix) const
{
	return multiply(matrix);
}

template <typename T>
Vec3<T> Mat3<T>::operator*(const Vec3<T>& matrix) const
{
	return multiply(matrix);
}

template <typename T>
void Mat3<T>::operator*=(const Mat3<T>& matrix)
{
	memcpy(&this->values, multiply(matrix).values, sizeof(this->values));
}

template <typename T>
string Mat3<T>::toString()
{
	return Mat<T>::toString(values, MAT3_SIZE);
}

template <typename T>
Mat3<T>* Mat3<T>::decomposeLU() const
{
	Mat3<T> lowerMatrix = Mat3<T>::identity();
	Mat3<T> upperMatrix = this->clone();
	Mat3<T>* result = new Mat3<T>[2];

	vector<Mat3<T>> elementarInverseMatrixes;
	Mat3<T> elementarInverseMatrix;

	int rowSize = MAT3_ROWSIZE;
	int colSize = MAT3_ROWSIZE;

#if MAJOR_COLUMN_ORDER
	int pivotRowIndex = 0;

	for (int column = 0; column < colSize; column++)
	{
		T pivot = upperMatrix[pivotRowIndex * rowSize + column];
		T pivotOperator = 1 / pivot;

		for (int row = 0; row < rowSize; row++)
			upperMatrix[row * rowSize + column] *= pivotOperator;

		elementarInverseMatrix = Mat3<T>::identity();
		elementarInverseMatrix[pivotRowIndex * rowSize + column] = pivot;
		elementarInverseMatrixes.push_back(elementarInverseMatrix);

		for (int lowerColumns = column + 1; lowerColumns < rowSize; lowerColumns++)
		{
			pivot = upperMatrix[pivotRowIndex * rowSize + lowerColumns];
			pivotOperator = -pivot;

			for (int row = 0; row < rowSize; row++)
				upperMatrix[row * rowSize + lowerColumns] += pivotOperator * upperMatrix[row * rowSize + column];

			elementarInverseMatrix = Mat3<T>::identity();
			elementarInverseMatrix[pivotRowIndex * rowSize + lowerColumns] = pivot;
			elementarInverseMatrixes.push_back(elementarInverseMatrix);
		}

		pivotRowIndex++;
	}

	for (int i = 0; size_t(i) < elementarInverseMatrixes.size(); i++)
		lowerMatrix *= elementarInverseMatrixes[i];
#else
	size_t pivotColumnIndex = 0;

	for (size_t line = 0; line < rowSize; line++)
	{
		T pivot = upperMatrix[line * rowSize + pivotColumnIndex];
		T pivotOperator = 1 / pivot;

		for (int column = 0; column < colSize; column++)
			upperMatrix[line * rowSize + column] *= pivotOperator;

		elementarInverseMatrix = Mat3<T>::identity();
		elementarInverseMatrix[line * rowSize + pivotColumnIndex] = pivot;
		elementarInverseMatrixes.push_back(elementarInverseMatrix);

		for (int lowerLines = line + 1; lowerLines < rowSize; lowerLines++)
		{
			pivot = upperMatrix[lowerLines * rowSize + pivotColumnIndex];
			pivotOperator = -pivot;

			for (int column = 0; column < colSize; column++)
				upperMatrix[lowerLines * rowSize + column] += pivotOperator * upperMatrix[line * rowSize + column];

			elementarInverseMatrix = Mat3<T>::identity();
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
Mat3<T>* Mat3<T>::decomposeLDU() const
{
	Mat3<T> diagonalMatrix = Mat3<T>::identity();
	Mat3<T>* result = new Mat3<T>[3];

	Mat3<T>* lowerAndUpperMatrixes = decomposeLU();

	Mat3<T> upperMatrix = lowerAndUpperMatrixes[1];
	int diagonalIndex = 0;

#if MAJOR_COLUMN_ORDER
	for (int column = 0; column < MAT3_ROWSIZE; column++)
	{
		T pivot = upperMatrix[diagonalIndex * MAT3_ROWSIZE + column];

		diagonalMatrix[column * MAT3_ROWSIZE + diagonalIndex] = pivot;

		for (int row = column; row < MAT3_ROWSIZE; row++)
			upperMatrix[column * MAT3_ROWSIZE + row] /= pivot;

		diagonalIndex++;
	}
#else
	for (int row = 0; row < MAT3_ROWSIZE; row++)
	{
		T pivot = upperMatrix[row * MAT3_ROWSIZE + diagonalIndex];

		diagonalMatrix[row * MAT3_ROWSIZE + diagonalIndex] = pivot;

		for (int column = row; column < MAT3_ROWSIZE; column++)
			upperMatrix[row * MAT3_ROWSIZE + column] /= pivot;

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
AutovalueAutovector3<T> Mat3<T>::getAutovalueAndAutovector(const unsigned short maxIteration) const
{
	Mat3<T> matrix = *this;
	Vec3<T> autovector = { T(1), T(1), T(1) };
	T autovalue;

	for (unsigned short iterationIndex = 0; iterationIndex < maxIteration; iterationIndex++)
	{
		Vec3<T> ax = matrix * autovector;
		autovalue = ax.maximum();
		autovector = ax / autovalue;
	}

	return AutovalueAutovector3<T>{ autovalue, autovector };
}

namespace OpenML
{
	template class Mat3<int>;
	template class Mat3<float>;
	template class Mat3<double>;
}