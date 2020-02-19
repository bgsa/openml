#ifdef OPENCL_ENABLED

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
	return ALLOC_NEW(GpuCommand)(deviceId, deviceContext, commandQueue);
}

size_t GpuCommandManager::cacheProgram(const char* source, size_t sourceSize, const char* buildOptions)
{
	cl_int errorCode;
	cl_program program = clCreateProgramWithSource(deviceContext, 1, &source, &sourceSize, &errorCode);
	HANDLE_OPENCL_ERROR(errorCode);

	cachedPrograms.emplace_back(program);

	const char* defaultOptions = "-Werror -cl-denorms-are-zero -cl-mad-enable -cl-finite-math-only \0";
	// -cl-no-signed-zero   -cl-fast-relaxed-math    not working

	char* options = StringHelper::crate();
	StringHelper::copy(defaultOptions, options);

	if (buildOptions != NULL)
		StringHelper::append(buildOptions, options, DEFAULT_STRING_LENGTH);

	HANDLE_OPENCL_BUILD_ERROR(clBuildProgram(program, 1, &deviceId, options, NULL, NULL), program, deviceId);

	ALLOC_RELEASE(options);
	return cachedPrograms.size() - 1;
}

void GpuCommandManager::executeReadBuffer(cl_mem gpuBuffer, size_t bufferSize, void* cpuBuffer, bool waitToFinish)
{
	HANDLE_OPENCL_RUNTIME_ERROR(clEnqueueReadBuffer(commandQueue, gpuBuffer, waitToFinish, 0, bufferSize, cpuBuffer, 0, NULL, NULL));
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

	for each (cl_program program in cachedPrograms)
		HANDLE_OPENCL_ERROR(clReleaseProgram(program));

	HANDLE_OPENCL_ERROR(clReleaseCommandQueue(commandQueue));
}

#endif