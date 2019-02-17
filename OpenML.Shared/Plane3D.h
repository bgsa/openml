#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include "Line3D.h"

namespace OpenML
{
	template <typename T>
	class Plane3D
	{
	public:
		Vec3<T> point;
		Vec3<T> normalVector;

		API_INTERFACE inline Plane3D();
		API_INTERFACE inline Plane3D(const Vec3<T>& point, const Vec3<T>& vector);
		API_INTERFACE inline Plane3D(const Vec3<T>& point1, const Vec3<T>& point2, const Vec3<T>& point3);

		API_INTERFACE inline Vec4<T> getEquation() const;

		API_INTERFACE inline Vec3<T>* findIntersection(const Line3D<T>& line) const;
	
	};

	typedef Plane3D<int> Plane3Di;
	typedef Plane3D<float> Plane3Df;
	typedef Plane3D<double> Plane3Dd;
}