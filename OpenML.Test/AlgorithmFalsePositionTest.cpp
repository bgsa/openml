#pragma once

#include "CppUnitTest.h"
#include <AlgorithmFalsePosition.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	float funcFalsePosition(float x)
	{
		return std::cos(x) - x;
	}

	TEST_CLASS(AlgorithmFalsePositionTest)
	{
	public:

		TEST_METHOD(AlgorithmFalsePosition_solve_Test)
		{
			AlgorithmFalsePosition<float> algorithm;
			float result = algorithm.solve(0.5f, PI/4, funcFalsePosition);

			Assert::IsTrue(isCloseEnough(result, 0.7390f), L"Wrong value.", LINE_INFO());
		}

	};
}