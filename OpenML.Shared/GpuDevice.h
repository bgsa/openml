#pragma once

#include <OpenML.h>
#include <CL/cl.h>

namespace OpenML
{
	class GpuContext;

	class GpuDevice
	{
	private:
		GpuContext* context = nullptr;

	public:
		cl_device_id id;
		cl_context deviceContext;
		char* name;
		char* version;
		char* driverVersion;
		cl_device_type type;
		cl_uint computeUnits;
		
		GpuDevice(GpuContext* context, cl_device_id id);

		~GpuDevice();
	};

}