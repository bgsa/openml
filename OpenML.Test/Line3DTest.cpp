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

		TEST_METHOD(Line3D_closestPointOnTheLine_point_Test1)
		{
			Line3Df line = Line3Df(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(7.0f, 10.0f, 0.0f);

			Vec3f expected = { 7.0f, 0.0f, 0.0f };

			Vec3f result = line.closestPointOnTheLine(point);
			
			Assert::AreEqual(expected.x(), result.x(), L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.y(), result.y(), L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.z(), result.z(), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_closestPointOnTheLine_point_Test2)
		{
			Line3Df line = Line3Df(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(-3.0f, 10.0f, 0.0f);

			Vec3f expected = { 0.0f, 0.0f, 0.0f };

			Vec3f result = line.closestPointOnTheLine(point);

			Assert::AreEqual(expected.x(), result.x(), L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.y(), result.y(), L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.z(), result.z(), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_closestPointOnTheLine_point_Test3)
		{
			Line3Df line = Line3Df(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(11.0f, 10.0f, 0.0f);

			Vec3f expected = { 10.0f, 0.0f, 0.0f };

			Vec3f result = line.closestPointOnTheLine(point);

			Assert::AreEqual(expected.x(), result.x(), L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.y(), result.y(), L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.z(), result.z(), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_squaredDistance_point_Test1)
		{
			Line3Df line = Line3Df(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(5.0f, 10.0f, 0.0f);

			float expected = 100.0f;

			float result = line.squaredDistance(point);

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_distance_point_Test1)
		{
			Line3Df line = Line3Df(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(5.0f, 10.0f, 0.0f);

			float expected = 10.0f;

			float result = line.distance(point);

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

	};
}