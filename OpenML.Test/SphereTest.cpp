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
			Sphere sphere = Sphere();

			Assert::AreEqual(sphere.center[0], 0.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[1], 0.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[2], 0.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.ray, 1.0f, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Sphere_constructor_center_ray_Test)
		{
			Sphere sphere = Sphere({ 1.0f, 2.0f ,3.0f }, 4.0f);
			
			Assert::AreEqual(sphere.center[0], 1.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[1], 2.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[2], 3.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.ray, 4.0f, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Sphere_constructor_2points_Test)
		{
			Sphere sphere = Sphere(Vec3f(2.0f, 2.0f, 2.0f), Vec3f(6.0f, 6.0f, 6.0f));

			Assert::AreEqual(sphere.center[0], 4.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[1], 4.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[2], 4.0f, L"Wrong value.", LINE_INFO());
			Assert::IsTrue(isCloseEnough(sphere.ray, 3.46410f), L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Sphere_constructor_3points_Test1)
		{
			Sphere sphere = Sphere(
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
			Sphere sphere = Sphere(
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
			Sphere sphere = Sphere(
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
			Sphere sphere = Sphere({ 0.0f, 0.0f, 0.0f }, 10.0f);
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
			Sphere sphere1 = Sphere({ 10.0f, 0.0f, 0.0f }, 10.0f);
			Sphere sphere2 = Sphere({ -10.0f, 0.0f, 0.0f }, 10.0f);
			ColisionStatus expected = ColisionStatus::INLINE;
			ColisionStatus result = sphere1.colisionStatus(sphere2);
			Assert::IsTrue(result == expected, L"The point should lie on sphere boundary", LINE_INFO());

			sphere2 = Sphere({ -9.0f, 0.0f, 0.0f }, 10.0f);
			expected = ColisionStatus::INSIDE;
			result = sphere1.colisionStatus(sphere2);
			Assert::IsTrue(result == expected, L"The point should lie inside the sphere", LINE_INFO());

			sphere2 = Sphere({ -11.0f, 0.0f, 0.0f }, 10.0f);
			expected = ColisionStatus::OUTSIDE;
			result = sphere1.colisionStatus(sphere2);
			Assert::IsTrue(result == expected, L"The point should be outside the sphere", LINE_INFO());
		}

		TEST_METHOD(Sphere_colisionStatus_plane_Test)
		{
			Sphere sphere = Sphere({ 10.0f, 0.0f, 0.0f }, 10.0f);
			Plane3D plane = Plane3D(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
			ColisionStatus expected = ColisionStatus::INLINE;
			ColisionStatus result = sphere.colisionStatus(plane);
			Assert::IsTrue(result == expected, L"The plane should lie/support on sphere boundary", LINE_INFO());

			plane = Plane3D(Vec3f(3.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
			expected = ColisionStatus::INSIDE;
			result = sphere.colisionStatus(plane);
			Assert::IsTrue(result == expected, L"The point should lie inside the sphere", LINE_INFO());

			plane = Plane3D(Vec3f(-3.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
			expected = ColisionStatus::OUTSIDE;
			result = sphere.colisionStatus(plane);
			Assert::IsTrue(result == expected, L"The point should be outside the sphere", LINE_INFO());
		}

		TEST_METHOD(Sphere_buildFrom_AABB_Test)
		{
			AABB aabb = AABB(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(10.0f, 10.0f, 10.0f));
			
			Sphere sphere = Sphere::buildFrom(aabb);

			Vec3f expectedCenterPoint = Vec3f(5.0f, 5.0f, 5.0f);

			Assert::AreEqual(5.0f, sphere.ray, L"wring value", LINE_INFO());

			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(expectedCenterPoint[i], sphere.center[i], L"wring value", LINE_INFO());
		}

		TEST_METHOD(Sphere_buildFrom_pointList_Test)
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

			Sphere sphere = Sphere::buildFrom(list);
			
			Vec3f expectedCenterPoint = Vec3f(6.0f, 5.0f, 5.15f);

			Assert::IsTrue( isCloseEnough(9.193612f, sphere.ray), L"wring value", LINE_INFO());

			for (size_t i = 0; i < 3; i++)
				Assert::IsTrue(isCloseEnough(expectedCenterPoint[i], sphere.center[i]), L"wring value", LINE_INFO());
		}

		TEST_METHOD(Sphere_enclose_sphere_Test1)
		{
			Sphere sphere1 = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 2.0f);
			Sphere sphere2 = Sphere(Vec3f(4.0f, 0.0f, 0.0f), 1.0f);

			Sphere result = sphere1.enclose(sphere2);

			Vec3f expectedCenter = Vec3f(1.5f, 0.0f, 0.0f);
			float expectedRay = 3.5f;

			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(expectedCenter[i], result.center[i], L"Wrong value.", LINE_INFO());

			Assert::AreEqual(expectedRay, result.ray, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Sphere_enclose_sphere_Test2)
		{
			Sphere sphere1 = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Sphere sphere2 = Sphere(Vec3f(1.0f, 1.0f, 1.0f), 3.0f);

			Sphere result = sphere1.enclose(sphere2);

			Vec3f expectedCenter = Vec3f(0.0f, 0.0f, 0.0f);
			float expectedRay = 10.0f;

			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(expectedCenter[i], result.center[i], L"Wrong value.", LINE_INFO());

			Assert::AreEqual(expectedRay, result.ray, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Sphere_enclose_sphere_Test3)
		{
			Sphere sphere1 = Sphere(Vec3f(0.0f, 0.0f, 0.0f), 10.0f);
			Sphere sphere2 = Sphere(Vec3f(1.0f, 1.0f, 1.0f), 3.0f);

			Sphere result = sphere2.enclose(sphere1); //swapped

			Vec3f expectedCenter = Vec3f(0.0f, 0.0f, 0.0f);
			float expectedRay = 10.0f;

			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(expectedCenter[i], result.center[i], L"Wrong value.", LINE_INFO());

			Assert::AreEqual(expectedRay, result.ray, L"Wrong value.", LINE_INFO());
		}

	};
}