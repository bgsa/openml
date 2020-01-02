#pragma once

#include "CppUnitTest.h"
#include <AABB.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(AABBTest)
	{
	public:

		TEST_METHOD(AABB_constructor_empty_Test)
		{
			AABB aabb = AABB();

			for (size_t i = 0; i < 3; i++)
			{
				Assert::AreEqual(Vec3f(-0.5f, -0.5f, -0.5f)[i], aabb.minPoint[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(Vec3f(0.5f, 0.5f, 0.5f)[i], aabb.maxPoint[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(AABB_constructor_twoPoints_Test)
		{
			Vec3f minPoint = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f maxPoint = Vec3f(10.0f, 10.0f, 10.0f);

			AABB aabb = AABB(minPoint, maxPoint);

			for (size_t i = 0; i < 3; i++)
			{
				Assert::AreEqual(aabb.minPoint[i], minPoint[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(aabb.maxPoint[i], maxPoint[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(AABB_constructor_minPointAndDistances_Test)
		{
			Vec3f minPoint = Vec3f(10.0f, 20.0f, 30.0f);
			AABB aabb = AABB(minPoint, 10.0f, 12.0f, 15.0f);
			Vec3f maxPointExpected = Vec3f(20.0f, 32.0f, 45.0f);

			for (size_t i = 0; i < 3; i++)
			{
				Assert::AreEqual(aabb.minPoint[i], minPoint[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(aabb.maxPoint[i], maxPointExpected[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(AABB_center_Test)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));

			Vec3f result = aabb.center();

			Vec3f expected = Vec3f(5.0f, 5.0f, 5.0f);

			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(expected[i], result[i], L"wrong value!.", LINE_INFO());
		}

		TEST_METHOD(AABB_collisionStatus_AABB_Test)
		{
			//Check on X axis
			AABB aabb1 = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			AABB aabb2 = AABB(Vec3f(10.0f, 10.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			CollisionStatus result = aabb1.collisionStatus(aabb2);
			Assert::IsTrue(result == CollisionStatus::INSIDE, L"Mistake!.", LINE_INFO());

			aabb1 = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABB(Vec3f(9.0f, 10.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.collisionStatus(aabb2);
			Assert::IsTrue(result == CollisionStatus::INSIDE, L"Mistake!.", LINE_INFO());

			aabb1 = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABB(Vec3f(11.0f, 10.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.collisionStatus(aabb2);
			Assert::IsTrue(result == CollisionStatus::OUTSIDE, L"Mistake!.", LINE_INFO());

			//Check on Y axis
			aabb1 = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABB(Vec3f(0.0f, 10.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.collisionStatus(aabb2);
			Assert::IsTrue(result == CollisionStatus::INSIDE, L"Mistake!.", LINE_INFO());

			aabb1 = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABB(Vec3f(0.0f, 11.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.collisionStatus(aabb2);
			Assert::IsTrue(result == CollisionStatus::OUTSIDE, L"Mistake!.", LINE_INFO());

			//Check on z axis
			aabb1 = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABB(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.collisionStatus(aabb2);
			Assert::IsTrue(result == CollisionStatus::INSIDE, L"Mistake!.", LINE_INFO());

			aabb1 = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABB(Vec3f(0.0f, 0.0f, 11.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.collisionStatus(aabb2);
			Assert::IsTrue(result == CollisionStatus::OUTSIDE, L"Mistake!.", LINE_INFO());
		}

		TEST_METHOD(AABB_collisionStatus_Plane_Test)
		{
			Plane3D plane = Plane3D(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			CollisionStatus result = aabb.collisionStatus(plane);
			CollisionStatus expected = CollisionStatus::INLINE;
			Assert::IsTrue(result == expected, L"Mistake!.", LINE_INFO());

			aabb = AABB(Vec3f(0.0f, 1.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			result = aabb.collisionStatus(plane);
			expected = CollisionStatus::OUTSIDE;
			Assert::IsTrue(result == expected, L"Mistake!.", LINE_INFO());

			aabb = AABB(Vec3f(0.0f, -1.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			result = aabb.collisionStatus(plane);
			expected = CollisionStatus::INSIDE;
			Assert::IsTrue(result == expected, L"Mistake!.", LINE_INFO());
		}

		TEST_METHOD(AABB_collisionStatus_Sphere_Test)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 20.0f, 0.0f), 10.0f);
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			CollisionStatus result = aabb.collisionStatus(sphere);
			CollisionStatus expected = CollisionStatus::INLINE;
			Assert::IsTrue(result == expected, L"Mistake!.", LINE_INFO());

			sphere = Sphere(Vec3f(0.0f, 18.0f, 0.0f), 10.0f);
			result = aabb.collisionStatus(sphere);
			expected = CollisionStatus::INSIDE;
			Assert::IsTrue(result == expected, L"Mistake!.", LINE_INFO());

			sphere = Sphere(Vec3f(0.0f, 22.0f, 0.0f), 10.0f);
			result = aabb.collisionStatus(sphere);
			expected = CollisionStatus::OUTSIDE;
			Assert::IsTrue(result == expected, L"Mistake!.", LINE_INFO());
		}

		TEST_METHOD(AABB_closestPointInAABB_Test1)
		{
			Vec3f minPoint = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f maxPoint = Vec3f(10.0f, 10.0f, 10.0f);
			AABB aabb = AABB(minPoint, maxPoint);
			Vec3f point = Vec3f(-1.0f, 4.0f, 5.0f);

			Vec3f result = aabb.closestPointInAABB(point);

			Vec3f expected = Vec3f(0.0f, 4.0f, 5.0f);

			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AABB_closestPointInAABB_Test2)
		{
			Vec3f minPoint = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f maxPoint = Vec3f(10.0f, 10.0f, 10.0f);
			AABB aabb = AABB(minPoint, maxPoint);
			Vec3f point = Vec3f(100.0f, 100.0f, 100.0f);

			Vec3f result = aabb.closestPointInAABB(point);

			Vec3f expected = Vec3f(10.0f, 10.0f, 10.0f);

			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AABB_closestPointInAABB_Test3)
		{
			Vec3f minPoint = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f maxPoint = Vec3f(10.0f, 10.0f, 10.0f);
			AABB aabb = AABB(minPoint, maxPoint);
			Vec3f point = Vec3f(5.0f, 7.0f, 8.0f);

			Vec3f result = aabb.closestPointInAABB(point);

			Vec3f expected = Vec3f(5.0f, 7.0f, 8.0f);

			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AABB_squaredDistance_Test1)
		{
			Vec3f minPoint = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f maxPoint = Vec3f(10.0f, 10.0f, 10.0f);
			AABB aabb = AABB(minPoint, maxPoint);
			Vec3f point = Vec3f(5.0f, 7.0f, 8.0f);

			float result = aabb.squaredDistance(point);
			float expected = 0.0f;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AABB_squaredDistance_Test2)
		{
			Vec3f minPoint = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f maxPoint = Vec3f(10.0f, 10.0f, 10.0f);
			AABB aabb = AABB(minPoint, maxPoint);
			Vec3f point = Vec3f(-2.0f, 0.0f, 0.0f);

			float result = aabb.squaredDistance(point);
			float expected = 4.0f;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AABB_distance_Test)
		{
			Vec3f minPoint = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f maxPoint = Vec3f(10.0f, 10.0f, 10.0f);
			AABB aabb = AABB(minPoint, maxPoint);
			Vec3f point = Vec3f(-2.0f, 0.0f, 0.0f);

			float result = aabb.distance(point);
			float expected = 2.0f;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AABB_buildFrom_pointList_Test)
		{
			int pointsCont = 6;
			Vec3f* points = ALLOC_ARRAY(Vec3f, pointsCont);
			points[0] = { 0.0f, 0.0f, 0.3f };
			points[1] = { 10.0f, 10.0f, 10.0f };
			points[2] = { 5.0f, 5.0f, 5.0f };
			points[3] = { -1.0f, 1.0f, 1.0f }; //min point (index 3)
			points[4] = { 12.0f, 10.0f, 10.0f }; // max point (index 4)
			points[5] = { 8.0f, 1.0f, 1.0f };
			Vec3List<float> list = Vec3List<float>(points, pointsCont);

			AABB aabb = AABB::buildFrom(list);

			Vec3f expectedMinPoint = Vec3f(-1.0f, 0.0f, 0.3f);
			Vec3f expectedMaxPoint = Vec3f(12.0f, 10.0f, 10.0f);

			for (size_t i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedMinPoint[i], aabb.minPoint[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedMaxPoint[i], aabb.maxPoint[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(AABB_buildFrom_sphere_Test)
		{
			Sphere sphere = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);

			AABB aabb = AABB::buildFrom(sphere);

			Vec3f expectedMinPoint = Vec3f(-10.0f, -10.0f, -10.0f);
			Vec3f expectedMaxPoint = Vec3f(10.0f, 10.0f, 10.0f);

			for (size_t i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedMinPoint[i], aabb.minPoint[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedMaxPoint[i], aabb.maxPoint[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(AABB_enclose_AABB_Test)
		{
			AABB aabb1 = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			AABB aabb2 = AABB(Vec3f(20.0f, -1.0f, 2.0f), Vec3f(22.0f, 5.0f, 11.0f));

			AABB result = aabb1.enclose(aabb2);

			Vec3f expectedMinPoint = Vec3f(0.0f, -1.0f, 0.0f);
			Vec3f expectedMaxPoint = Vec3f(22.0f, 10.0f, 11.0f);

			for (size_t i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedMinPoint[i], result.minPoint[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedMaxPoint[i], result.maxPoint[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(AABB_enclose_sphere_Test)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			Sphere sphere = Sphere(Vec3f(-20.0f, 0.0f, 3.0f), 10.0f);

			AABB result = aabb.enclose(sphere);

			Vec3f expectedMinPoint = Vec3f(-30.0f, -10.0f, -7.0f);
			Vec3f expectedMaxPoint = Vec3f(10.0f, 10.0f, 13.0f);

			for (size_t i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedMinPoint[i], result.minPoint[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedMaxPoint[i], result.maxPoint[i], L"Wrong value.", LINE_INFO());
			}
		}
		
	};
}