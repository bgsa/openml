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

__kernel void sort(
    __global volatile float*  vector,
    __constant size_t* n, 
    __constant size_t* elementsPerWorkItem_global, 
    __global volatile float*  output
    )
{   
    __private int    minElement = 0;
    __private size_t currentDigit = 0;
    __private size_t bucketIndex = 0;
    __private size_t elementsPerWorkItem = *elementsPerWorkItem_global;
    
    __private size_t inputThreadIndex = get_global_id(0) * elementsPerWorkItem; // 1023 * 128

    __private size_t bucket[10];

	for (size_t digitIndex = 0; digitIndex < MAX_DIGIT_MANTISSA; digitIndex++)
	{
        for(size_t i = 0 ; i < 10; i++)
            bucket[i] = 0;

        for (size_t i = 0 ; i < elementsPerWorkItem; i++) // cada thread do grupo processa X elementos do input
        {
            currentDigit = digit(vector[inputThreadIndex + i], digitIndex);
            bucket[currentDigit] ++;
        }

        for (size_t j = 1; j < 10; j++)  //scan
            bucket[j] += bucket[j - 1];

        for (int i = elementsPerWorkItem - 1; i >= 0; i--) // cada thread processa X elementos do input
        {
            bucketIndex = digit(vector[inputThreadIndex + i], digitIndex);

            output[inputThreadIndex + bucket[bucketIndex] - 1] = vector[inputThreadIndex + i];
            bucket[bucketIndex] --;
        }
        
        for (size_t i = 0 ; i < elementsPerWorkItem; i++) // cada thread do grupo processa X elementos do input
            vector[inputThreadIndex + i] = output[inputThreadIndex + i];
    }
    
    for (int digitIndex = 0; digitIndex < MAX_DIGIT_EXPOENT; digitIndex++)
	{
        for(size_t i = 0 ; i < 10; i++)
            bucket[i] = 0;

        for (size_t i = 0 ; i < elementsPerWorkItem; i++) 
        {
            currentDigit = digit(((int) vector[inputThreadIndex + i]) + minElement, digitIndex);
            bucket[currentDigit] ++;
        }

        for (size_t j = 1; j < 10; j++)
            bucket[j] += bucket[j - 1];

        for (int i = elementsPerWorkItem - 1; i >= 0; i--) // cada thread processa X elementos do input
        {
            bucketIndex = digit(((int) vector[inputThreadIndex + i]) + minElement, digitIndex);

            output[inputThreadIndex + bucket[bucketIndex] - 1] = vector[inputThreadIndex + i];
            bucket[bucketIndex] --;
        }

        for (size_t i = 0 ; i < elementsPerWorkItem; i++) // cada thread do grupo processa X elementos do input
            vector[inputThreadIndex + i] = output[inputThreadIndex + i];
    }

}