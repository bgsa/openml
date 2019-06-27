#pragma once

#include "CppUnitTest.h"
#include "GpuContext.h"
#include "GpuCommand.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(GpuCommandTest)
	{
	public:

		TEST_METHOD(GpuCommand_execute_Test)
		{
			const int LIST_SIZE = 1024;
			float* param1 = (float*)malloc(sizeof(float) * LIST_SIZE);
			float* param2 = (float*)malloc(sizeof(float) * LIST_SIZE);
			
			for (size_t i = 0; i < LIST_SIZE; i++) {
				param1[i] = float(i);
				param2[i] = float(LIST_SIZE - i);
			}

			std::string source = "__kernel void sum(__global const float *A, __global const float *B, __global float *C) {";
			source += "int i = get_global_id(0);";
			source += "C[i] = A[i] + B[i];}";

			size_t globalWorkSize = LIST_SIZE;
			size_t localWorkSize = 64;
			
			GpuContext* context = GpuContext::init();
			GpuCommand* command = context->defaultDevice->commandManager->createCommand();

			float* result = command
				->setInputParameter(param1, sizeof(float) * LIST_SIZE)
				->setInputParameter(param2, sizeof(float) * LIST_SIZE)
				->setOutputParameter(sizeof(float) * LIST_SIZE)
				->build(source.c_str(), sizeof(char) * source.length(), "sum")
				->execute(&globalWorkSize, &localWorkSize)
				->fetch<float>();

			Assert::AreEqual(1024.0f, *result, L"Wrong value.", LINE_INFO());

			delete command;
			delete[] result, param1, param2;
		}

	};
}