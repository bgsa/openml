#pragma once

#include "CppUnitTest.h"
#include <AlgorithmSorting.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{

	TEST_CLASS(AlgorithmSortingTest)
	{
	public:

		TEST_METHOD(AlgorithmSorting_radix_Test1)
		{
			AlgorithmSorting sorting;
			const size_t count = 7;

			float vec[count] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f, 3.12f, 3.01f };
			float expected[count] = { -2.0f, 2.0f, 3.01f, 3.1f, 3.12f, 3.4f, 7.0f };

			float* result = sorting.radix(vec, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test2)
		{
			AlgorithmSorting sorting;

			int result[12] = { 3, 2, 7, 3, -2, 0, -1000, 4, 8, 3, 11, -1 };
			int expected[12] = { -1000, -2, -1, 0, 2, 3, 3, 3, 4, 7, 8, 11 };

			sorting.radix(result, 12);

			for (size_t i = 0; i < 12; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_native_Test1)
		{
			AlgorithmSorting sorting;
			const size_t count = 7;

			float vec[count] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f, 3.12f, 3.01f };
			float expected[count] = { -2.0f, 2.0f, 3.01f, 3.1f, 3.12f, 3.4f, 7.0f };

			sorting.native(vec, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], vec[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_nativeIndex_Test1)
		{
			AlgorithmSorting sorting;
			const size_t count = 7;

			float vec[count] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f, 3.12f, 3.01f };
			size_t expected[count] = { 4, 1, 6, 3, 5, 0, 2 };

			size_t* result = sorting.nativeIndex(vec, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

	};
}