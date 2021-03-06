#if OPENCL_ENABLED

#pragma once

#include <OpenML.h>
#include <algorithm>
#include <CL/cl.h>

#include "GpuCommandManager.h"

namespace OpenML
{
	class GpuDevice
	{
	private:
		cl_device_id id;
		cl_context deviceContext;

	public:
		char* name;
		char* version;
		char* driverVersion;
		cl_device_type type;
		cl_uint computeUnits;
		//bool isAvailable = false;
		std::vector<std::string> extensions;
		size_t maxParameterSize = 256;
		size_t maxWorkGroupSize = 1;
		cl_uint maxWorkItemDimension = 3;
		size_t maxWorkItemSizes[3];
		cl_ulong globalMemorySize;
		cl_ulong globalMemoryCacheSize;
		cl_ulong localMemorySize;
		cl_ulong localMemoryLength;
		cl_ulong maxMemoryAllocSize;
		cl_ulong constantsBufferSize;
		cl_uint maxConstantArgument;
		cl_uint memoryAlign;
		cl_uint clockFrequency;
		std::string profile;

		GpuCommandManager* commandManager = nullptr;
		
		GpuDevice(cl_device_id id);

		bool isGPU();
		bool isCPU();

		cl_mem createBuffer(size_t sizeOfValue, cl_mem_flags memoryFlags);
		cl_mem createBuffer(void * value, size_t sizeOfValue, cl_mem_flags memoryFlags, bool writeValueOnDevice = true);
		void releaseBuffer(cl_mem memoryBuffer);
		void releaseBuffer(size_t length, cl_mem memoryBuffers ...);

		size_t getLocalWorkSize(size_t elementsLength);

		size_t getThreadLength(size_t elementsLength);

		~GpuDevice();
	};

}

#endif