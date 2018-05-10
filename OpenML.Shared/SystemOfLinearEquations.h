#pragma once

#include "OpenML.h"
#include <iomanip>

using namespace OpenML;

template <typename T>
class SystemOfLinearEquations
{
private:

	string printMatrix(T* matrix, size_t rowSize, size_t colSize, int precision = 4)
	{
		size_t total = rowSize * colSize;
		string content;

		for (size_t i = 0; i < total; i++)
		{
			stringstream stream;
			stream << fixed << setprecision(precision) << matrix[i];
			string numberAsString = stream.str();

			bool isPositive = matrix[i] >= 0;

			if (isPositive)
				numberAsString = " " + numberAsString;

			content += " " + numberAsString + " ";

			if ((i + 1) % colSize == 0)
				content += '\n';
		}

		return content;
	}

public:

	/// <summary>
	/// Solve a system of linear equations nxn
	/// </summary>
	API_INTERFACE T* solve(T* matrix, size_t rowSize, size_t colSize) 
	{
		T* upperMatrix = new T[rowSize * colSize];
		memcpy(upperMatrix, matrix, sizeof(upperMatrix) * rowSize * colSize);

		T* result = new T[colSize - 1];
		
		size_t pivotColumnIndex = 0;

		for (size_t line = 0; line < rowSize; line++)
		{
			float pivot = upperMatrix[line * colSize + pivotColumnIndex];

			if (pivot == T(0)) 
			{
				for (size_t i = line + 1; i < rowSize; i++)
				{
					pivot = upperMatrix[i * colSize + pivotColumnIndex];

					if (pivot != T(0)) 
					{
						//troca linha
						for (size_t column = 0; column < colSize; column++)
						{
							T temp = upperMatrix[line * colSize + column];
							upperMatrix[line * colSize + column] = upperMatrix[i * colSize + column];
							upperMatrix[i * colSize + column] = temp;
						}

						break;
					}
				}
			}			

			float pivotOperator = 1 / pivot;

			for (size_t column = 0; column < colSize; column++)
				upperMatrix[line * colSize + column] *= pivotOperator;
			
			for (size_t lowerLines = line + 1; lowerLines < rowSize; lowerLines++)
			{
				pivot = upperMatrix[lowerLines * colSize + pivotColumnIndex];
				pivotOperator = -pivot;

				for (size_t column = 0; column < colSize; column++)
					upperMatrix[lowerLines * colSize + column] += pivotOperator * upperMatrix[line * colSize + column];
			}

			pivotColumnIndex++;
		}

		//string content = printMatrix(upperMatrix, rowSize, colSize);

		for (long row = rowSize - 1; row >= 0; row--)
		{			
			result[row] = upperMatrix[row * colSize + colSize - 1];

			for (size_t column = colSize - 1; column > size_t(row) + 1; column--)
			{
				result[row] -= upperMatrix[row * colSize + column - 1] * result[column - 1];
			}
		}
		
		return result;
	}

	/// <summary>
	/// Get the line equation in 2 points for 2D space
	/// The result is a vector with 3 components (a, b, c)
	/// Line equation: "ax + bx + c = 0"
	/// </summary>
	API_INTERFACE static Vec3<T> getLineEquation(Vec2<T> point1, Vec2<T> point2)
	{
		Vec3<T> result;
		
		Mat3<T> matrix = {
			T(1), T(1), T(1),
			point1.x(), point1.y(), T(1),
			point2.x(), point2.y(), T(1)
		};

		T a = matrix.cofactorIJ(0, 0);
		T b = matrix.cofactorIJ(0, 1);
		T c = matrix.cofactorIJ(0, 2);

		return Vec3<T>(a, b, c);
	}

	/// <summary>
	/// Get the line equation in 3 points for 2D space
	/// The result is a vector with 1 components (a, b, c, d)
	/// Line equation: "a(x^2 + y) + bx + cy + d = 0"
	/// </summary>
	API_INTERFACE static Vec4<T> getCircleEquation(Vec2<T> point1, Vec2<T> point2, Vec2<T> point3)
	{
		Vec4<T> result;

		T m21 = pow(point1.x(), 2) + pow(point1.y(), 2);
		T m31 = pow(point2.x(), 2) + pow(point2.y(), 2);
		T m41 = pow(point3.x(), 2) + pow(point3.y(), 2);

		Mat4<T> matrix = {
			T(1), T(1), T(1), T(1),
			m21, point1.x(), point1.y(), T(1),
			m31, point2.x(), point2.y(), T(1),
			m41, point3.x(), point3.y(), T(1)
		};

		T a = matrix.cofactorIJ(0, 0);
		T b = matrix.cofactorIJ(0, 1);
		T c = matrix.cofactorIJ(0, 2);
		T d = matrix.cofactorIJ(0, 3);

		return Vec4<T>(a, b, c, d);
	}
};
