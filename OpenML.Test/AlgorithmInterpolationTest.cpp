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

	};
}