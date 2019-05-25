#pragma once

#include "CppUnitTest.h"
#include <AlgorithmAitken.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	float funcAitken(float x)
	{
		return std::sqrtf(10.0f / (x + 4.0f));
	}

	TEST_CLASS(AlgorithmAitkenTest)
	{
	public:

		TEST_METHOD(AlgorithmAitken_solve_Test)
		{
			AlgorithmAitken<float> algorithm;
			const float initialApproximation = 1.5f;

			float result = algorithm.solve(initialApproximation, funcAitken);

			Assert::IsTrue(isCloseEnough(result, 1.3652f), L"Wrong value.", LINE_INFO());
		}

	};
}