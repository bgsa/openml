#pragma once

#include "CppUnitTest.h"
#include <OpenML.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(OpenMLTest)
	{
	public:

		TEST_METHOD(OpenML_clamp_Test)
		{
			float result = clamp(1.0f, 0.0f, 2.0f);
			float expected = 1.0f;			
			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());

			result = clamp(-1.0f, 0.0f, 2.0f);
			expected = 0.0f;
			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());

			result = clamp(3.0f, 0.0f, 2.0f);
			expected = 2.0f;
			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());

			result = clamp(2.0f, 0.0f, 2.0f);
			expected = 2.0f;
			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());

			result = clamp(0.0f, 0.0f, 2.0f);
			expected = 0.0f;
			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());

			result = clamp(0.0001f, 0.0f, 2.0f);
			expected = 0.0001f;
			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}
	
	};
}