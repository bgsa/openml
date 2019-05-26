#pragma once

#include "CppUnitTest.h"
#include <AlgorithmHorner.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	float funcHorner(float x)
	{
		return 2 * std::pow(x , 4) - 3 * std::pow(x , 2) + 3*x - 4;
	}

	TEST_CLASS(AlgorithmHornerTest)
	{
	public:

		TEST_METHOD(AlgorithmHorner_polynomialDivision_Test)
		{
			AlgorithmHorner<float> algorithm;
			float polynomial[5] = { 2.0f, 0.0f, -3.0f, 3.0f, -4.0f };
			float x0 = -2.0f;
			float expected[5] = { 2.0f, -4.0f, 5.0f, -7.0f, 10.0f };

			float* result = algorithm.polynomialDivision(x0, polynomial, 5);

			for (size_t i = 0; i < 5; i++)
				Assert::IsTrue(isCloseEnough(result[i], expected[i]), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmHorner_findRoots_Test)
		{
			AlgorithmHorner<float> algorithm;
			float polynomial[5] = { 2.0f, 0.0f, -3.0f, 3.0f, -4.0f };
			float x0 = -2.0f;
			float expected[5] = { -2.0f, -1.7959f, -1.7424f, -1.7389f, -1.7389f };

			float* result = algorithm.findRoots(x0, polynomial, 5);

			for (size_t i = 0; i < 5; i++)
				Assert::IsTrue(isCloseEnough(result[i], expected[i]), L"Wrong value.", LINE_INFO());
		}

	};
}