#pragma once

#include "GpuContext.h"

namespace OpenML
{
	class GpuCommand
	{
	private:
		GpuContext* context = nullptr;

		cl_program program = nullptr;
		cl_command_queue commandQueue = nullptr;
		cl_kernel kernel = nullptr;

		std::vector<cl_mem> inputParameters;
		cl_mem outputParameter = nullptr;
		size_t outputSize = 0;

		GpuCommand(GpuContext* context);

	public:

		static GpuCommand* create(GpuContext* context);

		GpuCommand* setInputParameter(void* value, size_t sizeOfValue);

		GpuCommand* setOutputParameter(size_t sizeOfValue);

		GpuCommand* setSource(const char* source, size_t sourceSize);

		GpuCommand* build(std::string kernelName);

		GpuCommand* execute(size_t* globalWorkSize, size_t* localWorkSize);

		template <typename T>
		T* fetch();

		~GpuCommand();
	};

}