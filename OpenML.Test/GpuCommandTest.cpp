#pragma once

#include "CppUnitTest.h"
#include "GpuContext.h"
#include "GpuCommand.h"

#include <IFile.h>
#include <IFileManager.h>
#include <Factory.h>

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
			float* param1 = ALLOC_ARRAY(float, LIST_SIZE);
			float* param2 = ALLOC_ARRAY(float, LIST_SIZE);
			
			for (size_t i = 0; i < LIST_SIZE; i++) {
				param1[i] = (float) i;
				param2[i] = (float) (LIST_SIZE - i);
			}

			size_t globalWorkSize = LIST_SIZE;
			size_t localWorkSize = 64;
			
			GpuContext* context = GpuContext::init();
			GpuDevice* gpu = context->defaultDevice;

			IFileManager* fileManager = Factory::getFileManagerInstance();
			std::string source = fileManager->readTextFile("sumVector.cl");
			size_t sumProgram = gpu->commandManager->cacheProgram(source.c_str(), sizeof(char) * source.length());

			GpuCommand* command = gpu->commandManager->createCommand();

			float* result = command
				->setInputParameter(param1, sizeof(float) * LIST_SIZE)
				->setInputParameter(param2, sizeof(float) * LIST_SIZE)
				->setOutputParameter(sizeof(float) * LIST_SIZE)
				->buildFromProgram(gpu->commandManager->cachedPrograms[sumProgram], "sum")
				->execute(1, &globalWorkSize, &localWorkSize)
				->fetch<float>();

			Assert::AreEqual(1024.0f, *result, L"Wrong value.", LINE_INFO());
			
			delete fileManager;
			command->~GpuCommand();
			ALLOC_RELEASE(result);
			ALLOC_RELEASE(command);
			ALLOC_RELEASE(param2);
			ALLOC_RELEASE(param1);
		}

	};
}