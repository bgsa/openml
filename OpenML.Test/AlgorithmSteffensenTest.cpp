#pragma once

#include "CppUnitTest.h"
#include <AlgorithmSteffensen.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	float funcSteffensen(float x)
	{
		//return std::powf(x, 3) + 4 * std::pow(x, 2) - 10;

		return std::sqrtf(10.0f / (x + 4.0f));
	}

	TEST_CLASS(AlgorithmSteffensenTest)
	{
	public:

		TEST_METHOD(AlgorithmSteffensen_solve_Test)
		{
			AlgorithmSteffensen<float> algorithm;
			float result = algorithm.solve(1.5f, funcSteffensen);

			Assert::IsTrue(isCloseEnough(result, 1.3652f), L"Wrong value.", LINE_INFO());
		}

	};
}