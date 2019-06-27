#pragma once

#include "OpenML.h"
#include "CL/cl.h"

namespace OpenML
{

	class GpuCommand
	{
		friend class GpuCommandManager;

	private:
		cl_device_id deviceId;
		cl_context deviceContext;

		cl_program program = nullptr;
		cl_command_queue commandQueue = nullptr;
		cl_kernel kernel = nullptr;

		std::vector<cl_mem> inputParameters;
		cl_mem outputParameter = nullptr;
		size_t outputSize = 0;
		
		GpuCommand(cl_device_id deviceId, cl_context deviceContext, cl_command_queue commandQueue);

	public:

		GpuCommand* setInputParameter(void* value, size_t sizeOfValue);

		GpuCommand* setOutputParameter(size_t sizeOfValue);
		
		GpuCommand* build(const char* source, size_t sourceSize, std::string kernelName);

		GpuCommand* execute(size_t* globalWorkSize, size_t* localWorkSize);

		template <typename T>
		T* fetch();

		~GpuCommand();
	};

}