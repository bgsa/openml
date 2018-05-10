#include "Mat3.h"

using namespace OpenML;

template <typename T>
Mat3<T>::Mat3()
{
	static T emptyMatrix[MAT3_SIZE] = {
		T(0), T(0), T(0),
		T(0), T(0), T(0),
		T(0), T(0), T(0)
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
Vec3<T> Mat3<T>::xAxis()
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
Vec3<T> Mat3<T>::yAxis()
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
Vec3<T> Mat3<T>::zAxis()
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
Vec3<T> Mat3<T>::primaryDiagonal()
{
	return Vec3<T> {
		values[0],
			values[4],
			values[8]
	};
}

template <typename T>
Vec3<T> Mat3<T>::secondaryDiagonal()
{
	return Vec3<T> {
		values[2],
			values[4],
			values[6]
	};
}

template <typename T>
Mat3<T> Mat3<T>::transpose()
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
Mat3<T> Mat3<T>::multiply(Mat3<T> matrixB)
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
Vec3<T> Mat3<T>::multiply(Vec3<T> vector)
{
	Vec3<T> result;

	result[0] = values[0 * MAT3_ROWSIZE + 0] * vector[0] + values[0 * MAT3_ROWSIZE + 1] * vector[1] + values[0 * MAT3_ROWSIZE + 2] * vector[2];
	result[1] = values[1 * MAT3_ROWSIZE + 0] * vector[0] + values[1 * MAT3_ROWSIZE + 1] * vector[1] + values[1 * MAT3_ROWSIZE + 2] * vector[2];
	result[2] = values[2 * MAT3_ROWSIZE + 0] * vector[0] + values[2 * MAT3_ROWSIZE + 1] * vector[1] + values[2 * MAT3_ROWSIZE + 2] * vector[2];

	return result;
}

template <typename T>
T Mat3<T>::determinantIJ(size_t i, size_t j)
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
T Mat3<T>::cofactorIJ(size_t i, size_t j)
{
	T determinantIJValue = determinantIJ(i, j);

	if (OpenML::isOdd(i + j))
		determinantIJValue *= -1;

	return determinantIJValue;
}

template <typename T>
void Mat3<T>::scale(T xScale, T yScale, T zScale)
{
	values[0] *= xScale;
	values[4] *= yScale;
	values[8] *= zScale;
}

template <typename T>
T Mat3<T>::determinant()
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
size_t Mat3<T>::sizeInBytes()
{
	return MAT3_SIZE * sizeof(T);
}

template <typename T>
Mat3<T> Mat3<T>::clone()
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
Mat3<T> Mat3<T>::operator*(Mat3<T> matrix)
{
	return multiply(matrix);
}

template <typename T>
Vec3<T> Mat3<T>::operator*(Vec3<T> matrix)
{
	return multiply(matrix);
}

template <typename T>
void Mat3<T>::operator*=(Mat3<T> matrix)
{
	memcpy(&this->values, multiply(matrix).values, sizeof(this->values));
}

template <typename T>
string Mat3<T>::toString()
{
	return Mat<T>::toString(values, MAT3_SIZE);
}

template <typename T>
Mat3<T>* Mat3<T>::decomposeLU()
{
	Mat3<T> lowerMatrix = Mat3<T>::identity();
	Mat3<T> upperMatrix = Mat3<T>(values);
	Mat3<T>* result = new Mat3<T>[2];

	vector<Mat3<T>> elementarInverseMatrixes;
	Mat3<T> elementarInverseMatrix;

	size_t rowSize = MAT3_ROWSIZE;
	size_t colSize = MAT3_ROWSIZE;

#if MAJOR_COLUMN_ORDER
	size_t pivotRowIndex = 0;

	for (size_t column = 0; column < colSize; column++)
	{
		T pivot = upperMatrix[pivotRowIndex * rowSize + column];
		T pivotOperator = 1 / pivot;

		for (size_t row = 0; row < rowSize; row++)
			upperMatrix[row * rowSize + column] *= pivotOperator;

		elementarInverseMatrix = Mat3<T>::identity();
		elementarInverseMatrix[pivotRowIndex * rowSize + column] = pivot;
		elementarInverseMatrixes.push_back(elementarInverseMatrix);

		for (size_t lowerColumns = column + 1; lowerColumns < rowSize; lowerColumns++)
		{
			pivot = upperMatrix[pivotRowIndex * rowSize + lowerColumns];
			pivotOperator = -pivot;

			for (size_t row = 0; row < rowSize; row++)
				upperMatrix[row * rowSize + lowerColumns] += pivotOperator * upperMatrix[row * rowSize + column];

			elementarInverseMatrix = Mat3<T>::identity();
			elementarInverseMatrix[pivotRowIndex * rowSize + lowerColumns] = pivot;
			elementarInverseMatrixes.push_back(elementarInverseMatrix);
		}

		pivotRowIndex++;
	}

	for (size_t i = 0; i < elementarInverseMatrixes.size(); i++)
		lowerMatrix *= elementarInverseMatrixes[i];
#else
	size_t pivotColumnIndex = 0;

	for (size_t line = 0; line < rowSize; line++)
	{
		float pivot = upperMatrix[line * rowSize + pivotColumnIndex];
		float pivotOperator = 1 / pivot;

		for (size_t column = 0; column < colSize; column++)
			upperMatrix[line * rowSize + column] *= pivotOperator;

		elementarInverseMatrix = Mat3<T>::identity();
		elementarInverseMatrix[line * rowSize + pivotColumnIndex] = pivot;
		elementarInverseMatrixes.push_back(elementarInverseMatrix);

		for (size_t lowerLines = line + 1; lowerLines < rowSize; lowerLines++)
		{
			pivot = upperMatrix[lowerLines * rowSize + pivotColumnIndex];
			pivotOperator = -pivot;

			for (size_t column = 0; column < colSize; column++)
				upperMatrix[lowerLines * rowSize + column] += pivotOperator * upperMatrix[line * rowSize + column];

			elementarInverseMatrix = Mat3<T>::identity();
			elementarInverseMatrix[lowerLines * rowSize + pivotColumnIndex] = pivot;
			elementarInverseMatrixes.push_back(elementarInverseMatrix);
		}

		pivotColumnIndex++;
	}

	for (size_t i = 0; i < elementarInverseMatrixes.size(); i++)
		lowerMatrix *= elementarInverseMatrixes[i];
#endif

	result[0] = lowerMatrix;
	result[1] = upperMatrix;

	return result;
}

template <typename T>
Mat3<T>* Mat3<T>::decomposeLDU()
{
	Mat3<T> diagonalMatrix = Mat3<T>::identity();
	Mat3<T>* result = new Mat3<T>[3];

	Mat3<T>* lowerAndUpperMatrixes = decomposeLU();

	Mat3<T> upperMatrix = lowerAndUpperMatrixes[1];
	unsigned short diagonalIndex = 0;

#if MAJOR_COLUMN_ORDER
	for (size_t column = 0; column < MAT3_ROWSIZE; column++)
	{
		T pivot = upperMatrix[diagonalIndex * MAT3_ROWSIZE + column];

		diagonalMatrix[column * MAT3_ROWSIZE + diagonalIndex] = pivot;

		for (size_t row = column; row < MAT3_ROWSIZE; row++)
			upperMatrix[column * MAT3_ROWSIZE + row] /= pivot;

		diagonalIndex++;
	}
#else
	for (size_t row = 0; row < MAT3_ROWSIZE; row++)
	{
		T pivot = upperMatrix[row * MAT3_ROWSIZE + diagonalIndex];

		diagonalMatrix[row * MAT3_ROWSIZE + diagonalIndex] = pivot;

		for (size_t column = row; column < MAT3_ROWSIZE; column++)
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
AutovalueAutovector3<T> Mat3<T>::getAutovalueAndAutovector(const unsigned short maxIteration)
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


template class Mat3<int>;
template class Mat3<float>;
template class Mat3<double>;