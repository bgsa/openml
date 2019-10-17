#define OFFSET_GLOBAL (*strider) + (*offsetSum)

__kernel void findMinMax(
    __global   float * input,
    __constant size_t* n,
    __global   float * output,
    __constant size_t* strider,
    __constant size_t* offsetSum
    )
{
    __private size_t elementsPerWorkItem = *n / get_global_size(0);
    __private size_t threadIndex = get_global_id(0);
    __private size_t inputIndex = (elementsPerWorkItem * threadIndex);
    __private size_t offset = elementsPerWorkItem;

    __private float min = FLT_MAX;
    __private float max = -FLT_MAX;

    for( size_t i = 0 ; i < elementsPerWorkItem ; i++ )
    {
        if( min > input[(inputIndex + i) * OFFSET_GLOBAL] )
            min = input[(inputIndex + i) * OFFSET_GLOBAL];

        if( max < input[(inputIndex + i) * OFFSET_GLOBAL] )
            max = input[(inputIndex + i) * OFFSET_GLOBAL];
    }

    input[inputIndex * OFFSET_GLOBAL] = min;
    input[(inputIndex + 1) * OFFSET_GLOBAL] = max;

    barrier(CLK_GLOBAL_MEM_FENCE);

    for(size_t i = 2; i < elementsPerWorkItem + 1; i <<= 1)
    {
        if (threadIndex % i == 0)
        {
            if (min > input[(inputIndex + offset) * OFFSET_GLOBAL]) 
            {
                min = input[(inputIndex + offset) * OFFSET_GLOBAL];
                input[inputIndex * OFFSET_GLOBAL] = min;
            }

            if (max < input[(inputIndex + offset + 1) * OFFSET_GLOBAL]) 
            {
                max = input[(inputIndex + offset + 1) * OFFSET_GLOBAL];
                input[(inputIndex + 1) * OFFSET_GLOBAL] = max;
            }

            offset <<= 1;
        }

        barrier(CLK_GLOBAL_MEM_FENCE);
    }

    if (get_local_id(0) == 0) 
    {
        output[get_group_id(0)] = min;
        output[get_group_id(0) + get_num_groups(0)] = max;
    }
}

__kernel void findMax(
    __global   float * input,
    __constant size_t* n,
    __global   float * output
    )
{
    __private size_t elementsPerWorkItem = *n / get_global_size(0);
    __private size_t threadIndex = get_global_id(0);
    __private size_t inputIndex = elementsPerWorkItem * threadIndex;
    __private size_t offset = elementsPerWorkItem;

    __private float max = -FLT_MAX;

    for( size_t i = 0 ; i < elementsPerWorkItem ; i++ )
        if( max < input[inputIndex + i] )
            max = input[inputIndex + i];

    input[inputIndex] = max;

    barrier(CLK_GLOBAL_MEM_FENCE);

    for(size_t i = 2; i < elementsPerWorkItem + 1; i <<= 1)
    {
        if (threadIndex % i == 0)
        {
            if (max < input[inputIndex + offset]) 
            {
                max = input[inputIndex + offset];
                input[inputIndex] = max;
            }

            offset <<= 1;
        }

        barrier(CLK_GLOBAL_MEM_FENCE);
    }

    if (get_local_id(0) == 0) 
        output[get_group_id(0)] = max;
}
