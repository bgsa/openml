#define OVERLOAD  __attribute__((overloadable))

size_t OVERLOAD digit(float value, size_t index)
{
    size_t mantissa = (size_t) value;
    mantissa = (size_t) (fabs( ((float) mantissa) - value) * 10000);

    size_t result = (size_t) ( (size_t) (mantissa / pow(10.0, (double) index)) % 10);

    return result;
}

size_t OVERLOAD digit(int value, size_t index)
{
    return ((int) (value  / pow(10.0, (double) index))) % 10;
}

__kernel void sort(volatile __global float* vector, volatile __global size_t* globalCounter, __global size_t* bucket, __global float* output) 
{
    __private size_t workItemIndex = get_global_id(0);
    __private size_t n = *globalCounter;

    if (workItemIndex > n - 1)
        return;

	__private size_t maxDigitMantissa = 4;
    __private size_t maxDigitExpoent = 4;
    __private int minElement = 34567;

    __private size_t currentDigit = 0;
    __private size_t mantissa = 0; 

    __private size_t bucketIndex = 0;

	for (size_t digitIndex = 0; digitIndex < maxDigitMantissa; digitIndex++)
	{
        *globalCounter = n - 1;

        if (workItemIndex == 0) 
            for(size_t i = 0; i < 10; i++)
                bucket[i] = 0;

        barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

        currentDigit = digit(vector[workItemIndex], digitIndex);
        atomic_inc(&bucket[currentDigit]);

        barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

        if (workItemIndex == 0)
		    for (size_t j = 1; j < 10; j++)
			    bucket[j] += bucket[j - 1];

        barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

        while (*globalCounter != UINT_MAX)
            if (*globalCounter == workItemIndex)
            {
                bucketIndex = digit(vector[workItemIndex], digitIndex);

                output[bucket[bucketIndex] - 1] = vector[workItemIndex];
                atomic_dec(&bucket[bucketIndex]);

                atomic_dec(globalCounter);
            }

        barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

        vector[workItemIndex] = output[workItemIndex];

        barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);
	}


	for (int digitIndex = 0; digitIndex < maxDigitExpoent; digitIndex++)
	{
        *globalCounter = n - 1;

        if (workItemIndex == 0)
            for(size_t i = 0; i < 10; i++)
                bucket[i] = 0;

        barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

        currentDigit = digit(((int) vector[workItemIndex]) + minElement, digitIndex);
        atomic_inc(&bucket[currentDigit]);

        barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

        if (workItemIndex == 0)
            for (size_t j = 1; j < 10; j++)
                bucket[j] += bucket[j - 1];

        while (*globalCounter != UINT_MAX)
            if (*globalCounter == workItemIndex)
            {
                bucketIndex = digit(((int) vector[workItemIndex]) + minElement, digitIndex);

                output[bucket[bucketIndex] - 1] = vector[workItemIndex];
                atomic_dec(&bucket[bucketIndex]);

                atomic_dec(globalCounter);
            }

        barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

        vector[workItemIndex] = output[workItemIndex];

        barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);
	}

}