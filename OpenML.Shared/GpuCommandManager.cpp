#include "GpuCommandManager.h"

GpuCommandManager::GpuCommandManager(cl_context deviceContext, cl_device_id deviceId, cl_command_queue_properties queueProperties)
{
	this->deviceContext = deviceContext;
	this->deviceId = deviceId;

	cl_int errorCode;

#ifdef DEBUG
	if (queueProperties != NULL)
		queueProperties |= CL_QUEUE_PROFILING_ENABLE;
	else
		queueProperties = CL_QUEUE_PROFILING_ENABLE;
#endif
	commandQueue = clCreateCommandQueue(deviceContext, deviceId, queueProperties, &errorCode);

	HANDLE_OPENCL_ERROR(errorCode);
}

GpuCommand* GpuCommandManager::createCommand()
{
	return new GpuCommand(deviceId, deviceContext, commandQueue);
}

void GpuCommandManager::flush()
{
	HANDLE_OPENCL_ERROR(clFlush(commandQueue));
	HANDLE_OPENCL_ERROR(clFinish(commandQueue));
}

GpuCommandManager::~GpuCommandManager()
{
	HANDLE_OPENCL_ERROR(clFlush(commandQueue));
	HANDLE_OPENCL_ERROR(clFinish(commandQueue));
	HANDLE_OPENCL_ERROR(clReleaseCommandQueue(commandQueue));
}