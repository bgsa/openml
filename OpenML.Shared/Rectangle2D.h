#pragma once

#include "OpenML.h"
#include "Line2D.h"
#include "Triangle2D.h"

namespace OpenML
{
	template <typename T>
	class Rectangle2D
	{
	public:
		Point2D<T> point1;
		Point2D<T> point2;
		Point2D<T> point3;
		Point2D<T> point4;

		API_INTERFACE Rectangle2D();
		API_INTERFACE Rectangle2D(Point2D<T>* points);
		API_INTERFACE Rectangle2D(Point2D<T> point1, Point2D<T> point2, Point2D<T> point3, Point2D<T> point4);
		API_INTERFACE Rectangle2D(T* point1, T* point2, T* point3, T* point4);

		T API_INTERFACE width();

		T API_INTERFACE height();

		T API_INTERFACE area();

		T API_INTERFACE perimeter();

		T API_INTERFACE diagonalLength();

		///<summary>
		///Get the lines that makes the rectangle
		///</summary>
		Line2D<T>* getLines();

		///<summary>
		///Get the status of colision of the point into the rectangle
		///</summary>
		Colision2DStatus API_INTERFACE getSatusColision(Point2D<T> point);
	
		///<summary>
		///Chech the line has intersection with the rectangle
		///</summary>
		bool API_INTERFACE hasIntersection(Line2D<T> line);

		///<summary>
		///Chech the triangle has intersection with the rectangle
		///</summary>
		bool API_INTERFACE hasIntersection(Triangle2D<T> triangle);

		///<summary>
		///Chech the circle has intersection with the rectangle
		///</summary>
		bool API_INTERFACE hasIntersection(Circle2D<T> circle);
	};

	typedef Rectangle2D<int> Rectangle2Di;
	typedef Rectangle2D<float> Rectangle2Df;
	typedef Rectangle2D<double> Rectangle2Dd;
}