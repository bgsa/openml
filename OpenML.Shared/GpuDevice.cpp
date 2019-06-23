#include "GpuDevice.h"


GpuDevice::GpuDevice(GpuContext* context, cl_device_id id)
{
	this->context = context;
	this->id = id;

	cl_int errorCode;
	this->deviceContext = clCreateContext(NULL, 1, &this->id, NULL, NULL, &errorCode);
		
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
	
	clGetDeviceInfo(id, CL_DEVICE_TYPE, sizeof(type), &type, NULL);
	clGetDeviceInfo(id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(computeUnits), &computeUnits, NULL);
}

GpuDevice::~GpuDevice()
{
	if (deviceContext != nullptr) 
	{
		clReleaseContext(deviceContext);
		deviceContext = nullptr;
	}

	delete[] name;
	delete[] version;
	delete[] driverVersion;
}
