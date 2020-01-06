#pragma once

#include "CppUnitTest.h"
#include <Vec3.h>
#include <Line3D.h>
#include <AABB.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(Line3DTest)
	{
	public:

		TEST_METHOD(Line3D_centerOfSegment_Test1)
		{
			Line3D line = Line3D(Vec3f{ 2.0f, 2.0f, 2.0f }, Vec3f{ 4.0f, 4.0f, 2.0f });

			Vec3f center = line.centerOfSegment();
			Vec3f expected = Vec3f(3.0f, 3.0f, 2.0f);

			for (int i = 0; i < 3; i++)
				Assert::AreEqual(expected[i], center[i], L"wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_lengthOfSegment_Test1)
		{
			Line3D line = Line3D(Vec3f{ 2.0f, 2.0f, 2.0f }, Vec3f{ 4.0f, 4.0f, 4.0f });

			float result = line.lengthOfSegment();
			float expected = 3.46410f;

			Assert::IsTrue(isCloseEnough(expected, result), L"wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_hasIntersectionOnSegment_AABB_Test1)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Line3D line = Line3D(Vec3f{ -5.0f, 5.0f, 6.0f }, Vec3f{ 20.0f, 5.0f, 6.0f });

			CollisionStatus result = line.hasIntersectionOnSegment(aabb);

			Assert::IsTrue(result == CollisionStatus::INSIDE, L"Ther should have a intersection.", LINE_INFO());			
		}

		TEST_METHOD(Line3D_hasIntersectionOnSegment_AABB_Test2)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Line3D line = Line3D(Vec3f{ -5.0f, 5.0f, 6.0f }, Vec3f{ -1.0f, 5.0f, 6.0f });

			CollisionStatus result = line.hasIntersectionOnSegment(aabb);

			Assert::IsTrue(result == CollisionStatus::OUTSIDE, L"Ther should have a intersection.", LINE_INFO());
		}

		TEST_METHOD(Line3D_hasIntersectionOnSegment_AABB_Test3)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Line3D line = Line3D(Vec3f{ 5.0f, 5.0f, 6.0f }, Vec3f{ 2.0f, 5.0f, 6.0f });

			CollisionStatus result = line.hasIntersectionOnSegment(aabb);

			Assert::IsTrue(result == CollisionStatus::INSIDE, L"Ther should have a intersection.", LINE_INFO());
		}

		TEST_METHOD(Line3D_hasIntersectionOnSegment_AABB_Test4)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Line3D line = Line3D(Vec3f{ 11.0f, 5.0f, 6.0f }, Vec3f{ 20.0f, 5.0f, 6.0f });

			CollisionStatus result = line.hasIntersectionOnSegment(aabb);

			Assert::IsTrue(result == CollisionStatus::OUTSIDE, L"Ther should have a intersection.", LINE_INFO());
		}

		TEST_METHOD(Line3D_hasIntersectionOnSegment_AABB_Test5)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Line3D line = Line3D(Vec3f{ -1.0f, 0.0f, 0.0f }, Vec3f{ -1.0f, 30.0f, 0.0f });

			CollisionStatus result = line.hasIntersectionOnSegment(aabb);

			Assert::IsTrue(result == CollisionStatus::OUTSIDE, L"Ther should have a intersection.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnRay_AABB_Test1)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Line3D line = Line3D(Vec3f{ -5.0f, 5.0f, 6.0f }, Vec3f{ 20.0f, 5.0f, 6.0f });

			DetailedCollisionStatus<float> result = line.findIntersectionOnRay(aabb);

			Vec3f expectedPoint1 = Vec3f(0.0f, 5.0f, 6.0f);
			Vec3f expectedPoint2 = Vec3f(10.0f, 5.0f, 6.0f);

			Assert::IsTrue(result.status == CollisionStatus::INSIDE, L"Ther should have a intersection.", LINE_INFO());
			Assert::AreEqual(2, result.pointsCount, L"Ther should have a intersection.", LINE_INFO());
			
			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedPoint1[i], result.points[0][i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedPoint2[i], result.points[1][i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(Line3D_findIntersectionOnRay_AABB_Test2)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Line3D line = Line3D(Vec3f{ -5.0f, 15.0f, 6.0f }, Vec3f{ 20.0f, 15.0f, 6.0f });

			DetailedCollisionStatus<float> result = line.findIntersectionOnRay(aabb);
			
			Assert::IsTrue(result.status == CollisionStatus::OUTSIDE, L"Ther should NOT have a intersection.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnRay_AABB_Test3)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Line3D line = Line3D(Vec3f{ -5.0f, 5.0f, 6.0f }, Vec3f{ 10.0f, 25.0f, 6.0f });

			DetailedCollisionStatus<float> result = line.findIntersectionOnRay(aabb);

			Assert::IsTrue(result.status == CollisionStatus::OUTSIDE, L"Ther should NOT have a intersection.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnRay_AABB_Test4)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Line3D line = Line3D(Vec3f{ 20.0f, 5.0f, 6.0f }, Vec3f{ 30.0f, 5.0f, 6.0f });

			DetailedCollisionStatus<float> result = line.findIntersectionOnRay(aabb);

			Assert::IsTrue(result.status == CollisionStatus::OUTSIDE, L"Ther should NOT have a intersection.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnRay_AABB_Test5)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Line3D line = Line3D(Vec3f{ 20.0f, 5.0f, 6.0f }, Vec3f{ -5.0f, 5.0f, 6.0f });

			DetailedCollisionStatus<float> result = line.findIntersectionOnRay(aabb);

			Vec3f expectedPoint1 = Vec3f(10.0f, 5.0f, 6.0f);

			Assert::IsTrue(result.status == CollisionStatus::INSIDE, L"Ther should have a intersection.", LINE_INFO());
			Assert::AreEqual(2, result.pointsCount, L"Ther should have a intersection.", LINE_INFO());

			for (int i = 0; i < 3; i++)
				Assert::AreEqual(expectedPoint1[i], result.points[0][i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnRay_AABB_Test6)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Line3D line = Line3D(Vec3f{ 3.0f, 3.0f, 6.0f }, Vec3f{ 15.0f, 3.0f, 6.0f });

			DetailedCollisionStatus<float> result = line.findIntersectionOnRay(aabb);

			Vec3f expectedPoint1 = Vec3f(3.0f, 3.0f, 6.0f);
			Vec3f expectedPoint2 = Vec3f(10.0f, 3.0f, 6.0f);

			Assert::IsTrue(result.status == CollisionStatus::INSIDE, L"Ther should have a intersection.", LINE_INFO());
			Assert::AreEqual(2, result.pointsCount, L"Ther should have a intersection.", LINE_INFO());

			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(expectedPoint1[i], result.points[0][i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedPoint2[i], result.points[1][i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(Line3D_hasIntersectionOnRay_sphere_Test1)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Line3D line = Line3D(Vec3f{ -20.0f, 0.0f, 0.0f }, Vec3f{ 20.0f, 0.0f, 0.0f });
			
			bool result = line.hasIntersectionOnRay(sphere);

			Assert::IsTrue(result, L"Ther should have a intersection.", LINE_INFO());
		}

		TEST_METHOD(Line3D_hasIntersectionOnRay_sphere_Test2)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Line3D line = Line3D(Vec3f{ 15.0f, 0.0f, 0.0f }, Vec3f{ 20.0f, 0.0f, 0.0f });

			bool result = line.hasIntersectionOnRay(sphere);

			Assert::IsFalse(result, L"Ther should NOT have a intersection.", LINE_INFO());
		}

		TEST_METHOD(Line3D_hasIntersectionOnRay_sphere_Test3)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Line3D line = Line3D(Vec3f{ -15.0f, 0.0f, 0.0f }, Vec3f{ -11.0f, 0.0f, 0.0f });

			bool result = line.hasIntersectionOnRay(sphere);

			Assert::IsTrue(result, L"Ther SHOULD have a intersection because it is a RAY.", LINE_INFO());
		}

		TEST_METHOD(Line3D_isOnSegment_point_Test1)
		{
			Line3D line = Line3D(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(5.0f, 0.0f, 0.0f);

			bool result = line.isOnSegment(point);

			Assert::IsTrue(result, L"Point should be on segment.", LINE_INFO());
		}

		TEST_METHOD(Line3D_isOnSegment_point_Test2)
		{
			Line3D line = Line3D(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(-1.0f, 0.0f, 0.0f);

			bool result = line.isOnSegment(point);

			Assert::IsFalse(result, L"Point should NOT be on segment.", LINE_INFO());
		}

		TEST_METHOD(Line3D_isOnSegment_point_Test3)
		{
			Line3D line = Line3D(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(11.0f, 0.0f, 0.0f);

			bool result = line.isOnSegment(point);

			Assert::IsFalse(result, L"Point should NOT be on segment.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnSegment_sphere_Test1)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Line3D line = Line3D(Vec3f{ -20.0f, 0.0f, 0.0f }, Vec3f{ 20.0f, 0.0f, 0.0f });

			Vec3f expectedPoint1 = { -10.0f, 0.0f, 0.0f };
			Vec3f expectedPoint2 = { 10.0f, 0.0f, 0.0f };

			DetailedCollisionStatus<float> result = line.findIntersectionOnSegment(sphere);

			Assert::IsTrue(result.status == CollisionStatus::INSIDE, L"There should be 2 intersection points.", LINE_INFO());
			Assert::AreEqual(result.pointsCount, 2, L"There should be 2 intersection points.", LINE_INFO());

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedPoint1[i], result.points[0][i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedPoint2[i], result.points[1][i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(Line3D_findIntersectionOnSegment_sphere_Test2)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Line3D line = Line3D(Vec3f{ -20.0f, 0.0f, 0.0f }, Vec3f{ 0.0f, 0.0f, 0.0f });

			Vec3f expectedPoint1 = { -10.0f, 0.0f, 0.0f };

			DetailedCollisionStatus<float> result = line.findIntersectionOnSegment(sphere);

			Assert::IsTrue(result.status == CollisionStatus::INSIDE, L"There should be 1 intersection points.", LINE_INFO());
			Assert::AreEqual(result.pointsCount, 1, L"There should be 1 intersection points.", LINE_INFO());

			for (int i = 0; i < 3; i++)
				Assert::AreEqual(expectedPoint1[i], result.points[0][i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnSegment_sphere_Test3)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Line3D line = Line3D(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 20.0f, 0.0f, 0.0f });

			Vec3f expectedPoint1 = { 0.0f, 0.0f, 0.0f };
			Vec3f expectedPoint2 = { 10.0f, 0.0f, 0.0f };

			DetailedCollisionStatus<float> result = line.findIntersectionOnSegment(sphere);

			Assert::IsTrue(result.status == CollisionStatus::INSIDE, L"There should be 2 intersection points.", LINE_INFO());
			Assert::AreEqual(result.pointsCount, 2, L"There should be 2 intersection points.", LINE_INFO());

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedPoint1[i], result.points[0][i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedPoint2[i], result.points[1][i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(Line3D_findIntersectionOnSegment_sphere_Test4)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Line3D line = Line3D(Vec3f{ -20.0f, 0.0f, 0.0f }, Vec3f{ -12.0f, 0.0f, 0.0f });

			DetailedCollisionStatus<float> result = line.findIntersectionOnSegment(sphere);

			Assert::IsTrue(result.status == CollisionStatus::OUTSIDE, L"There should be 0 intersection points.", LINE_INFO());
			Assert::AreEqual(result.pointsCount, 0, L"There should be 0 intersection points.", LINE_INFO());
			Assert::IsNull(result.points, L"There should be 0 intersection points.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnRay_sphere_Test1)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Line3D line = Line3D(Vec3f{ -20.0f, 0.0f, 0.0f }, Vec3f{ -12.0f, 0.0f, 0.0f });

			Vec3f expectedPoint1 = { -10.0f, 0.0f, 0.0f };
			Vec3f expectedPoint2 = {  10.0f, 0.0f, 0.0f };

			DetailedCollisionStatus<float> result = line.findIntersectionOnRay(sphere);

			Assert::IsTrue(result.status == CollisionStatus::INSIDE, L"There should be 2 intersection points.", LINE_INFO());
			Assert::AreEqual(result.pointsCount, 2, L"There should be 2 intersection points.", LINE_INFO());

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedPoint1[i], result.points[0][i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedPoint2[i], result.points[1][i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(Line3D_findIntersectionOnRay_sphere_Test2)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Line3D line = Line3D(Vec3f{ -20.0f, 10.0f, 0.0f }, Vec3f{ -12.0f, 10.0f, 0.0f });

			Vec3f expectedPoint1 = { 0.0f, 10.0f, 0.0f };

			DetailedCollisionStatus<float> result = line.findIntersectionOnRay(sphere);

			Assert::IsTrue(result.status == CollisionStatus::INLINE, L"There should be 1 intersection points (tangent).", LINE_INFO());
			Assert::AreEqual(result.pointsCount, 1, L"There should be 2 intersection points.", LINE_INFO());

			for (int i = 0; i < 3; i++)
				Assert::AreEqual(expectedPoint1[i], result.points[0][i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnRay_sphere_Test3)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Line3D line = Line3D(Vec3f{ -20.0f, 11.0f, 0.0f }, Vec3f{ -12.0f, 11.0f, 0.0f });
			
			DetailedCollisionStatus<float> result = line.findIntersectionOnRay(sphere);

			Assert::IsTrue(result.status == CollisionStatus::OUTSIDE, L"There should be 0 intersection.", LINE_INFO());
			Assert::AreEqual(result.pointsCount, 0, L"There should be 0 intersection points.", LINE_INFO());
			Assert::IsNull(result.points, L"There should be 0 intersection points.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnSegment_plane_Test1)
		{
			Plane3D plane = Plane3D(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(-1.0f, 0.0f, 0.0f));
			Line3D line = Line3D(Vec3f{ -2.0f, 2.0f, 0.0f }, Vec3f{ 2.0f, 2.0f, 0.0f });

			Vec3f expected = { 0.0f, 2.0f, 0.0f };

			Vec3f* result = line.findIntersectionOnSegment(plane);

			Assert::IsNotNull(result, L"Point should not be null.", LINE_INFO());

			for (int i = 0; i < 3; i++)
				Assert::IsTrue(expected[i] == result[0][i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnSegment_plane_Test2)
		{
			Plane3D plane = Plane3D(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(-1.0f, 0.0f, 0.0f));
			Line3D line = Line3D(Vec3f{ -2.0f, 2.0f, 0.0f }, Vec3f{ -4.0f, 2.0f, 0.0f });
			
			Vec3f* result = line.findIntersectionOnSegment(plane);

			Assert::IsNull(result, L"Point should not be null.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersectionOnSegment_plane_Test3)
		{
			Plane3D plane = Plane3D(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(-1.0f, 0.0f, 0.0f));
			Line3D line = Line3D(Vec3f{ -2.0f, 2.0f, 0.0f }, Vec3f{ -1.0f, 2.0f, 0.0f });

			Vec3f* result = line.findIntersectionOnSegment(plane);

			Assert::IsNull(result, L"Point should not be null.", LINE_INFO());
		}

		TEST_METHOD(Line3D_findIntersection_Test)
		{
			Line3D line1 = Line3D( Vec3f{ 6.0f, 8.0f, 4.0f }, Vec3f{ 12.0f, 15.0f, 4.0f });
			Line3D line2 = Line3D(Vec3f{ 6.0f, 8.0f, 2.0f }, Vec3f{ 12.0f, 15.0f, 6.0f });
			
			Vec3f expected = { 9.0f, 11.5f, 4.0f };

			Vec3f* result = line1.findIntersection(line2);

			Assert::IsNotNull(result, L"Value should not be null.", LINE_INFO());

			Assert::AreEqual(expected.x, result->x, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.y, result->y, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.z, result->z, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_closestPointOnTheLine_point_Test1)
		{
			Line3D line = Line3D(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(7.0f, 10.0f, 0.0f);

			Vec3f expected = { 7.0f, 0.0f, 0.0f };

			Vec3f result = line.closestPointOnTheLine(point);
			
			Assert::AreEqual(expected.x, result.x, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.y, result.y, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.z, result.z, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_closestPointOnTheLine_point_Test2)
		{
			Line3D line = Line3D(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(-3.0f, 10.0f, 0.0f);

			Vec3f expected = { 0.0f, 0.0f, 0.0f };

			Vec3f result = line.closestPointOnTheLine(point);

			Assert::AreEqual(expected.x, result.x, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.y, result.y, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.z, result.z, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_closestPointOnTheLine_point_Test3)
		{
			Line3D line = Line3D(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(11.0f, 10.0f, 0.0f);

			Vec3f expected = { 10.0f, 0.0f, 0.0f };

			Vec3f result = line.closestPointOnTheLine(point);

			Assert::AreEqual(expected.x, result.x, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.y, result.y, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expected.z, result.z, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_squaredDistance_point_Test1)
		{
			Line3D line = Line3D(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(5.0f, 10.0f, 0.0f);

			float expected = 100.0f;

			float result = line.squaredDistance(point);

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Line3D_distance_point_Test1)
		{
			Line3D line = Line3D(Vec3f{ 0.0f, 0.0f, 0.0f }, Vec3f{ 10.0f, 0.0f, 0.0f });
			Vec3f point = Vec3f(5.0f, 10.0f, 0.0f);

			float expected = 10.0f;

			float result = line.distance(point);

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

	};
}