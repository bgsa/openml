#define THREAD_ID get_global_id(0)
#define THREAD_COUNT get_global_size(0)

#define strider 20
#define offset  2

#define MIN_POINT_X kdops[indexes[i] * strider + offset + 1]
#define MIN_POINT_Y kdops[indexes[i] * strider + offset + 2]
#define MIN_POINT_Z kdops[indexes[i] * strider + offset + 3]
#define MAX_POINT_X kdops[indexes[i] * strider + offset + 4]
#define MAX_POINT_Y kdops[indexes[i] * strider + offset + 5]
#define MAX_POINT_Z kdops[indexes[i] * strider + offset + 6]

#define MIN_POINT_X_NEXT_KDOP kdops[indexes[j] * strider + offset + 1]
#define MIN_POINT_Y_NEXT_KDOP kdops[indexes[j] * strider + offset + 2]
#define MIN_POINT_Z_NEXT_KDOP kdops[indexes[j] * strider + offset + 3]
#define MAX_POINT_X_NEXT_KDOP kdops[indexes[j] * strider + offset + 4]
#define MAX_POINT_Y_NEXT_KDOP kdops[indexes[j] * strider + offset + 5]
#define MAX_POINT_Z_NEXT_KDOP kdops[indexes[j] * strider + offset + 6]

__kernel void sweepAndPrune(
	__global   float * kdops, 
	__constant size_t* kdopsCount, 
	__global   size_t* globalIndex, 
    __global   size_t* indexes, 
	__global   size_t* output)
{
    __private size_t elementsPerWorkItem = max( *kdopsCount / THREAD_COUNT , 1 );
    __private size_t inputThreadIndex = THREAD_ID * elementsPerWorkItem;
    __private size_t outputIndex = 0;

    for( size_t i = inputThreadIndex ; i < inputThreadIndex + elementsPerWorkItem ; i++ )  // compute each element for this thread
    {
        for(size_t j = i + 1; j < *kdopsCount; j++) // compute one element
        {
            if (MAX_POINT_X < MIN_POINT_X_NEXT_KDOP)  // if maxPoint currernt AABB greater than minPoint of right AABB, they do not collides in X axis
                break;

            if (MAX_POINT_Y >= MIN_POINT_Y_NEXT_KDOP && MIN_POINT_Y <= MAX_POINT_Y_NEXT_KDOP    //check KDOP collision
             && MAX_POINT_Z >= MIN_POINT_Z_NEXT_KDOP && MIN_POINT_Z <= MAX_POINT_Z_NEXT_KDOP)
            {
                outputIndex = atomic_add(globalIndex, 2);
                output[outputIndex] = i;
                output[outputIndex + 1] = j;
            }
        }
    }

}
