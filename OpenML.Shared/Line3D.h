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

		API_INTERFACE inline Line3D();

		API_INTERFACE inline Line3D(const Vec3<T>& point1, const Vec3<T>& point2);

		API_INTERFACE inline Line3D(Vec3<T>* points);

		API_INTERFACE inline Line3D(T* point1, T* point2);

		API_INTERFACE Vec3<T>* findIntersection(const Line3D<T>& line2) const;
	};

	typedef Line3D<int> Line3Di;
	typedef Line3D<float> Line3Df;
	typedef Line3D<double> Line3Dd;
}