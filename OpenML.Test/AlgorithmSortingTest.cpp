#pragma once

#include "CppUnitTest.h"
#include "TestHeader.h"
#include <AlgorithmSorting.h>
#include <chrono>
#include "Randomizer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

int comparatorFloatTest(const void* param1, const void* param2)
{
	const float obj1 = *(float*)param1;
	const float obj2 = *(float*)param2;

	if (obj1 < obj2)
		return -1;
	else
		if (obj1 > obj2)
			return 1;

	return 0;
}

int comparatorAABBFirstAxisTest(const void* param1, const void* param2)
{
	const AABBf obj1 = *(AABBf*)param1;
	const AABBf obj2 = *(AABBf*)param2;

	if (obj1.minPoint.x == obj2.minPoint.x)
		return 0;
	
	if (obj1.minPoint.x < obj2.minPoint.x)
		return -1;

	return 1;
}

namespace OpenMLTest
{

	TEST_CLASS(AlgorithmSortingTest)
	{
	private:

		float* getRandom(size_t count, size_t spaceSize = 10000)
		{
			Randomizer<int> randomizer(0, spaceSize);

			float* result = ALLOC_ARRAY(float, count);

			for (size_t i = 0; i < count; i++)
				result[i] = randomizer.rand() / 100.0f;

			return result;
		}

		AABBf* getRandomAABBs(size_t count, size_t spaceSize = 1000)
		{
			Randomizer<int> randomizerSize(0, 30);
			Randomizer<int> randomizerLocation(0, spaceSize);

			AABBf* aabbs = ALLOC_ARRAY(AABBf, count);

			for (size_t i = 0; i < count; i++)
			{
				int xMin = randomizerSize.rand();
				int yMin = randomizerSize.rand();
				int zMin = randomizerSize.rand();

				int xMax = randomizerSize.rand();
				int yMax = randomizerSize.rand();
				int zMax = randomizerSize.rand();

				int locationX = randomizerLocation.rand();
				int locationY = randomizerLocation.rand();
				int locationZ = randomizerLocation.rand();

				if (xMin == xMax)
					xMax++;

				if (yMin == yMax)
					yMax++;

				if (zMin == zMax)
					zMax++;

				if (xMin > xMax)
					std::swap(xMin, xMax);

				if (yMin > yMax)
					std::swap(yMin, yMax);

				if (zMin > zMax)
					std::swap(zMin, zMax);

				aabbs[i] = AABBf({ float(xMin + locationX), float(yMin + locationY), float(zMin + locationZ) }
				, { float(xMax + locationX), float(yMax + locationY), float(zMax + locationZ) });
			}

			return aabbs;
		}

	public:

		TEST_METHOD(AlgorithmSorting_radix_Test1)
		{
			const size_t count = 7;

			float vec[count] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f, 3.12f, 3.01f };
			float expected[count] = { -2.0f, 2.0f, 3.01f, 3.1f, 3.12f, 3.4f, 7.0f };
			
			AlgorithmSorting::radix(vec, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], vec[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test2)
		{
			size_t result[8] = { 2, 5,3,0,2,3,0,3 };
			size_t expected[8] = { 0,0,2,2,3,3,3,5 };

			AlgorithmSorting::radix(result, 8);

			for (size_t i = 0; i < 8; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test3)
		{
			size_t result[8] = { 200, 54, 35, 10, 4, 3, 50, 33 };
			size_t expected[8] = { 3, 4, 10, 33, 35, 50, 54, 200 };

			AlgorithmSorting::radix(result, 8);

			for (size_t i = 0; i < 8; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test4)
		{
			int result[8] = { 200, 54, 35, -10, 4, 3, -50, 33 };
			int expected[8] = { -50, -10, 3, 4, 33, 35, 54, 200 };
			
			AlgorithmSorting::radix(result, 8);

			for (size_t i = 0; i < 8; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test5)
		{
			const size_t count = 6;
			float result[count] = { 0.1f,0.111f,0.23f,0.03f,0.53f,0.08f };
			float expected[count] = { 0.03f, 0.08f, 0.1f, 0.111f, 0.23f, 0.53f };

			AlgorithmSorting::radix(result, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test6)
		{
			const size_t count = 6;
			float result[count] = { 57.1f, 0.111f, 1.23f, 0.03f, 0.53f, 2.08f };
			float expected[count] = { 0.03f, 0.111f, 0.53f, 1.23f, 2.08f, 57.1f };

			AlgorithmSorting::radix(result, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_radix_Test7)
		{
			const size_t count = 7;
			float result[count] = { 57.1f, 0.111f, -1.23f, 0.03f, 0.53f, 2.08f, -34567.56f };
			float expected[count] = { -34567.56f, -1.23f, 0.03f, 0.111f, 0.53f, 2.08f, 57.1f };

			AlgorithmSorting::radix(result, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_native_Test1)
		{
			const size_t count = 7;

			float vec[count] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f, 3.12f, 3.01f };
			float expected[count] = { -2.0f, 2.0f, 3.01f, 3.1f, 3.12f, 3.4f, 7.0f };

			AlgorithmSorting::native(vec, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], vec[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_nativeIndex_Test1)
		{
			const size_t count = 7;

			float vec[count] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f, 3.12f, 3.01f };
			size_t expected[count] = { 4, 1, 6, 3, 5, 0, 2 };

			size_t* result = AlgorithmSorting::nativeIndex(vec, count);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(AlgorithmSorting_quickSortNnative_Test1)
		{
			const size_t count = 7;

			float vec[count] = { 3.4f, 2.0f, 7.0f, 3.1f, -2.0f, 3.12f, 3.01f };
			float expected[count] = { -2.0f, 2.0f, 3.01f, 3.1f, 3.12f, 3.4f, 7.0f };

			AlgorithmSorting::quickSortNative(vec, count, sizeof(float), comparatorFloatTest);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(expected[i], vec[i], L"Wrong value.", LINE_INFO());
		}
		
		TEST_METHOD(AlgorithmSorting_radixGPU_Test1)
		{
			GpuContext* context = GpuContext::init();
			GpuDevice* gpu = context->defaultDevice;
			AlgorithmSorting::init(gpu);

			const size_t count = (size_t)std::pow(2.0, 17.0);
			float* vector = getRandom(count);
			float* result = ALLOC_COPY(vector, float, count);

			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

			AlgorithmSorting::native(vector, count);

			std::chrono::high_resolution_clock::time_point currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			currentTime = std::chrono::high_resolution_clock::now();

			result = AlgorithmSorting::radixGPU(gpu, result, count);

			currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(vector[i], result[i], L"Wrong value.", LINE_INFO());

			ALLOC_RELEASE(vector);
		}

		TEST_METHOD(AlgorithmSorting_radixGPU_Test2)
		{
			GpuContext* context = GpuContext::init();
			GpuDevice* gpu = context->defaultDevice;
			AlgorithmSorting::init(gpu);

			const size_t count = (size_t)std::pow(2.0, 17.0);
			AABBf* input1 = getRandomAABBs(count);
			AABBf* input2 = ALLOC_COPY(input1, AABBf, count);
			
			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

			AlgorithmSorting::quickSortNative(input1, count, sizeof(AABBf), comparatorAABBFirstAxisTest);

			std::chrono::high_resolution_clock::time_point currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			currentTime = std::chrono::high_resolution_clock::now();

			size_t* result = AlgorithmSorting::radixGPUIndexes(gpu, (float*) input2, count, 7, 1);

			currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(input1[i].minPoint.x, input2[result[i]].minPoint.x, L"Wrong value.", LINE_INFO());

			ALLOC_RELEASE(input1);
		}

		TEST_METHOD(AlgorithmSorting_radixGPUIndexes_Test1)
		{
			GpuContext* context = GpuContext::init();
			GpuDevice* gpu = context->defaultDevice;
			AlgorithmSorting::init(gpu);

			const size_t count = (size_t)std::pow(2.0, 17.0);
			float* vector = getRandom(count);

			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

			AlgorithmSorting::native(vector, count);

			std::chrono::high_resolution_clock::time_point currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			currentTime = std::chrono::high_resolution_clock::now();

			size_t* indexes = AlgorithmSorting::radixGPUIndexes(gpu, vector, count);

			currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(vector[i], vector[indexes[i]], L"Wrong value.", LINE_INFO());

			ALLOC_RELEASE(vector);
		}

	};
}