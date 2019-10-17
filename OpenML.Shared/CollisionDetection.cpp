#include "CollisionDetection.h"

std::vector<std::pair<AABB, AABB>> CollisionDetection::bruteForce(AABB* boundingVolumes, size_t count)
{
	std::vector<std::pair<AABB, AABB>> result;

	for (size_t i = 0; i < count; i++)
	{
		for (size_t j = i + 1; j < count; j++)
		{
			if (boundingVolumes[i].colisionStatus(boundingVolumes[j]) == ColisionStatus::INSIDE)
				result.push_back({ boundingVolumes[i] , boundingVolumes[j] });
		}
	}

	return result;
}
