#pragma once

#include "TestHeader.h"

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
			Point2Df point = Point2Df(10.0f, 10.0f);
			Rectangle2Df square = Rectangle2Df(
				{ 0.0f, 0.0f }, 
				{ 0.0f, 100.0f },
				{ 100.0f, 100.0f },
				{ 100.0f, 0.0f }
			);

			Colision2DStatus result = square.getSatusColision(point);

			if (result != Colision2DStatus::INSIDE)
				Assert::Fail(L"Point should be inside the square.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_getColisionStatus_Inside2_Test)
		{
			Point2Df point = Point2Df(100.0f, 60.0f);
			Rectangle2Df square = Rectangle2Df(
				{ 10.0f, 10.0f },
				{ 210.0f, 10.0f },
				{ 210.0f, 110.0f },
				{ 10.0f, 110.0f }
			);

			Colision2DStatus result = square.getSatusColision(point);

			if (result != Colision2DStatus::INSIDE)
				Assert::Fail(L"Point should be inside the square.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_getColisionStatus_Outside_Test)
		{
			Point2Df point = Point2Df(200.0f, 200.0f);
			Rectangle2Df rect = Rectangle2Df(
				{ 0.0f, 0.0f },
				{ 0.0f, 100.0f },
				{ 100.0f, 100.0f },
				{ 100.0f, 0.0f }
			);

			Colision2DStatus result = rect.getSatusColision(point);

			if (result != Colision2DStatus::OUTSIDE)
				Assert::Fail(L"Point should be inside the square.", LINE_INFO());
		}

		TEST_METHOD(Rectangle2D_hasIntersection_Line_True_Test)
		{
			Line2Df line = Line2Df(Point2Df(50.0f, 0.0f), Point2Df(50.0f, 200.0f));
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
			Line2Df line = Line2Df(Point2Df(110.0f, 0.0f), Point2Df(110.0f, 200.0f));
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
			Triangle2Df triangle = Triangle2Df(Point2Df(50.0f, 10.0f), Point2Df(150.0f, 200.0f), Point2Df(200.0f, 200.0f));
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
			Triangle2Df triangle = Triangle2Df(Point2Df(120.0f, 110.0f), Point2Df(150.0f, 200.0f), Point2Df(200.0f, 200.0f));
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
			Circle2Df circle = Circle2Df(Point2Df(105.0f, 50.0f), 10.0f);
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
			Circle2Df circle = Circle2Df(Point2Df(111.0f, 50.0f), 10.0f);
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
			Point2Df point1 = { 0.3f, 0.0f };
			Point2Df point2 = { 1.0f, 0.3f };
			Point2Df point3 = { 0.7f, 1.0f };
			Point2Df point4 = { 0.0f, 0.7f };
			Point2Df points[] = { point1, point2, point3, point4 };

			Rectangle2Df result = Rectangle2Df::getBoundingBox(points, 4);

			Point2Df point1Expected = { 0.0f, 0.0f };
			Point2Df point2Expected = { 1.0f, 0.0f };
			Point2Df point3Expected = { 1.0f, 1.0f };
			Point2Df point4Expected = { 0.0f, 1.0f };

			Assert::AreEqual(point1Expected, result.point1, L"Wring value.", LINE_INFO());
			Assert::AreEqual(point2Expected, result.point2, L"Wring value.", LINE_INFO());
			Assert::AreEqual(point3Expected, result.point3, L"Wring value.", LINE_INFO());
			Assert::AreEqual(point4Expected, result.point4, L"Wring value.", LINE_INFO());
		}

	};
}