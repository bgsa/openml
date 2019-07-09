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

	errorCode = clEnqueueWriteBuffer(commandQueue, memoryBuffer, CL_TRUE, 0, sizeOfValue, value, 0, NULL, NULL);

	assert(errorCode == CL_SUCCESS);

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

	assert(errorCode == CL_SUCCESS);

	return this;
}

GpuCommand* GpuCommand::build(const char* source, size_t sourceSize, std::string kernelName)
{
	cl_int errorCode;
	program = clCreateProgramWithSource(deviceContext, 1, &source, &sourceSize, &errorCode);

	assert(errorCode == CL_SUCCESS);

	errorCode = clBuildProgram(program, 1, &deviceId, NULL, NULL, NULL);

#if  DEBUG
	if (errorCode == CL_BUILD_PROGRAM_FAILURE) 
	{
		size_t logSize;
		errorCode = clGetProgramBuildInfo(program, deviceId, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
		char* msg = (char*)malloc((logSize + 1));
		clGetProgramBuildInfo(program, deviceId, CL_PROGRAM_BUILD_LOG, logSize, msg, NULL);
		msg[logSize] = '\0';

		assert(false);
		free(msg);
	}
#endif


	assert(errorCode == CL_SUCCESS);

	kernel = clCreateKernel(program, kernelName.c_str(), &errorCode);

	assert(errorCode == CL_SUCCESS);

	for (size_t i = 0; i < inputParameters.size(); i++) 
	{
		errorCode = clSetKernelArg(kernel, i, sizeof(cl_mem), (void *)&inputParameters[i]);
		assert(errorCode == CL_SUCCESS);
	}

	clSetKernelArg(kernel, inputParameters.size(), sizeof(cl_mem), (void *)&outputParameter);

	return this;
}

GpuCommand* GpuCommand::execute(size_t workDimnmsion, size_t* globalWorkSize, size_t* localWorkSize)
{
	assert(isPowerOf2(*globalWorkSize));
	//assert(isPowerOf2(*localWorkSize));

	cl_int errorCode;
	errorCode = clEnqueueNDRangeKernel(commandQueue, kernel, workDimnmsion, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);

	assert(errorCode == CL_SUCCESS);

	return this;
}

template <typename T>
T* GpuCommand::fetch()
{
	void* result = std::malloc(outputSize);

	cl_int errorCode = clEnqueueReadBuffer(commandQueue, outputParameter, CL_TRUE, 0, outputSize, result, 0, NULL, NULL);

	assert(errorCode == CL_SUCCESS);

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

template <typename T>
T* GpuCommand::fetchInOutParameter(size_t index)
{
	size_t size = inputParametersSize[index];

	void* result = std::malloc(size);
	cl_int errorCode = clEnqueueReadBuffer(commandQueue, inputParameters[index], CL_TRUE, 0, size, result, 0, NULL, NULL);

	assert(errorCode == CL_SUCCESS);

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