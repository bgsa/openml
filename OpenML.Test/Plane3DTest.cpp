#pragma once

#include "CppUnitTest.h"
#include <Plane3D.h>
#include <Vec3.h>
#include <Vec4.h>
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
			Vec3f point1 = { 2.0f, 1.0f, -1.0f };
			Vec3f point2 = { 0.0f, 1.0f, 2.0f };
			Vec3f point3 = { -1.0f, -1.0f, 3.0f };
			
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
			Vec3f point1 = { 2.0f, 1.0f, -1.0f };
			Vec3f point2 = { 0.0f, 1.0f, 2.0f };
			Vec3f point3 = { -1.0f, -1.0f, 3.0f };

			Vec4f expected = Vec4f(0.824163377f, -0.137360558f, 0.549442232f, -0.961523890f);

			Plane3Df plane = Plane3Df(point1, point2, point3);
			Vec4f components = plane.getEquation();

			for (size_t i = 0; i < 4; i++)
				Asserts::isCloseEnough(expected[0], components[0], 0.0009f, "Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Plane3D_getEquation2_Test)
		{
			Vec3f point = { 2.0f, 1.0f, -1.0f };
			Vec3f vector = { 1.0f, -2.0f, 3.0f };

			Vec4f expected = Vec4f(1.0f, -2.0f, 3.0f, 3.0f);

			Plane3Df plane = Plane3Df(point, vector);
			Vec4f components = plane.getEquation();

			for (size_t i = 0; i < 4; i++)
				Assert::AreEqual(expected[0], components[0], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Plane3D_getEquation3_Test)
		{
			Vec3f point1 = { 1.0f, 2.0f, 0.0f };
			Vec3f point2 = { 2.0f, 0.0f, -1.0f };
			Vec3f point3 = { 3.0f, -2.0f, -1.0f };

			Vec4f expected = Vec4f(-0.894427180f, -0.447213590f, 0.0f, 1.78885436f);

			Plane3Df plane = Plane3Df(point1, point2, point3);
			Vec4f components = plane.getEquation();

			for (size_t i = 0; i < 4; i++)
				Asserts::isCloseEnough(expected[0], components[0], 0.0009f, "Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Plane3D_findIntersection_Test)
		{
			Line3Df line = Line3Df(Vec3f{ 2.0f, 4.0f, 6.0f }, Vec3f{ 11.0f, 10.0f, 7.0f });
			Plane3Df plane = Plane3Df(Vec3f(1.0f, 10.0f, 5.0f), Vec3f(2.0f, 2.0f, 1.0f), Vec3f(4.0f, 4.0f, 1.0f));

			Vec3f  expected = Vec3f(-13.8571415f, -6.57142735f, 4.23809528f);

			Vec3f* intersection = plane.findIntersection(line);

			Assert::IsNotNull(intersection, L"There should be an intersection", LINE_INFO());

			Asserts::isCloseEnough(expected.x, intersection->x, 0.0009f, "Wrong value", LINE_INFO());
			Asserts::isCloseEnough(expected.y, intersection->y, 0.0009f, "Wrong value", LINE_INFO());
			Asserts::isCloseEnough(expected.z, intersection->z, 0.0009f, "Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_angle_Test1)
		{
			Plane3Df plane1 = Plane3Df(Vec3f(1.0f, 1.0f, 1.0f), Vec3f(1.0f, 1.0f, 1.0f).normalize());
			Plane3Df plane2 = Plane3Df(Vec3f(1.0f, 1.0f, 1.0f), Vec3f(1.0f, -2.0f, 3.0f).normalize());

			Vec4f a = plane1.getEquation();
			Vec4f b = plane2.getEquation();

			float expected = 0.308606714f;
			float result = plane1.angle(plane2);

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_angle_Test2)
		{
			Plane3Df plane1 = Plane3Df(2.0f, 4.0f, 1.0f, 3.0f);
			Plane3Df plane2 = Plane3Df(-1.0f, 3.0f, 2.0f, 1.0f);

			float expected = 0.6998542122f;
			float result = plane1.angle(plane2);

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_distance_point_Test1)
		{
			Plane3Df plane = Plane3Df(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f));
			Vec3f point = Vec3f(0.0f, 0.0f, 10.0f);

			float expected = 10.0f;
			float result = plane.distance(point);

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_distance_point_Test2)
		{
			Plane3Df plane = Plane3Df(Vec3f(0.0f, 0.0f, 8.0f), Vec3f(0.0f, 0.0f, 1.0f));
			Vec3f point = Vec3f(0.0f, 0.0f, 10.0f);

			float expected = 2.0f;
			float result = plane.distance(point);

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_distance_point_Test3)
		{
			Plane3Df plane = Plane3Df(Vec3f(0.0f, 0.0f, -4.0f), Vec3f(0.0f, 0.0f, 1.0f));
			Vec3f point = Vec3f(0.0f, 0.0f, 10.0f);

			float expected = 14.0f;
			float result = plane.distance(point);

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_distance_point_Test4)
		{
			Plane3Df plane = Plane3Df(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 1.0f));
			Vec3f point = Vec3f(0.0f, 0.0f, 10.0f);

			float expected = 7.07106781f;
			float result = plane.distance(point);

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_closestPointOnThePlane_point_Test1)
		{
			Plane3Df plane = Plane3Df(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f));
			Vec3f point = Vec3f(10.0f, 5.0f, -10.0f);

			Vec3f expected = Vec3f(10.0f, 5.0f, 0.0f);;

			Vec3f result = plane.closestPointOnThePlane(point);

			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_constructor_equation_Test)
		{
			Plane3Df plane = Plane3Df(1.0f, 5.0f, 3.0f, 13.0f);
			Vec3f point = Vec3f(2.0f, 4.0f, 1.0f);

			float expected = 6.42317247f;
			float result = plane.distance(point);
			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());

			plane = Plane3Df(2.0f, -2.0f, 5.0f, 8.0f);
			point = Vec3f(4.0f, -4.0f, 3.0f);
			expected = 6.78902864f;
			result = plane.distance(point);
			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
			
			plane = Plane3Df(2.0f, -2.0f, -1.0f, 3.0f);
			point = Vec3f(2.0f, -1.0f, 2.0f);			
			expected = 2.33333325f;
			result = plane.distance(point);
			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());

			plane = Plane3Df(1.0f, 1.0f, 1.0f, 0.0f);
			point = Vec3f(3.0f, -1.0f, 4.0f);
			expected = 3.46410179f;
			result = plane.distance(point);
			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());

			plane = Plane3Df(4.0f, -1.0f, 1.0f, 5.0f);
			point = Vec3f(1.0f, 3.0f, -6.0f);
			expected = 0.0f;
			result = plane.distance(point);
			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_orientation_Test1)
		{
			Vec3f point1 = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f point2 = Vec3f(1.0f, 0.0f, 0.0f);
			Vec3f point3 = Vec3f(1.0f, 1.0f, 0.0f);

			Plane3Df plane = Plane3Df(point1, point2, point3);
			Vec3f targetPoint = Vec3f(0.0f, 0.0f, 10.0f);

			Orientation result = plane.orientation(targetPoint);

			Assert::IsTrue(result == Orientation::LEFT, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_orientation_Test2)
		{
			Vec3f point1 = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f point2 = Vec3f(1.0f, 0.0f, 0.0f);
			Vec3f point3 = Vec3f(1.0f, 1.0f, 0.0f);

			Plane3Df plane = Plane3Df(point1, point2, point3);
			Vec3f targetPoint = Vec3f(0.0f, 0.0f, -10.0f);

			Orientation result = plane.orientation(targetPoint);

			Assert::IsTrue(result == Orientation::RIGHT, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_orientation_Test3)
		{
			Vec3f point1 = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f point2 = Vec3f(1.0f, 0.0f, 0.0f);
			Vec3f point3 = Vec3f(1.0f, 1.0f, 0.0f);

			Plane3Df plane = Plane3Df(point1, point2, point3);
			Vec3f targetPoint = Vec3f(-10.0f, 10.0f, 0.0f);

			Orientation result = plane.orientation(targetPoint);

			Assert::IsTrue(result == Orientation::NONE, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_isParallel_Test1)
		{
			Vec3f point1 = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f point2 = Vec3f(1.0f, 0.0f, 0.0f);
			Vec3f point3 = Vec3f(1.0f, 1.0f, 0.0f);

			Plane3Df plane1 = Plane3Df(point1, point2, point3);

			point1 = Vec3f(0.0f, 0.0f, 10.0f);
			point2 = Vec3f(1.0f, 0.0f, 10.0f);
			point3 = Vec3f(1.0f, 1.0f, 10.0f);

			Plane3Df plane2 = Plane3Df(point1, point2, point3);

			bool result = plane1.isParallel(plane2);

			Assert::IsTrue(result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_isParallel_Test2)
		{
			Vec3f point1 = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f point2 = Vec3f(1.0f, 0.0f, 0.0f);
			Vec3f point3 = Vec3f(1.0f, 1.0f, 0.0f);

			Plane3Df plane1 = Plane3Df(point1, point2, point3);

			point1 = Vec3f(0.0f, 0.0f, -10.0f);
			point2 = Vec3f(3.0f, 10.0f, -10.0f);
			point3 = Vec3f(-4.0f, -1.0f, -10.0f);

			Plane3Df plane2 = Plane3Df(point1, point2, point3);

			bool result = plane1.isParallel(plane2);

			Assert::IsTrue(result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_isParallel_Test3)
		{
			Vec3f point1 = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f point2 = Vec3f(1.0f, 0.0f, 0.0f);
			Vec3f point3 = Vec3f(1.0f, 1.0f, 0.0f);

			Plane3Df plane1 = Plane3Df(point1, point2, point3);

			point1 = Vec3f(0.0f, 0.0f, -10.0f);
			point2 = Vec3f(3.0f, 10.0f, 5.0f);
			point3 = Vec3f(-4.0f, -1.0f, 10.0f);

			Plane3Df plane2 = Plane3Df(point1, point2, point3);

			bool result = plane1.isParallel(plane2);

			Assert::IsFalse(result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_isPerpendicular_Test1)
		{
			Vec3f point1 = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f point2 = Vec3f(1.0f, 0.0f, 0.0f);
			Vec3f point3 = Vec3f(1.0f, 1.0f, 0.0f);

			Plane3Df plane1 = Plane3Df(point1, point2, point3);

			point1 = Vec3f(0.0f, 0.0f, 0.0f);
			point2 = Vec3f(1.0f, 0.0f, 0.0f);
			point3 = Vec3f(1.0f, 0.0f, 1.0f);

			Plane3Df plane2 = Plane3Df(point1, point2, point3);

			bool result = plane1.isPerpendicular(plane2);

			Assert::IsTrue(result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_isPerpendicular_Test2)
		{
			Vec3f point1 = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f point2 = Vec3f(1.0f, 0.0f, 0.0f);
			Vec3f point3 = Vec3f(1.0f, 1.0f, 0.0f);

			Plane3Df plane1 = Plane3Df(point1, point2, point3);

			point1 = Vec3f(0.0f, 0.0f, 0.0f);
			point2 = Vec3f(1.0f, 1.0f, 0.0f);
			point3 = Vec3f(1.0f, 0.0f, 1.0f);

			Plane3Df plane2 = Plane3Df(point1, point2, point3);

			bool result = plane1.isPerpendicular(plane2);

			Assert::IsFalse(result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Plane3D_findIntersection_plane_Test1)
		{
			Plane3Df plane1 = Plane3Df(2.0f, 3.0f, 1.0f, 3.0f);
			Plane3Df plane2 = Plane3Df(-1.0f, 1.0f, 1.0f, 2.0f);

			Line3Df* result = plane1.findIntersection(plane2);

			Assert::IsNotNull(result, L"Line should not be null!", LINE_INFO());

			Vec3f expectedPoint1 = Vec3f(0.315789491f, -0.973684311f, -0.710526347f);
			Vec3f expectedPoint2 = Vec3f(0.624396205f, -1.43659437f, 0.0609903336f);
			
			for (size_t i = 0; i < 3; i++) 
			{
				Assert::AreEqual(result->point1[i], expectedPoint1[i], L"Wrong value", LINE_INFO());
				Assert::AreEqual(result->point2[i], expectedPoint2[i], L"Wrong value", LINE_INFO());
			}

		}
	};
}