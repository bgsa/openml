#pragma once

#include "CppUnitTest.h"
#include <Vec2.h>
#include <Vec3.h>
#include <Line2D.h>
#include <Circle2D.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(Circle2DTest)
	{
	public:

		TEST_METHOD(Circle2D_constructorWithThreePoints_Test)
		{
			Circle2Df circle = Circle2Df(
				Vec2f(-3.0f, 4.0f),
				Vec2f(4.0f, 5.0f),
				Vec2f(1.0f, -4.0f)
			);

			Vec2f center = circle.center;
			float ray = circle.ray;

			Assert::AreEqual(1.0f, center.x(), L"Wrong value.", LINE_INFO());
			Assert::AreEqual(1.0f, center.y(), L"Wrong value.", LINE_INFO());
			Assert::AreEqual(5.0f, ray, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Circle2D_area_Test)
		{
			Vec2f center = Vec2f(7.0f, 5.0f);
			float ray = 3.0f;
			Circle2Df circle = Circle2Df(center, ray);

			float result = circle.area();
			float expected = 28.27f;

			Assert::AreEqual(expected, OpenML::round(result, 2), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Circle2D_circumference_Test)
		{
			Vec2f center = Vec2f(7.0f, 5.0f);
			float ray = 3.0f;
			Circle2Df circle = Circle2Df(center, ray);

			float result = circle.circumference();
			float expected = 18.85f;

			Assert::AreEqual(expected, OpenML::round(result, 2), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Circle2D_hasIntersection1_Test)
		{
			Circle2Df circle1 = Circle2Df(Vec2f(-4.0f, 4.0f), 3.0f);
			Circle2Df circle2 = Circle2Df(Vec2f(0.0f, 9.0f), 5.0f);

			bool result = circle1.hasIntersection(circle2);

			Assert::IsTrue(result, L"Circles should intersect.", LINE_INFO());
		}

		TEST_METHOD(Circle2D_hasIntersection2_Test)
		{
			Circle2Df circle1 = Circle2Df(Vec2f(4.0f, -3.0f), 5.0f);
			Circle2Df circle2 = Circle2Df(Vec2f(-4.0f, -3.0f), 3.0f);

			bool result = circle1.hasIntersection(circle2);

			Assert::IsTrue(result, L"Circles should intersect.", LINE_INFO());
		}

		TEST_METHOD(Circle2D_findIntersection1_Test)
		{
			Circle2Df circle1 = Circle2Df(Vec2f(-4.0f, 4.0f), 3.0f);
			Circle2Df circle2 = Circle2Df(Vec2f(0.0f, 9.0f), 5.0f);

			Vec2f* result = circle1.findIntersection(circle2);

			Vec2f intersection1 = Vec2f(-1.0017f, 4.1013f);
			Vec2f intersection2 = Vec2f(-4.5592f, 6.9474f);
			
			Assert::IsNotNull(result, L"Circles should intersect.", LINE_INFO());
			
			Assert::IsTrue(isCloseEnough(result[0].x(), intersection1.x()), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(result[0].y(), intersection1.y()), L"Wrong value.", LINE_INFO());

			Assert::IsTrue(isCloseEnough(intersection2.x(), result[1].x()), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(intersection2.y(), result[1].y()), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Circle2D_findIntersection2_Test)
		{
			Circle2Df circle1 = Circle2Df(Vec2f(4.0f, -3.0f), 5.0f);
			Circle2Df circle2 = Circle2Df(Vec2f(-4.0f, -3.0f), 3.0f);

			Vec2f* result = circle1.findIntersection(circle2);

			Vec2f intersection = Vec2f(-1.0f, -3.0f);

			Assert::IsNotNull(result, L"Circles should intersect.", LINE_INFO());

			Assert::AreEqual(intersection.x(), OpenML::round(result[0].x(), 3), L"Wrong value.", LINE_INFO());
			Assert::AreEqual(intersection.y(), OpenML::round(result[0].y(), 3), L"Wrong value.", LINE_INFO());
		}

	};
}