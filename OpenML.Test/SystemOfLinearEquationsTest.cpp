#pragma once

#include "GlobalHeader.h"
#include "CppUnitTest.h"
#include "SystemOfLinearEquations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpenMLTest
{
	TEST_CLASS(SystemOfLinearEquationsTest)
	{
	public:

		TEST_METHOD(solve_2varaibles_Test)
		{
			SystemOfLinearEquations<float> linearSystem;
			size_t rowSize = 2;
			size_t colSize = 3;

			float* matrix = new float[rowSize * colSize] {
				1.0f,  1.0f, 3.0f,
				1.0f, -1.0f, 1.0f
			};

			float* expected = new float[colSize - 1] { 2.0f, 1.0f };

			float* result = linearSystem.solve(matrix, rowSize, colSize);

			for (size_t i = 0; i < colSize - 1; i++)
				Assert::AreEqual(expected[i], ceil(result[i]), L"Value wrong", LINE_INFO());
		}

		TEST_METHOD(solve_3varaibles_Test)
		{				
			SystemOfLinearEquations<float> linearSystem;
			size_t rowSize = 3;
			size_t colSize = 4;

			float* matrix = new float[rowSize * colSize]{
				2.0f,  1.0f, -3.0f, -1.0f,
				-1.0f, 3.0f, 2.0f, 12.0f,
				3.0f, 1.0f, -3.0, 0.0f
			};

			float* expected = new float[colSize - 1]{ 1.0f, 3.0f, 2.0f };

			float* result = linearSystem.solve(matrix, rowSize, colSize);

			for (size_t i = 0; i < colSize - 1; i++)
				Assert::AreEqual(expected[i], ceil(result[i]), L"Value wrong", LINE_INFO());
		}

		TEST_METHOD(solve_4varaibles_Test)
		{
			SystemOfLinearEquations<float> linearSystem;
			size_t rowSize = 4;
			size_t colSize = 5;

			float* matrix = new float[rowSize * colSize]{
				1.0f, -1.0f, 2.0f, -1.0f, -8.0f,
				2.0f, -2.0f, 3.0f, -3.0f, -20.0f,
				1.0f, 1.0f, 1.0f, 0.0f, -2.0f,
				1.0f, -1.0f, 4.0f, 3.0f, 4.0f,
			};

			float* expected = new float[colSize - 1]{ -7.0f, 3.0f, 2.0f, 2.0f };

			float* result = linearSystem.solve(matrix, rowSize, colSize);

			for (size_t i = 0; i < colSize - 1; i++)
				Assert::AreEqual(expected[i], ceil(result[i]), L"Value wrong", LINE_INFO());
		}

		TEST_METHOD(getLineEquation_Test)
		{
			Vec2f point1 = { 2.0f, 1.0f };
			Vec2f point2 = { 3.0f, 7.0f };

			Vec3f expected = { -6.0f, 1.0f, 11.0f };

			Vec3f result = SystemOfLinearEquations<float>::getLineEquation(point1, point2);

			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(expected[i], result[i], L"Value wrong", LINE_INFO());
		}

		TEST_METHOD(getCircleEquation_Test)
		{
			Vec2f point1 = { 1.0f, 7.0f };
			Vec2f point2 = { 6.0f, 2.0f };
			Vec2f point3 = { 4.0f, 6.0f };

			Vec4f expected = { 10.0f, -20.0f, -40.0f, -200.0f };

			Vec4f result = SystemOfLinearEquations<float>::getCircleEquation(point1, point2, point3);

			for (size_t i = 0; i < 4; i++)
				Assert::AreEqual(expected[i], result[i], L"Value wrong", LINE_INFO());
		}
	};
}
