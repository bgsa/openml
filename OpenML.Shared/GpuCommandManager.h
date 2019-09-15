#ifdef OPENCL_ENABLED

#pragma once

#include "GpuCommand.h"

namespace OpenML
{
	class GpuCommandManager
	{
		friend class GpuDevice;

	private:
		cl_device_id deviceId;
		cl_context deviceContext;
		cl_command_queue commandQueue;

		GpuCommandManager(cl_context deviceContext, cl_device_id deviceId, cl_command_queue_properties queueProperties = NULL);

	public:
		std::vector<cl_program> cachedPrograms;

		GpuCommand* createCommand();

		size_t cacheProgram(const char* source, size_t sourceSize, const char* buildOptions = "-Werror -cl-denorms-are-zero -cl-mad-enable -cl-finite-math-only -cl-finite-math-only");

		void executeReadBuffer(cl_mem gpuBuffer, size_t bufferSize, void* cpuBuffer, bool waitToFinish);

		void flush();

		~GpuCommandManager();
	};

}

#endif