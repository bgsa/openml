#pragma once

#include "Vec2.h"

template <typename T>
class Vec2List
{
private:
	std::vector<Vec2<T>> list;

public:

	Vec2List();
	Vec2List(const std::vector<Vec2<T>> &list);

	void add(Vec2<T> &value);

	API_INTERFACE size_t size();

	/// <summary>
	/// Find the point that contain the minimum X value
	/// </summary>		
	API_INTERFACE static Vec2<T>* findMinX();

	/// <summary>
	/// Find the point that contain the minimum Y value
	/// </summary>		
	static Vec2<T> API_INTERFACE findMinY();

	/// <summary>
	/// Find the point that contain the maximum X value
	/// </summary>		
	static Vec2<T> API_INTERFACE findMaxX();

	/// <summary>
	/// Find the point that contain the maximum Y value
	/// </summary>		
	static Vec2<T> API_INTERFACE findMaxY();

};

