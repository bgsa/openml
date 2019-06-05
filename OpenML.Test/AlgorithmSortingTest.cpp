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

			float vec[5] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f };
			float expected[5] = { -2.0f, 2.0f, 3.1f, 3.4f, 7.0f };

			float* result = sorting.radix(vec, 5);

			for (size_t i = 0; i < 5; i++)
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

	};
}