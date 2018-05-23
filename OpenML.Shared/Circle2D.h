#pragma once

#include "OpenML.h"

namespace OpenML
{
	template <typename T>
	class Circle2D 
	{
	public:
		T ray;
		Point2D<T> center;

		API_INTERFACE inline Circle2D();
		API_INTERFACE inline Circle2D(const Point2D<T>& center, T ray);
		API_INTERFACE inline Circle2D(const Point2D<T>& point1, const Point2D<T>& point2, const Point2D<T>& point3);

		API_INTERFACE inline T area();

		API_INTERFACE inline T circumference();

		API_INTERFACE T* calculatePoints(size_t& pointsCount);

		API_INTERFACE T getDistance(const Point2D<T>& point);

		API_INTERFACE Colision2DStatus getColisionStatus(const Point2D<T> &point);

		API_INTERFACE bool hasIntersection(const Circle2D<T>& circle2);

		API_INTERFACE Point2D<T>* findIntersection(const Circle2D<T>& circle2);

	};

	typedef Circle2D<int> Circle2Di;
	typedef Circle2D<float> Circle2Df;
	typedef Circle2D<double> Circle2Dd;
}