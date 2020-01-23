#define OFFSET_GLOBAL (*strider) + (*offsetSum)

__kernel void findMinMax(
    __global   float * input,
    __constant size_t* n,
    __global   float * output,
    __constant size_t* strider,
    __constant size_t* offsetSum
    )
{
    __private size_t elementsPerWorkItem = max((int) (*n / get_global_size(0)), 1);
    __private size_t threadIndex = get_global_id(0);
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

    if (get_local_id(0) == 0) 
    {
        output[get_group_id(0)] = minValue;
        output[get_group_id(0) + get_num_groups(0)] = maxValue;
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

    if (get_local_id(0) == 0) 
        output[get_group_id(0)] = maxValue;
}
