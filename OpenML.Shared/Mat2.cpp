#include "Mat2.h"

using namespace OpenML;

template <typename T>
Mat2<T>::Mat2(T defaultValue)
{
	static T emptyMatrix[MAT2_SIZE] = {
		defaultValue, defaultValue,
		defaultValue, defaultValue
	};

	memcpy(&values, emptyMatrix, sizeof(values));
}

template <typename T>
Mat2<T>::Mat2(T* values)
{
	memcpy(&this->values, values, sizeof(this->values));
}

template <typename T>
Mat2<T>::Mat2(T value11, T value12,	T value21, T value22)
{
	values[0] = value11;
	values[1] = value12;
	values[2] = value21;
	values[3] = value22;
}

template <typename T>
Mat2<T> Mat2<T>::identity()
{
	static T identityMatrix[MAT2_SIZE] = {
		T(1), T(0),
		T(0), T(1)
	};

	Mat2 result;
	memcpy(&result, identityMatrix, sizeof(values));

	return result;
}

template <typename T>
T* Mat2<T>::getValues()
{
	return values;
}

template <typename T>
T Mat2<T>::getValue(int x, int y)
{
	x--;
	y--;

	return values[y * MAT2_ROWSIZE + x];
}

template <typename T>
Vec2<T> Mat2<T>::xAxis() const
{
	Vec2<T> result;

#ifdef MAJOR_COLUMN_ORDER
	result = Vec2<T>{
		values[0],
		values[2]
	};
#else
	result = Vec2<T>{
		values[0],
		values[1]
	};
#endif

	return result;
}

template <typename T>
Vec2<T> Mat2<T>::yAxis() const
{
	Vec2<T> result;

#ifdef MAJOR_COLUMN_ORDER
	result = Vec2<T>{
		values[1],
		values[3]
	};
#else
	result = Vec2<T>{
		values[2],
		values[3]
	};
#endif

	return result;
}

template <typename T>
Vec2<T> Mat2<T>::primaryDiagonal() const
{
	return Vec2<T> {
		values[0],
			values[3]
	};
}

template <typename T>
Vec2<T> Mat2<T>::secondaryDiagonal() const
{
	return Vec2<T> {
		values[1],
			values[2]
	};
}

template <typename T>
Mat2<T> Mat2<T>::transpose() const
{
	Mat2<T> result;

	//copy principal diagonal
	result[0] = values[0];
	result[3] = values[3];

	//swap others numbers
	T temp = values[1];
	result[1] = values[2];
	result[2] = temp;

	return result;
}

template <typename T>
Mat2<T> Mat2<T>::multiply(const Mat2<T>& matrixB) const
{
	Mat2<T> result;

#ifdef MAJOR_COLUMN_ORDER
	for (int line = 0; line < MAT2_ROWSIZE; line++)
	{
		T ai0 = values[(0 * MAT2_ROWSIZE) + line];
		T ai1 = values[(1 * MAT2_ROWSIZE) + line];

		result[(0 * MAT2_ROWSIZE) + line] = ai0 * matrixB[(0 * MAT2_ROWSIZE) + 0] + ai1 * matrixB[(0 * MAT2_ROWSIZE) + 1];
		result[(1 * MAT2_ROWSIZE) + line] = ai0 * matrixB[(1 * MAT2_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT2_ROWSIZE) + 1];
	}
#else
	for (int column = 0; column < MAT2_ROWSIZE; column++)
	{
		T ai0 = values[(column * MAT2_ROWSIZE) + 0];
		T ai1 = values[(column * MAT2_ROWSIZE) + 1];

		result[(column * MAT2_ROWSIZE) + 0] = ai0 * matrixB[(0 * MAT2_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT2_ROWSIZE) + 0];
		result[(column * MAT2_ROWSIZE) + 1] = ai0 * matrixB[(0 * MAT2_ROWSIZE) + 1] + ai1 * matrixB[(1 * MAT2_ROWSIZE) + 1];
	}
#endif

	return result;
}

template <typename T>
Vec2<T> Mat2<T>::multiply(const Vec2<T>& vector) const
{
	Vec2<T> result;

	result[0] = values[0 * MAT2_ROWSIZE + 0] * vector[0] + values[0 * MAT2_ROWSIZE + 1] * vector[1];
	result[1] = values[1 * MAT2_ROWSIZE + 0] * vector[0] + values[1 * MAT2_ROWSIZE + 1] * vector[1];

	return result;
}

template <typename T>
Mat2<T> Mat2<T>::createScale(T xScale, T yScale)
{
	Mat2<T> result = Mat2<T>::identity();

	result.scale(xScale, yScale);

	return result;
}

template <typename T>
void Mat2<T>::scale(T xScale, T yScale)
{
	values[0] *= xScale;
	values[3] *= yScale;
}

template <typename T>
Mat2<T> Mat2<T>::createTranslate(T x, T y)
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

template <typename T>
T Mat2<T>::determinant() const
{
	return values[0] * values[3] - values[1] * values[2];
}

template <typename T>
AutovalueAutovector2<T> Mat2<T>::getAutovalueAndAutovector(const unsigned short maxIteration) const
{
	Mat2<T> matrix = *this;
	Vec2<T> autovector = { T(1), T(1) };
	T autovalue;

	for (unsigned short iterationIndex = 0; iterationIndex < maxIteration; iterationIndex++)
	{
		Vec2<T> ax = matrix * autovector;
		autovalue = ax.maximum();
		autovector = ax / autovalue;
	}

	return AutovalueAutovector2<T>{ autovalue, autovector };
}

template <typename T>
size_t Mat2<T>::sizeInBytes() const
{
	return MAT2_SIZE * sizeof(T);
}

template <typename T>
Mat2<T> Mat2<T>::clone() const
{
	Mat2<T> result;

	memcpy(&result, this, sizeof(Mat2<T>));

	return result;
}

template <typename T>
T& Mat2<T>::operator[](int index)
{
	assert(index >= 0 && index < MAT2_SIZE);

	return values[index];
}

template <typename T>
T Mat2<T>::operator[](int index) const
{
	assert(index >= 0 && index < MAT2_SIZE);

	return values[index];
}

template <typename T>
Mat2<T>::operator void*() const
{
	return (void*) values;
}

template <typename T>
Mat2<T>::operator T*()
{
	return values;
}

template <typename T>
Mat2<T> Mat2<T>::operator*(const Mat2<T>& matrix) const
{
	return multiply(matrix);
}

template <typename T>
Vec2<T> Mat2<T>::operator*(const Vec2<T>& vector) const
{
	return multiply(vector);
}

template <typename T>
void Mat2<T>::operator*=(const Mat2<T>& matrix)
{
	memcpy(&this->values, multiply(matrix).values, sizeof(this->values));
}

template <typename T>
string Mat2<T>::toString()
{
	return Mat<T>::toString(values, MAT2_SIZE);
}


namespace OpenML
{
	template class Mat2<int>;
	template class Mat2<float>;
	template class Mat2<double>;
}