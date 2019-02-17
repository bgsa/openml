#pragma once

#include "CppUnitTest.h"
#include <Vec3.h>
#include <Line3D.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(Line3DTest)
	{
	public:

		TEST_METHOD(Line3D_findIntersection_Test)
		{
			Line3Df line1 = Line3Df( Vec3f{ 6.0f, 8.0f, 4.0f }, Vec3f{ 12.0f, 15.0f, 4.0f });
			Line3Df line2 = Line3Df(Vec3f{ 6.0f, 8.0f, 2.0f }, Vec3f{ 12.0f, 15.0f, 6.0f });
			
			Vec3f expected = { 9.0f, 11.5f, 4.0f };

			Vec3f* result = line1.findIntersection(line2);

			Assert::IsNotNull(result, L"Value should not be null.", LINE_INFO());

			Assert::AreEqual(expected.x(), result->x(), L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.y(), result->y(), L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.z(), result->z(), L"Wrong value.", LINE_INFO());
		}

	};
}