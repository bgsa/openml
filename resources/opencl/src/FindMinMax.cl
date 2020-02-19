#include "OpenCLBase.cl"

#define MIN_GROUP_LENGTH min(GROUP_LENGTH, *indexesLength)
#define OFFSET_GLOBAL (INPUT_STRIDE) + (*offsetSum)

__kernel void findMinMax(
    __global   float * input,
    __constant size_t* n,
    __global   float * output,
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
        minValue = min( minValue , input[(inputIndex + i) * OFFSET_GLOBAL] );
        maxValue = max( maxValue , input[(inputIndex + i) * OFFSET_GLOBAL] );
    }

    input[inputIndex * OFFSET_GLOBAL] = minValue;
    input[(inputIndex + 1) * OFFSET_GLOBAL] = maxValue;

    barrier(CLK_GLOBAL_MEM_FENCE);

    for(size_t i = 2; i < elementsPerWorkItem + 1; i <<= 1)
    {
        if (threadIndex % i == 0)
        {
            minValue = min ( minValue , input[(inputIndex + offset) * OFFSET_GLOBAL] );

            /*
            if (minValue > input[(inputIndex + offset) * OFFSET_GLOBAL]) 
            {
                minValue = input[(inputIndex + offset) * OFFSET_GLOBAL];
                //input[inputIndex * OFFSET_GLOBAL] = minValue;
            }
            */

            maxValue = max ( maxValue , input[(inputIndex + offset + 1) * OFFSET_GLOBAL] );

/*
            if (maxValue < input[(inputIndex + offset + 1) * OFFSET_GLOBAL]) 
            {
                maxValue = input[(inputIndex + offset + 1) * OFFSET_GLOBAL];
                //input[(inputIndex + 1) * OFFSET_GLOBAL] = maxValue;
            }
*/

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
        maxValue = max( maxValue , input[ inputIndex + i ] );

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
    __constant float * input,
    __constant size_t* indexes,
    //const __global size_t* indexes,
    __constant size_t* indexesLength,
    __constant size_t* offsetSum,
    __global   float * output
    )
{
    //__local size_t cache[LOCAL_MEM_LENGTH];  // 12k memory

    //__private size_t maxLocalElements = min( (size_t) LOCAL_MEM_LENGTH , (size_t) (*indexesLength / (size_t) 16) ); // 16 = max workgroup
    //__private size_t maxLocalElements = min( (size_t) LOCAL_MEM_LENGTH , *indexesLength );
    //prefetch (indexes, *indexesLength);
    //event_t copyEvent[1];
    //copyEvent[0] = async_work_group_copy(cache, &indexes[GROUP_ID * 64], maxLocalElements, NULL);
                 //async_work_group_copy(cache, const __global uint *src, size_t nelem, event_t ev);

    if (THREAD_ID + 1 > *indexesLength) // guard
        return;

    __private const size_t elementsPerWorkItem = max((int) (*indexesLength / THREAD_LENGTH), 1);
    //__private const size_t elementsPerWorkItem = max((int) (*indexesLength / (2 * THREAD_LENGTH)), 1);
    __private float minValue = FLT_MAX;
    __private float maxValue = -FLT_MAX;

    __private const size_t inputIndex = THREAD_ID * elementsPerWorkItem;
    __private size_t currentIndex;
    __private size_t i;

    //for(i = 0 ; i < elementsPerWorkItem ; i++ )
    //    cache[cacheIndexBegin + i] = indexes[ (inputIndex + i) ];
    //    cache[cacheIndexBegin + i] = 0;
        //cache[0] = 0;
    //output[0] = LOCAL_MEM_LENGTH;
    //return;

    //event_t evt = async_work_group_copy(__local T *dst, const __global T *src, size_t num_gentypes, event_t event);
    //prefetch (const __global gentype *p, size_t num_elements);

    //for(i = max(inputIndex, maxLocalElements) ; i < min(maxLocalElements, inputIndex + elementsPerWorkItem) ; i++ )
    for(i = 0 ; i < elementsPerWorkItem ; i++ )
    {
        //currentIndex = indexes[i] * OFFSET_GLOBAL;
        currentIndex = indexes[inputIndex + i] * OFFSET_GLOBAL;
        minValue = min( minValue , input[ currentIndex ] );
        maxValue = max( maxValue , input[ currentIndex ] );
    }

    //__private size_t cacheIndexBegin = THREAD_LOCAL_ID * elementsPerWorkItem;
    //wait_group_events(1, copyEvent);

    /*
    //for(i = 0 ; i < elementsPerWorkItem ; i++ )
    for(i = min(inputIndex, maxLocalElements) ; i < max(maxLocalElements, inputIndex + elementsPerWorkItem) ; i++ )
    {
        //currentIndex = cache[cacheIndexBegin + i] * OFFSET_GLOBAL;
        currentIndex = cache[i] * OFFSET_GLOBAL;
        minValue = min( minValue , input[ currentIndex ] );
        maxValue = max( maxValue , input[ currentIndex ] );
    }
    */

    __private size_t outputIndex = THREAD_ID * 2;
    output[outputIndex] = minValue;
    output[outputIndex + 1] = maxValue;
    
    barrier(CLK_GLOBAL_MEM_FENCE);  // each thread found the min and max values
    //prefetch (output, (*indexesLength) * 2);

    for(i = 2; i < elementsPerWorkItem * 2 +1 ; i*=2)
    {
        if (THREAD_ID % i == 0)
        {
            output[outputIndex] = min( output[outputIndex] , output[outputIndex + i] );
            output[outputIndex+1] = max( output[outputIndex+1] , output[outputIndex + i+1] );
        }

        barrier(CLK_GLOBAL_MEM_FENCE);
    }

    barrier(CLK_GLOBAL_MEM_FENCE);

    //const size_t newIndexLength = isEven(inputLength) ? inputLength : inputLength - 1;

    if (THREAD_ID == 0) 
    {
        minValue = output[0];
        maxValue = output[1];

        outputIndex = elementsPerWorkItem * 2;   // 256

        for(i = 0; i < MIN_GROUP_LENGTH; i++) {
            minValue = min( minValue , output[i * outputIndex] );
            maxValue = max( maxValue , output[i * outputIndex + 1] );
        }

        output[0] = minValue;
        output[1] = maxValue;
    }


}
