__kernel void sweepAndPrune(
	__global const float* points, 
	__global const size_t* pointsCount, 
	__global size_t* globalIndex, 
	__global float* output) 
{
    __private size_t workItemIndex = get_global_id(0);
    __private size_t index = workItemIndex * 6;
    __private size_t previousAABBIndex = workItemIndex - 1;
    __private const size_t aabbCount = *pointsCount;

    __private float minPointX = points[index];
    __private float minPointY = points[index + 1];
    __private float minPointZ = points[index + 2];
    __private float maxPointX = points[index + 3];
    __private float maxPointY = points[index + 4];
    __private float maxPointZ = points[index + 5];

    __private float minPointXotherAABB = 0;
    __private float maxPointXotherAABB = 0;
    __private size_t outputIndex = 0;
    __private size_t indexOtherAABB = 0;

    //check nexts AABBs on the right side
    for(size_t i = workItemIndex + 1; i < aabbCount; i++)
    {
        indexOtherAABB = i * 6;
        minPointXotherAABB = points[indexOtherAABB];

        if (maxPointX < minPointXotherAABB)  // if maxPoint currernt AABB greater than minPoint of right AABB, they do not collides in X axis
            break;

        //check AABB collision
        if (maxPointY > points[indexOtherAABB + 1] && minPointY < points[indexOtherAABB + 4]
         && maxPointZ > points[indexOtherAABB + 2] && minPointZ < points[indexOtherAABB + 5])
        {
            outputIndex = atomic_add(globalIndex, 2);
            output[outputIndex] = workItemIndex;
            output[outputIndex + 1] = i;
        }
    }

    //check previous AABBs on the left side
    while(previousAABBIndex != UINT_MAX)
    {
        indexOtherAABB = previousAABBIndex * 6;
        maxPointXotherAABB = points[indexOtherAABB + 3];

        if (maxPointXotherAABB < minPointX)  // if maxPoint other AABB lesser than minPoint of right AABB, they do not collides in X axis
            break;

        //check AABB collision
        if (maxPointY > points[indexOtherAABB + 1] && minPointY < points[indexOtherAABB + 4]
         && maxPointZ > points[indexOtherAABB + 2] && minPointZ < points[indexOtherAABB + 5])
        {
            outputIndex = atomic_add(globalIndex, 2);
            output[outputIndex] = previousAABBIndex;
            output[outputIndex + 1] = workItemIndex;
        }

        previousAABBIndex--;
    }
}