#pragma once

#include "Point3D.h"
#include "Vec3.h"

namespace OpenML 
{
	template <typename T>
	class Line3D
	{
	public:
		Point3D<T> point1;
		Point3D<T> point2;

		API_INTERFACE inline Line3D();

		API_INTERFACE inline Line3D(const Point3D<T>& point1, const Point3D<T>& point2);

		API_INTERFACE inline Line3D(Point3D<T>* points);

		API_INTERFACE inline Line3D(T* point1, T* point2);

		API_INTERFACE inline Line3D(const Vec3<T>& point1, const Vec3<T>& point2);

		API_INTERFACE Point3D<T>* findIntersection(const Line3D<T>& line2) const;
	};

	typedef Line3D<int> Line3Di;
	typedef Line3D<float> Line3Df;
	typedef Line3D<double> Line3Dd;
}