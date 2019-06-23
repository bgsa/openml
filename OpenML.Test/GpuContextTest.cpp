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
			GpuContext* gpu = GpuContext::instance();

			delete gpu;
		}

	};
}