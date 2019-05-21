#pragma once

#include "CppUnitTest.h"
#include <AlgorithmNewton.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	float funcNewton(float x)
	{
		return std::cos(x) - x;;
	}

	float funcDerivatedNewton(float x)
	{
		return -std::sin(x) - 1;
	}

	TEST_CLASS(AlgorithmNewtonTest)
	{
	public:

		TEST_METHOD(AlgorithmNewton_solve_Test)
		{
			AlgorithmNewton<float> algorithm;
			float result = algorithm.solve(float(PI / 4), funcNewton, funcDerivatedNewton);

			Assert::IsTrue(isCloseEnough(result, 0.7390f), L"Wrong value.", LINE_INFO());
		}

	};
}