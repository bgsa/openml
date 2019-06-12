#pragma once

#include "OpenML.h"
#include "Line3D.h"

namespace OpenML
{
	template <typename T>
	class Triangle3D
	{
	public:
		Vec3<T> point1;
		Vec3<T> point2;
		Vec3<T> point3;

		API_INTERFACE inline Triangle3D();
		API_INTERFACE inline Triangle3D(const Vec3<T>& point1, const Vec3<T>& point2, const Vec3<T>& point3);
		API_INTERFACE inline Triangle3D(T* point1, T* point2, T* point3);

		API_INTERFACE Line3D<T>* getLines() const;

		API_INTERFACE Vec3<T> barycentric(const Vec3<T>& point) const;

	};

	typedef Triangle3D<int> Triangle3Di;
	typedef Triangle3D<float> Triangle3Df;
	typedef Triangle3D<double> Triangle3Dd;
}