#pragma once

#include "TestHeader.h"

namespace OpenMLTest
{
	TEST_CLASS(Point2DTest)
	{
	public:

		TEST_METHOD(Point2D_findMinX_Test)
		{
			Vec2f point1 = { 0.3f, 0.0f };
			Vec2f point2 = { 1.0f, 0.3f };
			Vec2f point3 = { 0.7f, 1.0f };
			Vec2f point4 = { 0.0f, 0.7f };
			Vec2f points[] = { point1, point2, point3, point4 };

			Point2Df pointExpected = point4;

			Point2Df result = Point2Df::findMinX(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Point2D_findMinY_Test)
		{
			Vec2f point1 = { 0.3f, 0.0f };
			Vec2f point2 = { 1.0f, 0.3f };
			Vec2f point3 = { 0.7f, 1.0f };
			Vec2f point4 = { 0.0f, 0.7f };
			Vec2f points[] = { point1, point2, point3, point4 };

			Point2Df pointExpected = point1;

			Point2Df result = Point2Df::findMinY(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Point2D_findMaxX_Test)
		{
			Vec2f point1 = { 0.3f, 0.0f };
			Vec2f point2 = { 1.0f, 0.3f };
			Vec2f point3 = { 0.7f, 1.0f };
			Vec2f point4 = { 0.0f, 0.7f };
			Vec2f points[] = { point1, point2, point3, point4 };

			Point2Df pointExpected = point2;

			Point2Df result = Point2Df::findMaxX(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Point2D_findMaxY_Test)
		{
			Vec2f point1 = { 0.3f, 0.0f };
			Vec2f point2 = { 1.0f, 0.3f };
			Vec2f point3 = { 0.7f, 1.0f };
			Vec2f point4 = { 0.0f, 0.7f };
			Vec2f points[] = { point1, point2, point3, point4 };

			Point2Df pointExpected = point3;

			Point2Df result = Point2Df::findMaxY(points, 4);

			Assert::AreEqual(pointExpected, result, L"Wrong value.", LINE_INFO());
		}

	};
}