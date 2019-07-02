#if OPENCL_ENABLED

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

		GpuCommandManager(cl_context deviceContext, cl_device_id deviceId);

	public:
		GpuCommand* createCommand();

		~GpuCommandManager();
	};

}

#endif