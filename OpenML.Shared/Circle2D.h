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

		API_INTERFACE Circle2D();
		API_INTERFACE Circle2D(Point2D<T> center, T ray);
		API_INTERFACE Circle2D(Point2D<T> point1, Point2D<T> point2, Point2D<T> point3);

		T API_INTERFACE area();

		T API_INTERFACE circumference();

		T* calculatePoints(size_t& pointsCount);

		T API_INTERFACE getDistance(Point2D<T> point);

		Colision2DStatus API_INTERFACE getColisionStatus(Point2D<T> point);

		bool API_INTERFACE hasIntersection(Circle2D<T> circle2);

		Point2D<T>* findIntersection(Circle2D<T> circle2);

	};

	typedef Circle2D<int> Circle2Di;
	typedef Circle2D<float> Circle2Df;
	typedef Circle2D<double> Circle2Dd;
}