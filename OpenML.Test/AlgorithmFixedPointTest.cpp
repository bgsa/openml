#pragma once

#include "CppUnitTest.h"
#include <AlgorithmFixedPoint.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	float funcFixedPoint(float x)
	{
		float numerator = std::powf(x, 3) + 4 * std::pow(x, 2) - 10;

		float numeratorDerived = 3 * std::pow(x, 2) + 8 * x;

		return x - (numerator / numeratorDerived);
	}

	TEST_CLASS(AlgorithmFixedPointTest)
	{
	public:

		TEST_METHOD(AlgorithmFixedPoint_solve_Test)
		{
			AlgorithmFixedPoint<float> algorithm;
			const float initialApproximation = 1.5f;

			float result = algorithm.solve(initialApproximation, funcFixedPoint);

			Assert::IsTrue(isCloseEnough(result, 1.3652f), L"Wrong value.", LINE_INFO());
		}

	};
}