#pragma once

#include "CppUnitTest.h"
#include <Plane3D.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Point3D.h>
#include "Asserts.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(Plane3DTest)
	{
	public:

		TEST_METHOD(Plane3D_ContructorWithThreePoints_Test)
		{
			Point3Df point1 = { 2.0f, 1.0f, -1.0f };
			Point3Df point2 = { 0.0f, 1.0f, 2.0f };
			Point3Df point3 = { -1.0f, -1.0f, 3.0f };
			
			Vec3f normalVectorExpected = Vec3f(0.824163377f, -0.137360558f, 0.549442232f);

			Plane3Df plane = Plane3Df(point1, point2, point3);

			Asserts::isCloseEnough(plane.normalVector[0], normalVectorExpected[0], 0.0009f, "Wrong value", LINE_INFO());
			Asserts::isCloseEnough(plane.normalVector[1], normalVectorExpected[1], 0.0009f, "Wrong value", LINE_INFO());
			Asserts::isCloseEnough(plane.normalVector[2], normalVectorExpected[2], 0.0009f, "Wrong value", LINE_INFO());

			Assert::AreEqual(point2.x, plane.point.x, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(point2.y, plane.point.y, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(point2.z, plane.point.z, L"Wrong value.", LINE_INFO());
		}
		
		TEST_METHOD(Plane3D_getEquation1_Test)
		{
			Point3Df point1 = { 2.0f, 1.0f, -1.0f };
			Point3Df point2 = { 0.0f, 1.0f, 2.0f };
			Point3Df point3 = { -1.0f, -1.0f, 3.0f };

			Vec4f expected = Vec4f(0.824163377f, -0.137360558f, 0.549442232f, -0.961523890f);

			Plane3Df plane = Plane3Df(point1, point2, point3);
			Vec4f components = plane.getEquation();

			for (size_t i = 0; i < 4; i++)
				Asserts::isCloseEnough(expected[0], components[0], 0.0009f, "Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Plane3D_getEquation2_Test)
		{
			Point3Df point = { 2.0f, 1.0f, -1.0f };
			Vec3f vector = { 1.0f, -2.0f, 3.0f };

			Vec4f expected = Vec4f(1.0f, -2.0f, 3.0f, 3.0f);

			Plane3Df plane = Plane3Df(point, vector);
			Vec4f components = plane.getEquation();

			for (size_t i = 0; i < 4; i++)
				Assert::AreEqual(expected[0], components[0], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Plane3D_getEquation3_Test)
		{
			Point3Df point1 = { 1.0f, 2.0f, 0.0f };
			Point3Df point2 = { 2.0f, 0.0f, -1.0f };
			Point3Df point3 = { 3.0f, -2.0f, -1.0f };

			Vec4f expected = Vec4f(-0.894427180f, -0.447213590f, 0.0f, 1.78885436f);

			Plane3Df plane = Plane3Df(point1, point2, point3);
			Vec4f components = plane.getEquation();

			for (size_t i = 0; i < 4; i++)
				Asserts::isCloseEnough(expected[0], components[0], 0.0009f, "Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Plane3D_findIntersection_Test)
		{
			Line3Df line = Line3Df(Point3Df{ 2.0f, 4.0f, 6.0f }, Point3Df{ 11.0f, 10.0f, 7.0f });
			Plane3Df plane = Plane3Df(Point3Df(1.0f, 10.0f, 5.0f), Point3Df(2.0f, 2.0f, 1.0f), Point3Df(4.0f, 4.0f, 1.0f));

			Point3Df expected = Point3Df(-13.8571415f, -6.57142735f, 4.23809528f);
						
			Point3Df* intersection = plane.findIntersection(line);

			Assert::IsNotNull(intersection, L"There should be an intersection", LINE_INFO());

			Asserts::isCloseEnough(expected.x, intersection->x, 0.0009f, "Wrong value", LINE_INFO());
			Asserts::isCloseEnough(expected.y, intersection->y, 0.0009f, "Wrong value", LINE_INFO());
			Asserts::isCloseEnough(expected.z, intersection->z, 0.0009f, "Wrong value", LINE_INFO());
		}

	};
}