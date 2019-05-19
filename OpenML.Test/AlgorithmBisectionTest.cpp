#pragma once

#include "CppUnitTest.h"
#include <AlgorithmBisection.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	float func(float x)
	{
		return std::powf(x, 3) + 4 * std::pow(x, 2) - 10;
	}

	TEST_CLASS(BisectionAlgorithmTest)
	{
	public:

		TEST_METHOD(BisectionAlgorithm_Test)
		{
			AlgorithmBisection<float> alg;
			float result = alg.solve(1.0f, 2.0f, func);
			
			Assert::IsTrue(isCloseEnough(result, 1.36523f), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(BisectionAlgorithm_maxNumberOfIteration_Test)
		{
			AlgorithmBisection<float> alg;
			int result = alg.maxNumberOfIteration();

			Assert::AreEqual(result, 14, L"Wrong value.", LINE_INFO());
		}

	};
}