#if OPENCL_ENABLED

#pragma once

#include "OpenML.h"
#include "GpuLog.hpp"
#include "CL/cl.h"

namespace OpenML
{

	class GpuCommand
	{
		friend class GpuCommandManager;

	private:
		cl_device_id deviceId;
		cl_context deviceContext;

		cl_program program = NULL;
		cl_command_queue commandQueue = NULL;
		cl_kernel kernel = NULL;

		std::vector<cl_mem> inputParameters;
		std::vector<size_t> inputParametersSize;
		std::vector<bool> inputParametersKeep;
		cl_mem outputParameter = NULL;
		size_t outputSize = 0;
				
		GpuCommand(cl_device_id deviceId, cl_context deviceContext, cl_command_queue commandQueue);

	public:

		double timeToExecuteInMiliseconds = 0.0;

		cl_mem getInputParameter(size_t index);

		GpuCommand* setInputParameter(void* value, size_t sizeOfValue, cl_mem_flags memoryFlags, bool keepBuffer = false);
		GpuCommand* setInputParameter(void* value, size_t sizeOfValue);
		GpuCommand* setInputParameter(cl_mem buffer, size_t sizeOfValue);

		GpuCommand* updateInputParameterValue(size_t index, const void* value);
		GpuCommand* updateInputParameter(size_t index, cl_mem memoryBuffer);

		cl_mem getOutputParameter();
		GpuCommand* setOutputParameter(size_t sizeOfValue);

		GpuCommand* swapInputParameter(size_t index1, size_t index2);

		GpuCommand* copyParameters(size_t targetParameterIndex, cl_mem destination);
		
		GpuCommand* buildFromProgram(cl_program program, const char* kernelName);
		GpuCommand* build(const char* source, size_t sourceSize, const char* kernelName);

		GpuCommand* execute(size_t workDimnmsion, const size_t* globalWorkSize, const size_t* localWorkSize, const size_t* globalOffset = NULL);

		void fetch(void* buffer);

		template <typename T> 
		T* fetch();

		void fetchInOutParameter(void* buffer, size_t index);

		template <typename T>
		T* fetchInOutParameter(size_t index);

		~GpuCommand();
	};

}

#endif