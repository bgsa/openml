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

		Line3D() {	};
		Line3D(Point3D<T> point1, Point3D<T> point2)
		{
			assert(point1 != point2);

			this->point1 = point1;
			this->point2 = point2;
		}
		Line3D(Point3D<T>* points)
		{
			assert(points[0] != point[1]);

			this->point1 = points[0];
			this->point2 = points[1];
		}
		Line3D(T* point1, T* point2)
		{
			assert(points[0] != point[1]);

			this->point1 = Point3D<T>(point1[0], point1[1], point1[2]);
			this->point2 = Point3D<T>(point2[0], point2[1], point2[2]);
		}
		Line3D(Vec3<T> point1, Vec3<T> point2)
		{
			assert(points[0] != point[1]);

			this->point1 = Point3D<T>(point1[0], point1[1], point1[2]);
			this->point2 = Point3D<T>(point2[0], point2[1], point2[2]);
		}

		Point3D<T>* findIntersection(Line3D<T> line2)
		{
			Vec3<T> line1point1 = point1.toVec3();
			Vec3<T> line1point2 = point2.toVec3();

			Vec3<T> line2point1 = line2.point1.toVec3();
			Vec3<T> line2point2 = line2.point2.toVec3();

			Vec3<T> da = line1point2 - line1point1;
			Vec3<T> db = line2point2 - line2point1;
			Vec3<T> dc = line2point1 - line1point1;

			Vec3<T> dAcrossB = da.cross(db);

			T value = dc.dot(dAcrossB);

			if (value != T(0))
				return nullptr;

			T numerador = dc.cross(db).dot(dAcrossB);
			T denominador = dAcrossB.squared();

			T s = numerador / denominador;

			if (s >= 0 && s <= 1)
				return new Point3D<T>(da * s + line1point1);

			return nullptr;
		}
	};

	typedef Line3D<int> Line3Di;
	typedef Line3D<float> Line3Df;
	typedef Line3D<double> Line3Dd;
}