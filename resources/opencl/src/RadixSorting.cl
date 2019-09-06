#define OVERLOAD  __attribute__((overloadable))

size_t OVERLOAD digit(float value, size_t index)
{
    size_t mantissa = (size_t) (fabs(((float) ((size_t) value)) - value) * 10000);

    return (size_t) ( (size_t) (mantissa / pow(10.0, (double) index)) % 10);
}

size_t OVERLOAD digit(int value, size_t index)
{
    return ((int) (value  / pow(10.0, (double) index))) % 10;
}

__kernel void count(
    __global   float * input,
    __constant size_t* elementsPerWorkItem_global, 
    __constant size_t* digitIndex_global,
    __constant bool  * useExpoent,
    __constant float * minValue_global,
    __global   size_t* globalBucket
    )
{
    __private size_t bucket[10];
    __private size_t currentDigit = 0;
    __private size_t digitIndex = *digitIndex_global;
    __private float  minValue = *minValue_global;
    __private size_t globalBucketOffset = 10 * get_global_id(0);
    __private size_t elementsPerWorkItem = *elementsPerWorkItem_global;    
    __private size_t inputThreadIndex = get_global_id(0) * elementsPerWorkItem; // 1023 * 128

    for(size_t i = 0 ; i < 10; i++)
        bucket[i] = 0;

    if (*useExpoent)
        for (size_t i = 0 ; i < elementsPerWorkItem; i++) //make a histogram
        {
            currentDigit = digit((int) (input[inputThreadIndex + i] + minValue), digitIndex);
            bucket[currentDigit]++;
        }
    else
        for (size_t i = 0 ; i < elementsPerWorkItem; i++) //make a histogram
        {
            currentDigit = digit(input[inputThreadIndex + i], digitIndex);
            bucket[currentDigit]++;
        }


    for (size_t i = 0 ; i < 10; i++) //write on global bucket in order to do prefix scan
        globalBucket[globalBucketOffset + i] = bucket[i];
}

__kernel void prefixScan(
    __constant size_t* previousBuffer,
    __global   size_t* nextBuffer,
    __constant size_t* offset_global
    )
{
    __private size_t globalBufferIndex = 10 * get_global_id(0);
    __private size_t offset = *offset_global;

    if (globalBufferIndex < offset)
    {
        for(size_t i = 0; i < 10; i++)
            nextBuffer[globalBufferIndex + i] = previousBuffer[globalBufferIndex + i];
    }
    else 
    {
        for(size_t i = 0; i < 10; i++)
            nextBuffer[globalBufferIndex + i] = previousBuffer[globalBufferIndex + i - offset] + previousBuffer[globalBufferIndex + i];
    }
}

__kernel void reorder(
    __constant float * input,
    __constant size_t* elementsPerWorkItem_global,
    __constant size_t* digitIndex_global,
    __constant bool  * useExpoent,
    __global   size_t* offsetTable,
    __constant float * minValue_global,
    __global   float * output
    )
{
    __private size_t elementsPerWorkItem = *elementsPerWorkItem_global;
    __private size_t digitIndex = *digitIndex_global;
    __private float  minValue = *minValue_global;
    __private size_t inputThreadIndex = get_global_id(0) * elementsPerWorkItem; // 1023 * 128
    __private size_t offsetTable_Index = get_global_id(0) * 10;
    __private size_t offsetTable_LastBucketIndex = (get_global_size(0) * 10) - 10;

    __private size_t globalAddress;
    __private size_t currentDigit;
    __private size_t startIndex[10];

    startIndex[0] = 0;
    for(size_t i = 1; i < 10; i++)
        startIndex[i] = startIndex[i-1] + offsetTable[offsetTable_LastBucketIndex + i-1];

    if (*useExpoent)
        for (int i = elementsPerWorkItem - 1; i >= 0; i--)
        {
            currentDigit = digit((int) (input[inputThreadIndex + i] + minValue), digitIndex);  // get the digit to process
            globalAddress = startIndex[currentDigit] + offsetTable[offsetTable_Index + currentDigit] - 1; // get the global output address where the element is going to be stored
            output[globalAddress] = input[inputThreadIndex + i];   // store the element in right gloal output address
            offsetTable[offsetTable_Index + currentDigit]--;    // decrement the offset table to store the others elements before
        }
    else
        for (int i = elementsPerWorkItem - 1; i >= 0; i--)
        {
            currentDigit = digit(input[inputThreadIndex + i], digitIndex);  // get the digit to process
            globalAddress = startIndex[currentDigit] + offsetTable[offsetTable_Index + currentDigit] - 1; // get the global output address where the element is going to be stored
            output[globalAddress] = input[inputThreadIndex + i];   // store the element in right gloal output address
            offsetTable[offsetTable_Index + currentDigit]--;    // decrement the offset table to store the others elements before
        }
}
