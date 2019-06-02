#pragma once

#include "OpenML.h"
#include "AABB.h"
#include <unordered_map>

namespace OpenML
{

	template <typename T>
	class HashGrid
	{
	private:
		size_t cellSize;
		float cellSizeInverted;

	public:
		HashGrid();
		HashGrid(size_t cellSize);

		API_INTERFACE void setCellSize(size_t cellSize);
		API_INTERFACE size_t getCellSize();

		API_INTERFACE Vec3<T> findCell(const Vec3<T>& point);

		API_INTERFACE int findCellIndex(const Vec3<T>& point);

		API_INTERFACE Vec3List<T>* findRangeCell(const AABB<T>& aabb);

		API_INTERFACE std::vector<int> findRangeCellIndex(const AABB<T>& aabb);

		API_INTERFACE std::unordered_multimap<AABB<T>, AABB<T>, AABB<T>, AABB<T>> findCollisions(AABB<T>* aabbs, size_t aabbCount);

	};

}

