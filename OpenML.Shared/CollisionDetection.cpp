#include "CollisionDetection.h"

template <typename T>
std::vector<std::pair<AABB<T>, AABB<T>>> CollisionDetection::bruteForce(AABB<T>* boundingVolumes, size_t count)
{
	std::vector<std::pair<AABB<T>, AABB<T>>> result;

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

template std::vector<std::pair<AABB<int>, AABB<int>>> CollisionDetection::bruteForce<int>(AABB<int>*, size_t);
template std::vector<std::pair<AABB<float>, AABB<float>>> CollisionDetection::bruteForce<float>(AABB<float>*, size_t);
template std::vector<std::pair<AABB<double>, AABB<double>>> CollisionDetection::bruteForce<double>(AABB<double>*, size_t);