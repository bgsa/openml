#include "Triangle3D.h"

template <typename T>
Triangle3D<T>::Triangle3D()
{
}

template <typename T>
Triangle3D<T>::Triangle3D(const Vec3<T>& point1, const Vec3<T>& point2, const Vec3<T>& point3)
{
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
}

template <typename T>
Triangle3D<T>::Triangle3D(T* point1, T* point2, T* point3)
{
	this->point1 = Vec3<T>(point1[0], point1[1]);
	this->point2 = Vec3<T>(point2[0], point2[1]);
	this->point3 = Vec3<T>(point3[0], point3[1]);
}

template<typename T>
Line3D<T>* Triangle3D<T>::getLines() const
{
	Line3D<T>* lines = new Line3D<T>[3];

	lines[0] = Line3D<T>(point1, point2);
	lines[1] = Line3D<T>(point2, point3);
	lines[2] = Line3D<T>(point3, point1);

	return lines;
}

template<typename T>
Vec3<T> Triangle3D<T>::barycentric(const Vec3<T>& point) const
{
	Vec3<T> result;
	Vec3<T> v0 = point2 - point1;
	Vec3<T> v1 = point3 - point1;
	Vec3<T> v2 = point - point1;
	
	T d00 = v0.dot(v0); 
	T d01 = v0.dot(v1);
	T d11 = v1.dot(v1);
	T d20 = v2.dot(v0);
	T d21 = v2.dot(v1);
	
	T denom = T(1) / (d00 * d11 - d01 * d01);
	
	result[1] = (d11 * d20 - d01 * d21) * denom;
	result[2] = (d00 * d21 - d01 * d20) * denom;
	result[0] = T(1) - result[1] - result[2];

	return result;
}

namespace OpenML
{
	template class Triangle3D<int>;
	template class Triangle3D<float>;
	template class Triangle3D<double>;
}