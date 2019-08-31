#if OPENCL_ENABLED

#include "GpuDevice.h"

GpuDevice::GpuDevice(cl_device_id id)
{
	this->id = id;

	cl_int errorCode;
	this->deviceContext = clCreateContext(NULL, 1, &this->id, NULL, NULL, &errorCode);
	HANDLE_OPENCL_ERROR(errorCode);

	this->commandManager = new GpuCommandManager(deviceContext, id);
		
	size_t valueSize;
	clGetDeviceInfo(id, CL_DEVICE_NAME, 0, NULL, &valueSize);
	name = (char*)ALLOC_SIZE(valueSize);
	clGetDeviceInfo(id, CL_DEVICE_NAME, valueSize, name, NULL);

	clGetDeviceInfo(id, CL_DEVICE_VERSION, 0, NULL, &valueSize);
	version = (char*)ALLOC_SIZE(valueSize);
	clGetDeviceInfo(id, CL_DEVICE_VERSION, valueSize, version, NULL);

	clGetDeviceInfo(id, CL_DRIVER_VERSION, 0, NULL, &valueSize);
	driverVersion = (char*)ALLOC_SIZE(valueSize);
	clGetDeviceInfo(id, CL_DRIVER_VERSION, valueSize, driverVersion, NULL);
	
	//clGetDeviceInfo(id, CL_DEVICE_AVAILABLE, sizeof(isAvailable), &isAvailable, NULL);	
	clGetDeviceInfo(id, CL_DEVICE_TYPE, sizeof(type), &type, NULL);
	clGetDeviceInfo(id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(computeUnits), &computeUnits, NULL);
	clGetDeviceInfo(id, CL_DEVICE_MAX_PARAMETER_SIZE, sizeof(maxParameterSize), &maxParameterSize, NULL);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(maxWorkGroupSize), &maxWorkGroupSize, NULL);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(maxWorkItemDimension), &maxWorkItemDimension, NULL);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(size_t) * 3, maxWorkItemSizes, NULL);
	clGetDeviceInfo(id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &globalMemorySize, NULL);
	clGetDeviceInfo(id, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(cl_ulong), &globalMemoryCacheSize, NULL);	
	clGetDeviceInfo(id, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &localMemorySize, NULL);
	
	clGetDeviceInfo(id, CL_DEVICE_PROFILE, 0, NULL, &valueSize);
	char* profileAsArray = (char*)ALLOC_SIZE(valueSize);
	clGetDeviceInfo(id, CL_DEVICE_PROFILE, valueSize, profileAsArray, NULL);
	profile = std::string(profileAsArray);

	clGetDeviceInfo(id, CL_DEVICE_EXTENSIONS, 0, NULL, &valueSize);
	char* extensionsAsArray = (char*)ALLOC_SIZE(valueSize);
	clGetDeviceInfo(id, CL_DEVICE_EXTENSIONS, valueSize, extensionsAsArray, NULL);

	std::string extensionName;
	for (size_t i = 0; i < valueSize; i++)
	{
		if (extensionsAsArray[i] == ' ')
		{
			extensions.emplace_back(extensionName);
			extensionName.clear();
		}
		else
			extensionName += extensionsAsArray[i];
	}

	ALLOC_RELEASE(profileAsArray);;
}

bool GpuDevice::isGPU() 
{
	return (type & CL_DEVICE_TYPE_GPU) || (type & CL_DEVICE_TYPE_ALL);
}

bool GpuDevice::isCPU()
{
	return (type & CL_DEVICE_TYPE_CPU) || (type & CL_DEVICE_TYPE_ALL);
}

cl_mem GpuDevice::createBuffer(size_t sizeOfValue, cl_mem_flags memoryFlags)
{
	cl_int errorCode;
	cl_mem memoryBuffer = clCreateBuffer(deviceContext, memoryFlags, sizeOfValue, NULL, &errorCode);
	HANDLE_OPENCL_ERROR(errorCode);

	return memoryBuffer;
}

void GpuDevice::releaseBuffer(cl_mem memoryBuffer)
{
	HANDLE_OPENCL_ERROR(clReleaseMemObject(memoryBuffer));
}

GpuDevice::~GpuDevice()
{
	if (commandManager != nullptr)
	{
		delete commandManager;
		commandManager = nullptr;
	}

	clReleaseContext(deviceContext);

	ALLOC_RELEASE(driverVersion);
	ALLOC_RELEASE(version);
	ALLOC_RELEASE(name);
}

#endif