#pragma once

#include "Point2D.h"
#include "Colision2DStatus.h"
#include "Triangle2D.h"

namespace OpenML
{
	template <typename T>
	class Rectangle2D
	{
	public:
		Point2D<T> point1;
		Point2D<T> point2;
		Point2D<T> point3;
		Point2D<T> point4;

		Rectangle2D() { };
		Rectangle2D(Point2D<T>* points)
		{
			this->point1 = points[0];
			this->point2 = points[1];
			this->point3 = points[2];
			this->point4 = points[3];
		}
		Rectangle2D(Point2D<T> point1, Point2D<T> point2, Point2D<T> point3, Point2D<T> point4)
		{
			this->point1 = point1;
			this->point2 = point2;
			this->point3 = point3;
			this->point4 = point4;
		}
		Rectangle2D(T* point1, T* point2, T* point3, T* point4)
		{
			this->point1 = Point2D<T>(point1[0], point1[1]);
			this->point2 = Point2D<T>(point2[0], point2[1]);
			this->point3 = Point2D<T>(point3[0], point3[1]);
			this->point4 = Point2D<T>(point4[0], point4[1]);
		}

		T width() 
		{
			T width = point1.x - point2.x;

			if (width == 0)
				width = point1.x - point3.x;

			return T(abs(width));
		}

		T height()
		{
			T height = point1.y - point2.y;

			if (height == 0)
				height = point1.y - point3.y;

			return T(abs(height));
		}

		T area()
		{
			T area = width() * height();

			return area;
		}

		T perimeter()
		{
			T perimeter = 2 * width() + 2 * height();

			return perimeter;
		}

		T diagonalLength() 
		{
			T w = width();
			T h = height();

			T diagonal = sqrt(w * w + h * h);

			return diagonal;
		}

		///<summary>
		///Get the lines that makes the rectangle
		///</summary>
		Line2D<T>* getLines() 
		{
			Line2D<T>* lines = new Line2D<T>[4];
			lines[0] = Line2D<T>(point1, point2);
			lines[1] = Line2D<T>(point2, point3);
			lines[2] = Line2D<T>(point3, point4);
			lines[3] = Line2D<T>(point4, point1);

			return lines;
		}

		Colision2DStatus getSatusColision(Point2D<T> point)
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
	
		///<summary>
		///Chech the line has intersection with the rectangle
		///</summary>
		bool hasIntersection(Line2D<T> line)
		{
			Line2D<T> line1 = Line2D<T>(point1, point2);
			Line2D<T> line2 = Line2D<T>(point2, point3);
			Line2D<T> line3 = Line2D<T>(point3, point4);
			Line2D<T> line4 = Line2D<T>(point4, point1);

			Point2D<T>* point = line1.findIntersection(line);

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

		///<summary>
		///Chech the triangle has intersection with the rectangle
		///</summary>
		bool hasIntersection(Triangle2D<T> triangle)
		{
			Line2D<T>* linesOfRectangle = getLines();
			Line2D<T>* linesOfTriangle = triangle.getLines();

			for (size_t i = 0; i < 4; i++)
				for (size_t j = 0; j < 3; j++)
				{
					Line2D<T> line1 = linesOfRectangle[i];
					Line2D<T> line2 = linesOfTriangle[j];

					Point2D<T>* point = line1.findIntersection(line2);
					
					if (point != nullptr)
						return true;
				}

			return false;
		}

		///<summary>
		///Chech the circle has intersection with the rectangle
		///</summary>
		bool hasIntersection(Circle2D<T> circle)
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
	};

	typedef Rectangle2D<int> Rectangle2Di;
	typedef Rectangle2D<float> Rectangle2Df;
	typedef Rectangle2D<double> Rectangle2Dd;
}