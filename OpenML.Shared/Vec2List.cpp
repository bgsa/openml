#include "Vec2List.h"

template <typename T>
Vec2List<T>::Vec2List()
{
}

template <typename T>
Vec2List<T>::Vec2List(const std::vector<Vec2<T>> &list)
{
	this->list = list;
}

template <typename T>
void Vec2List<T>::add(const Vec2<T> &value) 
{

}

template <typename T>
size_t Vec2List<T>::size() 
{
	return list.size();
}

template <typename T>
Vec2<T>* Vec2List<T>::findMinX() 
{
	if (size() == 0)
		return nullptr;

	Vec2<T>* result = &list[0];

	for (Vec2<T> point : list)
	{
		if (point[0] < result->[0])
			result = &point;
	}

	return result;
}


