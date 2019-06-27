#include "GpuCommand.h"

GpuCommand::GpuCommand(cl_device_id deviceId, cl_context deviceContext, cl_command_queue commandQueue)
{
	this->deviceId = deviceId;
	this->deviceContext= deviceContext;
	this->commandQueue = commandQueue;
}

GpuCommand* GpuCommand::setInputParameter(void* value, size_t sizeOfValue)
{
	cl_int errorCode;
	cl_mem memoryBuffer = clCreateBuffer(deviceContext, CL_MEM_READ_ONLY, sizeOfValue, NULL, &errorCode);

	errorCode = clEnqueueWriteBuffer(commandQueue, memoryBuffer, CL_TRUE, 0, sizeOfValue, value, 0, NULL, NULL);

	inputParameters.emplace_back(memoryBuffer);

	return this;
}

GpuCommand* GpuCommand::setOutputParameter(size_t sizeOfValue)
{
	cl_int errorCode;
	outputParameter = clCreateBuffer(deviceContext, CL_MEM_WRITE_ONLY, sizeOfValue, NULL, &errorCode);
	outputSize = sizeOfValue;

	return this;
}

GpuCommand* GpuCommand::build(const char* source, size_t sourceSize, std::string kernelName)
{
	cl_int errorCode;

	program = clCreateProgramWithSource(deviceContext, 1, &source, &sourceSize, &errorCode);

	errorCode = clBuildProgram(program, 1, &deviceId, NULL, NULL, NULL);

	kernel = clCreateKernel(program, kernelName.c_str(), &errorCode);

	for (size_t i = 0; i < inputParameters.size(); i++)
		errorCode = clSetKernelArg(kernel, i, sizeof(cl_mem), (void *)&inputParameters[i]);

	clSetKernelArg(kernel, inputParameters.size(), sizeof(cl_mem), (void *)&outputParameter);

	return this;
}

GpuCommand* GpuCommand::execute(size_t* globalWorkSize, size_t* localWorkSize)
{
	cl_int errorCode;
	errorCode = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);

	return this;
}

template <typename T>
T* GpuCommand::fetch()
{
	cl_int errorCode;

	void* result = std::malloc(outputSize);

	errorCode = clEnqueueReadBuffer(commandQueue, outputParameter, CL_TRUE, 0, outputSize, result, 0, NULL, NULL);

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


GpuCommand::~GpuCommand()
{
	cl_int errorCode;

	if (kernel != nullptr)
	{
		errorCode = clReleaseKernel(kernel);
		kernel = nullptr;
	}
		
	if (program != nullptr)
	{
		errorCode = clReleaseProgram(program);
		program = nullptr;
	}
	
	for (size_t i = 0; i < inputParameters.size(); i++)
		errorCode = clReleaseMemObject(inputParameters[i]);

	if (outputParameter != nullptr)
	{
		errorCode = clReleaseMemObject(outputParameter);
		outputParameter = nullptr;
	}
}