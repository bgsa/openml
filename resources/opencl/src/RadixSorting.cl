#define OVERLOAD  __attribute__((overloadable))

#define THREAD_ID get_global_id(0)
#define THREAD_COUNT get_global_size(0)

#define OFFSET_GLOBAL (*strider) + *offset
#define MAX_DIGITS_DECIMALS 4
#define BUCKET_LENGTH 10


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
    __constant float * input,
    __constant size_t* indexes,
    __constant size_t* inputLength,
    __constant size_t* digitIndex,
    __constant bool  * useExpoent,
    __constant float * minMaxValues,
    __global   size_t* offsetTable,
    __constant size_t* strider,
    __constant size_t* offset
    )
{
    if (THREAD_ID + 1 > *inputLength) // guard
        return;

    __private size_t globalBucketOffset = BUCKET_LENGTH * THREAD_ID;
    __private size_t elementsPerWorkItem = max( (int) (*inputLength / THREAD_COUNT) , 1 );
    __private size_t inputThreadIndex = THREAD_ID * elementsPerWorkItem;
    __private float  minValue = -min(0.0f, minMaxValues[0]);
    __private size_t bucket[BUCKET_LENGTH];
    
    for(size_t i = 0 ; i < BUCKET_LENGTH; i++)
        bucket[i] = 0;

    if (*useExpoent)
        for (size_t i = 0 ; i < elementsPerWorkItem; i++) //make a histogram for expoent of float
        {
            bucket[
                digit((int) (input[indexes[inputThreadIndex + i] * OFFSET_GLOBAL] + minValue), *digitIndex)
            ]++;
        }
    else
        for (size_t i = 0 ; i < elementsPerWorkItem ; i++) //make a histogram for mantissa of float
        {
            bucket[
                digit(input[indexes[inputThreadIndex + i] * OFFSET_GLOBAL] + minValue, *digitIndex)
            ]++;
        }

    for (size_t i = 0 ; i < BUCKET_LENGTH; i++) //write on global bucket in order to do prefix scan
        offsetTable[globalBucketOffset + i] = bucket[i];
}

__kernel void prefixScan(
    __constant size_t* previousOffsetTable,
    __global   size_t* nextOffsetTable,
    __global   size_t* offsetPrefixScan,
    __constant size_t* inputLength
    )
{
    if (THREAD_ID + 1 > *inputLength) // guard
        return;

    __private size_t offsetTableIndex = THREAD_ID * BUCKET_LENGTH;
    __private size_t offset = *offsetPrefixScan;

    if (offsetTableIndex < offset)
        for(size_t i = 0; i < BUCKET_LENGTH; i++)
            nextOffsetTable[offsetTableIndex + i] = previousOffsetTable[offsetTableIndex + i];
    else 
        for(size_t i = 0; i < BUCKET_LENGTH; i++)
            nextOffsetTable[offsetTableIndex + i] = previousOffsetTable[offsetTableIndex + i - offset] 
                                                    + previousOffsetTable[offsetTableIndex + i];

    barrier(CLK_GLOBAL_MEM_FENCE);
    if (THREAD_ID == 0)
        offsetPrefixScan[0] = *offsetPrefixScan * 2;
}

__kernel void reorder(
    __constant float * input,
    __constant size_t* inputLength,
    __global   size_t* digitIndex_global,
    __global   bool  * useExpoent,
    __global   size_t* offsetTable,
    __constant float * minMaxValues,
    __constant size_t* indexesInput,
    __global   size_t* indexesOutput,
    __constant size_t* strider,
    __constant size_t* offset,
    __global   size_t* offsetPrefixScan
    )
{
    if (THREAD_ID + 1 > *inputLength) // guard
        return;

    __private size_t elementsPerWorkItem = max( (int) (*inputLength / THREAD_COUNT) , 1 );
    __private size_t digitIndex = *digitIndex_global;
    __private size_t indexesInputBegin = THREAD_ID * elementsPerWorkItem;
    __private size_t offsetTable_Index = THREAD_ID * BUCKET_LENGTH;
    __private size_t offsetTable_LastBucketIndex = ( min(THREAD_COUNT, *inputLength) * BUCKET_LENGTH) - BUCKET_LENGTH;
    __private float  minValue = -min(0.0f, minMaxValues[0]);

    __private size_t globalAddress;
    __private size_t currentDigit;
    __private size_t startIndex[BUCKET_LENGTH];

    startIndex[0] = 0;
    for(size_t i = 1; i < BUCKET_LENGTH; i++)
        startIndex[i] = startIndex[i-1] + offsetTable[offsetTable_LastBucketIndex + i-1];

    if (*useExpoent)
        for (int i = elementsPerWorkItem - 1; i >= 0; i--)
        {
            currentDigit = digit((int) (input[indexesInput[indexesInputBegin + i] * OFFSET_GLOBAL] + minValue), digitIndex);  // get the digit to process            
            
            globalAddress = startIndex[currentDigit] + offsetTable[offsetTable_Index + currentDigit] - 1; // get the global output address where the element is going to be stored

            indexesOutput[globalAddress] = indexesInput[indexesInputBegin + i];

            offsetTable[offsetTable_Index + currentDigit]--;    // decrement the offset table to store the others elements before
        }
    else
        for (int i = elementsPerWorkItem - 1; i >= 0; i--)
        {
            currentDigit = digit(input[indexesInput[indexesInputBegin + i] * OFFSET_GLOBAL] + minValue, digitIndex);  // get the digit to process

            globalAddress = startIndex[currentDigit] + offsetTable[offsetTable_Index + currentDigit] - 1; // get the global output address where the element is going to be stored

            indexesOutput[globalAddress] = indexesInput[indexesInputBegin + i];

            offsetTable[offsetTable_Index + currentDigit]--;    // decrement the offset table to store the others elements before
        }


    barrier(CLK_GLOBAL_MEM_FENCE);
    if (THREAD_ID)
        offsetPrefixScan[0] = BUCKET_LENGTH;

    if (THREAD_ID == 0)
    {
        if ( !useExpoent[0] && digitIndex == MAX_DIGITS_DECIMALS - 1) // if decimal digits is being processed and it already have processed 4 digits ...
        {
            useExpoent[0] = true;
            digitIndex_global[0] = 0;
        }
        else
            digitIndex_global[0] = *digitIndex_global + 1;
    }

}
