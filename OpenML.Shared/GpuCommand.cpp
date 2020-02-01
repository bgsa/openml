#if OPENCL_ENABLED

#include "GpuCommand.h"

GpuCommand::GpuCommand(cl_device_id deviceId, cl_context deviceContext, cl_command_queue commandQueue)
{
	this->deviceId = deviceId;
	this->deviceContext= deviceContext;
	this->commandQueue = commandQueue;
}

cl_mem GpuCommand::getInputParameter(size_t index)
{
	return inputParameters[index];
}

GpuCommand* GpuCommand::setInputParameter(cl_mem buffer, size_t sizeOfValue)
{	
	inputParameters.emplace_back(buffer);
	inputParametersSize.emplace_back(sizeOfValue);
	inputParametersKeep.emplace_back(true);

	return this;
}

GpuCommand* GpuCommand::setInputParameter(void* value, size_t sizeOfValue, cl_mem_flags memoryFlags, bool keepBuffer)
{
	/* if (value == NULL)
		memoryFlags |= CL_MEM_ALLOC_HOST_PTR;
	else
		memoryFlags |= CL_MEM_USE_HOST_PTR; */

	cl_int errorCode;
	cl_mem memoryBuffer = clCreateBuffer(deviceContext, memoryFlags, sizeOfValue, value, &errorCode);
	HANDLE_OPENCL_ERROR(errorCode);

	HANDLE_OPENCL_ERROR(clEnqueueWriteBuffer(commandQueue, memoryBuffer, CL_FALSE, 0, sizeOfValue, value, 0, NULL, NULL));

	inputParameters.emplace_back(memoryBuffer);
	inputParametersSize.emplace_back(sizeOfValue);
	inputParametersKeep.emplace_back(keepBuffer);

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

GpuCommand* GpuCommand::updateInputParameterValue(size_t index, const void* value)
{
	HANDLE_OPENCL_ERROR(clEnqueueWriteBuffer(commandQueue, 
		inputParameters[index], 
		CL_TRUE, 
		0, 
		inputParametersSize[index],
		value, 
		0, NULL, NULL));

	return this;
}

GpuCommand* GpuCommand::updateInputParameter(size_t index, cl_mem memoryBuffer)
{
	inputParameters[index] = memoryBuffer;

	HANDLE_OPENCL_ERROR(clSetKernelArg(kernel, index, sizeof(cl_mem), &inputParameters[index]));

	return this;
}

GpuCommand* GpuCommand::swapInputParameter(size_t index1, size_t index2)
{
	cl_mem temp1 = inputParameters[index1];
	inputParameters[index1] = inputParameters[index2];
	inputParameters[index2] = temp1;

	size_t temp2 = inputParametersSize[index1];
	inputParametersSize[index1] = inputParametersSize[index2];
	inputParametersSize[index2] = temp2;

	bool temp3 = inputParametersKeep[index1];
	inputParametersKeep[index1] = inputParametersKeep[index2];
	inputParametersKeep[index2] = temp3;

	HANDLE_OPENCL_ERROR(clSetKernelArg(kernel, index1, sizeof(cl_mem), &inputParameters[index1]));
	HANDLE_OPENCL_ERROR(clSetKernelArg(kernel, index2, sizeof(cl_mem), &inputParameters[index2]));

	return this;
}

GpuCommand* GpuCommand::copyParameters(size_t targetParameterIndex, cl_mem source)
{
	HANDLE_OPENCL_ERROR(clEnqueueCopyBuffer(
		commandQueue, 
		source,
		inputParameters[targetParameterIndex], 
		0, 
		0, 
		inputParametersSize[targetParameterIndex],
		0,
		NULL, 
		NULL));

	return this;
}

GpuCommand* GpuCommand::buildFromProgram(cl_program program, const char* kernelName)
{
	cl_int errorCode;

	kernel = clCreateKernel(program, kernelName, &errorCode);
	HANDLE_OPENCL_ERROR(errorCode);

	for (size_t i = 0; i < inputParameters.size(); i++)
		HANDLE_OPENCL_ERROR(clSetKernelArg(kernel, i, sizeof(cl_mem), &inputParameters[i]));

	if (outputParameter != NULL)
		HANDLE_OPENCL_ERROR(clSetKernelArg(kernel, inputParameters.size(), sizeof(cl_mem), &outputParameter));

	return this;
}

GpuCommand* GpuCommand::build(const char* source, size_t sourceSize, const char* kernelName)
{
	cl_int errorCode;
	program = clCreateProgramWithSource(deviceContext, 1, &source, &sourceSize, &errorCode);

	HANDLE_OPENCL_ERROR(errorCode);

	HANDLE_OPENCL_BUILD_ERROR(clBuildProgram(program, 1, &deviceId, NULL, NULL, NULL), program, deviceId);
	
	return buildFromProgram(program, kernelName);
}

GpuCommand* GpuCommand::execute(size_t workDimnmsion, const size_t* globalWorkSize, const size_t* localWorkSize, const size_t* globalOffset)
{
	assert(isPowerOf2(*globalWorkSize));
	//assert(isPowerOf2(*localWorkSize));

	cl_event* events = NULL;

#ifdef DEBUG
	events = ALLOC_ARRAY(cl_event, 1);
	cl_ulong time_start, time_end;
#endif

	HANDLE_OPENCL_ERROR(clEnqueueNDRangeKernel(commandQueue, kernel, workDimnmsion, globalOffset, globalWorkSize, localWorkSize, 0, NULL, events));

#ifdef DEBUG
	clWaitForEvents(1, events);
	clGetEventProfilingInfo(events[0], CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(events[0], CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

	timeToExecuteInMiliseconds = (time_end - time_start) / 1000000.0;

	ALLOC_RELEASE(events);
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
	void* result = ALLOC_SIZE(outputSize);

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

	void* result = ALLOC_SIZE(size);

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
template bool* GpuCommand::fetchInOutParameter(size_t index);

GpuCommand::~GpuCommand()
{
	if (kernel != nullptr)
	{
		HANDLE_OPENCL_ERROR(clReleaseKernel(kernel));
		kernel = nullptr;
	}
		
	if (program != nullptr)
	{
		HANDLE_OPENCL_ERROR(clReleaseProgram(program));
		program = nullptr;
	}
	
	for (size_t i = 0; i < inputParameters.size(); i++) 
		if (!inputParametersKeep[i]) 
			HANDLE_OPENCL_ERROR(clReleaseMemObject(inputParameters[i]));

	if (outputParameter != nullptr)
	{
		HANDLE_OPENCL_ERROR(clReleaseMemObject(outputParameter));
		outputParameter = nullptr;
	}
}

#endif