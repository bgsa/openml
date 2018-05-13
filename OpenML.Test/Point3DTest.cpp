#pragma once

#include "TestHeader.h"

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

		TEST_METHOD(Point3D_findMinX_Test)
		{
			Point3Df point1 = { 0.3f, 0.0f, 0.0f };
			Point3Df point2 = { 1.0f, 0.3f, 0.0f };
			Point3Df point3 = { 0.7f, 1.0f, 0.0f };
			Point3Df point4 = { 0.0f, 0.7f, 0.0f };
			Point3Df points[] = { point1, point2, point3, point4 };

			Point3Df pointExpected = point4;

			Point3Df result = Point3Df::findMinX(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Point3D_findMinY_Test)
		{
			Point3Df point1 = { 0.3f, 0.0f, 0.0f };
			Point3Df point2 = { 1.0f, 0.3f, 0.0f };
			Point3Df point3 = { 0.7f, 1.0f, 0.0f };
			Point3Df point4 = { 0.0f, 0.7f, 0.0f };
			Point3Df points[] = { point1, point2, point3, point4 };

			Point3Df pointExpected = point1;

			Point3Df result = Point3Df::findMinY(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Point3D_findMinZ_Test)
		{
			Point3Df point1 = { 0.3f, 0.0f, 6.0f };
			Point3Df point2 = { 1.0f, 0.3f, 4.0f };
			Point3Df point3 = { 0.7f, 1.0f, 7.0f };
			Point3Df point4 = { 0.0f, 0.7f, 1.0f };
			Point3Df points[] = { point1, point2, point3, point4 };

			Point3Df pointExpected = point4;

			Point3Df result = Point3Df::findMinZ(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Point3D_findMaxX_Test)
		{
			Point3Df point1 = { 0.3f, 0.0f, 6.0f };
			Point3Df point2 = { 1.0f, 0.3f, 4.0f };
			Point3Df point3 = { 0.7f, 1.0f, 7.0f };
			Point3Df point4 = { 0.0f, 0.7f, 1.0f };
			Point3Df points[] = { point1, point2, point3, point4 };

			Point3Df pointExpected = point2;

			Point3Df result = Point3Df::findMaxX(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Point3D_findMaxY_Test)
		{
			Point3Df point1 = { 0.3f, 0.0f, 6.0f };
			Point3Df point2 = { 1.0f, 0.3f, 4.0f };
			Point3Df point3 = { 0.7f, 1.0f, 7.0f };
			Point3Df point4 = { 0.0f, 0.7f, 1.0f };
			Point3Df points[] = { point1, point2, point3, point4 };

			Point3Df pointExpected = point3;

			Point3Df result = Point3Df::findMaxY(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Point3D_findMaxZ_Test)
		{
			Point3Df point1 = { 0.3f, 0.0f, 6.0f };
			Point3Df point2 = { 1.0f, 0.3f, 7.0f };
			Point3Df point3 = { 0.7f, 1.0f, 4.0f };
			Point3Df point4 = { 0.0f, 0.7f, 1.0f };
			Point3Df points[] = { point1, point2, point3, point4 };

			Point3Df pointExpected = point2;

			Point3Df result = Point3Df::findMaxZ(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

	};
}