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

		Plane3D() {	};
		Plane3D(Point3D<T> point, Vec3<T> vector)
		{
			this->point = point;
			this->normalVector = vector;
		}
		Plane3D(Point3D<T> point1, Point3D<T> point2, Point3D<T> point3)
		{
			Vec3<T> point1AsVec3 = point1.toVec3();
			Vec3<T> ab = point1AsVec3 - point2.toVec3();
			Vec3<T> ac = point1AsVec3 - point3.toVec3();

			point = point2;

			normalVector = Vec3<T>{
				ab[1] * ac[2] - (ab[2] * ac[1]),
				ab[2] * ac[0] - (ab[0] * ac[2]),
				ab[0] * ac[1] - (ab[1] * ac[0])
			}.normalize();
		}

		Vec4<T> getEquation()
		{
			T value = (normalVector * T(-1)).dot(point.toVec3());

			return Vec4<T>(
				normalVector[0],
				normalVector[1],
				normalVector[2],
				value
				);
		}

		Point3Df* findIntersection(Line3D<T> line)
		{
			Vec3<T> point1AsVec3 = line.point1.toVec3();
			Vec3<T> lineAsVector = line.point2.toVec3() - point1AsVec3;

			T angle = normalVector.dot(lineAsVector);

			if (angle == T(0))
				return nullptr;

			Vec4<T> planeEquation = getEquation();

			T numerator = -(planeEquation[0] * point1AsVec3[0] + planeEquation[1] * point1AsVec3[1] + planeEquation[2] * point1AsVec3[2] + planeEquation[3]);
			T denominator = planeEquation[0] * lineAsVector[0] + planeEquation[1] * lineAsVector[1] + planeEquation[2] * lineAsVector[2];

			T t = numerator / denominator;

			Point3D<T>* intersection = new Point3D<T>(
				point1AsVec3[0] + lineAsVector[0] * t,
				point1AsVec3[1] + lineAsVector[1] * t,
				point1AsVec3[2] + lineAsVector[2] * t
				);

			return intersection;
		}
	
	};

	typedef Plane3D<int> Plane3Di;
	typedef Plane3D<float> Plane3Df;
	typedef Plane3D<double> Plane3Dd;
}