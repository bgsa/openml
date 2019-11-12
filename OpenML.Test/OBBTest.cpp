#pragma once

#include "CppUnitTest.h"
#include "TestHeader.h"
#include <OBB.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(OBBTest)
	{
	public:

		TEST_METHOD(OBB_constructor_empty_Test)
		{
			OBB obb = OBB();

			Assert::AreEqual(Vec3f(0.0f), obb.center, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(Vec3f(0.5f), obb.halfWidth, L"Wrong value.", LINE_INFO());
			Assert::IsTrue(Mat3f::identity() == obb.orientation, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(OBB_constructor_withCenter_Test)
		{
			Vec3f center(1.0f, 2.0f, 3.0f);

			OBB obb = OBB(center);

			Assert::AreEqual(center, obb.center, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(OBB_constructor_withHalfWidth_Test)
		{
			Vec3f center(1.0f, 2.0f, 3.0f);
			Vec3f halfWidth(1.0f, 2.0f, 3.0f);

			OBB obb = OBB(center, halfWidth);

			Assert::AreEqual(halfWidth, obb.halfWidth, L"Wrong value.", LINE_INFO());
		}

	};
}