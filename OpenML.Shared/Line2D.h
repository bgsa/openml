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

		Line2D() {	};
		Line2D(Point2D<T> point1, Point2D<T> point2)
		{
			assert(point1 != point2);

			this->point1 = point1;
			this->point2 = point2;
		}
		Line2D(T* point1, T* point2)
		{
			assert(point1 != point2);

			this->point1 = Point2D<T>(point1[0], point1[1]);
			this->point2 = Point2D<T>(point2[0], point2[1]);
		}

		/// <summary>
		/// Get the angle of the line
		/// </summary>
		T angle() 
		{
			T deltaY = point2.y - point1.y;
			T deltaX = point2.x - point1.x;

			T angle = T(atan(deltaY / deltaX));
			return angle;
		}

		/// <summary>
		/// Get the slope/inclination of the line
		/// </summary>
		T slope()
		{
			T deltaY = point2.y - point1.y;
			T deltaX = point2.x - point1.x;

			T slope = T(deltaY / deltaX);

			return slope;
		}
				
		/// <summary>
		/// Get the line equation in 2 points for 2D space
		/// The result is a vector with 2 components (m, b)
		/// Parametric line equation: "y = mx + b"
		/// </summary>
		Vec2<T> getParametricEquation()
		{
			T m = slope();
			T b = -(m * point1.x) + point1.y;

			 return Vec2<T>(m, b);
		}

		/// <summary>
		/// Get the line equation in 2 points for 2D space
		/// The result is a vector with 3 components (a, b, c)
		/// Line equation: "ax + bx + c = 0"
		/// </summary>
		Vec3<T> getEquation()
		{
			Vec3<T> values = SystemOfLinearEquations<T>::getLineEquation(point1.toVec2(), point2.toVec2());

			return values;
		}

		/// <summary>
		/// Indicate whether the point is ON the vector
		/// It means the point is a point on this line
		/// </summary>
		bool isOnTheLine(Point2D<T> point) 
		{
			VerticalOrientation orientation = getOrientation(point);

			if (orientation != VerticalOrientation::NONE)
				return false;

			// check the range of the line x point
			float point1PosX = point1.x > point2.x ? point2.x : point1.x;
			float point2PosX = point1PosX + deltaX();

			float point1PosY = point1.y > point2.y ? point2.y : point1.y;
			float point2PosY = point1PosY + deltaY();

			if (point.x < point1PosX || point.x > point2PosX
				|| point.y < point1PosY || point.y > point2PosY)
				return false;

			return true;
		}

		/// <summary>
		/// Indicate whether the point is on the left of the vector/line
		/// </summary>
		bool isOnTheLeft(Point2D<T> point) {
			VerticalOrientation orientation = getOrientation(point);
			return orientation == VerticalOrientation::LEFT;
		}

		/// <summary>
		/// Indicate whether the point is on the right of the vector/line
		/// </summary>
		bool isOnTheRight(Point2D<T> point) {
			VerticalOrientation orientation = getOrientation(point);
			return orientation == VerticalOrientation::RIGHT;
		}

		/// <summary>
		/// Indicate whether the point is on the left, right or is a point of the line line/vector
		/// </summary>
		VerticalOrientation getOrientation(Point2D<T> point)
		{
			Mat3<T> lineMatrix = {
				T(1), T(1), T(1),
				point1.x, point2.x, point.x,
				point1.y, point2.y, point.y
			};

			int determinant = (int)lineMatrix.determinant();

			if (determinant == 0)
				return VerticalOrientation::NONE;
			if (determinant > 0)
				return VerticalOrientation::LEFT;
			else
				return VerticalOrientation::RIGHT;
		}

		/// <summary>
		/// Get te distance from this line to the point
		/// </summary>
		T getDistance(Point2D<T> point)
		{
			Vec3<T> values = getEquation();

			float numerador = fabsf(values[0] * point.x + values[1] * point.y + values[2]);
			float denominador = sqrt(values[0] * values[0] + values[1] * values[1]);

			float distanceFromPointToLine = numerador / denominador;

			return distanceFromPointToLine;
		}

		/// <summary>
		/// Find the point of intersection of the line and the othr line
		/// It can return NULL if there is no intersection
		/// </summary>
		Point2D<T>* findIntersection(Line2D<T> otherLine) 
		{
			Point2D<T> line2Point1 = otherLine.point1;
			Point2D<T> line2Point2 = otherLine.point2;

			T determinant = (line2Point2.x - line2Point1.x) * (point2.y - point1.y) - (line2Point2.y - line2Point1.y) * (point2.x - point1.x);

			if (determinant == 0.0)
				return nullptr; // intersection not found
			
			double s = ((line2Point2.x - line2Point1.x) * (line2Point1.y - point1.y) - (line2Point2.y - line2Point1.y) * (line2Point1.x - point1.x)) / determinant;
			//double t = ((point2.x - point1.x) * (line2Point1.y - point1.y) - (point2.y - point1.y) * (line2Point1.x - point1.x)) / determinant;

			Point2D<T>* intersection = new Point2D<T>(
				point1.x + (point2.x - point1.x)* T(s),
				point1.y + (point2.y - point1.y)* T(s)
			);

			if (!isOnTheLine(*intersection))
				return nullptr;  // intersection not found on this line

			if (!otherLine.isOnTheLine(*intersection))
				return nullptr;  // intersection not found on this line

			return intersection;
		}

		Colision2DStatus hasIntersections(Circle2D<T> circle) 
		{
			T distanceCenterToLine = ceil(getDistance(circle.center));
			float ray = ceil(circle.ray);

			if (distanceCenterToLine > ray)
				return Colision2DStatus::OUTSIDE;

			if (distanceCenterToLine < ray)
				return Colision2DStatus::INSIDE;

			return Colision2DStatus::INLINE;
		}

		float deltaX()
		{
			return fabsf(point1.x - point2.x);
		}
		float deltaY()
		{
			return fabsf(point1.y - point2.y);
		}
	};

	typedef Line2D<int> Line2Di;
	typedef Line2D<float> Line2Df;
	typedef Line2D<double> Line2Dd;
}