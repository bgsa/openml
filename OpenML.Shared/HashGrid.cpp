#include "HashGrid.h"

template <typename T>
int findCellIndexByCellId(const Vec3<T>& cell)
{
	const int h1 = 0x8da6b343; // Large multiplicative constants; 
	const int h2 = 0xd8163841; // here arbitrarily chosen primes 
	const int h3 = 0xcb1ab31f;

	return h1 * int(cell.x) + h2 * int(cell.y) + h3 * int(cell.z);
}

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

	if (point.x < T(0))
		negativeCellX = -1;

	if (point.y < T(0))
		negativeCellY = -1;

	if (point.z < T(0))
		negativeCellZ = -1;

	Vec3<T> cell = {
		T(int(point.x * cellSizeInverted) + negativeCellX),
		T(int(point.y * cellSizeInverted) + negativeCellY),
		T(int(point.z * cellSizeInverted) + negativeCellZ)
	};
	
	return cell;
}

template <typename T>
int HashGrid<T>::findCellIndex(const Vec3<T>& point)
{
	Vec3<T> cell = findCell(point);

	return findCellIndexByCellId(cell);
}

template <typename T>
Vec3List<T>* HashGrid<T>::findRangeCell(const AABB<T>& aabb) 
{	
	Vec3List<T>* list = new Vec3List<T>();
	Vec3<T> minCell = findCell(aabb.minPoint);
	Vec3<T> maxCell = findCell(aabb.maxPoint);

	Vec3<T> deltaPoints = (maxCell - minCell) + T(1);
		
	list->count = int(std::abs(
			(deltaPoints.x == T(0) ? T(1) : deltaPoints.x)
		* (deltaPoints.y == T(0) ? T(1) : deltaPoints.y) 
		* (deltaPoints.z == T(0) ? T(1) : deltaPoints.z)));

	list->points = new Vec3<T>[list->count];

	size_t index = 0;
	
	for (T x = minCell.x; x <= maxCell.x; x++)
		for (T y = minCell.y; y <= maxCell.y; y++)
			for (T z = minCell.z; z <= maxCell.z; z++)
			{
				list->points[index] = Vec3<T>(x, y, z);
				index++;
			}

	return list;
}

template <typename T>
std::vector<int> HashGrid<T>::findRangeCellIndex(const AABB<T>& aabb)
{
	Vec3List<T>* cells = findRangeCell(aabb);

	std::vector<int> hashes = std::vector<int>(cells->count);

	for (int i = 0; i < cells->count; i++)
		hashes[i] = findCellIndexByCellId(cells->points[i]);

	delete cells;
	
	return hashes;
}

template <typename T>
bool findValue(const std::unordered_multimap<AABB<T>, AABB<T>, AABB<T>, AABB<T>>& map, const AABB<T>& key, const AABB<T>& value)
{
	std::pair<AABB<T>, AABB<T>> pair = std::make_pair(key, value);
	auto its = map.equal_range(key);
	
	for (auto it = its.first; it != its.second; ++it) 
		if (it->second == value)
			return true;

	return false;
}

template <typename T>
bool findValue2(const std::unordered_multimap<AABB<T>, AABB<T>, AABB<T>, AABB<T>>& map, const AABB<T>& key, const AABB<T>& value)
{
	std::pair<AABB<T>, AABB<T>> pair = std::make_pair(key, value);
	auto its = map.equal_range(key);

	for (auto it = its.first; it != its.second; ++it)
		if (it->second == value)
			return true;

	return false;
}

template <typename T>
std::unordered_multimap<AABB<T>, AABB<T>, AABB<T>, AABB<T>> HashGrid<T>::findCollisions(AABB<T>* aabbs, size_t aabbCount)
{
	std::unordered_multimap<AABB<T>, AABB<T>, AABB<T>, AABB<T>> pairs;
	std::multimap<int, AABB<T>> spatialVolume;
		
	for (size_t aabbIndex = 0; aabbIndex < aabbCount; aabbIndex++)
	{
		AABB<T> aabb = aabbs[aabbIndex];
		std::vector<int> hashes = findRangeCellIndex(aabb);
		
		for each (int hash in hashes)
		{
			auto its = spatialVolume.equal_range(hash);

			for (auto it = its.first; it != its.second; ++it) 
			{
				bool hasCollisionAABB = aabb.colisionStatus(it->second) == ColisionStatus::INSIDE;

				if (hasCollisionAABB && !findValue(pairs, aabb, it->second))   //check if exists on map
					pairs.emplace(aabb, it->second);
			}
			
			spatialVolume.emplace( hash, aabbs[aabbIndex] );
		}
	}

	return pairs;
}


namespace OpenML
{
	template class HashGrid<int>;
	template class HashGrid<float>;
	template class HashGrid<double>;
}