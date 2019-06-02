#pragma once

#include "CppUnitTest.h"
#include <HashGrid.h>
#include "AABB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{

	TEST_CLASS(HashGridTest)
	{
	public:

		TEST_METHOD(AlgorithmAitken_findCell_Test)
		{
			HashGrid<float> grid(10);
			Vec3f point = {0.0f, 0.0f, 0.0f};
			Vec3f expected = Vec3f(0.0f);
			Vec3f result;

			for (float x = 0; x < 10; x++)
				for (float y = 0; y < 10; y++)
					for (float z = 0; z < 10; z++) 
					{
						point = Vec3f(x, y, z);

						Vec3f result = grid.findCell(point);

						for (size_t i = 0; i < 3; i++)
							Assert::AreEqual(result[i], expected[i], L"Wrong value.", LINE_INFO());
					}

			point = Vec3f(12.0f, 1.0f, 34.0f);
			result = grid.findCell(point);
			expected = Vec3f(1.0f, 0.0f, 3.0f);
			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(result[i], expected[i], L"Wrong value.", LINE_INFO());

			point = Vec3f(-2.0f, -2.0f, -2.0f);
			result = grid.findCell(point);
			expected = Vec3f(-1.0f, -1.0f, -1.0f);
			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(result[i], expected[i], L"Wrong value.", LINE_INFO());

			point = Vec3f(-11.0f, -11.0f, -11.0f);
			result = grid.findCell(point);
			expected = Vec3f(-2.0f, -2.0f, -2.0f);
			for (size_t i = 0; i < 3; i++)
				Assert::AreEqual(result[i], expected[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmAitken_findCellIndex_Test)
		{
			HashGrid<float> grid(10);
			Vec3f point = { 12.0f, 1.0f, 34.0f };
			int expected = -285815648;			
			int result = grid.findCellIndex(point);
			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());

			point = { 17.0f, 8.0f, 30.0f };
			expected = -285815648;
			result = grid.findCellIndex(point);
			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());

			point = { 0.0f, 1.0f, 4.0f };
			expected = 0;
			result = grid.findCellIndex(point);
			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());

			point = { 0.0f, -1.0f, -4.0f };
			expected = 1557075104;
			result = grid.findCellIndex(point);
			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmAitken_findRangeCell_Test1)
		{
			HashGrid<float> grid(10);

			AABBf aabb = AABBf({ 3.0f, 3.0f, 3.0f }, { 35.0f, 35.0f, 35.0f });

			Vec3f expectedCells[64];
			size_t index = 0;

			for (float x = 0; x < 4; x++)
				for (float y = 0; y < 4; y++)
					for (float z = 0; z < 4; z++) {
						expectedCells[index] = Vec3f(x, y, z);
						index++;
					}

			Vec3f* result = grid.findRangeCell(aabb);

			for (size_t index = 0; index < 64; index++) 
			{
				Assert::AreEqual(expectedCells[index][0], result[index][0], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedCells[index][1], result[index][1], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedCells[index][2], result[index][2], L"Wrong value.", LINE_INFO());
			}
		}

		TEST_METHOD(AlgorithmAitken_findRangeCell_Test2)
		{
			HashGrid<float> grid(10);

			AABBf aabb = AABBf({ -13.0f, -13.0f, -13.0f }, { 4.0f, 4.0f, 4.0f });

			Vec3f expectedCells[27];
			size_t index = 0;

			for (float x = 0; x < 3; x++)
				for (float y = 0; y < 3; y++)
					for (float z = 0; z < 3; z++) {
						expectedCells[index] = Vec3f(x, y, z);
						index++;
					}

			Vec3f* result = grid.findRangeCell(aabb);

			for (size_t index = 0; index < 27; index++)
			{
				Assert::AreEqual(expectedCells[index][0], result[index][0], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedCells[index][1], result[index][1], L"Wrong value.", LINE_INFO());
				Assert::AreEqual(expectedCells[index][2], result[index][2], L"Wrong value.", LINE_INFO());
			}
		}

	};
}