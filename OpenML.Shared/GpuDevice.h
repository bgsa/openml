#pragma once

#include <OpenML.h>
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
		std::string profile;

		GpuCommandManager* commandManager = nullptr;
		
		GpuDevice(cl_device_id id);

		bool isGPU();
		bool isCPU();

		~GpuDevice();
	};

}