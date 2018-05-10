#pragma once

#include "Vec3.h"

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
		API_INTERFACE
		Point3D();

		/// <summary>
		/// Constructor with args
		/// </summary>
		API_INTERFACE
		Point3D(T x, T y, T z);

		/// <summary>
		/// Constructor from a 3D vector
		/// </summary>
		API_INTERFACE
		Point3D(Vec3<T> vector);

		/// <summary>
		/// Constructor with values as array
		/// </summary>
		API_INTERFACE
		Point3D(T* values);

		/// <summary>
		/// Get the distance between two 3D points
		/// </summary>
		API_INTERFACE
		T distance(Point3D<T> otherPoint);

		/// <summary>
		/// Convert to a 3D vector
		/// </summary>
		API_INTERFACE
		Vec3<T> toVec3();

		/// <summary>
		/// Compare this point to another one. Compare each component.
		/// </summary>
		API_INTERFACE bool operator==(const Point3D<T> &other) const;

		/// <summary>
		/// Compare this point to another one. Compare each component.
		/// </summary>
		API_INTERFACE bool operator!=(const Point3D<T> &other) const;
	};

	typedef Point3D<int> Point3Di;
	typedef Point3D<float> Point3Df;
	typedef Point3D<double> Point3Dd;
}