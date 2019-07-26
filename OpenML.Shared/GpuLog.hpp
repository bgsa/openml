#ifdef OPENCL_ENABLED

#pragma once

#include "OpenML.h"
#include <CL/cl.h>

#if DEBUG
	#define HANDLE_OPENCL_ERROR(errorCode) GpuLog::handleCompileError(errorCode);
#else
	#define HANDLE_OPENCL_ERROR
#endif

#if DEBUG
#define HANDLE_OPENCL_RUNTIME_ERROR(errorCode) GpuLog::handleRuntimeError(errorCode);
#else
#define HANDLE_OPENCL_RUNTIME_ERROR
#endif

#if DEBUG
	#define HANDLE_OPENCL_BUILD_ERROR(errorCode, program, deviceId) GpuLog::handleBuildError(errorCode, program, deviceId);
#else
	#define HANDLE_OPENCL_BUILD_ERROR
#endif

namespace OpenML
{

	class GpuLog
	{
	public:

		///<summary>
		///Handle Build errors
		///</summary>
		API_INTERFACE static void handleBuildError(int errorCode, cl_program program, cl_device_id deviceId)
		{
			if (errorCode == CL_BUILD_PROGRAM_FAILURE)
			{
				size_t logSize;

				errorCode = clGetProgramBuildInfo(program, deviceId, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);

				char* errorMessage = (char*)malloc((logSize + 1));

				clGetProgramBuildInfo(program, deviceId, CL_PROGRAM_BUILD_LOG, logSize, errorMessage, NULL);

				errorMessage[logSize] = '\0';

				assert(false);
				std::free(errorMessage);
			}
		}

		///<summary>
		///Handle Runtime errors
		///</summary>
		API_INTERFACE static void handleRuntimeError(int errorCode)
		{
			std::string runtimeError = runtimeErrorMessage(errorCode);
			assert(errorCode == CL_SUCCESS);
		}

		///<summary>
		///Handle Compíle errors
		///</summary>
		API_INTERFACE static void handleCompileError(int errorCode)
		{
			std::string compileError = compileErrorMessage(errorCode);
			assert(errorCode == CL_SUCCESS);
		}

		///<summary>
		///Get the runtime error message, given the opencl code
		///</summary>
		API_INTERFACE static std::string runtimeErrorMessage(int errorCode)
		{
			switch (errorCode)
			{
			case CL_SUCCESS:
				return "Success";

			case CL_DEVICE_NOT_FOUND:
				return "Device not found";

			case CL_DEVICE_NOT_AVAILABLE:
				return "Device not available";

			case CL_COMPILER_NOT_AVAILABLE:
				return "Compiler not available";

			case CL_MEM_OBJECT_ALLOCATION_FAILURE :
				return "Memory allocation failure";

			case CL_OUT_OF_RESOURCES:
				return "Out of resources";

			case CL_OUT_OF_HOST_MEMORY:
				return "Out of host memory";

			case CL_PROFILING_INFO_NOT_AVAILABLE:
				return "Profiling Info not available";

			case CL_MEM_COPY_OVERLAP:
				return "Memory copy overlapy (eg: source and destination buffer are the same)";

			case CL_IMAGE_FORMAT_MISMATCH:
				return "Image format mismatch (eg: the source and destination image do not use the same format)";

			case CL_IMAGE_FORMAT_NOT_SUPPORTED:
				return "Image format not supported";

			case CL_BUILD_PROGRAM_FAILURE:
				return "Build program failure";

			case CL_MAP_FAILURE:
				return "Map failure: failure to map the requested region into the host address space";

			case CL_MISALIGNED_SUB_BUFFER_OFFSET:
				return "Sub-buffer object is specified as the value for an argument that is a buffer object and the offset specified when the sub-buffer object is created is not aligned to the device memory allignment";

			case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
				return "The execution status of any of the events in event_list is a negative integer value";

			case CL_COMPILE_PROGRAM_FAILURE:
				return "There is a failure to compile the program source";

			case CL_LINKER_NOT_AVAILABLE:
				return "Linker is not available (eg: CL_DEVICE_LINKER_AVAILABLE specified in the table of allowed values for param_name for clGetDeviceInfo is set to CL_FALSE)";

			case CL_LINK_PROGRAM_FAILURE:
				return "There is a failure to link the compiled binaries and/or libraries";

			case CL_DEVICE_PARTITION_FAILED:
				return "The partition name is supported by the implementation but in_device could not be further partitioned";

			case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:
				return "The argument information is not available for kernel";

			default:
				return "Unknonwn OpenCL runtime error";
			}
		}

		///<summary>
		///Get the compile error message, given the opencl code
		///</summary>
		API_INTERFACE static std::string compileErrorMessage(int errorCode)
		{
			switch (errorCode)
			{
			case CL_SUCCESS:
				return "Success";

			case CL_INVALID_VALUE:
				return "Invalid value";

			case CL_INVALID_DEVICE_TYPE:
				return "Invalid device type";

			case CL_INVALID_PLATFORM:
				return "Invalid plataform";

			case CL_INVALID_DEVICE:
				return "Invalid device";

			case CL_INVALID_CONTEXT:
				return "Invalid context";

			case CL_INVALID_QUEUE_PROPERTIES:
				return "Invalid queue properties";

			case CL_INVALID_COMMAND_QUEUE:
				return "Invalid command queue";

			case CL_INVALID_HOST_PTR:
				return "Invalid host pointer. This flag is valid only if host_ptr is not NULL";

			case CL_INVALID_MEM_OBJECT:
				return "Invalid memory object";

			case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
				return "Invalid image format descriptor";

			case CL_INVALID_IMAGE_SIZE:
				return "Invalid image size";

			case CL_INVALID_SAMPLER:
				return "Invalid sampler";

			case CL_INVALID_BINARY:
				return "Invalid binary";

			case CL_INVALID_BUILD_OPTIONS:
				return "Invalid build options";

			case CL_INVALID_PROGRAM:
				return "Invalid program";

			case CL_INVALID_PROGRAM_EXECUTABLE:
				return "Invalid program executable";

			case CL_INVALID_KERNEL_NAME:
				return "Invalid kernel name";

			case CL_INVALID_KERNEL_DEFINITION:
				return "Invalid kernel definition";

			case CL_INVALID_KERNEL:
				return "Invalid kernel";

			case CL_INVALID_ARG_INDEX:
				return "Invalid argument index";

			case CL_INVALID_ARG_VALUE:
				return "Invalid argument value";

			case CL_INVALID_ARG_SIZE:
				return "Invalid argument size";

			case CL_INVALID_KERNEL_ARGS:
				return "Invalid kernel arguments";

			case CL_INVALID_WORK_DIMENSION:
				return "Invalid work dimension";

			case CL_INVALID_WORK_GROUP_SIZE:
				return "Invalid work group size";

			case CL_INVALID_WORK_ITEM_SIZE:
				return "Invalid work item size";

			case CL_INVALID_GLOBAL_OFFSET:
				return "Invalid global offset";

			case CL_INVALID_EVENT_WAIT_LIST:
				return "Invalid event wait list";

			case CL_INVALID_EVENT:
				return "Invalid event";

			case CL_INVALID_OPERATION:
				return "Invalid operation";

			case CL_INVALID_GL_OBJECT:
				return "Invalid GL object";

			case CL_INVALID_BUFFER_SIZE:
				return "Invalid buffer size";

			case CL_INVALID_MIP_LEVEL:
				return "MipLevel is greater than zero and the OpenGL implementation does not support creating from non-zero mipmap levels";

			case CL_INVALID_GLOBAL_WORK_SIZE:
				return "Invalid global work size";

			case CL_INVALID_PROPERTY:
				return "Invalid property";

			case CL_INVALID_IMAGE_DESCRIPTOR:
				return "Invalid image descriptor";

			case CL_INVALID_COMPILER_OPTIONS:
				return "Invalid compiler options";

			case CL_INVALID_LINKER_OPTIONS:
				return "Invalid linker options";

			case CL_INVALID_DEVICE_PARTITION_COUNT:
				return "Invalid device partition count";

				/*
			case CL_INVALID_PIPE_SIZE:
				return "Invalid pipe size";

			case CL_INVALID_DEVICE_QUEUE:
				return "Invalid device queue";
				*/

			default:
				return "Unknown OpenCL compile error";
			}
		}
	};
}

#endif
