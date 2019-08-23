#define MIN_POINT_X points[index]
#define MIN_POINT_Y points[index + 1]
#define MIN_POINT_Z points[index + 2]
#define MAX_POINT_X points[index + 3]
#define MAX_POINT_Y points[index + 4]
#define MAX_POINT_Z points[index + 5]

#define MIN_POINT_X_OTHER_AABB points[(i*6)]
#define MAX_POINT_X_OTHER_AABB points[(previousAABBIndex*6) + 3]

__kernel void sweepAndPrune(
	__constant float*  points, 
	__constant size_t* pointsCount, 
	__global   size_t* globalIndex, 
	__global   float*  output) 
{
    __private size_t workItemIndex = get_global_id(0);
    __private size_t index = (workItemIndex * 6);
    __private size_t previousAABBIndex = workItemIndex - 1;
    __private size_t aabbCount = *pointsCount;

    __private size_t outputIndex = 0;

    //check nexts AABBs on the right side
    for(size_t i = workItemIndex + 1; i < aabbCount; i++)
    {
        if (MAX_POINT_X < MIN_POINT_X_OTHER_AABB)  // if maxPoint currernt AABB greater than minPoint of right AABB, they do not collides in X axis
            break;

        //check AABB collision
        if (MAX_POINT_Y > points[(i*6) + 1] && MIN_POINT_Y < points[(i*6) + 4]
         && MAX_POINT_Z > points[(i*6) + 2] && MIN_POINT_Z < points[(i*6) + 5])
        {
            outputIndex = atomic_add(globalIndex, 2);
            output[outputIndex] = workItemIndex;
            output[outputIndex + 1] = i;
        }
    }

    //check previous AABBs on the left side
    while(previousAABBIndex != UINT_MAX)
    {
        if (MAX_POINT_X_OTHER_AABB < MIN_POINT_X)  // if maxPoint other AABB lesser than minPoint of right AABB, they do not collides in X axis
            break;

        //check AABB collision
        if (MAX_POINT_Y > points[(previousAABBIndex*6) + 1] && MIN_POINT_Y < points[(previousAABBIndex*6) + 4]
         && MAX_POINT_Z > points[(previousAABBIndex*6) + 2] && MIN_POINT_Z < points[(previousAABBIndex*6) + 5])
        {
            outputIndex = atomic_add(globalIndex, 2);
            output[outputIndex] = previousAABBIndex;
            output[outputIndex + 1] = workItemIndex;
        }

        previousAABBIndex--;
    }
}