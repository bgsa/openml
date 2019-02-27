#pragma once

#include "CppUnitTest.h"
#include <Sphere.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(SphereTest)
	{
	public:

		TEST_METHOD(Sphere_constructor_Test)
		{
			Spheref sphere = Spheref();

			Assert::AreEqual(sphere.center[0], 0.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[1], 0.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[2], 0.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.ray, 1.0f, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Sphere_constructor_center_ray_Test)
		{
			Spheref sphere = Spheref({ 1.0f, 2.0f ,3.0f }, 4.0f);
			
			Assert::AreEqual(sphere.center[0], 1.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[1], 2.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[2], 3.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.ray, 4.0f, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Sphere_constructor_2points_Test)
		{
			Spheref sphere = Spheref(Vec3f(2.0f, 2.0f, 2.0f), Vec3f(6.0f, 6.0f, 6.0f));

			Assert::AreEqual(sphere.center[0], 4.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[1], 4.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[2], 4.0f, L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(sphere.ray, 3.46410f), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Sphere_constructor_3points_Test1)
		{
			Spheref sphere = Spheref(
				Vec3f(0.0f, 0.0f, 0.0f), 
				Vec3f(2.0f, 0.0f, 0.0f),
				Vec3f(1.0f, 2.0f, 0.0f)
			);

			Vec3f expectedCenter = Vec3f(1.0f, 0.75f, 0.0f);

			Assert::AreEqual(expectedCenter[0], sphere.center[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expectedCenter[1], sphere.center[1], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(expectedCenter[2], sphere.center[2], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(1.25f, sphere.ray, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Sphere_constructor_3points_Test2)
		{
			Spheref sphere = Spheref(
				Vec3f(2.0f, 2.0f, 0.0f),
				Vec3f(10.0f, 0.0f, 0.0f),
				Vec3f(12.0f, 30.0f, 10.0f)
			);

			Vec3f expectedCenter = Vec3f(9.53111458f, 15.1244574f, 4.92040539f);

			for (size_t i = 0; i < 3; i++)
				Assert::IsTrue(isCloseEnough(expectedCenter[i], sphere.center[i]), L"Wrong value.", LINE_INFO());
			
			Assert::IsTrue(isCloseEnough(sphere.ray, 15.9116144f), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Sphere_constructor_4points_Test)
		{
			Spheref sphere = Spheref(
				Vec3f(3.0f, 2.0f, 1.0f),
				Vec3f(1.0f, -2.0f, -3.0f),
				Vec3f(2.0f, 1.0f, 3.0f),
				Vec3f(-1.0f, 1.0f, 2.0f)
			);

			Vec3f expectedCenterPoint = Vec3f(1.263157f, -0.842105f, 0.210526f);
			float expectedRay = 3.423076f;

			for (size_t i = 0; i < 3; i++)
				Assert::IsTrue(isCloseEnough(expectedCenterPoint[i], sphere.center[i]), L"Wrong value.", LINE_INFO());

			Assert::IsTrue(isCloseEnough(expectedRay, sphere.ray), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Sphere_colisionStatus_point_Test)
		{
			Spheref sphere = Spheref({ 0.0f, 0.0f, 0.0f }, 10.0f);
			Vec3f point = Vec3f(7.071f, 5.0f, 5.0f);
			ColisionStatus expected = ColisionStatus::INLINE;
			ColisionStatus result = sphere.colisionStatus(point);
			Assert::IsTrue(result == expected, L"The point should lie on sphere boundary", LINE_INFO());

			point = Vec3f(1.0f, 1.0f, 1.0f);
			expected = ColisionStatus::INSIDE;
			result = sphere.colisionStatus(point);
			Assert::IsTrue(result == expected, L"The point should lie inside the sphere", LINE_INFO());

			point = Vec3f(11.0f, 10.0f, 10.0f);
			expected = ColisionStatus::OUTSIDE;
			result = sphere.colisionStatus(point);
			Assert::IsTrue(result == expected, L"The point should be outside the sphere", LINE_INFO());
		}

		TEST_METHOD(Sphere_colisionStatus_sphere_Test)
		{
			Spheref sphere1 = Spheref({ 10.0f, 0.0f, 0.0f }, 10.0f);
			Spheref sphere2 = Spheref({ -10.0f, 0.0f, 0.0f }, 10.0f);
			ColisionStatus expected = ColisionStatus::INLINE;
			ColisionStatus result = sphere1.colisionStatus(sphere2);
			Assert::IsTrue(result == expected, L"The point should lie on sphere boundary", LINE_INFO());

			sphere2 = Spheref({ -9.0f, 0.0f, 0.0f }, 10.0f);
			expected = ColisionStatus::INSIDE;
			result = sphere1.colisionStatus(sphere2);
			Assert::IsTrue(result == expected, L"The point should lie inside the sphere", LINE_INFO());

			sphere2 = Spheref({ -11.0f, 0.0f, 0.0f }, 10.0f);
			expected = ColisionStatus::OUTSIDE;
			result = sphere1.colisionStatus(sphere2);
			Assert::IsTrue(result == expected, L"The point should be outside the sphere", LINE_INFO());
		}

		TEST_METHOD(Sphere_colisionStatus_plane_Test)
		{
			Spheref sphere = Spheref({ 10.0f, 0.0f, 0.0f }, 10.0f);
			Plane3Df plane = Plane3Df(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
			ColisionStatus expected = ColisionStatus::INLINE;
			ColisionStatus result = sphere.colisionStatus(plane);
			Assert::IsTrue(result == expected, L"The plane should lie/support on sphere boundary", LINE_INFO());

			plane = Plane3Df(Vec3f(3.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
			expected = ColisionStatus::INSIDE;
			result = sphere.colisionStatus(plane);
			Assert::IsTrue(result == expected, L"The point should lie inside the sphere", LINE_INFO());

			plane = Plane3Df(Vec3f(-3.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
			expected = ColisionStatus::OUTSIDE;
			result = sphere.colisionStatus(plane);
			Assert::IsTrue(result == expected, L"The point should be outside the sphere", LINE_INFO());
		}

		TEST_METHOD(Sphere_buildFrom_AABB_Test)
		{
			AABBf aabb = AABBf(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			
			Spheref sphere = Spheref::buildFrom(aabb);

			Vec3f expectedCenterPoint = Vec3f(5.0f, 5.0f, 5.0f);

			Assert::AreEqual(5.0f, sphere.ray, L"wring value", LINE_INFO());

			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(expectedCenterPoint[i], sphere.center[i], L"wring value", LINE_INFO());
		}

	};
}