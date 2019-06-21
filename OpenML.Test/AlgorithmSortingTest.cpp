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

			float* result = AlgorithmSorting::radix(vec, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test2)
		{
			int result[12] = { 3, 2, 7, 3, -2, 0, -1000, 4, 8, 3, 11, -1 };
			int expected[12] = { -1000, -2, -1, 0, 2, 3, 3, 3, 4, 7, 8, 11 };

			AlgorithmSorting::radix(result, 12);

			for (size_t i = 0; i < 12; i++)
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

	};
}