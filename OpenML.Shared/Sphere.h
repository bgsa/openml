#pragma once

#include "OpenML.h"
#include "Vec3.h"
#include "Mat4.h"
#include "Plane3D.h"
#include "ColisionStatus.h"
#include "BoundingVolume.h"

namespace OpenML
{

	template <typename T>
	class Sphere
		: public BoundingVolume
	{
	public:
		Vec3<T> center;
		T ray;

		/// <summary>
		/// Default construct - unit sphere with the center in origin
		/// </summary>
		API_INTERFACE inline Sphere();

		/// <summary>
		/// Construct with the center point and a ray
		/// </summary>
		API_INTERFACE inline Sphere(const Vec3<T> &center, T ray);

		/// <summary>
		/// Build the sphere from 1 point (center) and ray = 1
		/// </summary>
		API_INTERFACE Sphere(const Vec3<T> &point1);

		/// <summary>
		/// Build the sphere from 2 (support) points
		/// </summary>
		API_INTERFACE Sphere(const Vec3<T> &point1, const Vec3<T> &point2);

		/// <summary>
		/// Build the sphere from 3 (support) points
		/// </summary>
		API_INTERFACE Sphere(const Vec3<T> &point1, const Vec3<T> &point2, const Vec3<T> &point3);

		/// <summary>
		/// Build the sphere from 4 points
		/// </summary>
		API_INTERFACE Sphere(const Vec3<T> &point1, const Vec3<T> &point2, const Vec3<T> &point3, const Vec3<T> &point4);

		/// <summary>
		/// Check the status of colision against the point
		/// </summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const Vec3<T> &point) const;

		/// <summary>
		/// Check the status of colision against the plane
		/// </summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const Plane3D<T> &plane) const;

		/// <summary>
		/// Check the status of colision against the plane
		/// </summary>
		API_INTERFACE inline ColisionStatus colisionStatus(const Sphere<T> &sphere) const;

		/// <summary>
		/// Build a enclosing sphere from an AABB
		/// </summary>
		API_INTERFACE static Sphere<T> buildFrom(const AABB<T> &aabb);

		/// <summary>
		/// Build a enclosing sphere from an AABB
		/// </summary>
		API_INTERFACE static Sphere<T> buildFrom(const Vec3List<T>& pointList);

		/// <summary>
		/// Enclose/add the sphere in another one
		/// </summary>
		API_INTERFACE Sphere<T> enclose(const Sphere<T>& sphere);

		/// <summary>
		/// Enclose/add the sphere in AABB
		/// </summary>
		API_INTERFACE Sphere<T> enclose(const AABB<T>& aabb);


	};

	typedef Sphere<int> Spherei;
	typedef Sphere<float> Spheref;
	typedef Sphere<double> Sphered;
}