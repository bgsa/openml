#pragma once

#include "CppUnitTest.h"
#include <GpuCommand.h>

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
				param1[i] = i;
				param2[i] = LIST_SIZE - i;
			}

			std::string source = "__kernel void sum(__global const float *A, __global const float *B, __global float *C) {";
			source += "int i = get_global_id(0);";
			source += "C[i] = A[i] + B[i];}";

			size_t globalWorkSize = LIST_SIZE;
			size_t localWorkSize = 64;

			GpuCommand* command = GpuCommand::create();

			float* result = command
				->setInputParameter(param1, sizeof(float) * LIST_SIZE)
				->setInputParameter(param2, sizeof(float) * LIST_SIZE)
				->setOutputParameter(sizeof(float) * LIST_SIZE)
				->setSource(source.c_str(), sizeof(char) * source.length())
				->build("sum")
				->execute(&globalWorkSize, &localWorkSize)
				->fetch<float>();

			Assert::AreEqual(1024.0f, *result, L"Wrong value.", LINE_INFO());

			delete command;
		}

	};
}