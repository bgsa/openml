#include "OpenCLBase.cl"

#define OFFSET_GLOBAL (*strider) + (*offsetSum)

__kernel void findMinMax(
    __global   float * input,
    __constant size_t* n,
    __global   float * output,
    __constant size_t* strider,
    __constant size_t* offsetSum
    )
{
    __private size_t elementsPerWorkItem = max((int) (*n / THREAD_LENGTH), 1);
    __private size_t threadIndex = THREAD_ID;
    __private size_t inputIndex = (elementsPerWorkItem * threadIndex);
    __private size_t offset = elementsPerWorkItem;

    __private float minValue = FLT_MAX;
    __private float maxValue = -FLT_MAX;

    for( size_t i = 0 ; i < elementsPerWorkItem ; i++ )
    {
        if( minValue > input[(inputIndex + i) * OFFSET_GLOBAL] )
            minValue = input[(inputIndex + i) * OFFSET_GLOBAL];

        if( maxValue < input[(inputIndex + i) * OFFSET_GLOBAL] )
            maxValue = input[(inputIndex + i) * OFFSET_GLOBAL];
    }

    input[inputIndex * OFFSET_GLOBAL] = minValue;
    input[(inputIndex + 1) * OFFSET_GLOBAL] = maxValue;

    barrier(CLK_GLOBAL_MEM_FENCE);

    for(size_t i = 2; i < elementsPerWorkItem + 1; i <<= 1)
    {
        if (threadIndex % i == 0)
        {
            if (minValue > input[(inputIndex + offset) * OFFSET_GLOBAL]) 
            {
                minValue = input[(inputIndex + offset) * OFFSET_GLOBAL];
                input[inputIndex * OFFSET_GLOBAL] = minValue;
            }

            if (maxValue < input[(inputIndex + offset + 1) * OFFSET_GLOBAL]) 
            {
                maxValue = input[(inputIndex + offset + 1) * OFFSET_GLOBAL];
                input[(inputIndex + 1) * OFFSET_GLOBAL] = maxValue;
            }

            offset <<= 1;
        }

        barrier(CLK_GLOBAL_MEM_FENCE);
    }

    if (THREAD_LOCAL_ID == 0) 
    {
        output[GROUP_ID] = minValue;
        output[GROUP_ID + GROUP_LENGTH] = maxValue;
    }
}

__kernel void findMax(
    __global   float * input,
    __constant size_t* n,
    __global   float * output
    )
{
    __private size_t elementsPerWorkItem = *n / THREAD_LENGTH;
    __private size_t threadIndex = THREAD_ID;
    __private size_t inputIndex = elementsPerWorkItem * threadIndex;
    __private size_t offset = elementsPerWorkItem;

    __private float maxValue = -FLT_MAX;

    for( size_t i = 0 ; i < elementsPerWorkItem ; i++ )
        if( maxValue < input[inputIndex + i] )
            maxValue = input[inputIndex + i];

    input[inputIndex] = maxValue;

    barrier(CLK_GLOBAL_MEM_FENCE);

    for(size_t i = 2; i < elementsPerWorkItem + 1; i <<= 1)
    {
        if (threadIndex % i == 0)
        {
            if (maxValue < input[inputIndex + offset]) 
            {
                maxValue = input[inputIndex + offset];
                input[inputIndex] = maxValue;
            }

            offset <<= 1;
        }

        barrier(CLK_GLOBAL_MEM_FENCE);
    }

    if (THREAD_LOCAL_ID == 0) 
        output[GROUP_ID] = maxValue;
}

__kernel void findMinMaxIndexes(
    __global   float * input,
    __global   size_t* indexes,
    __constant size_t* indexesLength,
    __constant size_t* strider,
    __constant size_t* offsetSum,
    __global   float * output
    )
{
    if (THREAD_ID + 1 > *indexesLength) // guard
        return;

    __private size_t elementsPerWorkItem = max((int) (*indexesLength / THREAD_LENGTH), 1);
    __private size_t threadIndex = THREAD_ID;
    __private size_t inputIndex = elementsPerWorkItem * threadIndex;
    __private size_t outputIndex = threadIndex * 2;

    __private float minValue = FLT_MAX;
    __private float maxValue = -FLT_MAX;

    size_t currentIndex;

    for( size_t i = 0 ; i < elementsPerWorkItem ; i++ )
    {
        //currentIndex = (inputIndex + i) * OFFSET_GLOBAL;
        currentIndex = indexes[ (inputIndex + i) ] * OFFSET_GLOBAL;

        if( minValue > input[ currentIndex ] )
            minValue = input[ currentIndex ];

        if( maxValue < input[ currentIndex ] )
            maxValue = input[ currentIndex ];
    }

    output[outputIndex] = minValue;
    output[outputIndex + 1] = maxValue;
    
    barrier(CLK_GLOBAL_MEM_FENCE);  // each thread found the min and max values

    for(size_t i = 2; i < elementsPerWorkItem + 1; i=i*2)
    {
        if (threadIndex % i == 0)
        {
            if (minValue > output[outputIndex + i]) 
            {
                minValue = output[outputIndex + i];
                output[outputIndex] = minValue;
            }

            if (maxValue < output[outputIndex + i + 1]) 
            {
                maxValue = output[outputIndex + i + 1];
                output[outputIndex + 1] = maxValue;
            }
        }

        barrier(CLK_LOCAL_MEM_FENCE);
    }

    barrier(CLK_GLOBAL_MEM_FENCE); // each group found the min and max values

    size_t newIndexLength = isEven(*indexesLength) ? *indexesLength : *indexesLength - 1;

    if (THREAD_LOCAL_ID == 0 && GROUP_ID < newIndexLength)  // first thread of each group, keep processing
    {
        for(size_t i = 2; i < min(GROUP_LENGTH, *indexesLength); i=i*2 )
        {
            if (GROUP_ID % i == 0)
            {
                if (minValue > output[ outputIndex + (i * THREAD_LOCAL_LENGTH) ]) 
                {
                    minValue = output[ outputIndex + (i * THREAD_LOCAL_LENGTH) ];
                    output[outputIndex] = minValue;
                }

                if (maxValue < output[ outputIndex + (i * THREAD_LOCAL_LENGTH) + 1 ]) 
                {
                    maxValue = output[ outputIndex + (i * THREAD_LOCAL_LENGTH) + 1 ];
                    output[outputIndex + 1] = maxValue;
                }
            }

            barrier(CLK_GLOBAL_MEM_FENCE);
        }
    }

    barrier(CLK_GLOBAL_MEM_FENCE);

    if (THREAD_ID == 0) // check if the last group was verified
    {
        if (output[ (*indexesLength-1) * 2 ] < minValue)
            output[0] = output[ (*indexesLength-1) * 2 ];

        if (output[ (*indexesLength-1) * 2 + 1 ] > maxValue ) 
            output[1] = output[ (*indexesLength-1) * 2 + 1 ];
    }

}
