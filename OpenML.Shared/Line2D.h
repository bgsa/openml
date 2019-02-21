#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Mat3.h"
#include "Orientation.h"
#include "ColisionStatus.h"
#include "Circle2D.h"
#include "SystemOfLinearEquations.h"

namespace OpenML 
{
	template <typename T>
	class Line2D
	{
	public:
		Vec2<T> point1;
		Vec2<T> point2;

		API_INTERFACE inline Line2D();
		API_INTERFACE inline Line2D(const Vec2<T>& point1, const Vec2<T>& point2);
		API_INTERFACE inline Line2D(T* point1, T* point2);

		/// <summary>
		/// Get the angle of the line
		/// </summary>
		API_INTERFACE inline T angle() const;

		/// <summary>
		/// Get the slope/inclination of the line
		/// </summary>
		API_INTERFACE inline T slope() const;
				
		/// <summary>
		/// Get the line equation in 2 points for 2D space
		/// The result is a vector with 2 components (m, b)
		/// Parametric line equation: "y = mx + b"
		/// </summary>
		API_INTERFACE inline Vec2<T> getParametricEquation() const;

		/// <summary>
		/// Get the line equation in 2 points for 2D space
		/// The result is a vector with 3 components (a, b, c)
		/// Line equation: "ax + bx + c = 0"
		/// </summary>
		API_INTERFACE Vec3<T> getEquation() const;
		
		/// <summary>
		/// Convert line to directional ray
		/// <summary>
		API_INTERFACE Vec2<T> toRay();

		/// <summary>
		/// Indicate whether the point is ON the vector
		/// It means the point is a point on this line
		/// </summary>
		API_INTERFACE bool isOnTheLine(const Vec2<T>& point) const;

		/// <summary>
		/// Indicate whether the point is on the left of the vector/line
		/// </summary>
		API_INTERFACE bool isOnTheLeft(const Vec2<T>& point) const;

		/// <summary>
		/// Indicate whether the point is on the right of the vector/line
		/// </summary>
		API_INTERFACE bool isOnTheRight(const Vec2<T>& point) const;

		/// <summary>
		/// Indicate whether the point is on the left, right or is a point of the line line/vector
		/// </summary>
		API_INTERFACE Orientation getOrientation(const Vec2<T>& point) const;

		/// <summary>
		/// Get te distance from this line to the point
		/// </summary>
		API_INTERFACE inline T getDistance(Vec2<T> point) const;

		/// <summary>
		/// Find the point of intersection of the line and the othr line
		/// It can return NULL if there is no intersection
		/// </summary>
		API_INTERFACE Vec2<T>* findIntersection(const Line2D<T>& otherLine) const;

		/// <summary>
		/// Check the line has intersection with the circle
		/// </summary>
		API_INTERFACE inline ColisionStatus hasIntersections(const Circle2D<T>& circle) const;

		/// <summary>
		/// Get the delta X - diference max X - min X
		/// </summary>
		API_INTERFACE inline T deltaX() const;

		/// <summary>
		/// Get the delta Y - diference max Y - min Y
		/// </summary>
		API_INTERFACE inline T deltaY() const;
	};

	typedef Line2D<int> Line2Di;
	typedef Line2D<float> Line2Df;
	typedef Line2D<double> Line2Dd;
}