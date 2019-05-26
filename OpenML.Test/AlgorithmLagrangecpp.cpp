#pragma once

#include "CppUnitTest.h"
#include <AlgorithmLagrange.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{

	TEST_CLASS(AlgorithmLagrangeTest)
	{
	public:

		float funcLagrange(float x) 
		{
			return 1.0f / x;
		}

		TEST_METHOD(AlgorithmLagrange_polynomialApproximation_Test1)
		{
			AlgorithmLagrange<float> algorithm;
			Vec2<float> points[2] = { Vec2<float>(2.0, 4.0f) , Vec2<float>(5.0f, 1.0f) };

			float result = algorithm.polynomialApproximation(points, 2, 3.0f);

			Assert::IsTrue(isCloseEnough(3.0f, result), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmLagrange_polynomialApproximation_Test2)
		{
			AlgorithmLagrange<float> algorithm;
			Vec2<float> points[3] = { Vec2<float>(2.0, funcLagrange(2.0f)), 
									  Vec2<float>(2.75, funcLagrange(2.75f)), 
									  Vec2<float>(4.0, funcLagrange(4.0f))
									};

			float result = algorithm.polynomialApproximation(points, 3, 3.0f);

			Assert::IsTrue(isCloseEnough(0.3295f, result), L"Wrong value.", LINE_INFO());
		}

	};
}