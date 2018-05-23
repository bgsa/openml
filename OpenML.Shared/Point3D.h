#pragma once

#include "OpenML.h"

namespace OpenML 
{
	template <typename T>
	class Point3D
	{
	public:
		T x = T(0);
		T y = T(0);
		T z = T(0);

		/// <summary>
		/// Default constructor (0,0,0)
		/// </summary>
		API_INTERFACE Point3D();

		/// <summary>
		/// Constructor with args
		/// </summary>
		API_INTERFACE Point3D(T x, T y, T z);

		/// <summary>
		/// Constructor from a 3D vector
		/// </summary>
		API_INTERFACE Point3D(const Vec3<T>& vector);

		/// <summary>
		/// Constructor with values as array
		/// </summary>
		API_INTERFACE Point3D(T* values);

		/// <summary>
		/// Get the distance between two 3D points
		/// </summary>
		API_INTERFACE T distance(const Point3D<T>& otherPoint) const;

		/// <summary>
		/// Convert to a 3D vector
		/// </summary>
		API_INTERFACE Vec3<T> toVec3() const;

		/// <summary>
		/// Compare this point to another one. Compare each component.
		/// </summary>
		bool API_INTERFACE operator==(const Point3D<T> &other) const;

		/// <summary>
		/// Compare this point to another one. Compare each component.
		/// </summary>
		bool API_INTERFACE operator!=(const Point3D<T> &other) const;

		/// <summary>
		/// Find the point that contain the minimum X value
		/// </summary>		
		static Point3D<T> API_INTERFACE findMinX(Point3D<T>* points, size_t pointsCount);

		/// <summary>
		/// Find the point that contain the minimum Y value
		/// </summary>		
		static Point3D<T> API_INTERFACE findMinY(Point3D<T>* points, size_t pointsCount);

		/// <summary>
		/// Find the point that contain the minimum Z value
		/// </summary>		
		static Point3D<T> API_INTERFACE findMinZ(Point3D<T>* points, size_t pointsCount);

		/// <summary>
		/// Find the point that contain the maximum X value
		/// </summary>		
		static Point3D<T> API_INTERFACE findMaxX(Point3D<T>* points, size_t pointsCount);

		/// <summary>
		/// Find the point that contain the maximum Y value
		/// </summary>		
		static Point3D<T> API_INTERFACE findMaxY(Point3D<T>* points, size_t pointsCount);

		/// <summary>
		/// Find the point that contain the maximum Y value
		/// </summary>		
		static Point3D<T> API_INTERFACE findMaxZ(Point3D<T>* points, size_t pointsCount);
	};

	typedef Point3D<int> Point3Di;
	typedef Point3D<float> Point3Df;
	typedef Point3D<double> Point3Dd;
}