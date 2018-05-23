#pragma once

#include "OpenML.h"

namespace OpenML
{
	template <typename T>
	class Triangle2D
	{
	public:
		Point2D<T> point1;
		Point2D<T> point2;
		Point2D<T> point3;

		API_INTERFACE inline Triangle2D();
		API_INTERFACE inline Triangle2D(const Point2D<T>& point1, const Point2D<T>& point2, const Point2D<T>& point3);
		API_INTERFACE inline Triangle2D(T* point1, T* point2, T* point3);

		API_INTERFACE inline T area() const;

		API_INTERFACE inline T perimeter() const;

		API_INTERFACE inline T height() const;
		
		///<summary>
		///Get the lines that makes the rectangle
		///</summary>
		inline Line2D<T>* getLines() const;

		///<summary>
		///Chech the point is outside, inside or on the line of the triangle
		///</summary>
		API_INTERFACE Colision2DStatus getColisionStatus(const Point2D<T>& point) const;

		///<summary>
		///Chech the line has intersection with the triangle
		///</summary>
		API_INTERFACE bool hasIntersection(const Line2D<T>& line) const;

		///<summary>
		///Chech the circle has intersection with the triangle
		///</summary>
		API_INTERFACE bool hasIntersection(const Circle2D<T>& circle) const;

	};

	typedef Triangle2D<int> Triangle2Di;
	typedef Triangle2D<float> Triangle2Df;
	typedef Triangle2D<double> Triangle2Dd;
}