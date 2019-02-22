#pragma once

#include "Vec3.h"

namespace OpenML 
{
	template <typename T>
	class Line3D
	{
	public:
		Vec3<T> point1;
		Vec3<T> point2;

		///<summary>
		/// Empty constructor 
		///</summary>
		API_INTERFACE inline Line3D();

		///<summary>
		/// Build a line from 2 points
		///</summary>
		API_INTERFACE inline Line3D(const Vec3<T>& point1, const Vec3<T>& point2);

		///<summary>
		/// Build a line from 2 points as vector
		///</summary>
		API_INTERFACE inline Line3D(Vec3<T>* points);

		///<summary>
		/// Build a line from 2 points (3 numbers for each point)
		///</summary>
		API_INTERFACE inline Line3D(T* point1, T* point2);
		
		///<summary>
		/// Find intersections by 3D lines
		///</summary>
		API_INTERFACE Vec3<T>* findIntersection(const Line3D<T>& line2) const;

		///<summary>
		/// Get the closest point in the SEGMENT of line, given an arbitrary point
		///</summary>
		API_INTERFACE Vec3<T> closestPointOnTheLine(const Vec3<T>& target) const;

		///<summary>
		/// Get the SQUARED distance from SEGMENT of line and an arbitrary point
		///</summary>
		API_INTERFACE T squaredDistance(const Vec3<T>& target) const;

		///<summary>
		/// Get the SQUARED distance from SEGMENT of line and an arbitrary point
		///</summary>
		API_INTERFACE T distance(const Vec3<T>& target) const;

	};

	typedef Line3D<int> Line3Di;
	typedef Line3D<float> Line3Df;
	typedef Line3D<double> Line3Dd;
}