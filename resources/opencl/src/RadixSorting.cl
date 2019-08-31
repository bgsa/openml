#define OVERLOAD  __attribute__((overloadable))

#define MAX_DIGIT_MANTISSA 4
#define MAX_DIGIT_EXPOENT 4

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
    __constant size_t* n, 
    __constant size_t* elementsPerWorkItem_global, 
    __global   size_t* globalDigitIndex,
    __global   size_t* globalBucket
    )
{
    __private size_t bucket[10];
    __private size_t currentDigit = 0;
    __private size_t digitIndex = *globalDigitIndex;
    __private size_t globalBucketOffset = 10 * get_global_id(0);
    __private size_t elementsPerWorkItem = *elementsPerWorkItem_global;    
    __private size_t inputThreadIndex = get_global_id(0) * elementsPerWorkItem; // 1023 * 128

    for(size_t i = 0 ; i < 10; i++)
        bucket[i] = 0;

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
    __constant size_t* n, 
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

__kernel void recorder(
    __constant float* input,
    __constant size_t* offsetTable_global
    )
{
    __private size_t globalBufferIndex = 10 * get_global_id(0);
    __private size_t offsetTable = *offsetTable_global;


}
