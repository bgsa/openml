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

		TEST_METHOD(Sphere_constructor_center_ray_Test)
		{
			Spheref sphere = Spheref({ 1.0f, 2.0f ,3.0f }, 4.0f);
			
			Assert::AreEqual(sphere.center[0], 1.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[1], 2.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.center[2], 3.0f, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(sphere.ray, 4.0f, L"Wrong value.", LINE_INFO());
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

	};
}