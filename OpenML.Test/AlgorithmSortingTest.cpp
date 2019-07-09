#pragma once

#include "CppUnitTest.h"
#include <AlgorithmSorting.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

int comparatorFloatTest(const void* param1, const void* param2)
{
	const float obj1 = *(float*)param1;
	const float obj2 = *(float*)param2;

	if (obj1 < obj2)
		return -1;
	else
		if (obj1 > obj2)
			return 1;

	return 0;
}

namespace OpenMLTest
{

	TEST_CLASS(AlgorithmSortingTest)
	{
	public:

		TEST_METHOD(AlgorithmSorting_radix_Test1)
		{
			const size_t count = 7;

			float vec[count] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f, 3.12f, 3.01f };
			float expected[count] = { -2.0f, 2.0f, 3.01f, 3.1f, 3.12f, 3.4f, 7.0f };
			
			AlgorithmSorting::radix(vec, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], vec[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test2)
		{
			size_t result[8] = { 2, 5,3,0,2,3,0,3 };
			size_t expected[8] = { 0,0,2,2,3,3,3,5 };

			AlgorithmSorting::radix(result, 8);

			for (size_t i = 0; i < 8; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test3)
		{
			size_t result[8] = { 200, 54, 35, 10, 4, 3, 50, 33 };
			size_t expected[8] = { 3, 4, 10, 33, 35, 50, 54, 200 };

			AlgorithmSorting::radix(result, 8);

			for (size_t i = 0; i < 8; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test4)
		{
			int result[8] = { 200, 54, 35, -10, 4, 3, -50, 33 };
			int expected[8] = { -50, -10, 3, 4, 33, 35, 54, 200 };
			
			AlgorithmSorting::radix(result, 8);

			for (size_t i = 0; i < 8; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test5)
		{
			const size_t count = 6;
			float result[count] = { 0.1f,0.111f,0.23f,0.03f,0.53f,0.08f };
			float expected[count] = { 0.03f, 0.08f, 0.1f, 0.111f, 0.23f, 0.53f };

			AlgorithmSorting::radix(result, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test6)
		{
			const size_t count = 6;
			float result[count] = { 57.1f, 0.111f, 1.23f, 0.03f, 0.53f, 2.08f };
			float expected[count] = { 0.03f, 0.111f, 0.53f, 1.23f, 2.08f, 57.1f };

			AlgorithmSorting::radix(result, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test7)
		{
			const size_t count = 7;
			float result[count] = { 57.1f, 0.111f, -1.23f, 0.03f, 0.53f, 2.08f, -34567.56f };
			float expected[count] = { -34567.56f, -1.23f, 0.03f, 0.111f, 0.53f, 2.08f, 57.1f };

			AlgorithmSorting::radix(result, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_native_Test1)
		{
			const size_t count = 7;

			float vec[count] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f, 3.12f, 3.01f };
			float expected[count] = { -2.0f, 2.0f, 3.01f, 3.1f, 3.12f, 3.4f, 7.0f };

			AlgorithmSorting::native(vec, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], vec[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_nativeIndex_Test1)
		{
			const size_t count = 7;

			float vec[count] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f, 3.12f, 3.01f };
			size_t expected[count] = { 4, 1, 6, 3, 5, 0, 2 };

			size_t* result = AlgorithmSorting::nativeIndex(vec, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_quickSortNnative_Test1)
		{
			const size_t count = 7;

			float vec[count] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f, 3.12f, 3.01f };
			float expected[count] = { -2.0f, 2.0f, 3.01f, 3.1f, 3.12f, 3.4f, 7.0f };

			AlgorithmSorting::quickSortNative(vec, count, sizeof(float), comparatorFloatTest);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], vec[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radixGPU_Test1)
		{
			const size_t count = 7;
			float vector[count] = { 57.1f, 0.111f, -1.23f, 0.03f, 0.53f, 2.08f, -34567.56f };
			float expected[count] = { -34567.56f, -1.23f, 0.03f, 0.111f, 0.53f, 2.08f, 57.1f };

			float* result = AlgorithmSorting::radixGPU(vector, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());

			delete[] result;
		}

		TEST_METHOD(AlgorithmSorting_radixGPU_Test2)
		{
			const size_t count = 10;
			float vector[count] = { 57.1f, 0.111f, -1.23f, 0.03f, 0.53f, 2.08f, -34567.56f, 10.4f, -10.4f, 10.45f };
			float expected[count] = { -34567.56f, -10.4f , -1.23f, 0.03f, 0.111f, 0.53f, 2.08f, 10.4f, 10.45f, 57.1f };

			float* result = AlgorithmSorting::radixGPU(vector, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());

			delete[] result;
		}

	};
}