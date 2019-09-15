#ifdef OPENCL_ENABLED

#pragma once

#ifdef APPLE
	#include <OpenCL/opencl.h>
#else
	#include <CL/cl.h>
#endif

#include "OpenML.h"
#include "GpuDevice.h"

namespace OpenML
{
	class GpuContext
	{
	private:
		cl_platform_id platformId;
		
		GpuContext(cl_platform_id platformId);

	public:
		std::vector<GpuDevice*> devices;
		GpuDevice* defaultDevice = nullptr;
		
		API_INTERFACE static GpuContext* init();
		API_INTERFACE static GpuContext* init(cl_platform_id platformId);

		API_INTERFACE static std::vector<cl_platform_id> getPlatforms();

		API_INTERFACE static cl_platform_id GpuContext::getDefaultPlatforms();
		
		~GpuContext();
	};

}

#endif