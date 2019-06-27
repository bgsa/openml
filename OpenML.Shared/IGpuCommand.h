/*
#pragma once

#include "GpuContext.h"

namespace OpenML
{
	class GpuCommandManager;

	class IGpuCommand
	{
		friend class GpuCommandManager;

	protected:
		cl_command_queue* commandQueue = nullptr;

		virtual IGpuCommand* create(GpuCommandManager* commandManager) = 0;

	public:
		
	};

}
*/
