#include "Rectangle2D.h"
#include "Vec2List.h"

template<typename T>
Rectangle2D<T>::Rectangle2D() {
};

template<typename T>
Rectangle2D<T>::Rectangle2D(Vec2<T>* points)
{
	this->point1 = points[0];
	this->point2 = points[1];
	this->point3 = points[2];
	this->point4 = points[3];
}

template<typename T>
Rectangle2D<T>::Rectangle2D(const Vec2<T>& point1, const Vec2<T>& point2, const Vec2<T>& point3, const Vec2<T>& point4)
{
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
	this->point4 = point4;
}

template<typename T>
Rectangle2D<T>::Rectangle2D(T* point1, T* point2, T* point3, T* point4)
{
	this->point1 = Vec2<T>(point1[0], point1[1]);
	this->point2 = Vec2<T>(point2[0], point2[1]);
	this->point3 = Vec2<T>(point3[0], point3[1]);
	this->point4 = Vec2<T>(point4[0], point4[1]);
}

template<typename T>
T Rectangle2D<T>::width() const
{
	T width = point1.x() - point2.x();

	if (width == 0)
		width = point1.x() - point3.x();

	return abs(width);
}

template<typename T>
T Rectangle2D<T>::height() const
{
	T height = point1.y() - point2.y();

	if (height == 0)
		height = point1.y() - point3.y();

	return abs(height);
}

template<typename T>
T Rectangle2D<T>::area() const
{
	T area = width() * height();

	return area;
}

template<typename T>
T Rectangle2D<T>::perimeter() const
{
	T perimeter = 2 * width() + 2 * height();

	return perimeter;
}

template<typename T>
T Rectangle2D<T>::diagonalLength() const
{
	T w = width();
	T h = height();

	T diagonal = T(sqrt(w * w + h * h));

	return diagonal;
}

template<typename T>
Line2D<T>* Rectangle2D<T>::getLines() const
{
	Line2D<T>* lines = new Line2D<T>[4];
	lines[0] = Line2D<T>(point1, point2);
	lines[1] = Line2D<T>(point2, point3);
	lines[2] = Line2D<T>(point3, point4);
	lines[3] = Line2D<T>(point4, point1);

	return lines;
}

template<typename T>
Colision2DStatus Rectangle2D<T>::getSatusColision(const Vec2<T>& point) const
{
	T area1 = Triangle2D<T>(point1, point2, point).area();
	T area2 = Triangle2D<T>(point2, point3, point).area();
	T area3 = Triangle2D<T>(point3, point4, point).area();
	T area4 = Triangle2D<T>(point4, point1, point).area();
	T areaTotal = area1 + area2 + area3 + area4;

	T rectArea = area();

	if (int(areaTotal) > int(rectArea))
		return Colision2DStatus::OUTSIDE;

	return Colision2DStatus::INSIDE;
}

template<typename T>
bool Rectangle2D<T>::hasIntersection(const Line2D<T>& line) const
{
	Line2D<T> line1 = Line2D<T>(point1, point2);
	Line2D<T> line2 = Line2D<T>(point2, point3);
	Line2D<T> line3 = Line2D<T>(point3, point4);
	Line2D<T> line4 = Line2D<T>(point4, point1);

	Vec2<T>* point = line1.findIntersection(line);

	if (point != nullptr)
		return true;

	point = line2.findIntersection(line);

	if (point != nullptr)
		return true;

	point = line3.findIntersection(line);

	if (point != nullptr)
		return true;

	point = line4.findIntersection(line);

	if (point != nullptr)
		return true;

	return false;
}

template<typename T>
bool Rectangle2D<T>::hasIntersection(const Triangle2D<T>& triangle) const
{
	Line2D<T>* linesOfRectangle = getLines();
	Line2D<T>* linesOfTriangle = triangle.getLines();

	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 3; j++)
		{
			Line2D<T> line1 = linesOfRectangle[i];
			Line2D<T> line2 = linesOfTriangle[j];

			Vec2<T>* point = line1.findIntersection(line2);

			if (point != nullptr)
				return true;
		}

	return false;
}

template<typename T>
bool Rectangle2D<T>::hasIntersection(const Circle2D<T>& circle) const
{
	Line2D<T>* linesOfRectangle = getLines();

	for (size_t i = 0; i < 4; i++)
	{
		Line2D<T> line = linesOfRectangle[i];

		Colision2DStatus status = line.hasIntersections(circle);

		if (status == Colision2DStatus::INLINE || status == Colision2DStatus::INSIDE)
			return true;
	}

	return false;
}

template<typename T>
Rectangle2D<T> Rectangle2D<T>::getBoundingBox(Vec2List<T> &points)
{
	Vec2<T>* minX = points.findMinX();
	Vec2<T>* minY = points.findMinY();
	Vec2<T>* maxX = points.findMaxX();
	Vec2<T>* maxY = points.findMaxY();
	
	return Rectangle2D<T>(
		Vec2<T>(minX->x(), minY->y()),
		Vec2<T>(maxX->x(), minY->y()),
		Vec2<T>(maxX->x(), maxY->y()),
		Vec2<T>(minX->x(), maxY->y())
	);
}

namespace OpenML
{
	template class Rectangle2D<int>;
	template class Rectangle2D<float>;
	template class Rectangle2D<double>;
}