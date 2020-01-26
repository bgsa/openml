#define THREAD_ID get_global_id(0)
#define THREAD_COUNT get_global_size(0)

__kernel void initIndexes(
    __constant size_t* length,
    __global   size_t* indexes
    )
{
    if (THREAD_ID + 1 > *length) // guard
        return;

    __private size_t elementsPerWorkItem = max( (int)(*length / THREAD_COUNT) , 1);
    __private size_t inputThreadIndex = THREAD_ID * elementsPerWorkItem;

    for (size_t i = 0 ; i < elementsPerWorkItem ; i++)
        indexes[inputThreadIndex + i] = inputThreadIndex + i;
}
