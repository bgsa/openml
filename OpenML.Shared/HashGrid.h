#pragma once

#include "OpenML.h"
#include "AABB.h"

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

		API_INTERFACE Vec3<T>* findRangeCell(const AABB<T>& aabb);

	};

}