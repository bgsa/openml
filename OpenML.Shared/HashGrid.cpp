#include "HashGrid.h"

int findCellIndexByCellId(const Vec3f& cell)
{
	const int h1 = 0x8da6b343; // Large multiplicative constants; 
	const int h2 = 0xd8163841; // here arbitrarily chosen primes 
	const int h3 = 0xcb1ab31f;

	return h1 * int(cell.x) + h2 * int(cell.y) + h3 * int(cell.z);
}

HashGrid::HashGrid()
{
	setCellSize(10);
}

HashGrid::HashGrid(size_t cellSize)
{
	setCellSize(cellSize);
}

void HashGrid::setCellSize(size_t cellSize)
{
	this->cellSize = cellSize;
	this->cellSizeInverted = 1.0f / cellSize;
}

size_t HashGrid::getCellSize()
{
	return cellSize;
}

Vec3f HashGrid::findCell(const Vec3f& point) 
{
	int negativeCellX = 0;
	int negativeCellY = 0;
	int negativeCellZ = 0;

	if (point.x < 0.0f)
		negativeCellX = -1;

	if (point.y < 0.0f)
		negativeCellY = -1;

	if (point.z < 0.0f)
		negativeCellZ = -1;

	Vec3f cell = {
		float(int(point.x * cellSizeInverted) + negativeCellX),
		float(int(point.y * cellSizeInverted) + negativeCellY),
		float(int(point.z * cellSizeInverted) + negativeCellZ)
	};
	
	return cell;
}

int HashGrid::findCellIndex(const Vec3f& point)
{
	Vec3f cell = findCell(point);

	return findCellIndexByCellId(cell);
}

Vec3List<float>* HashGrid::findRangeCell(const AABB& aabb)
{	
	Vec3List<float>* list = ALLOC(Vec3List<float>);
	Vec3f minCell = findCell(aabb.minPoint);
	Vec3f maxCell = findCell(aabb.maxPoint);

	Vec3f deltaPoints = (maxCell - minCell) + 1.0f;
		
	list->count = int(std::abs(
			(deltaPoints.x == 0.0f ? 1.0f : deltaPoints.x)
		* (deltaPoints.y == 0.0f ? 1.0f : deltaPoints.y)
		* (deltaPoints.z == 0.0f ? 1.0f : deltaPoints.z)));

	list->points = ALLOC_ARRAY(Vec3f, list->count);

	size_t index = 0;
	
	for (float x = minCell.x; x <= maxCell.x; x++)
		for (float y = minCell.y; y <= maxCell.y; y++)
			for (float z = minCell.z; z <= maxCell.z; z++)
			{
				list->points[index] = Vec3f(x, y, z);
				index++;
			}

	return list;
}

std::vector<int> HashGrid::findRangeCellIndex(const AABB& aabb)
{
	Vec3List<float>* cells = findRangeCell(aabb);

	std::vector<int> hashes = std::vector<int>(cells->count);

	for (int i = 0; i < cells->count; i++)
		hashes[i] = findCellIndexByCellId(cells->points[i]);

	ALLOC_RELEASE(cells);
	
	return hashes;
}

bool findValue(const std::unordered_multimap<AABB, AABB, AABB, AABB>& map, const AABB& key, const AABB& value)
{
	std::pair<AABB, AABB> pair = std::make_pair(key, value);
	auto its = map.equal_range(key);
	
	for (auto it = its.first; it != its.second; ++it) 
		if (it->second == value)
			return true;

	return false;
}

bool findValue2(const std::unordered_multimap<AABB, AABB, AABB, AABB>& map, const AABB& key, const AABB& value)
{
	std::pair<AABB, AABB> pair = std::make_pair(key, value);
	auto its = map.equal_range(key);

	for (auto it = its.first; it != its.second; ++it)
		if (it->second == value)
			return true;

	return false;
}

std::unordered_multimap<AABB, AABB, AABB, AABB> HashGrid::findCollisions(AABB* aabbs, size_t aabbCount)
{
	std::unordered_multimap<AABB, AABB, AABB, AABB> pairs;
	std::multimap<int, AABB> spatialVolume;
		
	for (size_t aabbIndex = 0; aabbIndex < aabbCount; aabbIndex++)
	{
		AABB aabb = aabbs[aabbIndex];
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
