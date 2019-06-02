#include "HashGrid.h"

template <typename T>
HashGrid<T>::HashGrid()
{
	setCellSize(10);
}

template <typename T>
HashGrid<T>::HashGrid(size_t cellSize)
{
	setCellSize(cellSize);
}

template <typename T>
void HashGrid<T>::setCellSize(size_t cellSize)
{
	this->cellSize = cellSize;
	this->cellSizeInverted = 1.0f / cellSize;
}

template <typename T>
size_t HashGrid<T>::getCellSize()
{
	return cellSize;
}

template <typename T>
Vec3<T> HashGrid<T>::findCell(const Vec3<T>& point) 
{
	int negativeCellX = 0;
	int negativeCellY = 0;
	int negativeCellZ = 0;

	if (point[0] < T(0))
		negativeCellX = -1;

	if (point[1] < T(0))
		negativeCellY = -1;

	if (point[2] < T(0))
		negativeCellZ = -1;

	Vec3<T> cell = {
		T(int(point[0] * cellSizeInverted) + negativeCellX),
		T(int(point[1] * cellSizeInverted) + negativeCellY),
		T(int(point[2] * cellSizeInverted) + negativeCellZ)
	};
	
	return cell;
}

template <typename T>
int HashGrid<T>::findCellIndex(const Vec3<T>& point)
{
	Vec3<T> cell = findCell(point);

	const int h1 = 0x8da6b343; // Large multiplicative constants; 
	const int h2 = 0xd8163841; // here arbitrarily chosen primes 
	const int h3 = 0xcb1ab31f;
	
	return h1 * int(cell[0]) + h2 * int(cell[1]) + h3 * int(cell[2]);
}

template <typename T>
Vec3<T>* HashGrid<T>::findRangeCell(const AABB<T>& aabb) 
{
	Vec3<T> minCell = findCell(aabb.minPoint);
	Vec3<T> maxCell = findCell(aabb.maxPoint);

	Vec3<T> deltaPoints = (maxCell - minCell) + T(1);

	Vec3<T>* result = new Vec3<T>[size_t(deltaPoints[0] * deltaPoints[1] * deltaPoints[2])];
	size_t index = 0;

	for (T x = T(0); x < deltaPoints[0]; x++)
		for (T y = T(0); y < deltaPoints[1]; y++)
			for (T z = T(0); z < deltaPoints[2]; z++) 
			{
				result[index] = Vec3<T>(x, y, z);
				index++;
			}

	return result;
}

namespace OpenML
{
	template class HashGrid<int>;
	template class HashGrid<float>;
	template class HashGrid<double>;
}