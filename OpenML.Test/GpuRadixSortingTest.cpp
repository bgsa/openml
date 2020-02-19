#pragma once

#if OPENCL_ENABLED

#include "CppUnitTest.h"
#include "TestHeader.h"
#include <chrono>
#include "Randomizer.h"
#include <GpuRadixSorting.h>
#include <AABB.h>
#include <AlgorithmSorting.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{

	TEST_CLASS(GpuRadixSortingTest)
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

		AABB* getRandomAABBs(size_t count, size_t spaceSize = 1000)
		{
			Randomizer<int> randomizerSize(0, 30);
			Randomizer<int> randomizerLocation(0, spaceSize);

			AABB* aabbs = ALLOC_ARRAY(AABB, count);

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

				aabbs[i] = AABB({ float(xMin + locationX), float(yMin + locationY), float(zMin + locationZ) }
				, { float(xMax + locationX), float(yMax + locationY), float(zMax + locationZ) });
			}

			return aabbs;
		}

		static int comparatorFloatTest(const void* param1, const void* param2)
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

		static int comparatorAABBirstAxisTest(const void* param1, const void* param2)
		{
			const AABB obj1 = *(AABB*)param1;
			const AABB obj2 = *(AABB*)param2;

			if (obj1.minPoint.x == obj2.minPoint.x)
				return 0;

			if (obj1.minPoint.x < obj2.minPoint.x)
				return -1;

			return 1;
		}

	public:

		TEST_METHOD(AlgorithmSorting_radixGPU_Test1)
		{
			GpuContext* context = GpuContext::init();
			GpuDevice* gpu = context->defaultDevice;

			size_t count = (size_t)std::pow(2.0, 17.0);
			float* input1 = getRandom(count);
			float* input2 = ALLOC_COPY(input1, float, count);

			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

			AlgorithmSorting::native(input1, count);

			std::chrono::high_resolution_clock::time_point currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			std::ostringstream buildOptions;
			buildOptions << " -DINPUT_LENGTH=" << 131072;
			buildOptions << " -DINPUT_STRIDE=1";
			buildOptions << " -DINPUT_OFFSET=0";

			size_t strider = 1;
			size_t offset = 0;
			GpuRadixSorting* radixGpu = ALLOC_NEW(GpuRadixSorting)();
			radixGpu->init(gpu, buildOptions.str().c_str())->setParameters(input2, count, strider, offset);

			currentTime = std::chrono::high_resolution_clock::now();

			cl_mem output = radixGpu->execute();

			currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			size_t* orderedIndexes = ALLOC_ARRAY(size_t, count);
			gpu->commandManager->executeReadBuffer(output, count * SIZEOF_UINT, orderedIndexes, true);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(input1[i], input2[orderedIndexes[i]], L"Wrong value.", LINE_INFO());

			gpu->releaseBuffer(output);
			ALLOC_DELETE(radixGpu, GpuRadixSorting);
			ALLOC_RELEASE(input1);
		}

		TEST_METHOD(AlgorithmSorting_radixGPU_Test2)
		{
			GpuContext* context = GpuContext::init();
			GpuDevice* gpu = context->defaultDevice;

			std::chrono::milliseconds times[10];

			for (size_t i = 0; i < 10; i++)
			{

			const size_t count = (size_t)std::pow(2.0, 17.0);
			AABB* input1 = getRandomAABBs(count);
			AABB* input2 = ALLOC_COPY(input1, AABB, count);

			std::ostringstream buildOptions;
			buildOptions << " -DINPUT_LENGTH=" << count;
			buildOptions << " -DINPUT_STRIDE=" << AABB_STRIDER;
			buildOptions << " -DINPUT_OFFSET=" << AABB_OFFSET;
			//buildOptions << " –cl-fast-relaxed-math";
			//buildOptions << " -cl-unsafe-math-optimizations";

			GpuRadixSorting* radixSorting = ALLOC_NEW(GpuRadixSorting)();
			radixSorting->init(gpu, buildOptions.str().c_str())
				->setParameters((float*)input2, count, AABB_STRIDER, AABB_OFFSET);

			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

			AlgorithmSorting::quickSortNative(input1, count, sizeof(AABB), comparatorAABBirstAxisTest);

			std::chrono::high_resolution_clock::time_point currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			currentTime = std::chrono::high_resolution_clock::now();

			cl_mem output = radixSorting->execute();

			currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);
			times[i] = ms2;

			size_t* result = ALLOC_ARRAY(size_t, count * SIZEOF_UINT);
			gpu->commandManager->executeReadBuffer(output, count * SIZEOF_UINT, result, true);

			for (size_t i = 0; i < count; i++)
				Assert::AreEqual(input1[i].minPoint.x, input2[result[i]].minPoint.x, L"Wrong value.", LINE_INFO());

			ALLOC_RELEASE(input1);
			ALLOC_DELETE(radixSorting, GpuRadixSorting);

			}
		}

	};

}

#endif