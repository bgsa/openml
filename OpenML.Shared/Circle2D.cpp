#include "Circle2D.h"

template<typename T>
Circle2D<T>::Circle2D() 
{
	ray = T(0);
	center = Vec2<T>(T(0));
}

template<typename T>
Circle2D<T>::Circle2D(const Vec2<T>& center, T ray)
{
	this->center = center;
	this->ray = ray;
}

template<typename T>
Circle2D<T>::Circle2D(const Vec2<T>& point1, const Vec2<T>& point2, const Vec2<T>& point3)
{
	Mat4<T> matrix = {
		T(1), T(1), T(1), T(1),
		point1.x * point1.x + point1.y * point1.y, point1.x, point1.y, T(1),
		point2.x * point2.x + point2.y * point2.y, point2.x, point2.y, T(1),
		point3.x * point3.x + point3.y * point3.y, point3.x, point3.y, T(1),
	};

	T value = matrix.cofactorIJ(0, 0);

	T a = value / value;
	T b = matrix.cofactorIJ(0, 1) / value;
	T c = matrix.cofactorIJ(0, 2) / value;
	T d = matrix.cofactorIJ(0, 3) / value;

	T numerator = (b*b) + (c*c) - (4 * a * d);
	T denominator = 4 * a * a;

	this->center = Vec2<T>(-(b / 2 * a), -(c / 2 * a));
	this->ray = T(sqrt(numerator / denominator));
}

template<typename T>
T Circle2D<T>::area() const 
{
	return T(PI * ray * ray);
}

template<typename T>
T Circle2D<T>::circumference() const
{
	return T(2 * PI * ray);
}

template<typename T>
T* Circle2D<T>::calculatePoints(size_t& pointsCount) const
{
	const size_t vertexCount = 126;
	pointsCount = vertexCount / 2;

	T* points = new T[vertexCount];
	size_t index = 0;

	for (double angle = 0.0; angle < TWO_PI; angle += 0.1)
	{
		points[index + 0] = T(ray * cos(angle) + center.x);
		points[index + 1] = T(ray * sin(angle) + center.y);

		index += 2;
	}

	return points;
}

template<typename T>
T Circle2D<T>::distance(const Vec2<T>& point) const
{
	T distance = center.distance(point);
	return distance;
}

template<typename T>
ColisionStatus Circle2D<T>::colisionStatus(const Vec2<T>& point) const
{
	double distance = ceil(point.distance(center));
	double rayDistance = ceil(ray);

	if (distance > rayDistance)
		return OpenML::ColisionStatus::OUTSIDE;

	if (distance < rayDistance)
		return OpenML::ColisionStatus::INSIDE;

	return OpenML::ColisionStatus::INLINE;
}

template<typename T>
bool Circle2D<T>::hasIntersection(const Circle2D<T>& circle2) const
{
	T distance = center.distance(circle2.center);

	bool intersectionFound = ray + circle2.ray >= distance;

	return intersectionFound;
}

template<typename T>
Vec2<T>* Circle2D<T>::findIntersection(const Circle2D<T>& circle2) const
{
	Vec2<T> point1AsVector = center;
	Vec2<T> point2AsVector = circle2.center;

	T distance = point1AsVector.distance(point2AsVector);

	bool intersectionFound = ray + circle2.ray >= distance;

	if (!intersectionFound)
		return nullptr;

	double a = (ray*ray - circle2.ray*circle2.ray + distance * distance) / (2 * distance);
	double h = sqrt((ray * ray) - (a * a));

	Vec2<T> p3 = ((point2AsVector - point1AsVector) * T(a / distance)) + center;

	T x3 = T( p3[0] + h * (circle2.center.y - center.y) / distance );
	T y3 = T( p3[1] - h * (circle2.center.x - center.x) / distance );

	Vec2<T>* result;

	if (ray + circle2.ray == distance)   //has only one point
	{
		result = new Vec2<T>[1];
		result[0] = Vec2<T>(x3, y3);

		return result;
	}
	else
	{
		T x4 = T( p3[0] - h * (circle2.center.y - center.y) / distance);
		T y4 = T( p3[1] + h * (circle2.center.x - center.x) / distance);

		result = new Vec2<T>[2];
		result[0] = Vec2<T>(x3, y3);
		result[1] = Vec2<T>(x4, y4);
	}

	return result;
}


namespace OpenML
{
	template class Circle2D<int>;
	template class Circle2D<float>;
	template class Circle2D<double>;
}