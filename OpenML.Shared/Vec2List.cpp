#include "Vec2List.h"

using namespace OpenML;

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
void Vec2List<T>::add(Vec2<T> &value) 
{
	list.push_back(value);
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

	for (size_t i = 0 ; i != list.size() ; i ++)
	{
		if (list[i].x < result->x)
			result = &list[i];
	}

	return result;
}

template <typename T>
Vec2<T>* Vec2List<T>::findMinY()
{
	if (size() == 0)
		return nullptr;

	Vec2<T>* result = &list[0];

	for (size_t i = 0; i != list.size(); i++)
	{
		if (list[i].y < result->y)
			result = &list[i];
	}

	return result;
}

template <typename T>
Vec2<T>* Vec2List<T>::findMaxX()
{
	if (size() == 0)
		return nullptr;

	Vec2<T>* result = &list[0];

	for (size_t i = 0; i != list.size(); i++)
	{
		if (list[i].x > result->x)
			result = &list[i];
	}

	return result;
}

template <typename T>
Vec2<T>* Vec2List<T>::findMaxY()
{
	if (size() == 0)
		return nullptr;

	Vec2<T>* result = &list[0];

	for (size_t i = 0; i != list.size(); i++)
	{
		if (list[i].y > result->y)
			result = &list[i];
	}

	return result;
}

template <typename T>
void Vec2List<T>::sortByAxis(Vec2<T>* arr, size_t left, size_t right, int axisIndex)
{
	size_t i = left, j = right;
	Vec2<T> tmp;
	Vec2<T> pivot = arr[ (size_t) (left + right) / 2 ];
	size_t nextAxis = axisIndex == 0 ? axisIndex + 1 : axisIndex - 1;

	while (i <= j) 
	{
		while (arr[i][axisIndex] < pivot[axisIndex])
			i++;

		while (arr[j][axisIndex] > pivot[axisIndex])
			j--;

		if (i <= j)
		{
			std::swap(arr[i], arr[j]);
			i++;
			j--;
		}
	};
	
	if (left < j)
		sortByAxis(arr, left, j, axisIndex);
	if (i < right)
		sortByAxis(arr, i, right, axisIndex);
}

template <typename T>
void Vec2List<T>::sortByAxisXY()
{	
	Vec2List<T>::sortByAxis(&list[0], 0, list.size() - 1, 0);

	for (size_t i = 0; i < list.size(); i++)
	{
		for (size_t j = i + 1; j < list.size(); j++)
		{
			if (list[i][0] != list[j][0])
				break;

			if (list[i][1] > list[j][1]) {
				std::swap(list[i], list[j]);
			}
		}
	}
}

template <typename T>
void Vec2List<T>::sortByX()
{
	Vec2List<T>::sortByAxis(&list[0], 0, list.size() - 1, 0);
}

template <typename T>
void Vec2List<T>::sortByY()
{
	Vec2List<T>::sortByAxis(&list[0], 0, list.size() - 1, 1);
}

template <typename T>
Vec2<T> nextToTop(std::stack<Vec2<T>> values) 
{
	Vec2<T> topValue = values.top();

	values.pop();

	Vec2<T> nextToTopValue = values.top();

	values.push(topValue);

	return nextToTopValue;
}

template <typename T>
std::stack<Vec2<T>> Vec2List<T>::convexUpperHull()
{
	Vec2<T> point1 = list[0];
	Vec2<T> point2 = list[1];
	Vec2<T> currentPoint = list[2];
	T determinant = T(0);
	bool isCounterClockwise = false;

	std::stack<Vec2<T>> upperHull;
	upperHull.push(point1);
	upperHull.push(point2);
	
	for (size_t i = 2; i < list.size(); i++)
	{
		point1 = nextToTop(upperHull);
		point2 = upperHull.top();
		currentPoint = list[i];

		Mat3<T> lineMatrix = {
			T(1), T(1), T(1),
			currentPoint[0], point1[0], point2[0],
			currentPoint[1], point1[1], point2[1]
		};

		determinant = lineMatrix.determinant();

		isCounterClockwise = determinant >= T(0);
		
		while (isCounterClockwise)
		{
			upperHull.pop();

			if (upperHull.size() == 1)
				break;

			point1 = nextToTop(upperHull);
			point2 = upperHull.top();

			Mat3<T> lineMatrix = {
				T(1), T(1), T(1),
				currentPoint.x, point1.x, point2.x,
				currentPoint.y, point1.y, point2.y
			};

			isCounterClockwise = lineMatrix.determinant() >= T(0);
		}

		upperHull.push(list[i]);
	}

	return upperHull;
}

template <typename T>
std::stack<Vec2<T>> Vec2List<T>::convexLowerHull()
{
	Vec2<T> point1 = list[list.size() - 1];
	Vec2<T> point2 = list[list.size() - 2];
	Vec2<T> currentPoint = list[list.size() - 3];
	T determinant = T(0);
	bool isCounterClockwise = false;

	std::stack<Vec2<T>> lowerHull;
	lowerHull.push(point1);
	lowerHull.push(point2);

	for (size_t i = list.size() - 3; i != std::numeric_limits<size_t>::max() ; i--)
	{
		point1 = nextToTop(lowerHull);
		point2 = lowerHull.top();
		currentPoint = list[i];

		Mat3<T> lineMatrix = {
			T(1), T(1), T(1),
			currentPoint.x, point1.x, point2.x,
			currentPoint.y, point1.y, point2.y
		};

		determinant = lineMatrix.determinant();

		isCounterClockwise = determinant >= T(0);

		while (isCounterClockwise)
		{
			lowerHull.pop();

			if (lowerHull.size() == 1)
				break;

			point1 = nextToTop(lowerHull);
			point2 = lowerHull.top();

			Mat3<T> lineMatrix = {
				T(1), T(1), T(1),
				currentPoint.x, point1.x, point2.x,
				currentPoint.y, point1.y, point2.y
			};

			isCounterClockwise = lineMatrix.determinant() >= T(0);
		}

		lowerHull.push(list[i]);
	}

	return lowerHull;
}

template <typename T>
Vec2List<T> Vec2List<T>::convexHull()
{
	std::stack<Vec2<T>> upperHull = convexUpperHull();
	std::stack<Vec2<T>> lowerHull = convexLowerHull();

	Vec2List<T> result;

	lowerHull.pop();

	while ( ! lowerHull.empty() ) 
	{
		result.add(lowerHull.top());
		lowerHull.pop();
	}

	upperHull.pop();

	while ( ! upperHull.empty() )
	{
		result.add(upperHull.top());
		upperHull.pop();
	}

	return result;
}

namespace OpenML
{
	template class Vec2List<int>;
	template class Vec2List<float>;
	template class Vec2List<double>;
}