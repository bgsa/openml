#pragma once

#include "CppUnitTest.h"
#include "TestHeader.h"
#include <chrono>
#include <algorithm>
#include "MemoryAllocatorManager.h"

#if OPENCL_ENABLED
	#include <GpuCommand.h>
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
	MemoryAllocatorManager::init(ONE_MEGABYTE * 512);
	Logger::WriteMessage("TEST MODULE INITIALIZED");
}

TEST_MODULE_CLEANUP(ModuleCleanup)
{
	MemoryAllocatorManager::release();
	Logger::WriteMessage("TEST MODULE FINISHED");
}