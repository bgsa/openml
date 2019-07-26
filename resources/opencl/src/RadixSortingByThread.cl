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
    __global volatile float*  vector, 
    __global volatile float*  output
    )
{
    __private size_t digitCache[ELEMENTS_PER_WORKITEM];

    __private size_t threadGlobalId = get_global_id(0); // 1024
    __private size_t threadsGlobalCount = get_global_size(0); //global_work_size = 1024
    __private size_t threadsGroupCount = get_local_size(0); // 128
    __private size_t threadLocalId = get_local_id(0);
    __private size_t groupId = get_group_id(0);
    __private size_t groupCount = get_num_groups(0); // 8
    
	__private size_t maxDigitMantissa = 4;
    __private size_t maxDigitExpoent = 4;
    __private int    minElement = 0;

    __private size_t currentDigit = 0;
    __private size_t bucketIndex = 0;
    __private size_t index = 0;

    __private size_t inputThreadIndex = threadGlobalId * ELEMENTS_PER_WORKITEM; // 1023 * 128
    __private size_t inputGroupIndex = groupId * threadsGroupCount * ELEMENTS_PER_WORKITEM; // 7 * 128 * 128

    __private size_t bucket[10];

	for (size_t digitIndex = 0; digitIndex < maxDigitMantissa; digitIndex++)
	{
        for(size_t i = 0 ; i < 10; i++)
            bucket[i] = 0;

        for (size_t i = 0 ; i < ELEMENTS_PER_WORKITEM; i++) // cada thread do grupo processa X elementos do input
        {
            currentDigit = digitCache[i] = digit(vector[inputThreadIndex + i], digitIndex);
            bucket[currentDigit] ++;
        }

        for (size_t j = 1; j < 10; j++)  //scan
            bucket[j] += bucket[j - 1];

        for (int i = ELEMENTS_PER_WORKITEM - 1; i >= 0; i--) // cada thread processa X elementos do input
        {
            bucketIndex = digitCache[i];

            output[inputThreadIndex + bucket[bucketIndex] - 1] = vector[inputThreadIndex + i];
            bucket[bucketIndex] --;
        }
        
        for (size_t i = 0 ; i < ELEMENTS_PER_WORKITEM; i++) // cada thread do grupo processa X elementos do input
            vector[inputThreadIndex + i] = output[inputThreadIndex + i];
    }
    
    for (int digitIndex = 0; digitIndex < maxDigitExpoent; digitIndex++)
	{
        for(size_t i = 0 ; i < 10; i++)
            bucket[i] = 0;

        for (size_t i = 0 ; i < ELEMENTS_PER_WORKITEM; i++) 
        {
            currentDigit = digitCache[i] = digit(((int) vector[inputThreadIndex + i]) + minElement, digitIndex);
            bucket[currentDigit] ++;
        }

        for (size_t j = 1; j < 10; j++)
            bucket[j] += bucket[j - 1];

        for (int i = ELEMENTS_PER_WORKITEM - 1; i >= 0; i--) // cada thread processa X elementos do input
        {
            bucketIndex = digitCache[i];

            output[inputThreadIndex + bucket[bucketIndex] - 1] = vector[inputThreadIndex + i];
            bucket[bucketIndex] --;
        }

        for (size_t i = 0 ; i < ELEMENTS_PER_WORKITEM; i++) // cada thread do grupo processa X elementos do input
            vector[inputThreadIndex + i] = output[inputThreadIndex + i];
    }

}