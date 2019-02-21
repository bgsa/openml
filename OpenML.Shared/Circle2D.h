#pragma once

#include "OpenML.h"

namespace OpenML
{
	template <typename T>
	class Circle2D 
	{
	public:
		T ray;
		Vec2<T> center;

		API_INTERFACE inline Circle2D();
		API_INTERFACE inline Circle2D(const Vec2<T>& center, T ray);
		API_INTERFACE inline Circle2D(const Vec2<T>& point1, const Vec2<T>& point2, const Vec2<T>& point3);

		API_INTERFACE inline T area();

		API_INTERFACE inline T circumference();

		API_INTERFACE T* calculatePoints(size_t& pointsCount);

		API_INTERFACE T getDistance(const Vec2<T>& point);

		API_INTERFACE ColisionStatus getColisionStatus(const Vec2<T> &point);

		API_INTERFACE bool hasIntersection(const Circle2D<T>& circle2);

		API_INTERFACE Vec2<T>* findIntersection(const Circle2D<T>& circle2);

	};

	typedef Circle2D<int> Circle2Di;
	typedef Circle2D<float> Circle2Df;
	typedef Circle2D<double> Circle2Dd;
}