#pragma once

#include "CppUnitTest.h"
#include <AlgorithmBisection.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	float funcBisection(float x)
	{
		return std::powf(x, 3) + 4 * std::pow(x, 2) - 10;
	}

	TEST_CLASS(AlgorithmBisectionTest)
	{
	public:

		TEST_METHOD(AlgorithmBisection_solve_Test)
		{
			AlgorithmBisection<float> algorithm;
			float result = algorithm.solve(1.0f, 2.0f, funcBisection);
			
			Assert::IsTrue(isCloseEnough(result, 1.3652f), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmBisection_maxNumberOfIteration_Test)
		{
			AlgorithmBisection<float> algorithm;
			int result = algorithm.maxNumberOfIteration();

			Assert::AreEqual(result, 14, L"Wrong value.", LINE_INFO());
		}

	};
}