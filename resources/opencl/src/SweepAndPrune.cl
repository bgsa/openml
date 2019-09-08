#define THREAD_ID get_global_id(0)

#define ELEMENTS_IN_AABB 7
#define offset 1

#define MIN_POINT_X aabbs[index + offset]
#define MIN_POINT_Y aabbs[index + offset + 1]
#define MIN_POINT_Z aabbs[index + offset + 2]
#define MAX_POINT_X aabbs[index + offset + 3]
#define MAX_POINT_Y aabbs[index + offset + 4]
#define MAX_POINT_Z aabbs[index + offset + 5]

#define MIN_POINT_X_NEXT_AABB aabbs[(i*ELEMENTS_IN_AABB) + offset]

__kernel void sweepAndPrune(
	__global   float * aabbs, 
	__constant size_t* aabbsCount, 
	__global   size_t* globalIndex, 
	__global   size_t* output)
{
    __private size_t index = THREAD_ID * ELEMENTS_IN_AABB;
    __private size_t outputIndex = 0;

    for(size_t i = THREAD_ID + 1; i < *aabbsCount; i++)
    {
        if (MAX_POINT_X < MIN_POINT_X_NEXT_AABB)  // if maxPoint currernt AABB greater than minPoint of right AABB, they do not collides in X axis
            break;

        //check AABB collision
        if (MAX_POINT_Y >= aabbs[(i*ELEMENTS_IN_AABB) + offset + 1] && MIN_POINT_Y <= aabbs[(i*ELEMENTS_IN_AABB) + offset + 4]
         && MAX_POINT_Z >= aabbs[(i*ELEMENTS_IN_AABB) + offset + 2] && MIN_POINT_Z <= aabbs[(i*ELEMENTS_IN_AABB) + offset + 5])
        {
            outputIndex = atomic_add(globalIndex, 2);
            output[outputIndex] = THREAD_ID;
            output[outputIndex + 1] = i;
        }
    }
}
