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

		API_INTERFACE inline T area() const;

		API_INTERFACE inline T circumference() const;

		API_INTERFACE T* calculatePoints(size_t& pointsCount) const;

		API_INTERFACE T distance(const Vec2<T>& point) const;

		API_INTERFACE CollisionStatus collisionStatus(const Vec2<T> &point) const;

		API_INTERFACE bool hasIntersection(const Circle2D<T>& circle2) const;

		API_INTERFACE Vec2<T>* findIntersection(const Circle2D<T>& circle2) const;

	};

	typedef Circle2D<int> Circle2Di;
	typedef Circle2D<float> Circle2Df;
	typedef Circle2D<double> Circle2Dd;
}