#pragma once

#include "Point2D.h"
#include "Mat4.h"

namespace OpenML
{
	template <typename T>
	class Circle2D 
	{
	public:
		T ray;
		Point2D<T> center;

		Circle2D() { }
		Circle2D(Point2D<T> center, T ray) 
		{
			this->center = center;
			this->ray = ray;
		}
		Circle2D(Point2D<T> point1, Point2D<T> point2, Point2D<T> point3)
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
			this->ray = sqrt(numerator / denominator);
		}

		T area() {
			return T(PI * ray * ray);
		}

		T circumference() {
			return T(2 * PI * ray);
		}

		T* calculatePoints(size_t& pointsCount)
		{
			const size_t vertexCount = 126;
			pointsCount = vertexCount / 2;

			T* points = new T[vertexCount];
			size_t index = 0;

			for (float angle = 0.0; angle < TWO_PI; angle += 0.1f)
			{
				points[index + 0] = ray * cosf(angle) + center.x;
				points[index + 1] = ray * sinf(angle) + center.y;

				index += 2;
			}

			return points;
		}

		T getDistance(Point2D<T> point) 
		{
			T distance = center.getDistance(point);
			return distance;
		}

		Colision2DStatus getColisionStatus(Point2D<T> point)
		{
			float distance = ceil(point.toVec2().distance(center.toVec2()));
			float rayDistance = ceil(ray);

			if (distance > rayDistance)
				return OpenML::Colision2DStatus::OUTSIDE;

			if (distance < rayDistance)
				return OpenML::Colision2DStatus::INSIDE;

			return OpenML::Colision2DStatus::INLINE;
		}

		bool hasIntersection(Circle2D<T> circle2) 
		{
			T distance = center.toVec2().distance(circle2.center.toVec2());

			bool intersectionFound = ray + circle2.ray >= distance;

			return intersectionFound;
		}

		Point2D<T>* findIntersection(Circle2D<T> circle2)
		{
			Vec2<T> point1AsVector = center.toVec2();
			Vec2<T> point2AsVector = circle2.center.toVec2();

			T distance = point1AsVector.distance(point2AsVector);

			bool intersectionFound = ray + circle2.ray >= distance;

			if (!intersectionFound)
				return nullptr;
									
			float a, h;
			
			a = (ray*ray - circle2.ray*circle2.ray + distance * distance) / (2 * distance);
			h = sqrt(ray*ray - a*a);

			Vec2<T> p3 = ((point2AsVector - point1AsVector) * (a / distance)) + center.toVec2();

			float x3, y3, x4, y4;
			x3 = p3[0] + h*(circle2.center.y - center.y) / distance;
			y3 = p3[1] - h*(circle2.center.x - center.x) / distance;

			Point2D<T>* result;

			if (ray + circle2.ray == distance)   //has only one point
			{
				result = new Point2D<T>[1];
				result[0] = Point2D<T>(x3, y3);

				return result;
			}
			else 
			{
				x4 = p3[0] - h*(circle2.center.y - center.y) / distance;
				y4 = p3[1] + h*(circle2.center.x - center.x) / distance;

				result = new Point2D<T>[2];
				result[0] = Point2D<T>(x3, y3);
				result[1] = Point2D<T>(x4, y4);
			}

			return result;
		}

	};

	typedef Circle2D<int> Circle2Di;
	typedef Circle2D<float> Circle2Df;
	typedef Circle2D<double> Circle2Dd;
}