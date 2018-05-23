#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include "Point3D.h"
#include "Line3D.h"

namespace OpenML
{
	template <typename T>
	class Plane3D
	{
	public:
		Point3D<T> point;
		Vec3<T> normalVector;

		Plane3D();
		Plane3D(const Point3D<T>& point, const Vec3<T>& vector);
		Plane3D(const Point3D<T>& point1, const Point3D<T>& point2, const Point3D<T>& point3);

		Vec4<T> getEquation() const;

		Point3D<T>* findIntersection(const Line3D<T>& line) const;
	
	};

	typedef Plane3D<int> Plane3Di;
	typedef Plane3D<float> Plane3Df;
	typedef Plane3D<double> Plane3Dd;
}