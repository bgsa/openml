#pragma once

#include "CppUnitTest.h"
#include <Vec3.h>
#include <Point3D.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(Point3DTest)
	{
	public:

		TEST_METHOD(Point3D_Distance_Test)
		{
			Point3Df point1 = { 7.0f, 5.0f, 4.0f };
			Point3Df point2 = { 2.0f, 1.0f, 2.0f };
			float expected = 6.71f;

			float result = OpenML::round(point1.distance(point2), 2);

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}
		
	};
}