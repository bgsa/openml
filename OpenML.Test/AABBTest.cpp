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

		TEST_METHOD(AABB_constructor_twoPoints_Test)
		{
			Vec3f minPoint = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f maxPoint = Vec3f(10.0f, 10.0f, 10.0f);

			AABBf aabb = AABBf(minPoint, maxPoint);

			for (size_t i = 0; i < 3; i++)
			{
				Assert::AreEqual(aabb.minPoint[i], minPoint[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(aabb.maxPoint[i], maxPoint[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(AABB_constructor_minPointAndDistances_Test)
		{
			Vec3f minPoint = Vec3f(10.0f, 20.0f, 30.0f);
			AABBf aabb = AABBf(minPoint, 10.0f, 12.0f, 15.0f);
			Vec3f maxPointExpected = Vec3f(20.0f, 32.0f, 45.0f);

			for (size_t i = 0; i < 3; i++)
			{
				Assert::AreEqual(aabb.minPoint[i], minPoint[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(aabb.maxPoint[i], maxPointExpected[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(AABB_colisionStatus_AABB_Test)
		{
			//Check on X axis
			AABBf aabb1 = AABBf(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			AABBf aabb2 = AABBf(Vec3f(10.0f, 10.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			ColisionStatus result = aabb1.colisionStatus(aabb2);
			Assert::IsTrue(result == ColisionStatus::INSIDE, L"Mistake!.", LINE_INFO());

			aabb1 = AABBf(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABBf(Vec3f(9.0f, 10.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.colisionStatus(aabb2);
			Assert::IsTrue(result == ColisionStatus::INSIDE, L"Mistake!.", LINE_INFO());

			aabb1 = AABBf(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABBf(Vec3f(11.0f, 10.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.colisionStatus(aabb2);
			Assert::IsTrue(result == ColisionStatus::OUTSIDE, L"Mistake!.", LINE_INFO());

			//Check on Y axis
			aabb1 = AABBf(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABBf(Vec3f(0.0f, 10.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.colisionStatus(aabb2);
			Assert::IsTrue(result == ColisionStatus::INSIDE, L"Mistake!.", LINE_INFO());

			aabb1 = AABBf(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABBf(Vec3f(0.0f, 11.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.colisionStatus(aabb2);
			Assert::IsTrue(result == ColisionStatus::OUTSIDE, L"Mistake!.", LINE_INFO());

			//Check on z axis
			aabb1 = AABBf(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABBf(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.colisionStatus(aabb2);
			Assert::IsTrue(result == ColisionStatus::INSIDE, L"Mistake!.", LINE_INFO());

			aabb1 = AABBf(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			aabb2 = AABBf(Vec3f(0.0f, 0.0f, 11.0f), Vec3f(20.0f, 20.0f, 20.0f));
			result = aabb1.colisionStatus(aabb2);
			Assert::IsTrue(result == ColisionStatus::OUTSIDE, L"Mistake!.", LINE_INFO());
		}

		TEST_METHOD(AABB_closestPointInAABB_Test1)
		{
			Vec3f minPoint = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f maxPoint = Vec3f(10.0f, 10.0f, 10.0f);
			AABBf aabb = AABBf(minPoint, maxPoint);
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
			AABBf aabb = AABBf(minPoint, maxPoint);
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
			AABBf aabb = AABBf(minPoint, maxPoint);
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
			AABBf aabb = AABBf(minPoint, maxPoint);
			Vec3f point = Vec3f(5.0f, 7.0f, 8.0f);

			float result = aabb.squaredDistance(point);
			float expected = 0.0f;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AABB_squaredDistance_Test2)
		{
			Vec3f minPoint = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f maxPoint = Vec3f(10.0f, 10.0f, 10.0f);
			AABBf aabb = AABBf(minPoint, maxPoint);
			Vec3f point = Vec3f(-2.0f, 0.0f, 0.0f);

			float result = aabb.squaredDistance(point);
			float expected = 4.0f;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AABB_distance_Test)
		{
			Vec3f minPoint = Vec3f(0.0f, 0.0f, 0.0f);
			Vec3f maxPoint = Vec3f(10.0f, 10.0f, 10.0f);
			AABBf aabb = AABBf(minPoint, maxPoint);
			Vec3f point = Vec3f(-2.0f, 0.0f, 0.0f);

			float result = aabb.distance(point);
			float expected = 2.0f;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		
	};
}