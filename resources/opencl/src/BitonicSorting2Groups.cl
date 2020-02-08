#include "OpenCLBase.cl"

__kernel void sort(
    __global volatile float* input, 
    __constant size_t* n,
    __global volatile float*  output)
{
    __private size_t groupId = get_group_id(0);

    output[0] = get_group_id(0);
    output[1] = get_num_groups(0);

	if (groupId & 1)  // if group is odd, return
        return;
		
    __private size_t elementsPerGroup = *n / get_num_groups(0); // 131072 / 8 = 16384    |  131072 / 4 = 32768
    __private size_t elementsPerWorkItem = elementsPerGroup / get_local_size(0); // 16384 / 128 = 128   | 32768 / 256 = 128
    __private size_t inputThreadIndex = get_global_id(0) * elementsPerWorkItem; // 1023 * 128
	__private size_t nextIndexGroup = (groupId + 2) * elementsPerGroup + (groupId * elementsPerGroup);
	__private size_t maxInputThreadIndex = inputThreadIndex + elementsPerWorkItem;

    __private float temp;
    __private size_t first;
    __private size_t last;

    for(size_t first = inputThreadIndex; first < maxInputThreadIndex; ++first)
    {
        last = nextIndexGroup - first - 1;

        if (input[first] > input[last]) // se o input anterior é maior que o input posterior, troca
        {
            temp = input[first];
            input[first] = input[last];
            input[last] = temp;
        }
    }
}
