#include "Triangle2D.h"

template<typename T>
Triangle2D<T>::Triangle2D() { };

template<typename T>
Triangle2D<T>::Triangle2D(Point2D<T> point1, Point2D<T> point2, Point2D<T> point3)
{
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
}

template<typename T>
Triangle2D<T>::Triangle2D(T* point1, T* point2, T* point3)
{
	this->point1 = Point2D<T>(point1[0], point1[1]);
	this->point2 = Point2D<T>(point2[0], point2[1]);
	this->point3 = Point2D<T>(point3[0], point3[1]);
}

template<typename T>
T Triangle2D<T>::area()
{
	double numerator = fabs(point1.x * point2.y + point2.x * point3.y + point3.x * point1.y - point1.y * point2.x - point2.y * point3.x - point3.y * point1.x);
	T area = T(numerator / 2);

	return area;
}

template<typename T>
T Triangle2D<T>::perimeter()
{
	double term1 = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
	double term2 = sqrt((point2.x - point3.x) * (point2.x - point3.x) + (point2.y - point3.y) * (point2.y - point3.y));
	double term3 = sqrt((point3.x - point1.x) * (point3.x - point1.x) + (point3.y - point1.y) * (point3.y - point1.y));

	T perimeter = T(term1) + T(term2) + T(term3);

	return perimeter;
}

template<typename T>
T Triangle2D<T>::height()
{
	//T lengthVec1 = point1.getDistance(point2);
	T lengthVec2 = point2.getDistance(point3);

	T angle = point1.toVec2().angleRandians(point2.toVec2());

	T heigh = T(lengthVec2 * sin(angle));

	return heigh;
}

template<typename T>
Line2D<T>* Triangle2D<T>::getLines()
{
	Line2D<T>* lines = new Line2D<T>[3];
	lines[0] = Line2D<T>(point1, point2);
	lines[1] = Line2D<T>(point2, point3);
	lines[2] = Line2D<T>(point3, point1);

	return lines;
}

template<typename T>
Colision2DStatus Triangle2D<T>::getColisionStatus(Point2D<T> point)
{
	Line2D<T> line1 = Line2D<T>(point1, point2);
	Line2D<T> line2 = Line2D<T>(point2, point3);
	Line2D<T> line3 = Line2D<T>(point3, point1);

	VerticalOrientation orientation = line1.getOrientation(point);

	if (orientation == VerticalOrientation::RIGHT)
		return Colision2DStatus::OUTSIDE;

	if (orientation == VerticalOrientation::NONE)
		return Colision2DStatus::INLINE;

	orientation = line2.getOrientation(point);

	if (orientation == VerticalOrientation::RIGHT)
		return Colision2DStatus::OUTSIDE;

	if (orientation == VerticalOrientation::NONE)
		return Colision2DStatus::INLINE;

	orientation = line3.getOrientation(point);

	if (orientation == VerticalOrientation::RIGHT)
		return Colision2DStatus::OUTSIDE;

	if (orientation == VerticalOrientation::NONE)
		return Colision2DStatus::INLINE;

	return Colision2DStatus::INSIDE;
}

template<typename T>
bool Triangle2D<T>::hasIntersection(Line2D<T> line)
{
	Line2D<T> line1 = Line2D<T>(point1, point2);
	Line2D<T> line2 = Line2D<T>(point2, point3);
	Line2D<T> line3 = Line2D<T>(point3, point1);

	Point2D<T>* point = line1.findIntersection(line);

	if (point != nullptr)
		return true;

	point = line2.findIntersection(line);

	if (point != nullptr)
		return true;

	point = line3.findIntersection(line);

	if (point != nullptr)
		return true;

	return false;
}

template<typename T>
bool Triangle2D<T>::hasIntersection(Circle2D<T> circle)
{
	Line2D<T>* linesOfTriangle = getLines();

	for (size_t i = 0; i < 3; i++)
	{
		Line2D<T> line = linesOfTriangle[i];

		Colision2DStatus status = line.hasIntersections(circle);

		if (status == Colision2DStatus::INLINE || status == Colision2DStatus::INSIDE)
			return true;
	}

	return false;
}

namespace OpenML
{
	template class Triangle2D<int>;
	template class Triangle2D<float>;
	template class Triangle2D<double>;
}