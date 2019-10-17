#pragma once

#include "OpenML.h"
#include "Line3D.h"

namespace OpenML
{

	class Triangle3D
	{
	public:
		Vec3f point1;
		Vec3f point2;
		Vec3f point3;

		API_INTERFACE inline Triangle3D();
		API_INTERFACE inline Triangle3D(const Vec3f& point1, const Vec3f& point2, const Vec3f& point3);
		API_INTERFACE inline Triangle3D(float* point1, float* point2, float* point3);

		API_INTERFACE Line3D* getLines() const;

		API_INTERFACE Vec3f barycentric(const Vec3f& point) const;

	};

}