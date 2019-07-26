#if OPENCL_ENABLED

#include "GpuCommand.h"

GpuCommand::GpuCommand(cl_device_id deviceId, cl_context deviceContext, cl_command_queue commandQueue)
{
	this->deviceId = deviceId;
	this->deviceContext= deviceContext;
	this->commandQueue = commandQueue;
}

GpuCommand* GpuCommand::setInputParameter(void* value, size_t sizeOfValue, cl_mem_flags memoryFlags)
{
	cl_int errorCode;
	cl_mem memoryBuffer = clCreateBuffer(deviceContext, memoryFlags, sizeOfValue, NULL, &errorCode);
	HANDLE_OPENCL_ERROR(errorCode);

	HANDLE_OPENCL_ERROR(clEnqueueWriteBuffer(commandQueue, memoryBuffer, CL_TRUE, 0, sizeOfValue, value, 0, NULL, NULL));

	inputParameters.emplace_back(memoryBuffer);
	inputParametersSize.emplace_back(sizeOfValue);

	return this;
}

GpuCommand* GpuCommand::setInputParameter(void* value, size_t sizeOfValue)
{
	return setInputParameter(value, sizeOfValue, CL_MEM_READ_ONLY);
}

GpuCommand* GpuCommand::setOutputParameter(size_t sizeOfValue)
{
	cl_int errorCode;
	outputParameter = clCreateBuffer(deviceContext, CL_MEM_WRITE_ONLY, sizeOfValue, NULL, &errorCode);
	outputSize = sizeOfValue;

	HANDLE_OPENCL_ERROR(errorCode);

	return this;
}

GpuCommand* GpuCommand::build(const char* source, size_t sourceSize, std::string kernelName)
{
	cl_int errorCode;
	program = clCreateProgramWithSource(deviceContext, 1, &source, &sourceSize, &errorCode);

	HANDLE_OPENCL_ERROR(errorCode);

	HANDLE_OPENCL_BUILD_ERROR(clBuildProgram(program, 1, &deviceId, NULL, NULL, NULL), program, deviceId);
	
	kernel = clCreateKernel(program, kernelName.c_str(), &errorCode);

	HANDLE_OPENCL_ERROR(errorCode);

	for (size_t i = 0; i < inputParameters.size(); i++) 
		HANDLE_OPENCL_ERROR(clSetKernelArg(kernel, i, sizeof(cl_mem), (void *)&inputParameters[i]));

	clSetKernelArg(kernel, inputParameters.size(), sizeof(cl_mem), (void *)&outputParameter);

	return this;
}

GpuCommand* GpuCommand::execute(size_t workDimnmsion, size_t* globalWorkSize, size_t* localWorkSize, const size_t* globalOffset)
{
	assert(isPowerOf2(*globalWorkSize));
	//assert(isPowerOf2(*localWorkSize));

	cl_event* events = NULL;

#ifdef DEBUG
	events = new cl_event[1];
	cl_ulong time_start, time_end;
#endif

	HANDLE_OPENCL_ERROR(clEnqueueNDRangeKernel(commandQueue, kernel, workDimnmsion, globalOffset, globalWorkSize, localWorkSize, 0, NULL, events));

#ifdef DEBUG
	clWaitForEvents(1, events);
	clGetEventProfilingInfo(events[0], CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(events[0], CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

	timeToExecuteInMiliseconds = (time_end - time_start) / 1000000.0;

	delete[] events;
#endif

	return this;
}

void GpuCommand::fetch(void* buffer)
{
	HANDLE_OPENCL_RUNTIME_ERROR(clEnqueueReadBuffer(commandQueue, outputParameter, CL_TRUE, 0, outputSize, buffer, 0, NULL, NULL));
}

template <typename T>
T* GpuCommand::fetch()
{
	void* result = std::malloc(outputSize);

	HANDLE_OPENCL_RUNTIME_ERROR(clEnqueueReadBuffer(commandQueue, outputParameter, CL_TRUE, 0, outputSize, result, 0, NULL, NULL));
	
	return (T*) result;
}
template void* GpuCommand::fetch();
template short* GpuCommand::fetch();
template char* GpuCommand::fetch();
template int* GpuCommand::fetch();
template size_t* OpenML::GpuCommand::fetch();
template long long* OpenML::GpuCommand::fetch();
template float* GpuCommand::fetch();
template double* GpuCommand::fetch();

void GpuCommand::fetchInOutParameter(void* buffer, size_t index)
{
	size_t size = inputParametersSize[index];	

	HANDLE_OPENCL_RUNTIME_ERROR(clEnqueueReadBuffer(commandQueue, inputParameters[index], CL_TRUE, 0, size, buffer, 0, NULL, NULL));
}

template <typename T>
T* GpuCommand::fetchInOutParameter(size_t index)
{
	size_t size = inputParametersSize[index];

	void* result = std::malloc(size);

	HANDLE_OPENCL_RUNTIME_ERROR(clEnqueueReadBuffer(commandQueue, inputParameters[index], CL_TRUE, 0, size, result, 0, NULL, NULL));

	return (T*)result;
}
template void* GpuCommand::fetchInOutParameter(size_t index);
template short* GpuCommand::fetchInOutParameter(size_t index);
template char* GpuCommand::fetchInOutParameter(size_t index);
template int* GpuCommand::fetchInOutParameter(size_t index);
template size_t* GpuCommand::fetchInOutParameter(size_t index);
template long long* GpuCommand::fetchInOutParameter(size_t index);
template float* GpuCommand::fetchInOutParameter(size_t index);
template double* GpuCommand::fetchInOutParameter(size_t index);

GpuCommand::~GpuCommand()
{
	cl_int errorCode;

	if (kernel != nullptr)
	{
		errorCode = clReleaseKernel(kernel);
		assert(errorCode == CL_SUCCESS);
		kernel = nullptr;
	}
		
	if (program != nullptr)
	{
		errorCode = clReleaseProgram(program);
		assert(errorCode == CL_SUCCESS);
		program = nullptr;
	}
	
	for (size_t i = 0; i < inputParameters.size(); i++) 
	{
		errorCode = clReleaseMemObject(inputParameters[i]);
		assert(errorCode == CL_SUCCESS);
	}

	if (outputParameter != nullptr)
	{
		errorCode = clReleaseMemObject(outputParameter);
		assert(errorCode == CL_SUCCESS);
		outputParameter = nullptr;
	}
}

#endif