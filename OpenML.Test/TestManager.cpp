#pragma once

#include "CppUnitTest.h"
#include "TestHeader.h"
#include <chrono>
#include "MemoryAllocatorManager.h"

#if OPENCL_ENABLED
	#include <GpuCommand.h>
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

//TEST_DESCRIPTION("asdasdas")
//TEST_OWNER(ownerAlias)

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
	MemoryAllocatorManager::init();
	Logger::WriteMessage("TEST MODULE INITIALIZED");
}

TEST_MODULE_CLEANUP(ModuleCleanup)
{
	MemoryAllocatorManager::release();
	Logger::WriteMessage("TEST MODULE FINISHED");
}