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
		
	};
}