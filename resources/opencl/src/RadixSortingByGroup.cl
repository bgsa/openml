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

__kernel void sort(
    __global volatile float*  input, 
    __constant size_t* n, 
    __constant size_t* elementsPerWorkItem_global, 
    __global volatile float*  output)
{
    __private size_t threadGlobalId = get_global_id(0);
    __private size_t threadsGroupCount = get_local_size(0);
    __private size_t threadLocalId = get_local_id(0);

    __private size_t elementsPerWorkItem = *elementsPerWorkItem_global;

	__private size_t maxDigitMantissa = 4;
    __private size_t maxDigitExpoent = 4;
    __private int    minElement = 0;

    __private size_t inputThreadIndex = threadGlobalId * elementsPerWorkItem;
    __private size_t inputGroupIndex = get_group_id(0) * threadsGroupCount * elementsPerWorkItem;

    __local volatile size_t bucket[10];
    __local int sync;

    __private size_t bucketIndex = 0;

	for (size_t digitIndex = 0; digitIndex < maxDigitMantissa; digitIndex++)
	{
        if (threadLocalId < 10)  // each thread from [0..9] of a group, make the bucket zero
            bucket[threadLocalId] = 0;

        barrier(CLK_LOCAL_MEM_FENCE);

        for (size_t i = 0 ; i < elementsPerWorkItem; ++i) // for each thread process X elementos from input
        {
            bucketIndex = digit(input[inputThreadIndex + i], digitIndex);
            atomic_inc(&bucket[bucketIndex]);
            //atomic_inc(&bucket[digit(input[inputThreadIndex + i], digitIndex)]);
        }

        barrier(CLK_LOCAL_MEM_FENCE);

        if (threadLocalId == 0)  
		    for (size_t j = 1; j < 10; j++)  //scan
			    bucket[j] += bucket[j - 1];

        sync = threadsGroupCount - 1;    

        barrier(CLK_LOCAL_MEM_FENCE);

        while (sync >= 0)  // syncronize the workgroup threads for each thread execution (serial)
        {
            if (threadLocalId == sync) 
            {
                for (int i = elementsPerWorkItem - 1; i >= 0; --i) // for each thread process X elementos from input
                {
                    bucketIndex = digit(input[inputThreadIndex + i], digitIndex);
                    output[inputGroupIndex + atomic_dec(&bucket[bucketIndex]) - 1] = input[inputThreadIndex + i];
                    //output[inputGroupIndex + atomic_dec(&bucket[digit(input[inputThreadIndex + i], digitIndex)]) - 1] = input[inputThreadIndex + i];
                }

                atomic_dec(&sync);
            }

            barrier(CLK_LOCAL_MEM_FENCE);
        }

        for (size_t i = 0 ; i < elementsPerWorkItem; ++i)  // for each thread process X elementos from input
            input[inputThreadIndex + i] = output[inputThreadIndex + i];
    }

    for (int digitIndex = 0; digitIndex < maxDigitExpoent; digitIndex++)
	{
        if (threadLocalId < 10)
            bucket[threadLocalId] = 0;

        barrier(CLK_LOCAL_MEM_FENCE);

        for (size_t i = 0 ; i < elementsPerWorkItem; ++i) 
        {
            bucketIndex = digit(((int) input[inputThreadIndex + i]) + minElement, digitIndex);
            atomic_inc(&bucket[bucketIndex]);
            //atomic_inc(&bucket[digit(((int) input[inputThreadIndex + i]) + minElement, digitIndex)]);
        }

        barrier(CLK_LOCAL_MEM_FENCE);

        if (threadLocalId == 0)
            for (size_t j = 1; j < 10; j++)
                bucket[j] += bucket[j - 1];

        sync = threadsGroupCount - 1;    

        barrier(CLK_LOCAL_MEM_FENCE);

        while (sync >= 0)  // syncronize the workgroup threads for each thread execution (serial)
        {
            if (threadLocalId == sync) 
            {
                for (int i = elementsPerWorkItem - 1; i >= 0; --i) // for each thread process X elementos from input
                {
                    bucketIndex = digit(((int) input[inputThreadIndex + i]) + minElement, digitIndex);
                    output[inputGroupIndex + atomic_dec(&bucket[bucketIndex]) - 1] = input[inputThreadIndex + i];
                    //output[inputGroupIndex + atomic_dec(&bucket[digit(((int) input[inputThreadIndex + i]) + minElement, digitIndex)]) - 1] = input[inputThreadIndex + i];
                }

                atomic_dec(&sync);
            }

            barrier(CLK_LOCAL_MEM_FENCE);
        }

        for (size_t i = 0 ; i < elementsPerWorkItem; ++i)  // for each thread process X elementos from input
            input[inputThreadIndex + i] = output[inputThreadIndex + i];
    }

}