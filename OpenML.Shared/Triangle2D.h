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

		API_INTERFACE Triangle2D();
		API_INTERFACE Triangle2D(Point2D<T> point1, Point2D<T> point2, Point2D<T> point3);
		API_INTERFACE Triangle2D(T* point1, T* point2, T* point3);

		T API_INTERFACE area();

		T API_INTERFACE perimeter();

		T API_INTERFACE height();
		
		///<summary>
		///Get the lines that makes the rectangle
		///</summary>
		Line2D<T>* getLines();

		///<summary>
		///Chech the point is outside, inside or on the line of the triangle
		///</summary>
		Colision2DStatus API_INTERFACE getColisionStatus(Point2D<T> point);

		///<summary>
		///Chech the line has intersection with the triangle
		///</summary>
		bool API_INTERFACE hasIntersection(Line2D<T> line);

		///<summary>
		///Chech the circle has intersection with the triangle
		///</summary>
		bool API_INTERFACE hasIntersection(Circle2D<T> circle);

	};

	typedef Triangle2D<int> Triangle2Di;
	typedef Triangle2D<float> Triangle2Df;
	typedef Triangle2D<double> Triangle2Dd;
}