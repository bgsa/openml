#pragma once

#include "Point2D.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Mat3.h"
#include "Orientation.h"
#include "Colision2DStatus.h"
#include "Circle2D.h"
#include "SystemOfLinearEquations.h"

namespace OpenML 
{
	template <typename T>
	class Line2D
	{
	public:
		Point2D<T> point1;
		Point2D<T> point2;

		Line2D();
		Line2D(Point2D<T> point1, Point2D<T> point2);
		Line2D(T* point1, T* point2);

		/// <summary>
		/// Get the angle of the line
		/// </summary>
		T angle();

		/// <summary>
		/// Get the slope/inclination of the line
		/// </summary>
		T slope();
				
		/// <summary>
		/// Get the line equation in 2 points for 2D space
		/// The result is a vector with 2 components (m, b)
		/// Parametric line equation: "y = mx + b"
		/// </summary>
		Vec2<T> getParametricEquation();

		/// <summary>
		/// Get the line equation in 2 points for 2D space
		/// The result is a vector with 3 components (a, b, c)
		/// Line equation: "ax + bx + c = 0"
		/// </summary>
		Vec3<T> getEquation();

		/// <summary>
		/// Indicate whether the point is ON the vector
		/// It means the point is a point on this line
		/// </summary>
		bool isOnTheLine(Point2D<T> point);

		/// <summary>
		/// Indicate whether the point is on the left of the vector/line
		/// </summary>
		bool isOnTheLeft(Point2D<T> point);

		/// <summary>
		/// Indicate whether the point is on the right of the vector/line
		/// </summary>
		bool isOnTheRight(Point2D<T> point);

		/// <summary>
		/// Indicate whether the point is on the left, right or is a point of the line line/vector
		/// </summary>
		VerticalOrientation getOrientation(Point2D<T> point);

		/// <summary>
		/// Get te distance from this line to the point
		/// </summary>
		T getDistance(Point2D<T> point);

		/// <summary>
		/// Find the point of intersection of the line and the othr line
		/// It can return NULL if there is no intersection
		/// </summary>
		Point2D<T>* findIntersection(Line2D<T> otherLine);

		Colision2DStatus hasIntersections(Circle2D<T> circle);

		T deltaX();
		T deltaY();
	};

	typedef Line2D<int> Line2Di;
	typedef Line2D<float> Line2Df;
	typedef Line2D<double> Line2Dd;
}