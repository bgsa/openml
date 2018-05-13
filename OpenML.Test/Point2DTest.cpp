#pragma once

#include "TestHeader.h"

namespace OpenMLTest
{
	TEST_CLASS(Point2DTest)
	{
	public:

		TEST_METHOD(Point2D_findMinX_Test)
		{
			Point2Df point1 = { 0.3f, 0.0f };
			Point2Df point2 = { 1.0f, 0.3f };
			Point2Df point3 = { 0.7f, 1.0f };
			Point2Df point4 = { 0.0f, 0.7f };
			Point2Df points[] = { point1, point2, point3, point4 };

			Point2Df pointExpected = point4;

			Point2Df result = Point2Df::findMinX(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Point2D_findMinY_Test)
		{
			Point2Df point1 = { 0.3f, 0.0f };
			Point2Df point2 = { 1.0f, 0.3f };
			Point2Df point3 = { 0.7f, 1.0f };
			Point2Df point4 = { 0.0f, 0.7f };
			Point2Df points[] = { point1, point2, point3, point4 };

			Point2Df pointExpected = point1;

			Point2Df result = Point2Df::findMinY(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Point2D_findMaxX_Test)
		{
			Point2Df point1 = { 0.3f, 0.0f };
			Point2Df point2 = { 1.0f, 0.3f };
			Point2Df point3 = { 0.7f, 1.0f };
			Point2Df point4 = { 0.0f, 0.7f };
			Point2Df points[] = { point1, point2, point3, point4 };

			Point2Df pointExpected = point2;

			Point2Df result = Point2Df::findMaxX(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Point2D_findMaxY_Test)
		{
			Point2Df point1 = { 0.3f, 0.0f };
			Point2Df point2 = { 1.0f, 0.3f };
			Point2Df point3 = { 0.7f, 1.0f };
			Point2Df point4 = { 0.0f, 0.7f };
			Point2Df points[] = { point1, point2, point3, point4 };

			Point2Df pointExpected = point3;

			Point2Df result = Point2Df::findMaxY(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

	};
}