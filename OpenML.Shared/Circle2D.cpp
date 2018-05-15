#include "Circle2D.h"

template<typename T>
Circle2D<T>::Circle2D() 
{
}

template<typename T>
Circle2D<T>::Circle2D(Point2D<T> center, T ray)
{
	this->center = center;
	this->ray = ray;
}

template<typename T>
Circle2D<T>::Circle2D(Point2D<T> point1, Point2D<T> point2, Point2D<T> point3)
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

	this->center = OpenML::Point2D<T>(-(b / 2 * a), -(c / 2 * a));
	this->ray = T(sqrt(numerator / denominator));
}

template<typename T>
T Circle2D<T>::area() {
	return T(PI * ray * ray);
}

template<typename T>
T Circle2D<T>::circumference() {
	return T(2 * PI * ray);
}

template<typename T>
T* Circle2D<T>::calculatePoints(size_t& pointsCount)
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
T Circle2D<T>::getDistance(Point2D<T> point)
{
	T distance = center.getDistance(point);
	return distance;
}

template<typename T>
Colision2DStatus Circle2D<T>::getColisionStatus(Point2D<T> point)
{
	double distance = ceil(point.toVec2().distance(center.toVec2()));
	double rayDistance = ceil(ray);

	if (distance > rayDistance)
		return OpenML::Colision2DStatus::OUTSIDE;

	if (distance < rayDistance)
		return OpenML::Colision2DStatus::INSIDE;

	return OpenML::Colision2DStatus::INLINE;
}

template<typename T>
bool Circle2D<T>::hasIntersection(Circle2D<T> circle2)
{
	T distance = center.toVec2().distance(circle2.center.toVec2());

	bool intersectionFound = ray + circle2.ray >= distance;

	return intersectionFound;
}

template<typename T>
Point2D<T>* Circle2D<T>::findIntersection(Circle2D<T> circle2)
{
	Vec2<T> point1AsVector = center.toVec2();
	Vec2<T> point2AsVector = circle2.center.toVec2();

	T distance = point1AsVector.distance(point2AsVector);

	bool intersectionFound = ray + circle2.ray >= distance;

	if (!intersectionFound)
		return nullptr;

	double a = (ray*ray - circle2.ray*circle2.ray + distance * distance) / (2 * distance);
	double h = sqrt(ray*ray - a * a);

	Vec2<T> p3 = ((point2AsVector - point1AsVector) * T(a / distance)) + center.toVec2();

	T x3 = T( p3[0] + h * (circle2.center.y - center.y) / distance );
	T y3 = T( p3[1] - h * (circle2.center.x - center.x) / distance );

	Point2D<T>* result;

	if (ray + circle2.ray == distance)   //has only one point
	{
		result = new Point2D<T>[1];
		result[0] = Point2D<T>(x3, y3);

		return result;
	}
	else
	{
		T x4 = T( p3[0] - h * (circle2.center.y - center.y) / distance);
		T y4 = T( p3[1] + h * (circle2.center.x - center.x) / distance);

		result = new Point2D<T>[2];
		result[0] = Point2D<T>(x3, y3);
		result[1] = Point2D<T>(x4, y4);
	}

	return result;
}

template class Circle2D<int>;;
template class Circle2D<float>;
template class Circle2D<double>;