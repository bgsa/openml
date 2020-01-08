#pragma once

#include "CppUnitTest.h"
#include <DOP18.h>
#include "TestHeader.h"

namespace OpenMLTest
{
	TEST_CLASS(DOP18Test)
	{
	public:

		TEST_METHOD(DOP18_constructor_empty)
		{
			DOP18 kdop = DOP18();

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(-0.5f, kdop.min[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(0.5f, kdop.max[i], L"Wrong value.", LINE_INFO());
			}

			for (int i = 3; i < DOP18_ORIENTATIONS; i++)
			{
				Assert::AreEqual(-0.375f, kdop.min[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(0.375f, kdop.max[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(DOP18_centerOfBoundingVolume)
		{
			DOP18 kdop = DOP18();
			Vec3f result = Vec3f(0.0f);

			for (int i = 0; i < 3; i++)
				Assert::AreEqual(result[i], kdop.centerOfBoundingVolume()[i], L"Wrong value.", LINE_INFO());

			kdop.translate(10.0f, 3.0f, 1.0f);
			result = Vec3f(10.0f, 3.0f, 1.0f);

			for (int i = 0; i < 3; i++)
				Assert::AreEqual(result[i], kdop.centerOfBoundingVolume()[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(DOP18_translate)
		{
			DOP18 kdop = DOP18();
			kdop.translate(10.0f, 3.0f, 1.0f);

			Assert::IsTrue(isCloseEnough(kdop.min[0], 9.5f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.min[1], 2.5f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.min[2], 0.5f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.min[3], -0.375f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.min[4], -0.375f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.min[5], -0.375f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.min[6], -0.375f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.min[7], -0.375f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.min[8], -0.375f), L"Wrong value.", LINE_INFO());
			
			Assert::IsTrue(isCloseEnough(kdop.max[0], 10.5f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.max[1], 3.5f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.max[2], 1.5f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.max[3], 0.375f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.max[4], 0.375f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.max[5], 0.375f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.max[6], 0.375f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.max[7], 0.375f), L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(kdop.max[8], 0.375f), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(DOP18_scale_withFixing)
		{
			DOP18 kdop = DOP18();
			kdop.scale(2.0f, 2.0f, 2.0f);

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(-0.75f, kdop.min[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(0.75f, kdop.max[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(DOP18_scale_withoutFixing)
		{
			DOP18 kdop = DOP18();
			kdop.scale(1.1f, 1.1f, 1.1f);

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(-0.75f, kdop.min[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(0.75f, kdop.max[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(DOP18_rotate)
		{
			DOP18 kdop1 = DOP18();
			DOP18 kdop2 = DOP18();
			kdop1.translate(10.0f, 3.0f, 1.0f);
			kdop2.translate(10.0f, 3.0f, 1.0f);

			kdop1.rotate(float(degreesToRadians(15)), 1.0f, 1.0f, 1.0f);

			for (int i = 0; i < DOP18_ORIENTATIONS; i++)
			{
				Assert::AreEqual(kdop1.min[i], kdop2.min[i], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(kdop1.max[i], kdop2.max[i], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(DOP18_collisionStatus_outside)
		{
			DOP18 kdop1 = DOP18();
			DOP18 kdop2 = DOP18();

			kdop2.translate(10.0f, 3.0f, 1.0f);
			CollisionStatus result = kdop1.collisionStatus(kdop2);
			Assert::AreEqual(CollisionStatus::OUTSIDE, result, L"Wrong value.", LINE_INFO());

			kdop2 = DOP18();
			kdop2.translate(1.1f, 0.0f, 0.0f);
			result = kdop1.collisionStatus(kdop2);
			Assert::AreEqual(CollisionStatus::OUTSIDE, result, L"Wrong value.", LINE_INFO());

			kdop2 = DOP18();
			kdop2.translate(0.0f, 1.1f, 0.0f);
			result = kdop1.collisionStatus(kdop2);
			Assert::AreEqual(CollisionStatus::OUTSIDE, result, L"Wrong value.", LINE_INFO());

			kdop2 = DOP18();
			kdop2.translate(0.0f, -1.1f, 0.0f);
			result = kdop1.collisionStatus(kdop2);
			Assert::AreEqual(CollisionStatus::OUTSIDE, result, L"Wrong value.", LINE_INFO());

			kdop2 = DOP18();
			kdop2.translate(0.0f, 0.0f, -1.1f);
			result = kdop1.collisionStatus(kdop2);
			Assert::AreEqual(CollisionStatus::OUTSIDE, result, L"Wrong value.", LINE_INFO());

			kdop2 = DOP18();
			kdop2.translate(1.0f, 1.0f, 1.0f);
			result = kdop1.collisionStatus(kdop2);
			Assert::AreEqual(CollisionStatus::OUTSIDE, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(DOP18_collisionStatus_inside)
		{
			DOP18 kdop1 = DOP18();
			DOP18 kdop2 = DOP18();

			CollisionStatus result = kdop1.collisionStatus(kdop2);
			Assert::AreEqual(CollisionStatus::INSIDE, result, L"Wrong value.", LINE_INFO());

			kdop2 = DOP18();
			kdop2.translate(0.5f, 0.0f, 0.0f);
			result = kdop1.collisionStatus(kdop2);
			Assert::AreEqual(CollisionStatus::INSIDE, result, L"Wrong value.", LINE_INFO());
		}
		
	};
}