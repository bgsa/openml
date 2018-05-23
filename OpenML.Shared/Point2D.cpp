#include "Point2D.h"

using namespace OpenML;

template<typename T>
Point2D<T>::Point2D() {
}

template<typename T>
Point2D<T>::Point2D(T x, T y) {
	this->x = x;
	this->y = y;
}

template<typename T>
Point2D<T>::Point2D(const Vec2<T>& vector) {
	this->x = vector[0];
	this->y = vector[1];
}

template<typename T>
T Point2D<T>::getDistance(const Point2D<T>& otherPoint) const
{
	T distance = toVec2().distance(otherPoint.toVec2());
	return distance;
}

template<typename T>
Vec2<T> Point2D<T>::toVec2() const
{
	return Vec2<T>(x, y);
}

template<typename T>
bool Point2D<T>::operator==(const Point2D<T>& otherPoint) const
{
	return x == otherPoint.x
		&& y == otherPoint.y;
}

template<typename T>
bool Point2D<T>::operator!=(const Point2D<T>& otherPoint) const
{
	return x != otherPoint.x
		|| y != otherPoint.y;
}

template<typename T>
Point2D<T> Point2D<T>::findMinX(Point2D<T>* points, size_t pointsCount)
{
	Point2D<T> minXValue = points[0];

	for (size_t i = 1; i < pointsCount; i++)
	{
		if (points[i].x < minXValue.x)
			minXValue = points[i];
	}

	return minXValue;
}

template<typename T>
Point2D<T> Point2D<T>::findMinY(Point2D<T>* points, size_t pointsCount)
{
	Point2D<T> minYValue = points[0];

	for (size_t i = 1; i < pointsCount; i++)
	{
		if (points[i].y < minYValue.y)
			minYValue = points[i];
	}

	return minYValue;
}
	
template<typename T>
Point2D<T> Point2D<T>::findMaxX(Point2D<T>* points, size_t pointsCount)
{
	Point2D<T> maxXValue = points[0];

	for (size_t i = 1; i < pointsCount; i++)
	{
		if (points[i].x > maxXValue.x)
			maxXValue = points[i];
	}

	return maxXValue;
}
	
template<typename T>
Point2D<T> Point2D<T>::findMaxY(Point2D<T>* points, size_t pointsCount)
{
	Point2D<T> maxYValue = points[0];

	for (size_t i = 1; i < pointsCount; i++)
	{
		if (points[i].y > maxYValue.y)
			maxYValue = points[i];
	}

	return maxYValue;
}

namespace OpenML
{
	template class Point2D<int>;
	template class Point2D<float>;
	template class Point2D<double>;
}