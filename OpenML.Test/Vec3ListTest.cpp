#pragma once

#include "CppUnitTest.h"
#include <Vec3List.h>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(Vec3ListTest)
	{
	public:

		TEST_METHOD(Vec3List_constructorDefault_Test)
		{
			Vec3f* points = new Vec3f[2];
			points[0] = { 0.0f, 2.0f, -3.3f };
			points[1] = { -5.1f, 2.0f, 3.0f };

			Vec3List<float> list = Vec3List<float>(points, 2);

			Assert::AreEqual(2, list.count, L"Wrong value.", LINE_INFO());

			for (size_t i = 0; i < 2; i++)
				for (size_t j = 0; j < 3; j++)
					Assert::AreEqual(points[i][j], list.points[i][j], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3List_findExtremePointsAlongAxisX_Test)
		{
			int pointsCount = 6;
			Vec3f* points = new Vec3f[pointsCount];
			points[0] = { 0.0f, 0.0f, 0.3f };
			points[1] = { 10.0f, 10.0f, 10.0f };
			points[2] = { 5.0f, 5.0f, 5.0f };
			points[3] = { -1.0f, 1.0f, 1.0f }; //min point (index 3)
			points[4] = { 12.0f, 10.0f, 10.0f }; // max point (index 4)
			points[5] = { 8.0f, 1.0f, 1.0f };

			Vec3List<float> list = Vec3List<float>(points, pointsCount);

			int* result = list.findExtremePointsAlongAxisX();

			Assert::AreEqual(3, result[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(4, result[1], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3List_findExtremePointsAlongAxisY_Test)
		{
			int pointsCount = 6;
			Vec3f* points = new Vec3f[pointsCount];
			points[0] = { 0.0f, 0.0f, 0.3f };
			points[1] = { 10.0f, 10.0f, 10.0f };
			points[2] = { 5.0f, 5.0f, 5.0f };
			points[3] = { -1.0f, 1.0f, 1.0f };
			points[4] = { 12.0f, 10.0f, 10.0f };
			points[5] = { 8.0f, 1.0f, 1.0f };

			Vec3List<float> list = Vec3List<float>(points, pointsCount);

			int* result = list.findExtremePointsAlongAxisY();

			Assert::AreEqual(0, result[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(1, result[1], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3List_findExtremePointsAlongAxisZ_Test)
		{
			int pointsCount = 6;
			Vec3f* points = new Vec3f[pointsCount];
			points[0] = { 0.0f, 0.0f, 0.3f };
			points[1] = { 10.0f, 10.0f, 10.0f };
			points[2] = { 5.0f, 5.0f, 5.0f };
			points[3] = { -1.0f, 1.0f, 1.0f };
			points[4] = { 12.0f, 10.0f, 10.0f };
			points[5] = { 8.0f, 1.0f, 17.0f };

			Vec3List<float> list = Vec3List<float>(points, pointsCount);

			int* result = list.findExtremePointsAlongAxisZ();

			Assert::AreEqual(0, result[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(5, result[1], L"Wrong value.", LINE_INFO());
		}


	};
}