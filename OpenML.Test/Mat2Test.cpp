#pragma once

#include "CppUnitTest.h"
#include "Mat2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpenMLTest
{
	TEST_CLASS(Mat2Test)
	{
	public:

		TEST_METHOD(Mat2_constructorEmpty_Test)
		{
			Mat2f result;

			for (size_t i = 0; i < MAT2_SIZE; i++)
				Assert::AreEqual(0.0f, result[i], L"Value shoud be 0", LINE_INFO());
		}

		TEST_METHOD(Mat2_constructorValues_Test)
		{
			float emptyMatrix[MAT2_SIZE] = {
				1.0f, 2.0f, 
				4.0f, 5.0f
			};

			Mat2f result = Mat2f(emptyMatrix);

			for (size_t i = 0; i < MAT2_SIZE; i++)
				Assert::AreEqual(emptyMatrix[i], result[i], L"Value shoud be 0", LINE_INFO());
		}

		TEST_METHOD(Mat2_getValues_Test)
		{
			Mat2f matrix = {
				1.0f, 2.0f,
				4.0f, 5.0f
			};

			float* result = matrix.getValues();

			for (size_t i = 0; i < MAT2_SIZE; i++)
				Assert::AreEqual(matrix[i], result[i], L"Value shoud be 0", LINE_INFO());
		}

		TEST_METHOD(Mat2_getValue_Test)
		{
			Mat2f matrix = {
				1.0f, 2.0f,
				4.0f, 5.0f
			};

			Assert::AreEqual(1.0f, matrix.getValue(1, 1), L"Wrong value", LINE_INFO());
			Assert::AreEqual(4.0f, matrix.getValue(1, 2), L"Wrong value", LINE_INFO());
			Assert::AreEqual(2.0f, matrix.getValue(2, 1), L"Wrong value", LINE_INFO());
			Assert::AreEqual(5.0f, matrix.getValue(2, 2), L"Wrong value", LINE_INFO());
		}

#if MAJOR_COLUMN_ORDER
		TEST_METHOD(Mat2_xAxis_ColumnMajorOrder_Test)
		{
			Mat2f matrix = {
				1.0f, 2.0f,
				4.0f, 5.0f
			};

			Vec2f xAxis = matrix.xAxis();

			Assert::AreEqual(1.0f, xAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(4.0f, xAxis[1], L"Wrong value", LINE_INFO());
		}
#endif

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat2_xAxis_RowMajorOrder_Test)
		{
			Mat2f matrix = {
				1.0f, 2.0f,
				4.0f, 5.0f
			};

			Vec2f xAxis = matrix.xAxis();

			Assert::AreEqual(1.0f, xAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(2.0f, xAxis[1], L"Wrong value", LINE_INFO());
		}
#endif

#if MAJOR_COLUMN_ORDER
		TEST_METHOD(Mat2_yAxis_ColumnMajorRow_Test)
		{
			Mat2f matrix = {
				1.0f, 2.0f,
				4.0f, 5.0f
			};

			Vec2f yAxis = matrix.yAxis();

			Assert::AreEqual(2.0f, yAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(5.0f, yAxis[1], L"Wrong value", LINE_INFO());
		}
#endif

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat2_yAxis_RowMajorRow_Test)
		{
			Mat2f matrix = {
				1.0f, 2.0f,
				4.0f, 5.0f
			};

			Vec2f yAxis = matrix.yAxis();

			Assert::AreEqual(4.0f, yAxis[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(5.0f, yAxis[1], L"Wrong value", LINE_INFO());
		}
#endif

		TEST_METHOD(Mat2_primaryDiagonal_Test)
		{
			Mat2f matrix = {
				1.0f, 2.0f,
				4.0f, 5.0f
			};

			Vec2f primaryDiagonal = matrix.primaryDiagonal();

			Assert::AreEqual(1.0f, primaryDiagonal[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(5.0f, primaryDiagonal[1], L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Mat2_secondaryDiagonal_Test)
		{
			Mat2f matrix = {
				1.0f, 2.0f,
				4.0f, 5.0f
			};

			Vec2f secondaryDiagonal = matrix.secondaryDiagonal();

			Assert::AreEqual(2.0f, secondaryDiagonal[0], L"Wrong value", LINE_INFO());
			Assert::AreEqual(4.0f, secondaryDiagonal[1], L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Mat2_identity_Test)
		{
			Mat2f result = Mat2f::identity();

			for (size_t i = 0; i < MAT2_SIZE; i++)
				if (i % 3 == 0)
					Assert::AreEqual(1.0f, result[i], L"Value shoud be 0", LINE_INFO());
				else
					Assert::AreEqual(0.0f, result[i], L"Value shoud be 0", LINE_INFO());
		}

		TEST_METHOD(Mat2_transpose_Test)
		{
			Mat2f matrix = {
				1.0f, 2.0f,
				4.0f, 5.0f
			};
			Mat2f result = matrix.transpose();

			float expected[MAT2_SIZE] = {
				1.0f, 4.0f,
				2.0f, 5.0f
			};

			for (size_t i = 0; i < MAT2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value", LINE_INFO());
		}

#if MAJOR_COLUMN_ORDER
		TEST_METHOD(Mat2_multiply_MajorColumnOrder_Test)
		{
			Mat2f matrixA = {
				2.0f, 3.0f,
				3.0f, 4.0f
			};
			Mat2f matrixB = {
				0.0f, 1.0f,
				-1.0f, 0.0f
			};
			Mat2f expected = {
				3.0f, 4.0f,
				-2.0f, -3.0f
			};

			Mat2f result = matrixA.multiply(matrixB);

			for (size_t i = 0; i < MAT2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}
#endif

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat2_multiply_MajorRowOrder_Test)
		{
			Mat2f matrixA = {
				2.0f, 3.0f,
				3.0f, 4.0f
			};
			Mat2f matrixB = {
				0.0f, 1.0f,
				-1.0f, 0.0f
			};
			Mat2f expected = {
				-3.0f, 2.0f,
				-4.0f, 3.0f
			};

			Mat2f result = matrixA.multiply(matrixB);

			for (size_t i = 0; i < MAT2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}
#endif

		TEST_METHOD(Mat2_createScaled_Test)
		{
			Mat2f expected = {
				3.0f, 0.0f,
				0.0f, 4.0f
			};

			Mat2f result = Mat2f::createScale(3.0f, 4.0f);

			for (size_t i = 0; i < MAT2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat2_scale_Test)
		{
			Mat2f matrixA = {
				2.0f, 0.0f,
				0.0f, 4.0f
			};
			Mat2f expected = {
				4.0f, 0.0f,
				0.0f, 16.0f,
			};

			matrixA.scale(2.0f, 4.0f);

			for (size_t i = 0; i < MAT2_SIZE; i++)
				Assert::AreEqual(expected[i], matrixA[i], L"Wrong number", LINE_INFO());
		}
		
#if MAJOR_COLUMN_ORDER
		TEST_METHOD(Mat2_createTranslate_MajorColumnOrder_Test)
		{
			Mat2f expected = {
				1.0f, 0.0f,
				5.0f, 2.0f
			};

			Mat2f result = Mat2f::createTranslate(5.0f, 2.0f);

			for (size_t i = 0; i < MAT2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}
#endif

#if MAJOR_ROW_ORDER
		TEST_METHOD(Mat2_createTranslate_MajorRowOrder_Test)
		{
			Mat2f expected = {
				1.0f, 5.0f,
				0.0f, 2.0f
			};

			Mat2f result = Mat2f::createTranslate(5.0f, 2.0f);

			for (size_t i = 0; i < MAT2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong number", LINE_INFO());
		}
#endif

		TEST_METHOD(Mat2_determinant_Test)
		{
			Mat2f matrix = {
				2.0f, 9.0f,
				-1.0f, 6.0f
			};
			float expected = 21.0f;

			float result = matrix.determinant();

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Mat2_sizeInBytes_Test)
		{
			size_t result = Mat2f::identity().sizeInBytes();
			size_t expected = 16;

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Mat2_clone_Test)
		{
			Mat2f matrix = {
				1.0f, 2.0f,
				4.0f, 5.0f
			};

			Mat2f result = matrix.clone();

			for (size_t i = 0; i < MAT2_SIZE; i++)
				Assert::AreEqual(matrix[i], result[i], L"Wrong number", LINE_INFO());
		}

		TEST_METHOD(Mat2_getAutovalueAndAutovector_Test)
		{
			Mat2f matrix = {
				3.0f, 2.0f,
				2.0f, 3.0f
			};

			float expectedValue = 5.0f;
			Vec2f expectedVector = Vec2f{ 1.0f, 1.0f }; // VERIFICAR no livro algebra linear !
			AutovalueAutovector2<float> result = matrix.getAutovalueAndAutovector();

			Assert::AreEqual(ceil(expectedValue), ceil(result.autovalue), L"Wrong number", LINE_INFO());

			for (size_t i = 0; i < MAT2_ROWSIZE; i++)
				Assert::AreEqual(ceil(expectedVector[i]), ceil(result.autovector[i]), L"Wrong number", LINE_INFO());
		}

	};
}
