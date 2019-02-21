#pragma once

#include "Vec3.h"
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
		API_INTERFACE inline ColisionStatus colisionStatus(const Vec3<T> &point);

	};

	typedef Sphere<int> Spherei;
	typedef Sphere<float> Spheref;
	typedef Sphere<double> Sphered;
}