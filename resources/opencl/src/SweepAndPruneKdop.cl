#define ENV_64BITS
#ifdef ENV_64BITS
    #pragma OPENCL EXTENSION cl_khr_int64_base_atomics: enable
#endif

#define THREAD_ID get_global_id(0)
#define THREAD_COUNT get_global_size(0)

#define MIN_POINT input[indexes[i] * strider + minPointIndex]
#define MAX_POINT input[indexes[i] * strider + maxPointIndex]

#define MIN_POINT_NEXT input[indexes[j] * strider + minPointIndex]
#define MAX_POINT_NEXT input[indexes[j] * strider + maxPointIndex]


#define MIN_POINT_X input[indexes[i] * strider + 1 + 1]
#define MIN_POINT_Y input[indexes[i] * strider + 1 + 2]
#define MIN_POINT_Z input[indexes[i] * strider + 1 + 3]
#define MAX_POINT_X input[indexes[i] * strider + 1 + 4]
#define MAX_POINT_Y input[indexes[i] * strider + 1 + 5]
#define MAX_POINT_Z input[indexes[i] * strider + 1 + 6]

#define MIN_POINT_X_NEXT_AABB input[indexes[j] * strider + 1 + 1]
#define MIN_POINT_Y_NEXT_AABB input[indexes[j] * strider + 1 + 2]
#define MIN_POINT_Z_NEXT_AABB input[indexes[j] * strider + 1 + 3]
#define MAX_POINT_X_NEXT_AABB input[indexes[j] * strider + 1 + 4]
#define MAX_POINT_Y_NEXT_AABB input[indexes[j] * strider + 1 + 5]
#define MAX_POINT_Z_NEXT_AABB input[indexes[j] * strider + 1 + 6]

__kernel void sweepAndPrune(
	__constant float * input, 
	__constant size_t* inputLength, 
    __constant size_t* indexes,
    __constant size_t* strider_global,
	__constant size_t* offset_global,
    __constant size_t* minPointIndex_global,
    __constant size_t* maxPointIndex_global,
	__global   size_t* outputLength,
	__global   size_t* output)
{
    __private size_t elementsPerWorkItem = max( (int) (*inputLength / THREAD_COUNT) , 1 );
    __private size_t inputIndex = THREAD_ID * elementsPerWorkItem;
    __private size_t outputIndex = 0;
    __private size_t strider = *strider_global;
    __private size_t minPointIndex = *minPointIndex_global + *offset_global;
    __private size_t maxPointIndex = *maxPointIndex_global + *offset_global;

    for( size_t i = inputIndex ; i < inputIndex + elementsPerWorkItem ; i++ )
    {
        for(size_t j = i + 1; j < *inputLength ; j++)
        //for(size_t j = i + 1; j < i + elementsPerWorkItem ; j++)
        {

/*
            if (MAX_POINT_X < MIN_POINT_X_NEXT_AABB)  // if maxPoint currernt AABB greater than minPoint of right AABB, they do not collides in X axis
                break;

            if (MAX_POINT_Y >= MIN_POINT_Y_NEXT_AABB && MIN_POINT_Y <= MAX_POINT_Y_NEXT_AABB    //check AABB collision
             && MAX_POINT_Z >= MIN_POINT_Z_NEXT_AABB && MIN_POINT_Z <= MAX_POINT_Z_NEXT_AABB)
            {
                outputIndex = atomic_add(outputLength, 2);
                output[outputIndex] = i;
                output[outputIndex + 1] = j;
            }
            */

            if (MAX_POINT < MIN_POINT_NEXT)  // if maxPoint greater than minPoint of next, they do not collides anymore
                break;

            // MUITA COLISAO PARA POUCA MEMORIA !!!!!
            if (MAX_POINT >= MIN_POINT_NEXT && MIN_POINT <= MAX_POINT_NEXT)
            //if (MAX_POINT_Y >= MIN_POINT_Y_NEXT_AABB && MIN_POINT_Y <= MAX_POINT_Y_NEXT_AABB  && MAX_POINT_Z >= MIN_POINT_Z_NEXT_AABB && MIN_POINT_Z <= MAX_POINT_Z_NEXT_AABB)
            {
                outputIndex = atomic_add(outputLength, 2);
                output[outputIndex] = i;
                output[outputIndex + 1] = j;
            }

        }
    }


    barrier(CLK_GLOBAL_MEM_FENCE);
    if (THREAD_ID == 0) {
        output[0] = *outputLength;
        output[1] = *maxPointIndex_global;
        output[2] = *strider_global;
        output[3] = *offset_global;
        output[4] = *inputLength;
        output[5] = input[2];
    }


}
