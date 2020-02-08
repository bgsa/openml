#include "OpenCLBase.cl"

__kernel void initIndexes(
    __constant size_t* length,
    __global   size_t* indexes
    )
{
    if (THREAD_ID + 1 > *length) // guard
        return;

    __private size_t elementsPerWorkItem = max( (int)(*length / THREAD_LENGTH) , 1);
    __private size_t inputThreadIndex = THREAD_ID * elementsPerWorkItem;

    for (size_t i = 0 ; i < elementsPerWorkItem ; i++)
        indexes[inputThreadIndex + i] = inputThreadIndex + i;
}
