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

		API_INTERFACE inline Rectangle2D();
		API_INTERFACE inline Rectangle2D(Point2D<T>* points);
		API_INTERFACE inline Rectangle2D(const Point2D<T>& point1, const Point2D<T>& point2, const Point2D<T>& point3, const Point2D<T>& point4);
		API_INTERFACE inline Rectangle2D(T* point1, T* point2, T* point3, T* point4);

		///<summary>
		///Get the width of the rectangle
		///</summary>
		API_INTERFACE inline T width() const;

		///<summary>
		///Get the height of the rectangle
		///</summary>
		API_INTERFACE inline T height() const;

		///<summary>
		///Get the area of the rectangle
		///</summary>
		API_INTERFACE inline T area() const;

		///<summary>
		///Get the perimeter of the rectangle
		///</summary>
		API_INTERFACE inline T perimeter() const;

		///<summary>
		///Get the length of the rectangle diagonal
		///</summary>
		API_INTERFACE inline T diagonalLength() const;

		///<summary>
		///Get the lines that makes the rectangle
		///</summary>
		inline Line2D<T>* getLines() const;

		///<summary>
		///Get the status of colision of the point into the rectangle
		///</summary>
		inline Colision2DStatus getSatusColision(const Point2D<T>& point) const;
	
		///<summary>
		///Chech the line has intersection with the rectangle
		///</summary>
		API_INTERFACE bool hasIntersection(const Line2D<T>& line) const;

		///<summary>
		///Chech the triangle has intersection with the rectangle
		///</summary>
		API_INTERFACE bool hasIntersection(const Triangle2D<T>& triangle) const;

		///<summary>
		///Chech the circle has intersection with the rectangle
		///</summary>
		API_INTERFACE bool hasIntersection(const Circle2D<T>& circle) const;

		///<summary>
		///Get the bounding box, given a array of 2D points
		///It groups all points in a box
		///</summary>
		API_INTERFACE static Rectangle2D<T> getBoundingBox(Point2D<T>* points, size_t pointsCount);
	};

	typedef Rectangle2D<int> Rectangle2Di;
	typedef Rectangle2D<float> Rectangle2Df;
	typedef Rectangle2D<double> Rectangle2Dd;
}