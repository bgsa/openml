/*
#pragma once

#include "GpuCommandManager.h"

namespace OpenML
{

	class GpuCommandFactory
	{
		friend class GpuDevice;

	private:
		GpuCommandManager* commandManager = nullptr;

		GpuCommandFactory(GpuCommandManager* commandManager)
		{
			this->commandManager = commandManager;
		}

	public:

		//IGpuCommand* create();
	};

}
*/