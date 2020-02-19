#pragma once

#if OPENCL_ENABLED

#include "CppUnitTest.h"
#include "TestHeader.h"
#include <chrono>
#include "Randomizer.h"
#include <GpuInsertionSorting.h>
#include <AABB.h>
#include <AlgorithmSorting.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{

	TEST_CLASS(GpuRadixSortingTest)
	{
	private:

		float* getRandom(sp_uint count, sp_uint spaceSize = 10000)
		{
			Randomizer<int> randomizer(0, spaceSize);

			sp_float* result = ALLOC_ARRAY(sp_float, count);

			for (sp_uint i = 0; i < count; i++)
				result[i] = randomizer.rand() / 100.0f;

			return result;
		}

	public:

		TEST_METHOD(AlgorithmSorting_Insertion_Test1)
		{
			GpuContext* context = GpuContext::init();
			GpuDevice* gpu = context->defaultDevice;

			sp_uint count = (sp_uint)std::pow(2.0, 17.0);
			sp_float* input1 = getRandom(count);
			sp_float* input2 = ALLOC_COPY(input1, sp_float, count);
			sp_uint stride = 1;
			sp_uint offset = 0;

			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

			AlgorithmSorting::native(input1, count);

			std::chrono::high_resolution_clock::time_point currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			std::ostringstream buildOptions;
			buildOptions << " -DINPUT_STRIDE=" << stride;
			buildOptions << " -DINPUT_OFFSET=" << offset;

			GpuInsertionSorting* insertionSortGpu = ALLOC_NEW(GpuInsertionSorting)();
			insertionSortGpu->init(gpu, buildOptions.str().c_str())->setParameters(input2, count, stride, offset);

			currentTime = std::chrono::high_resolution_clock::now();

			cl_mem output = insertionSortGpu->execute();

			currentTime2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - currentTime);

			sp_uint* orderedIndexes = ALLOC_ARRAY(sp_uint, count);
			gpu->commandManager->executeReadBuffer(output, count * SIZEOF_UINT, orderedIndexes, true);

			for (sp_uint i = 0; i < count - 1; i++)
				Assert::IsTrue(input2[orderedIndexes[i]] <= input2[orderedIndexes[i+1]], L"Wrong value.", LINE_INFO());

			for (sp_uint i = 0; i < count; i++)
				Assert::AreEqual(input1[i], input2[orderedIndexes[i]], L"Wrong value.", LINE_INFO());

			gpu->releaseBuffer(output);
			ALLOC_DELETE(insertionSortGpu, GpuInsertionSorting);
			ALLOC_RELEASE(input1);
		}

	};

}

#endif