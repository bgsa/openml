#if OPENCL_ENABLED

#include "GpuRadixSorting.h"

GpuRadixSorting* GpuRadixSorting::init(GpuDevice* gpu, const char* buildOptions)
{
	if (this->gpu != NULL)
		return this;

	this->gpu = gpu;

	GpuCommands::init(gpu, buildOptions);

	IFileManager* fileManager = Factory::getFileManagerInstance();

	std::string sourceRadixSort = fileManager->readTextFile("RadixSorting.cl");
	radixSortProgramIndex = gpu->commandManager->cacheProgram(sourceRadixSort.c_str(), SIZEOF_CHAR * sourceRadixSort.length(), buildOptions);

	delete fileManager;
	return this;
}

GpuRadixSorting* GpuRadixSorting::setParameters(float* input, size_t inputLength, size_t strider, size_t offset)
{
	size_t offsetPrefixScanCpu = 10;
	bool useExpoent = false;
	size_t digitIndex = 0;
	const size_t inputSize = inputLength * strider * SIZEOF_FLOAT;

	inputGpu = gpu->createBuffer(input, inputSize, CL_MEM_READ_ONLY);
	indexesGpu = GpuCommands::creteIndexes(gpu, inputLength);
	indexesLengthGpu = gpu->createBuffer(&inputLength, SIZEOF_UINT, CL_MEM_READ_ONLY);
	offsetGpu = gpu->createBuffer(&offset, SIZEOF_UINT, CL_MEM_READ_ONLY);
	outputMinMaxGpu = gpu->createBuffer(inputLength * 2 * SIZEOF_FLOAT, CL_MEM_READ_WRITE);
	offsetPrefixScanGpu = gpu->createBuffer(&offsetPrefixScanCpu, SIZEOF_UINT, CL_MEM_READ_WRITE);
	digitIndexGpu = gpu->createBuffer(&digitIndex, SIZEOF_UINT, CL_MEM_READ_WRITE);
	useExpoentGpu = gpu->createBuffer(&useExpoent, SIZEOF_UINT, CL_MEM_READ_WRITE);
	outputIndexes = gpu->createBuffer(inputLength * SIZEOF_UINT, CL_MEM_READ_WRITE);

	GpuCommands::findMinMaxIndexesGPU(gpu, inputGpu, indexesGpu, indexesLengthGpu, offsetGpu, inputLength, strider, outputMinMaxGpu);
	gpu->commandManager->executeReadBuffer(outputMinMaxGpu, SIZEOF_FLOAT * 2, minMaxValues, true);

	const size_t elementsLengthAsPowOf2 = nextPowOf2(inputLength); //required for OpenCL
	const size_t elementsPerWorkItem = std::max(elementsLengthAsPowOf2 / gpu->maxWorkGroupSize, size_t(1));
	threadsCount = elementsLengthAsPowOf2 / elementsPerWorkItem;

	globalWorkSize[0] = threadsCount;
	globalWorkSize[1] = 0;
	globalWorkSize[2] = 0;
	localWorkSize[0] = elementsPerWorkItem;
	localWorkSize[1] = 0;
	localWorkSize[2] = 0;

	threadsCount = std::min(inputLength, threadsCount);

	const size_t offsetTableSize = SIZEOF_UINT * 10 * threadsCount;
	offsetTable1 = gpu->createBuffer(offsetTableSize, CL_MEM_READ_WRITE);
	offsetTable2 = gpu->createBuffer(offsetTableSize, CL_MEM_READ_WRITE);
	offsetTableResult = offsetTable2;
	cl_program program = gpu->commandManager->cachedPrograms[radixSortProgramIndex];

	commandCount = gpu->commandManager
		->createCommand()
		->setInputParameter(inputGpu, inputSize)
		->setInputParameter(indexesGpu, SIZEOF_UINT * inputLength)
		->setInputParameter(indexesLengthGpu, SIZEOF_UINT)
		->setInputParameter(digitIndexGpu, SIZEOF_UINT)
		->setInputParameter(useExpoentGpu, SIZEOF_BOOL)
		->setInputParameter(outputMinMaxGpu, SIZEOF_FLOAT * 2)
		->setInputParameter(offsetTable1, offsetTableSize)
		->buildFromProgram(program, "count");

	commandPrefixScan = gpu->commandManager
		->createCommand()
		->setInputParameter(offsetTable1, offsetTableSize)  //use buffer hosted GPU
		->setInputParameter(offsetTable2, offsetTableSize)
		->setInputParameter(offsetPrefixScanGpu, SIZEOF_UINT)
		->setInputParameter(indexesLengthGpu, SIZEOF_UINT)
		->buildFromProgram(program, "prefixScan");

	commandPrefixScanSwaped = gpu->commandManager
		->createCommand()
		->setInputParameter(offsetTable2, offsetTableSize)  //use buffer hosted GPU
		->setInputParameter(offsetTable1, offsetTableSize)
		->setInputParameter(offsetPrefixScanGpu, SIZEOF_UINT)
		->setInputParameter(indexesLengthGpu, SIZEOF_UINT)
		->buildFromProgram(program, "prefixScan");

	commandReorder = gpu->commandManager
		->createCommand()
		->setInputParameter(inputGpu, inputSize)
		->setInputParameter(indexesLengthGpu, SIZEOF_UINT)
		->setInputParameter(digitIndexGpu, SIZEOF_UINT)
		->setInputParameter(useExpoentGpu, SIZEOF_BOOL)
		->setInputParameter(offsetTableResult, offsetTableSize)
		->setInputParameter(outputMinMaxGpu, SIZEOF_FLOAT * 2)
		->setInputParameter(outputIndexes, SIZEOF_UINT * inputLength)
		->setInputParameter(indexesGpu, SIZEOF_UINT * inputLength)
		->setInputParameter(offsetPrefixScanGpu, SIZEOF_UINT)
		->buildFromProgram(program, "reorder");

	return this;
}

cl_mem GpuRadixSorting::execute()
{
	bool useExpoent = false;
	size_t digitIndex = 0;

	bool offsetChanged = false;
	bool indexesChanged = false;
	bool prefixScanSwaped = true;

	float minValue = -std::min(0.0f, minMaxValues[0]);

	commandCount->execute(1, globalWorkSize, localWorkSize);
	commandPrefixScan->execute(1, globalWorkSize, localWorkSize);

	do  // for each digit in one element
	{
		offsetChanged = false;

		do  // prefix scan
		{
			offsetPrefixScanCpu <<= 1;

			if (prefixScanSwaped)
				commandPrefixScanSwaped->execute(1, globalWorkSize, localWorkSize);
			else
				commandPrefixScan->execute(1, globalWorkSize, localWorkSize);

			offsetChanged = !offsetChanged;
			prefixScanSwaped = !prefixScanSwaped;

		} while (offsetPrefixScanCpu < (threadsCount * 10) >> 1);
		offsetPrefixScanCpu = 10;

		offsetTableResult = offsetChanged ? offsetTable1 : offsetTable2;

		commandReorder
			->updateInputParameter(4, offsetTableResult)
			->swapInputParameter(6, 7)
			->execute(1, globalWorkSize, localWorkSize);
		indexesChanged = !indexesChanged;

		if (++digitIndex > maxDigits)  // check the algorithm reach the result
		{
			if (useExpoent)
				break;

			useExpoent = true;
			digitIndex = 0;
			maxDigits = digitCount((int)(minMaxValues[1] + minValue));  // MAX_DIGITS_EXPOENT - 1;
		}

		commandCount
			->updateInputParameter(1, indexesChanged ? outputIndexes : indexesGpu)
			->execute(1, globalWorkSize, localWorkSize);

		if (prefixScanSwaped)
			commandPrefixScanSwaped->execute(1, globalWorkSize, localWorkSize);
		else
			commandPrefixScan->execute(1, globalWorkSize, localWorkSize);
		prefixScanSwaped = !prefixScanSwaped;

	} while (true);

	return outputIndexes;
}

GpuRadixSorting::~GpuRadixSorting()
{
	gpu->releaseBuffer(11, inputGpu, indexesGpu, indexesLengthGpu, offsetGpu,
						outputMinMaxGpu, offsetPrefixScanGpu, digitIndexGpu, useExpoentGpu,
						offsetTable1, offsetTable2);

	commandCount->~GpuCommand();
	commandPrefixScan->~GpuCommand();
	commandPrefixScanSwaped->~GpuCommand();
	commandReorder->~GpuCommand();
}

#endif