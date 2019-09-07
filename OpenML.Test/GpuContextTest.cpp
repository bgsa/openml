#pragma once

#include "CppUnitTest.h"
#include <GpuContext.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(GpuContextTest)
	{
	public:

		TEST_METHOD(GPUContext_instance_Test)
		{
			std::vector<cl_platform_id> platforms = GpuContext::getPlatforms();

			GpuContext* gpu = GpuContext::init(platforms[0]);

			Assert::IsTrue(gpu != NULL, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(GPUContext_getPlatforms_Test)
		{
			std::vector<cl_platform_id> platforms = GpuContext::getPlatforms();

			Assert::IsTrue(platforms.size() > 0, L"Wrong value.", LINE_INFO());
		}

	};
}