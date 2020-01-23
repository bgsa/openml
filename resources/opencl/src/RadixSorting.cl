#define OVERLOAD  __attribute__((overloadable))
#define THREAD_ID get_global_id(0)
#define THREAD_COUNT get_global_size(0)

#define OFFSET_GLOBAL (*strider) + *offset


size_t OVERLOAD digit(float value, size_t index)
{
    size_t mantissa = (size_t) (fabs(((float) ((size_t) value)) - value) * 10000);

    return (size_t) ( (size_t) (mantissa / pow(10.0, (double) index)) % 10);
}

size_t OVERLOAD digit(int value, size_t index)
{
    return ((int) (value  / pow(10.0, (double) index))) % 10;
}

/// Init the indexes array of elements
__kernel void initIndexes(
    __constant size_t* elementsPerWorkItem_global,
    __constant size_t* inputLength,
    __global   size_t* indexes
    )
{
    if (THREAD_ID + 1 > *inputLength) // guard
        return;

    __private size_t elementsPerWorkItem = *elementsPerWorkItem_global;
    __private size_t inputThreadIndex = THREAD_ID * elementsPerWorkItem;

    for (size_t i = 0 ; i < elementsPerWorkItem ; i++)
        indexes[inputThreadIndex + i] = inputThreadIndex + i;
}

__kernel void count(
    __global   float * input,
    __constant size_t* inputLength,
    __constant size_t* elementsPerWorkItem, 
    __constant size_t* digitIndex,
    __constant bool  * useExpoent,
    __constant float * minValue,
    __global   size_t* offsetTable,
    __constant size_t* strider,
    __constant size_t* offset
    )
{
    if (THREAD_ID + 1 > *inputLength) // guard
        return;

    __private size_t bucket[10];
    __private size_t currentDigit = 0;
    __private size_t globalBucketOffset = 10 * get_global_id(0);
    __private size_t inputThreadIndex = get_global_id(0) * *elementsPerWorkItem * *strider;

    for(size_t i = 0 ; i < 10; i++)
        bucket[i] = 0;

    if (*useExpoent)
        for (size_t i = 0 ; i < *elementsPerWorkItem; i++) //make a histogram for expoent of float
        {
            currentDigit = digit((int) (input[(inputThreadIndex + (i * OFFSET_GLOBAL))] + *minValue), *digitIndex);
            bucket[currentDigit]++;
        }
    else
        for (size_t i = 0 ; i < *elementsPerWorkItem ; i++) //make a histogram for mantissa of float
        {
            currentDigit = digit(input[inputThreadIndex + (i * OFFSET_GLOBAL)] + *minValue, *digitIndex);
            bucket[currentDigit]++;
        }

    for (size_t i = 0 ; i < 10; i++) //write on global bucket in order to do prefix scan
        offsetTable[globalBucketOffset + i] = bucket[i];
}

__kernel void prefixScan(
    __constant size_t* previousOffsetTable,
    __global   size_t* nextOffsetTable,
    __constant size_t* offset_parameter,
    __global   size_t* inputLength
    )
{
    if (THREAD_ID + 1 > *inputLength) // guard
        return;

    __private size_t globalBufferIndex = THREAD_ID * 10;
    __private size_t offset = *offset_parameter;

    if (globalBufferIndex < offset)
    {
        for(size_t i = 0; i < 10; i++)
            nextOffsetTable[globalBufferIndex + i] = previousOffsetTable[globalBufferIndex + i];
    }
    else 
    {
        for(size_t i = 0; i < 10; i++)
            nextOffsetTable[globalBufferIndex + i] = previousOffsetTable[globalBufferIndex + i - offset] + previousOffsetTable[globalBufferIndex + i];
    }
}

__kernel void reorder(
    __constant float * input,
    __global   size_t* inputLength,
    __constant size_t* elementsPerWorkItem_global,
    __constant size_t* digitIndex_global,
    __constant bool  * useExpoent,
    __global   size_t* offsetTable,
    __constant float * minValue,
    __constant size_t* indexesInput,
    __global   size_t* indexesOutput,
    __global   float * output,
    __constant size_t* strider,
    __constant size_t* offset
    )
{
    if (THREAD_ID + 1 > *inputLength) // guard
        return;

    __private size_t elementsPerWorkItem = *elementsPerWorkItem_global;
    __private size_t digitIndex = *digitIndex_global;
    __private size_t indexesInputBegin = THREAD_ID * elementsPerWorkItem;
    __private size_t inputThreadIndex = THREAD_ID * elementsPerWorkItem * *strider; // 1023 * 128
    __private size_t offsetTable_Index = THREAD_ID * 10;
    __private size_t offsetTable_LastBucketIndex = ( min(THREAD_COUNT, *inputLength) * 10) - 10;

    __private size_t globalAddress;
    __private size_t currentDigit;
    __private size_t startIndex[10];

    startIndex[0] = 0;
    for(size_t i = 1; i < 10; i++)
        startIndex[i] = startIndex[i-1] + offsetTable[offsetTable_LastBucketIndex + i-1];

    if (*useExpoent)
        for (int i = elementsPerWorkItem - 1; i >= 0; i--)
        {
            currentDigit = digit((int) (input[inputThreadIndex + (i * OFFSET_GLOBAL)] + *minValue), digitIndex);  // get the digit to process
            
            globalAddress = startIndex[currentDigit] + offsetTable[offsetTable_Index + currentDigit] - 1; // get the global output address where the element is going to be stored

            //copy all elements of item to output
            for (size_t j = 0 ; j < *strider ; j++)
                output[(globalAddress * *strider) + j] = input[inputThreadIndex + (i * *strider) + j];   // store the element in the new gloal output address

            indexesOutput[globalAddress] = indexesInput[indexesInputBegin + i];

            offsetTable[offsetTable_Index + currentDigit]--;    // decrement the offset table to store the others elements before
        }
    else
        for (int i = elementsPerWorkItem - 1; i >= 0; i--)
        {
            currentDigit = digit(input[inputThreadIndex + (i * OFFSET_GLOBAL)] + *minValue, digitIndex);  // get the digit to process

            globalAddress = startIndex[currentDigit] + offsetTable[offsetTable_Index + currentDigit] - 1; // get the global output address where the element is going to be stored

            //copy all elements of item to output
            for (size_t j = 0 ; j < *strider ; j++)
                output[(globalAddress * *strider) + j] = input[inputThreadIndex + (i * *strider) + j];   // store the element in the new gloal output address

            indexesOutput[globalAddress] = indexesInput[indexesInputBegin + i];

            offsetTable[offsetTable_Index + currentDigit]--;    // decrement the offset table to store the others elements before
        }
}
