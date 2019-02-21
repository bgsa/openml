#pragma once

#include "TestHeader.h"
#include "Vec2List.h"

namespace OpenMLTest
{
	TEST_CLASS(Rectangle2DTest)
	{
	public:

		TEST_METHOD(Rectangle2D_width_Test)
		{
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 0.0f, 100.0f },
				{ 20.0f, 100.0f },
				{ 20.0f, 0.0f }
			);

			float result = square.width();

			Assert::AreEqual(20.0f, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_height_Test)
		{
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 0.0f, 100.0f },
				{ 20.0f, 100.0f },
				{ 20.0f, 0.0f }
			);

			float result = square.height();

			Assert::AreEqual(100.0f, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_area_Test)
		{
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 0.0f, 100.0f },
				{ 20.0f, 100.0f },
				{ 20.0f, 0.0f }
			);

			float result = square.area();

			Assert::AreEqual(2000.0f, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_perimeter_Test)
		{
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 0.0f, 100.0f },
				{ 20.0f, 100.0f },
				{ 20.0f, 0.0f }
			);

			float result = square.perimeter();

			Assert::AreEqual(240.0f, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_diagonalLength_Test)
		{
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 0.0f, 100.0f },
				{ 20.0f, 100.0f },
				{ 20.0f, 0.0f }
			);

			float result = square.diagonalLength();

			Assert::AreEqual(101.980392f, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_getColisionStatus_Inside1_Test)
		{
			Vec2f point = Vec2f(10.0f, 10.0f);
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f }, 
				{ 0.0f, 100.0f },
				{ 100.0f, 100.0f },
				{ 100.0f, 0.0f }
			);

			ColisionStatus result = square.getSatusColision(point);

			if (result != ColisionStatus::INSIDE)
				Assert::Fail(L"Point should be inside the square.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_getColisionStatus_Inside2_Test)
		{
			Vec2f point = Vec2f(100.0f, 60.0f);
			Rectangle2Df square = Rectangle2Df(
				{ 10.0f, 10.0f },
				{ 210.0f, 10.0f },
				{ 210.0f, 110.0f },
				{ 10.0f, 110.0f }
			);

			ColisionStatus result = square.getSatusColision(point);

			if (result != ColisionStatus::INSIDE)
				Assert::Fail(L"Point should be inside the square.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_getColisionStatus_Outside_Test)
		{
			Vec2f point = Vec2f(200.0f, 200.0f);
			Rectangle2Df rect = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 0.0f, 100.0f },
				{ 100.0f, 100.0f },
				{ 100.0f, 0.0f }
			);

			ColisionStatus result = rect.getSatusColision(point);

			if (result != ColisionStatus::OUTSIDE)
				Assert::Fail(L"Point should be inside the square.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_hasIntersection_Line_True_Test)
		{
			Line2Df line = Line2Df(Vec2f(50.0f, 0.0f), Vec2f(50.0f, 200.0f));
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 100.0f, 0.0f },
				{ 100.0f, 100.0f },
				{ 0.0f, 100.0f }				
			);

			bool result = square.hasIntersection(line);

			Assert::IsTrue(result, L"Line should cross the square.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_hasIntersection_Line_False_Test)
		{
			Line2Df line = Line2Df(Vec2f(110.0f, 0.0f), Vec2f(110.0f, 200.0f));
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 100.0f, 0.0f },
				{ 100.0f, 100.0f },
				{ 0.0f, 100.0f }
			);

			bool result = square.hasIntersection(line);

			Assert::IsFalse(result, L"Line should cross the square.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_hasIntersection_Triangle_True_Test)
		{
			Triangle2Df triangle = Triangle2Df(Vec2f(50.0f, 10.0f), Vec2f(150.0f, 200.0f), Vec2f(200.0f, 200.0f));
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 100.0f, 0.0f },
				{ 100.0f, 100.0f },
				{ 0.0f, 100.0f }
			);

			bool result = square.hasIntersection(triangle);

			Assert::IsTrue(result, L"Triangle should intersect the square.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_hasIntersection_Triangle_False_Test)
		{
			Triangle2Df triangle = Triangle2Df(Vec2f(120.0f, 110.0f), Vec2f(150.0f, 200.0f), Vec2f(200.0f, 200.0f));
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 100.0f, 0.0f },
				{ 100.0f, 100.0f },
				{ 0.0f, 100.0f }
			);

			bool result = square.hasIntersection(triangle);

			Assert::IsFalse(result, L"Triangle should intersect the square.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_hasIntersection_Circle_True_Test)
		{
			Circle2Df circle = Circle2Df(Vec2f(105.0f, 50.0f), 10.0f);
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 100.0f, 0.0f },
				{ 100.0f, 100.0f },
				{ 0.0f, 100.0f }
			);

			bool result = square.hasIntersection(circle);

			Assert::IsTrue(result, L"Rectangle should intersect the circle.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_hasIntersection_Circle_False_Test)
		{
			Circle2Df circle = Circle2Df(Vec2f(111.0f, 50.0f), 10.0f);
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 100.0f, 0.0f },
				{ 100.0f, 100.0f },
				{ 0.0f, 100.0f }
			);

			bool result = square.hasIntersection(circle);

			Assert::IsFalse(result, L"Rectangle should NOT intersect the circle.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_getBoundingBox_Test)
		{
			Vec2fList points;
			points.add(Vec2f(0.3f, 0.0f));
			points.add(Vec2f(1.0f, 0.3f));
			points.add(Vec2f(0.7f, 1.0f));
			points.add(Vec2f(0.0f, 0.7f));

			Rectangle2Df result = Rectangle2Df::getBoundingBox(points);

			Vec2f point1Expected = { 0.0f, 0.0f };
			Vec2f point2Expected = { 1.0f, 0.0f };
			Vec2f point3Expected = { 1.0f, 1.0f };
			Vec2f point4Expected = { 0.0f, 1.0f };

			Assert::AreEqual(point1Expected, result.point1, L"Wring value.", LINE_INFO());
			Assert::AreEqual(point2Expected, result.point2, L"Wring value.", LINE_INFO());
			Assert::AreEqual(point3Expected, result.point3, L"Wring value.", LINE_INFO());
			Assert::AreEqual(point4Expected, result.point4, L"Wring value.", LINE_INFO());
		}

	};
}