#pragma once

#include "Vec3.h"
#include "Plane3D.h"
#include "ColisionStatus.h"

namespace OpenML
{

	template <typename T>
	class Sphere
	{
	public:
		Vec3<T> center;
		T ray;

		/// <summary>
		/// Default construct
		/// </summary>
		API_INTERFACE inline Sphere(const Vec3<T> &center, T ray);

		/// <summary>
		/// Check the status of colision against the point
		/// </summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const Vec3<T> &point) const;

		/// <summary>
		/// Check the status of colision against the plane
		/// </summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const Plane3D<T> &plane) const;

	};

	typedef Sphere<int> Spherei;
	typedef Sphere<float> Spheref;
	typedef Sphere<double> Sphered;
}