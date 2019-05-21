#pragma once

#include "CppUnitTest.h"
#include <AlgorithmSecant.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	float funcSecant(float x)
	{
		return std::cos(x) - x;;
	}

	TEST_CLASS(AlgorithmSecantTest)
	{
	public:

		TEST_METHOD(AlgorithmSecant_solve_Test)
		{
			AlgorithmSecant<float> algorithm;
			float result = algorithm.solve(0.5f, float(PI / 4), funcSecant);

			Assert::IsTrue(isCloseEnough(result, 0.7390f), L"Wrong value.", LINE_INFO());
		}

	};
}