#include "GpuCommandManager.h"

GpuCommandManager::GpuCommandManager(cl_context deviceContext, cl_device_id deviceId)
{
	this->deviceContext = deviceContext;
	this->deviceId = deviceId;

	cl_int errorCode;
	commandQueue = clCreateCommandQueue(deviceContext, deviceId, 0, &errorCode);
}

GpuCommand* GpuCommandManager::createCommand()
{
	return new GpuCommand(deviceId, deviceContext, commandQueue);
}

GpuCommandManager::~GpuCommandManager()
{
	cl_int errorCode; 
	
	errorCode = clFlush(commandQueue);
	errorCode = clFinish(commandQueue);
	errorCode = clReleaseCommandQueue(commandQueue);
}