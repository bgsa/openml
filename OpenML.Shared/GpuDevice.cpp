#include "GpuDevice.h"

GpuDevice::GpuDevice(cl_device_id id)
{
	this->id = id;

	cl_int errorCode;
	this->deviceContext = clCreateContext(NULL, 1, &this->id, NULL, NULL, &errorCode);

	this->commandManager = new GpuCommandManager(deviceContext, id);
		
	size_t valueSize;
	clGetDeviceInfo(id, CL_DEVICE_NAME, 0, NULL, &valueSize);
	name = (char*)std::malloc(valueSize);
	clGetDeviceInfo(id, CL_DEVICE_NAME, valueSize, name, NULL);

	clGetDeviceInfo(id, CL_DEVICE_VERSION, 0, NULL, &valueSize);
	version = (char*)std::malloc(valueSize);
	clGetDeviceInfo(id, CL_DEVICE_VERSION, valueSize, version, NULL);

	clGetDeviceInfo(id, CL_DRIVER_VERSION, 0, NULL, &valueSize);
	driverVersion = (char*)malloc(valueSize);
	clGetDeviceInfo(id, CL_DRIVER_VERSION, valueSize, driverVersion, NULL);
	
	//clGetDeviceInfo(id, CL_DEVICE_AVAILABLE, sizeof(isAvailable), &isAvailable, NULL);	
	clGetDeviceInfo(id, CL_DEVICE_TYPE, sizeof(type), &type, NULL);
	clGetDeviceInfo(id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(computeUnits), &computeUnits, NULL);
	clGetDeviceInfo(id, CL_DEVICE_MAX_PARAMETER_SIZE, sizeof(maxParameterSize), &maxParameterSize, NULL);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(maxWorkGroupSize), &maxWorkGroupSize, NULL);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(maxWorkItemDimension), &maxWorkItemDimension, NULL);

	clGetDeviceInfo(id, CL_DEVICE_PROFILE, 0, NULL, &valueSize);
	char* profileAsArray = (char*)malloc(valueSize);
	clGetDeviceInfo(id, CL_DEVICE_PROFILE, valueSize, profileAsArray, NULL);
	profile = std::string(profileAsArray);

	clGetDeviceInfo(id, CL_DEVICE_EXTENSIONS, 0, NULL, &valueSize);
	char* extensionsAsArray = (char*)malloc(valueSize);
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

	delete[] extensionsAsArray, profileAsArray;;
}

bool GpuDevice::isGPU() 
{
	return (type & CL_DEVICE_TYPE_GPU) || (type & CL_DEVICE_TYPE_ALL);
}

bool GpuDevice::isCPU()
{
	return (type & CL_DEVICE_TYPE_CPU) || (type & CL_DEVICE_TYPE_ALL);
}

GpuDevice::~GpuDevice()
{
	if (commandManager != nullptr)
	{
		delete commandManager;
		commandManager = nullptr;
	}

	clReleaseContext(deviceContext);

	delete[] name;
	delete[] version;
	delete[] driverVersion;
}
