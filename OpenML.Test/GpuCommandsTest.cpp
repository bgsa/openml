#pragma once

#include "CppUnitTest.h"
#include "TestHeader.h"
#include <chrono>
#include "Randomizer.h"
#include <GpuCommands.h>
#include <limits>

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

			float max = std::numeric_limits<float>().min();

			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < count; i++)
				if (input[i] > max)
					max = input[i];

			std::chrono::high_resolution_clock::time_point currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			currentTime = std::chrono::high_resolution_clock::now();

			cl_mem buffer = gpuCommands_findMaxGPUBuffer(gpu, input, count);
			float* output = ALLOC_ARRAY(float, 8);
			gpu->commandManager->executeReadBuffer(buffer, SIZEOF_FLOAT, output, true);
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