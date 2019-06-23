#pragma once

#ifdef APPLE
	#include <OpenCL/opencl.h>
#else
	#include <CL/cl.h>
#endif

#include "OpenML.h"

namespace OpenML
{
	class GpuContext
	{
	private:		
		friend class GpuCommand;

		cl_context openclContext;
		size_t plataformCount;
		cl_platform_id platformId;
		cl_device_id deviceId = NULL;
		cl_uint devicesCount;

		GpuContext();

	public:
		
		API_INTERFACE static GpuContext* instance();
		
		~GpuContext();

	};

}