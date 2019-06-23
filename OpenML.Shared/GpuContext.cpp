#include "GpuContext.h"

static GpuContext* gpu = nullptr;

GpuContext::GpuContext()
{
}

GpuContext* GpuContext::instance()
{
	if (gpu != nullptr)
		return gpu;
	
	gpu = new GpuContext;

	clGetPlatformIDs(1, &gpu->platformId, &gpu->plataformCount);
	clGetDeviceIDs(gpu->platformId, CL_DEVICE_TYPE_DEFAULT, 1, &gpu->deviceId, &gpu->devicesCount);

	cl_int errorCode;
	gpu->openclContext = clCreateContext(NULL, 1, &gpu->deviceId, NULL, NULL, &errorCode);

	return gpu;
}

GpuContext::~GpuContext()
{
	if (openclContext != nullptr) 
	{
		clReleaseContext(openclContext);
		openclContext = nullptr;
	}
}