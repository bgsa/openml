#pragma once

#include "CppUnitTest.h"
#include <AlgorithmInterpolation.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{

	TEST_CLASS(AlgorithmInterpolationTest)
	{
	public:

		TEST_METHOD(AlgorithmInterpolation_findInterpolation_Test)
		{
			AlgorithmInterpolation<float> algorithm;
			const float x = 1.5f;
			Vec2<float> points[5] = {
				{1.0f, 0.7651977f},
				{1.3f, 0.6200860f},
				{1.6f, 0.4554022f},
				{1.9f, 0.2818186f},
				{2.2f, 0.1103623f}
			};

			float result = algorithm.findInterpolation(x, points, 5);

			Assert::IsTrue(isCloseEnough(result, 0.511820018f), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmInterpolation_getInterpolationPolynomial_Test)
		{
			AlgorithmInterpolation<float> algorithm;
			const float x = 1.5f;
			Vec2<float> points[5] = {
				{1.0f, 0.7651977f},
				{1.3f, 0.6200860f},
				{1.6f, 0.4554022f},
				{1.9f, 0.2818186f},
				{2.2f, 0.1103623f}
			};

			float* result = algorithm.getInterpolationPolynomial(points, 5);

			float expected[5] = {
				0.7651977f,
				-0.4837057f,
				-0.1087339f,
				0.0658784f,
				0.0018251f
			};

			for (size_t i = 0; i < 5; i++)
				Assert::IsTrue(isCloseEnough(expected[i], result[i]), L"Wrong value.", LINE_INFO());			

			delete[] result;
		}

		TEST_METHOD(AlgorithmInterpolation_getInterpolationPolynomialDescription_Test)
		{
			AlgorithmInterpolation<float> algorithm;
			const float x = 1.5f;
			Vec2<float> points[5] = {
				{1.0f, 0.7651977f},
				{1.3f, 0.6200860f},
				{1.6f, 0.4554022f},
				{1.9f, 0.2818186f},
				{2.2f, 0.1103623f}
			};

			std::string result = algorithm.getInterpolationPolynomialDescription(points, 5);

			std::string expected = "P4(x) = 0.765198 - 0.483706(x - 1) - 0.108734(x - 1)(x - 1.3) + 0.0658779(x - 1)(x - 1.3)(x - 1.6) + 0.00182617(x - 1)(x - 1.3)(x - 1.6)(x - 1.9)";

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

	};
}