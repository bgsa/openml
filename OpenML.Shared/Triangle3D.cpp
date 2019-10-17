#include "Triangle3D.h"

Triangle3D::Triangle3D()
{
}

Triangle3D::Triangle3D(const Vec3f& point1, const Vec3f& point2, const Vec3f& point3)
{
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
}

Triangle3D::Triangle3D(float* point1, float* point2, float* point3)
{
	this->point1 = Vec3f(point1[0], point1[1]);
	this->point2 = Vec3f(point2[0], point2[1]);
	this->point3 = Vec3f(point3[0], point3[1]);
}

Line3D* Triangle3D::getLines() const
{
	Line3D* lines = ALLOC_NEW_ARRAY(Line3D, 3);

	lines[0] = Line3D(point1, point2);
	lines[1] = Line3D(point2, point3);
	lines[2] = Line3D(point3, point1);

	return lines;
}

Vec3f Triangle3D::barycentric(const Vec3f& point) const
{
	Vec3f result;
	Vec3f v0 = point2 - point1;
	Vec3f v1 = point3 - point1;
	Vec3f v2 = point - point1;
	
	float d00 = v0.dot(v0); 
	float d01 = v0.dot(v1);
	float d11 = v1.dot(v1);
	float d20 = v2.dot(v0);
	float d21 = v2.dot(v1);
	
	float denom = 1.0f / (d00 * d11 - d01 * d01);
	
	result[1] = (d11 * d20 - d01 * d21) * denom;
	result[2] = (d00 * d21 - d01 * d20) * denom;
	result[0] = 1.0f - result[1] - result[2];

	return result;
}
