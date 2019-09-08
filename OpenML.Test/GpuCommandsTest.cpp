#pragma once

#include "CppUnitTest.h"
#include "TestHeader.h"
#include <chrono>
#include "Randomizer.h"
#include <GpuCommands.h>
#include <limits>
#include <AABB.h>

#undef max
#undef min

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{

	TEST_CLASS(GpuCommandsTest)
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

		TEST_METHOD(GpuCommands_findMinMaxGPU)
		{
			GpuContext* context = GpuContext::init();
			GpuDevice* gpu = context->defaultDevice;
			gpuCommands_init(gpu);

			const size_t count = (size_t)std::pow(2.0, 17.0);
			float* input = getRandom(count);

			float min = std::numeric_limits<float>().max();
			float max = std::numeric_limits<float>().min();

			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < count; i++)
			{
				if (input[i] > max)
					max = input[i];

				if (input[i] < min)
					min = input[i];
			}

			std::chrono::high_resolution_clock::time_point currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			currentTime = std::chrono::high_resolution_clock::now();

			float* result = gpuCommands_findMinMaxGPU(gpu, input, count);

			currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			Assert::AreEqual(min, result[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(max, result[1], L"Wrong value.", LINE_INFO());

			ALLOC_RELEASE(input);
		}

		TEST_METHOD(GpuCommands_findMinMaxGPU_withOffsets)
		{
			GpuContext* context = GpuContext::init();
			GpuDevice* gpu = context->defaultDevice;
			gpuCommands_init(gpu);

			const size_t offsetMultiplier = 7;
			const size_t offsetSum = 1;

			const size_t count = (size_t)std::pow(2.0, 17.0);
			AABBf* aabbs = getRandomAABBs(count);

			float min = std::numeric_limits<float>().max();
			float max = std::numeric_limits<float>().min();

			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < count; i++)
			{
				if (aabbs[i].minPoint.x > max)
					max = aabbs[i].minPoint.x;

				if (aabbs[i].minPoint.x < min)
					min = aabbs[i].minPoint.x;
			}

			std::chrono::high_resolution_clock::time_point currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			currentTime = std::chrono::high_resolution_clock::now();

			float* result = gpuCommands_findMinMaxGPU(gpu, (float*)aabbs, count, offsetMultiplier, offsetSum);

			currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			Assert::AreEqual(min, result[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(max, result[1], L"Wrong value.", LINE_INFO());

			ALLOC_RELEASE(aabbs);
		}
		

		TEST_METHOD(GpuCommands_findMaxGPU)
		{
			GpuContext* context = GpuContext::init();
			GpuDevice* gpu = context->defaultDevice;
			gpuCommands_init(gpu);

			const size_t count = (size_t)std::pow(2.0, 17.0);
			float* input = getRandom(count);

			float max = std::numeric_limits<float>().min();

			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < count; i++)
				if (input[i] > max)
					max = input[i];

			std::chrono::high_resolution_clock::time_point currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			currentTime = std::chrono::high_resolution_clock::now();

			float result = gpuCommands_findMaxGPU(gpu, input, count);

			currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			Assert::AreEqual(max, result, L"Wrong value.", LINE_INFO());

			ALLOC_RELEASE(input);
		}

		TEST_METHOD(GpuCommands_findMaxGPUBuffer)
		{
			GpuContext* context = GpuContext::init();
			GpuDevice* gpu = context->defaultDevice;
			gpuCommands_init(gpu);

			const size_t count = (size_t)std::pow(2.0, 17.0);
			float* input = getRandom(count);

			float max = FLT_MIN;

			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < count; i++)
				if (input[i] > max)
					max = input[i];

			std::chrono::high_resolution_clock::time_point currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			currentTime = std::chrono::high_resolution_clock::now();

			cl_mem buffer = gpuCommands_findMaxGPUBuffer(gpu, input, count);
			float* output = ALLOC_ARRAY(float, 8);
			gpu->commandManager->executeReadBuffer(buffer, SIZEOF_FLOAT*8, output, true);
			float result = FLT_MIN;

			for (size_t i = 0; i < 8; i++)
				if (result < output[i])
					result = output[i];

			currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			Assert::AreEqual(max, result, L"Wrong value.", LINE_INFO());

			ALLOC_RELEASE(input);
		}

	};
}