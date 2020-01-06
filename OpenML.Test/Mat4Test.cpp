#pragma once

#include "CppUnitTest.h"
#include <Mat4.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(Mat4Test)
	{
	public:

		TEST_METHOD(Mat4_constructorEmpty_Test)
		{
			Mat4f result;

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(0.0f, result[i], L"Value shoud be 0", LINE_INFO());
		}

		TEST_METHOD(Mat4_constructorValues_Test)
		{
			float emptyMatrix[MAT4_SIZE] = {
				 1.0f,  2.0f,  3.0f,  4.0f, 
				 5.0f,  6.0f,  7.0f,  8.0f, 
				 9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Mat4f result = Mat4f(emptyMatrix);

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(emptyMatrix[i], result[i], L"Value shoud be 0", LINE_INFO());
		}

		TEST_METHOD(Mat4_constructor_4vec4_Test)
		{
			Vec4f vector1 = Vec4f(1.0f, 2.0f, 3.0f, 4.0f);
			Vec4f vector2 = Vec4f(5.0f, 6.0f, 7.0f, 8.0f);
			Vec4f vector3 = Vec4f(9.0f, 10.0f, 11.0f, 12.0f);
			Vec4f vector4 = Vec4f(13.0f, 14.0f, 15.0f, 16.0f);

			Mat4f matrix = Mat4f(vector1, vector2, vector3, vector4);

#if MAJOR_COLUMN_ORDER
			Mat4f expected = Mat4f(
				1.0f, 5.0f, 9.0f, 13.0f,
				2.0f, 6.0f, 10.0f, 14.0f,
				3.0f, 7.0f, 11.0f, 15.0f,
				4.0f, 8.0f, 12.0f, 16.0f
			);

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], matrix[i], L"Value shoud be 0", LINE_INFO());
#else
			for (int i = 0; i < 4; i++)
				Assert::AreEqual(vector1[i], matrix[i], L"Value shoud be 0", LINE_INFO());

			for (int i = 4; i < 8; i++)
				Assert::AreEqual(vector2[i], matrix[i], L"Value shoud be 0", LINE_INFO());

			for (int i = 8; i < 12; i++)
				Assert::AreEqual(vector3[i], matrix[i], L"Value shoud be 0", LINE_INFO());

			for (int i = 12; i < 16; i++)
				Assert::AreEqual(vector4[i], matrix[i], L"Value shoud be 0", LINE_INFO());
#endif
		}

		TEST_METHOD(Mat4_getValues_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			float* result = matrix.getValues();

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(matrix[i], result[i], L"Value shoud be 0", LINE_INFO());
		}

		TEST_METHOD(Mat4_getValue_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Assert::AreEqual(1.0f, matrix.getValue(1, 1), L"Wrong value", LINE_INFO());
			Assert::AreEqual(5.0f, matrix.getValue(1, 2), L"Wrong value", LINE_INFO());
			Assert::AreEqual(9.0f, matrix.getValue(1, 3), L"Wrong value", LINE_INFO());
			Assert::AreEqual(13.0f, matrix.getValue(1, 4), L"Wrong value", LINE_INFO());

			Assert::AreEqual(2.0f, matrix.getValue(2, 1), L"Wrong value", LINE_INFO());
			Assert::AreEqual(6.0f, matrix.getValue(2, 2), L"Wrong value", LINE_INFO());
			Assert::AreEqual(10.0f, matrix.getValue(2, 3), L"Wrong value", LINE_INFO());
			Assert::AreEqual(14.0f, matrix.getValue(2, 4), L"Wrong value", LINE_INFO());

			Assert::AreEqual(3.0f, matrix.getValue(3, 1), L"Wrong value", LINE_INFO());
			Assert::AreEqual(7.0f, matrix.getValue(3, 2), L"Wrong value", LINE_INFO());
			Assert::AreEqual(11.0f, matrix.getValue(3, 3), L"Wrong value", LINE_INFO());
			Assert::AreEqual(15.0f, matrix.getValue(3, 4), L"Wrong value", LINE_INFO());

			Assert::AreEqual(4.0f, matrix.getValue(4, 1), L"Wrong value", LINE_INFO());
			Assert::AreEqual(8.0f, matrix.getValue(4, 2), L"Wrong value", LINE_INFO());
			Assert::AreEqual(12.0f, matrix.getValue(4, 3), L"Wrong value", LINE_INFO());
			Assert::AreEqual(16.0f, matrix.getValue(4, 4), L"Wrong value", LINE_INFO());
		}

#if MAJOR_COLUMN_ORDER
		TEST_METHOD(Mat4_xAxis_MajorColumnOrder_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Vec4f xAxis = matrix.xAxis();

			Assert::AreEqual(1.0f, xAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(5.0f, xAxis[1], L"Wrong value", LINE_INFO());
			Assert::AreEqual(9.0f, xAxis[2], L"Wrong value", LINE_INFO());
			Assert::AreEqual(13.0f, xAxis[3], L"Wrong value", LINE_INFO());
		}
#endif

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat4_xAxis_MajorRowOrder_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Vec4f xAxis = matrix.xAxis();

			Assert::AreEqual(1.0f, xAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(2.0f, xAxis[1], L"Wrong value", LINE_INFO());
			Assert::AreEqual(3.0f, xAxis[2], L"Wrong value", LINE_INFO());
			Assert::AreEqual(4.0f, xAxis[3], L"Wrong value", LINE_INFO());
		}
#endif

#if MAJOR_COLUMN_ORDER
		TEST_METHOD(Mat4_yAxis_MajorColumnOrder_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Vec4f yAxis = matrix.yAxis();

			Assert::AreEqual(2.0f, yAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(6.0f, yAxis[1], L"Wrong value", LINE_INFO());
			Assert::AreEqual(10.0f, yAxis[2], L"Wrong value", LINE_INFO());
			Assert::AreEqual(14.0f, yAxis[3], L"Wrong value", LINE_INFO());
		}
#endif

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat4_yAxis_MajorRowOrder_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Vec4f yAxis = matrix.yAxis();

			Assert::AreEqual(5.0f, yAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(6.0f, yAxis[1], L"Wrong value", LINE_INFO());
			Assert::AreEqual(7.0f, yAxis[2], L"Wrong value", LINE_INFO());
			Assert::AreEqual(8.0f, yAxis[3], L"Wrong value", LINE_INFO());
		}
#endif

#if MAJOR_COLUMN_ORDER
		TEST_METHOD(Mat4_zAxis_MajorColumnOrder_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Vec4f zAxis = matrix.zAxis();

			Assert::AreEqual(3.0f, zAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(7.0f, zAxis[1], L"Wrong value", LINE_INFO());
			Assert::AreEqual(11.0f, zAxis[2], L"Wrong value", LINE_INFO());
			Assert::AreEqual(15.0f, zAxis[3], L"Wrong value", LINE_INFO());
		}
#endif

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat4_zAxis_MajorRowOrder_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Vec4f zAxis = matrix.zAxis();

			Assert::AreEqual(9.0f, zAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(10.0f, zAxis[1], L"Wrong value", LINE_INFO());
			Assert::AreEqual(11.0f, zAxis[2], L"Wrong value", LINE_INFO());
			Assert::AreEqual(12.0f, zAxis[3], L"Wrong value", LINE_INFO());
		}
#endif

#if MAJOR_COLUMN_ORDER
		TEST_METHOD(Mat4_wAxis_MajorColumnOrder_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Vec4f wAxis = matrix.wAxis();

			Assert::AreEqual(4.0f, wAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(8.0f, wAxis[1], L"Wrong value", LINE_INFO());
			Assert::AreEqual(12.0f, wAxis[2], L"Wrong value", LINE_INFO());
			Assert::AreEqual(16.0f, wAxis[3], L"Wrong value", LINE_INFO());
		}
#endif

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat4_wAxis_MajorRowOrder_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Vec4f wAxis = matrix.wAxis();

			Assert::AreEqual(13.0f, wAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(14.0f, wAxis[1], L"Wrong value", LINE_INFO());
			Assert::AreEqual(15.0f, wAxis[2], L"Wrong value", LINE_INFO());
			Assert::AreEqual(16.0f, wAxis[3], L"Wrong value", LINE_INFO());
		}
#endif

		TEST_METHOD(Mat4_primaryDiagonal_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Vec4f primaryDiagonal = matrix.primaryDiagonal();

			Assert::AreEqual(1.0f, primaryDiagonal[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(6.0f, primaryDiagonal[1], L"Wrong value", LINE_INFO());
			Assert::AreEqual(11.0f, primaryDiagonal[2], L"Wrong value", LINE_INFO());
			Assert::AreEqual(16.0f, primaryDiagonal[3], L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Mat4_secondaryDiagonal_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};

			Vec4f secondaryDiagonal = matrix.secondaryDiagonal();

			Assert::AreEqual(4.0f, secondaryDiagonal[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(7.0f, secondaryDiagonal[1], L"Wrong value", LINE_INFO());
			Assert::AreEqual(10.0f, secondaryDiagonal[2], L"Wrong value", LINE_INFO());
			Assert::AreEqual(13.0f, secondaryDiagonal[3], L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Mat4_identity_Test)
		{
			Mat4f result = Mat4f::identity();

			for (int i = 0; i < MAT4_SIZE; i++)
				if (i % (MAT4_ROWSIZE+1) == 0)
					Assert::AreEqual(1.0f, result[i], L"Value shoud be 0", LINE_INFO());
				else
					Assert::AreEqual(0.0f, result[i], L"Value shoud be 0", LINE_INFO());
		}

		TEST_METHOD(Mat4_determinant_Test)
		{
			Mat4f matrix = {
				2.0f,  1.0f,  6.0f,  0.0f,
				5.0f,  0.0f,  1.0f,  3.0f,
			   -2.0f,  5.0f,  1.0f,  8.0f,
			   11.0f,  4.0f, -2.0f, -7.0f
			};
			float result = matrix.determinant();
			float expected = -3192.0f;

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Mat4_determinantIJ_Test)
		{
			Mat4f matrix = {
				2.0f,  1.0f,  6.0f,  0.0f,
				5.0f,  0.0f,  1.0f,  3.0f,
				-2.0f,  5.0f,  1.0f,  8.0f,
				11.0f,  4.0f, -2.0f, -7.0f
			};
			float result1 = matrix.determinantIJ(1,0);
			float expected1 = 411.0f;
			Assert::AreEqual(expected1, result1, L"Wrong value", LINE_INFO());

			float result2 = matrix.determinantIJ(1, 1);
			float expected2 = 462.0f;
			Assert::AreEqual(expected2, result2, L"Wrong value", LINE_INFO());

			Mat3f matrix3x3 = {
				0.0f,  1.0f,  3.0f,
				5.0f,  1.0f,  8.0f,
				4.0f, -2.0f, -7.0f
			};
			float determinant3x3 = matrix3x3.determinant();

			float result3 = matrix.determinantIJ(0, 0);
			Assert::AreEqual(determinant3x3, result3, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Mat4_cofactorIJ_Test)
		{
			Mat4f matrix = {
				2.0f,  1.0f,  6.0f,  0.0f,
				5.0f,  0.0f,  1.0f,  3.0f,
				-2.0f,  5.0f,  1.0f,  8.0f,
				11.0f,  4.0f, -2.0f, -7.0f
			};
			float result1 = matrix.cofactorIJ(1, 0);
			float expected1 = -411.0f;
			Assert::AreEqual(expected1, result1, L"Wrong value", LINE_INFO());

			float result2 = matrix.cofactorIJ(1, 1);
			float expected2 = 462.0f;
			Assert::AreEqual(expected2, result2, L"Wrong value", LINE_INFO());

			float result3 = matrix.cofactorIJ(1, 2);
			float expected3 = 60.0f;
			Assert::AreEqual(expected3, result3, L"Wrong value", LINE_INFO());

			float result4 = matrix.cofactorIJ(1, 3);
			float expected4 = -399.0f;
			Assert::AreEqual(expected4, result4, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Mat4_transpose_Test)
		{
			Mat4f matrix = {
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			};
			Mat4f result = matrix.transpose();

			float expected[MAT4_SIZE] = {
				1.0f,  5.0f,  9.0f,  13.0f,
				2.0f,  6.0f,  10.0f,  14.0f,
				3.0f, 7.0f, 11.0f, 15.0f,
				4.0f, 8.0f, 12.0f, 16.0f
			};

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value", LINE_INFO());
		}

#if MAJOR_COLUMN_ORDER
		TEST_METHOD(Mat4_multiply_MajorColumnOrder1_Test)
		{
			Mat4f matrixA = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};
			Mat4f matrixB = {
				2.0f, 5.0f, -2.0f, 4.0f,
				1.0f, -3.0f, 8.0f, 8.0f,
				0.0f, 7.0f, -4.0f, 7.0f,
				4.0f, 4.0f, 5.0f, 2.0f
			};
			Mat4f expected = {
				-4.0f, 72.0f, 22.0f, 2.0f,
				42.0f, -29.0f, -2.0f, 39.0f,
				-19.0f, 104.0f, 24.0f, -26.0f,
				25.0f, 27.0f, 29.0f, 43.0f
			};

			Mat4f result = matrixA * matrixB;

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_multiply_MajorColumnOrder2_Test)
		{
			Mat4f matrixA = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};
			Mat4f matrixB = {
				2.0f, 5.0f, -2.0f, 4.0f,
				1.0f, -3.0f, 8.0f, 8.0f,
				0.0f, 7.0f, -4.0f, 7.0f,
				4.0f, 4.0f, 5.0f, 2.0f
			};
			Mat4f expected = {
				-4.0f, 72.0f, 22.0f, 2.0f,
				42.0f, -29.0f, -2.0f, 39.0f,
				-19.0f, 104.0f, 24.0f, -26.0f,
				25.0f, 27.0f, 29.0f, 43.0f
			};

			Mat4f result = matrixA.multiply(matrixB);

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}
#endif

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat4_multiply_MajorRowOrder1_Test)
		{
			Mat4f matrixA = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};
			Mat4f matrixB = {
				2.0f, 5.0f, -2.0f, 4.0f,
				1.0f, -3.0f, 8.0f, 8.0f,
				0.0f, 7.0f, -4.0f, 7.0f,
				4.0f, 4.0f, 5.0f, 2.0f
			};
			Mat4f expected = {
				47.0f, 61.0f, 53.0f, 72.0f,
				-4.0f, -14.0f, 42.0f, 80.0f,
				13.0f, 49.0f, -35.0f, -15.0f,
				6.0f, -7.0f, 30.0f, 36.0f
			};

			Mat4f result = matrixA.multiply(matrixB);

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_multiply_MajorRowOrder2_Test)
		{
			Mat4f matrixA = {
				1.0f, 0.0f,  0.0f,  0.0f,
				3.0f, -3.0f,  0.0f,  0.0f,
				-1.0f, 0.0f,  2.0f,  0.0f,
				-3.0f, 4.0f, -2.0f,  1.0f
			};

			Mat4f matrixB = {
				1.0f, -2.0f, -2.0f, -3.0f,
				0.0f, 1.0f,  6.0f,  0.0f,
				0.0f,  0.0f,  1.0f,  4.0f,
				0.0f,  0.0f,  0.0f,  1.0f
			};

			Mat4f expected = {
				1.0f, -2.0f, -2.0f, -3.0f,
				3.0f, -9.0f, -24.0f, -9.0f,
				-1.0f, 2.0f, 4.0f, 11.0f,
				-3.0f, 10.0f, 28.0f, 2.0f
			};

			Mat4f result = matrixA * matrixB;

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}
#endif

		TEST_METHOD(Mat4_createScaled_Test)
		{
			Mat4f expected = {
				2.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 4.0f, 0.0f, 0.0f,
				0.0f, 0.0f, -3.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			Mat4f result = Mat4f::createScale(2.0f, 4.0f, -3.0f);

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_scale_Test)
		{
			Mat4f matrixA = {
				2.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 4.0f, 0.0f, 0.0f,
				0.0f, 0.0f, -3.0f, 0.0f,
				1.0f, -10.0f, 5.0f, 1.0f
			};
			Mat4f expected = {
				4.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 16.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 9.0f, 0.0f,
				1.0f, -10.0f, 5.0f, 1.0f
			};

			matrixA.scale(2.0f, 4.0f, -3.0f);

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], matrixA[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_createRotate_Test)
		{
			Mat4f expected = {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.866025388f, 0.5f, 0.0f,
				0.0f, -0.5f, 0.866025388f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			float angle = (float)degreesToRadians(30);
			
			Mat4f result = Mat4f::createRotate(angle, 1.0f, 0.0f, 0.0f);

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}

#if MAJOR_COLUMN_ORDER
		TEST_METHOD(Mat4_createTranslate_MajorColumnOrder_Test)
		{
			Mat4f expected = {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 2.0f, -3.0f, 1.0f
			};

			Mat4f result = Mat4f::createTranslate(0.0f, 2.0f, -3.0f);

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}
#endif

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat4_createTranslate_MajorRowOrder_Test)
		{
			Mat4f expected = {
				1.0f, 0.0f, 0.0f, 4.0f,
				0.0f, 1.0f, 0.0f, 2.0f,
				0.0f, 0.0f, 1.0f, -3.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			Mat4f result = Mat4f::createTranslate(4.0f, 2.0f, -3.0f);

			for (size_t i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}
#endif

		TEST_METHOD(Mat4_sizeInBytes_Test)
		{
			size_t result = Mat4f::identity().sizeInBytes();
			size_t expected = 4*16;

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Mat4_clone_Test)
		{
			Mat4f matrix = {
				2.0f, 5.0f, -2.0f, 4.0f,
				1.0f, -3.0f, 8.0f, 8.0f,
				0.0f, 7.0f, -4.0f, 7.0f,
				4.0f, 4.0f, 5.0f, 2.0f
			};

			Mat4f result = matrix.clone();

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(matrix[i], result[i], L"Wrong number", LINE_INFO());
		}
		
		TEST_METHOD(Mat4_toMat3_Test)
		{
			Mat4f matrix = {
				2.0f, 5.0f, -2.0f, 4.0f,
				1.0f, -3.0f, 8.0f, 8.0f,
				0.0f, 7.0f, -4.0f, 7.0f,
				4.0f, 4.0f, 5.0f, 2.0f
			};
			Mat3f expected = {
				2.0f, 5.0f, -2.0f,
				1.0f, -3.0f, 8.0f,
				0.0f, 7.0f, -4.0f
			};

			Mat3f result = matrix.toMat3();

			for (int i = 0; i < MAT3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}
		
#if MAJOR_COLUMN_ORDER
		TEST_METHOD(Mat4_operatorMultiplyValue_Test)
		{
			Mat4f matrixA = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};
			Mat4f expected = {
				8.0f, 6.0f, 4.0f, 18.0f,
				-4.0f, 16.0f, 8.0f, -4.0f,
				6.0f, -10.0f, 2.0f, 6.0f,
				2.0f, 8.0f, 0.0f, 0.0f
			};

			Mat4f result = matrixA * 2.0f;

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}
#endif

		TEST_METHOD(Mat4_operatorPlusValue_Test)
		{
			Mat4f matrixA = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};
			Mat4f expected = {
				6.0f, 5.0f, 4.0f, 11.0f,
				0.0f, 10.0f, 6.0f, 0.0f,
				5.0f, -3.0f, 3.0f, 5.0f,
				3.0f, 6.0f, 2.0f, 2.0f
			};

			Mat4f result = matrixA + 2.0f;

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_operatorPlusMatrix_Test)
		{
			Mat4f matrixA = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};
			Mat4f matrixB = {
				2.0f, 5.0f, -2.0f, 4.0f,
				1.0f, -3.0f, 8.0f, 8.0f,
				0.0f, 7.0f, -4.0f, 7.0f,
				4.0f, 4.0f, 5.0f, 2.0f
			};
			Mat4f expected = {
				6.0f, 8.0f, 0.0f, 13.0f,
				-1.0f, 5.0f, 12.0f, 6.0f,
				3.0f, 2.0f, -3.0f, 10.0f,
				5.0f, 8.0f, 5.0f, 2.0f
			};

			Mat4f result = matrixA + matrixB;

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_operatorMinusMatrix_Test)
		{
			Mat4f matrixA = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};
			Mat4f matrixB = {
				2.0f, 5.0f, -2.0f, 4.0f,
				1.0f, -3.0f, 8.0f, 8.0f,
				0.0f, 7.0f, -4.0f, 7.0f,
				4.0f, 4.0f, 5.0f, 2.0f
			};
			Mat4f expected = {
				2.0f, -2.0f, 4.0f, 5.0f,
				-3.0f, 11.0f, -4.0f, -10.0f,
				3.0f, -12.0f, 5.0f, -4.0f,
				-3.0f, 0.0f, -5.0f, -2.0f
			};

			Mat4f result = matrixA - matrixB;

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat3_operatorMinus_Test)
		{
			Mat4f matrixA = {
				-2.0f, 1.0f, 3.0f, 10.0f,
				0.0f, 4.0f, -2.0f, 5.0f,
				7.0f, 1.0f, 0.0f, 3.0f,
				-7.0f, -1.0f, -0.0f, -3.0f
			};
			Mat4f expected = {
				2.0f, -1.0f, -3.0f, -10.0f,
				0.0f, -4.0f, +2.0f, -5.0f,
				-7.0f, -1.0f, 0.0f, -3.0f,
				7.0f, 1.0f, 0.0f, 3.0f
			};

			Mat4f result = -matrixA;

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_operatorMinus_scalar_Test)
		{
			Mat4f matrixA = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};
			Mat4f expected = {
				2.0f, 1.0f, 0.0f, 7.0f,
				-4.0f, 6.0f, 2.0f, -4.0f,
				1.0f, -7.0f, -1.0f, 1.0f,
				-1.0f, 2.0f, -2.0f, -2.0f
			};

			Mat4f result = matrixA - 2.0f;

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_operatorEqualValue_Test)
		{
			Mat4f matrixA = {
				1.0f,  1.0f,  1.0f, 1.0f,
				1.0f,  1.0f,  1.0f, 1.0f,
				1.0f,  1.0f,  1.0f, 1.0f,
				1.0f,  1.0f,  1.0f, 1.0f
			};

			bool result = matrixA == 1.0f;
			Assert::IsTrue(result, L"Wrong number", LINE_INFO());

			matrixA[4] = 0.0f;

			result = matrixA == 1.0f;

			Assert::IsFalse(result, L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_operatorEqualMatrix_Test)
		{
			Mat4f matrixA = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};
			Mat4f matrixB = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};

			bool result = matrixA == matrixB;
			Assert::IsTrue(result, L"Wrong number", LINE_INFO());

			matrixB[5] = 10.0f;
			result = matrixA == matrixB;
			Assert::IsFalse(result, L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_operatorNotEqualMatrix_Test)
		{
			Mat4f matrixA = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};
			Mat4f matrixB = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};

			bool result = matrixA != matrixB;
			Assert::IsFalse(result, L"Wrong number", LINE_INFO());

			matrixB[5] = 10.0f;
			result = matrixA != matrixB;
			Assert::IsTrue(result, L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_operatorIndex_Test)
		{
			Mat4f matrixA = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};
			float expected[16] = {
				4.0f,  3.0f,  2.0f, 9.0f,
				-2.0f,  8.0f, 4.0f, -2.0f,
				3.0f,  -5.0f,  1.0f, 3.0f,
				1.0f, 4.0f,  0.0f, 0.0f
			};

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], matrixA[i], L"Wrong number", LINE_INFO());
		}

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat4_decomposeLU_MajorRowOrder_Test)
		{
			Mat4f matrix = {
				1.0f, -2.0f, -2.0f, -3.0f,
				3.0f, -9.0f,  0.0f, -9.0f,
				-1.0f,  2.0f,  4.0f,  7.0f,
				-3.0f, -6.0f,  26.0f, 2.0f
			};

			Mat4f lowerMatrixExpected = {
				1.0f, 0.0f,  0.0f,  0.0f,
				3.0f, -3.0f,  0.0f,  0.0f,
				-1.0f, 0.0f,  2.0f,  0.0f,
				-3.0f, -12.0f, -4.0f,  1.0f
			};

			Mat4f upperMatrixExpected = {
				1.0f, -2.0f, -2.0f, -3.0f,
				0.0f, 1.0f,  -2.0f,  0.0f,
				0.0f,  0.0f,  1.0f,  2.0f,
				0.0f,  0.0f,  0.0f,  1.0f
			};

			Mat4f* decomposeLU = matrix.decomposeLU();
			Mat4f lowerMatrixResult = decomposeLU[0];
			Mat4f upperMatrixResult = decomposeLU[1];
			Mat4f result = lowerMatrixResult * upperMatrixResult;

			for (size_t i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(result[i], matrix[i], L"Wrong number", LINE_INFO());

			for (size_t i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(lowerMatrixResult[i], lowerMatrixExpected[i], L"Wrong number", LINE_INFO());

			for (size_t i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(upperMatrixResult[i], upperMatrixExpected[i], L"Wrong number", LINE_INFO());
		}
#endif

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat4_decomposeLDU_MajorRowOrder_Test)
		{
			Mat4f matrix = {
				 1.0f, -2.0f, -2.0f, -3.0f,
				 3.0f, -9.0f,  0.0f, -9.0f,
				-1.0f,  2.0f,  4.0f,  7.0f,
				-3.0f, -6.0f,  26.0f, 2.0f
			};

			Mat4f lowerMatrixExpected = {
				 1.0f, 0.0f,  0.0f,  0.0f,
				 3.0f, -3.0f,  0.0f,  0.0f,
				-1.0f, 0.0f,  2.0f,  0.0f,
				-3.0f, -12.0f, -4.0f,  1.0f
			};

			Mat4f diagonalMatrixExpected = {
				1.0f, 0.0f,  0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f,  0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			Mat4f upperMatrixExpected = {
				1.0f, -2.0f, -2.0f, -3.0f,
				0.0f, 1.0f, -2.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 2.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			Mat4f* decomposeLDU = matrix.decomposeLDU();
			Mat4f lowerMatrixResult = decomposeLDU[0];
			Mat4f diagonalMatrixResult = decomposeLDU[1];
			Mat4f upperMatrixResult = decomposeLDU[2];
			Mat4f result = lowerMatrixResult * diagonalMatrixResult * upperMatrixResult;

			for (size_t i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(result[i], matrix[i], L"Wrong number", LINE_INFO());

			for (size_t i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(lowerMatrixResult[i], lowerMatrixExpected[i], L"Wrong number", LINE_INFO());

			for (size_t i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(upperMatrixResult[i], upperMatrixExpected[i], L"Wrong number", LINE_INFO());

			for (size_t i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(diagonalMatrixResult[i], diagonalMatrixExpected[i], L"Wrong number", LINE_INFO());
		}
#endif

		TEST_METHOD(Mat4_divide_operator_Test)
		{
			Mat4f matrixA = {
				2.0f, 1.0f, 3.0f, -6.0f,
				0.0f, 4.0f, -2.0f, 4.0f,
				7.0f, 1.0f, 0.0f, 4.0f,
				7.0f, 1.0f, 0.0f, 4.0f
			};
			Mat4f expected = {
				1.0f, 0.5f, 1.5f, -3.0f,
				0.0f, 2.0f, -1.0f, 2.0f,
				3.5f, 0.5f, 0.0f, 2.0f,
				3.5f, 0.5f, 0.0f, 2.0f
			};

			Mat4f result = matrixA / 2.0f;

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat4_divide_equal_operator_Test)
		{
			Mat4f matrixA = {
				2.0f, 1.0f, 3.0f, -6.0f,
				0.0f, 4.0f, -2.0f, 4.0f,
				7.0f, 1.0f, 0.0f, 4.0f,
				7.0f, 1.0f, 0.0f, 4.0f
			};
			Mat4f expected = {
				1.0f, 0.5f, 1.5f, -3.0f,
				0.0f, 2.0f, -1.0f, 2.0f,
				3.5f, 0.5f, 0.0f, 2.0f,
				3.5f, 0.5f, 0.0f, 2.0f
			};

			matrixA /= 2.0f;

			for (int i = 0; i < MAT4_SIZE; i++)
				Assert::AreEqual(expected[i], matrixA[i], L"Wrong number", LINE_INFO());
		}

	};
}
