#include "Line2D.h"

template <typename T>
Line2D<T>::Line2D() {
};

template <typename T>
Line2D<T>::Line2D(const Vec2<T>& point1, const Vec2<T>& point2)
{
	assert(point1 != point2);

	this->point1 = point1;
	this->point2 = point2;
}

template <typename T>
Line2D<T>::Line2D(T* point1, T* point2)
{
	assert(point1 != point2);

	this->point1 = Vec2<T>(point1[0], point1[1]);
	this->point2 = Vec2<T>(point2[0], point2[1]);
}

template <typename T>
T Line2D<T>::angle() const
{
	T deltaY = point2.y() - point1.y();
	T deltaX = point2.x() - point1.x();

	T angle = T(atan(deltaY / deltaX));
	return angle;
}

template <typename T>
T Line2D<T>::slope() const
{
	T deltaY = point2.y() - point1.y();
	T deltaX = point2.x() - point1.x();

	T slope = T(deltaY / deltaX);

	return slope;
}

template <typename T>
Vec2<T> Line2D<T>::getParametricEquation() const
{
	T m = slope();
	T b = -(m * point1.x()) + point1.y();

	return Vec2<T>(m, b);
}

template <typename T>
Vec3<T> Line2D<T>::getEquation() const
{
	Vec3<T> values = SystemOfLinearEquations<T>::getLineEquation(point1, point2);

	return values;
}

template <typename T>
Vec2<T> Line2D<T>::toRay()
{
	Vec2<T> result = (point2 - point1);

	result = result.normalize();

	return result;
}

template <typename T>
bool Line2D<T>::isOnTheLine(const Vec2<T>& point) const
{
	Orientation orientation = getOrientation(point);

	if (orientation != Orientation::NONE)
		return false;

	// check the range of the line x point
	T point1PosX = point1.x() > point2.x() ? point2.x() : point1.x();
	T point2PosX = point1PosX + deltaX();

	T point1PosY = point1.y() > point2.y() ? point2.y() : point1.y();
	T point2PosY = point1PosY + deltaY();

	if (point.x() < point1PosX || point.x() > point2PosX
		|| point.y() < point1PosY || point.y() > point2PosY)
		return false;

	return true;
}

template <typename T>
bool Line2D<T>::isOnTheLeft(const Vec2<T>& point) const {
	Orientation orientation = getOrientation(point);
	return orientation == Orientation::LEFT;
}

template <typename T>
bool Line2D<T>::isOnTheRight(const Vec2<T>& point) const {
	Orientation orientation = getOrientation(point);
	return orientation == Orientation::RIGHT;
}

template <typename T>
Orientation Line2D<T>::getOrientation(const Vec2<T>& point) const
{
	Mat3<T> lineMatrix = {
		T(1), T(1), T(1),
		point1.x(), point2.x(), point.x(),
		point1.y(), point2.y(), point.y()
	};

	int determinant = (int)lineMatrix.determinant();

	if (determinant == 0)
		return Orientation::NONE;
	if (determinant > 0)
		return Orientation::LEFT;
	else
		return Orientation::RIGHT;
}

template <typename T>
T Line2D<T>::getDistance(Vec2<T> point) const
{
	Vec3<T> values = getEquation();

	double numerador = fabs(values[0] * point.x() + values[1] * point.y() + values[2]);
	double denominador = sqrt(values[0] * values[0] + values[1] * values[1]);

	double distanceFromPointToLine = numerador / denominador;

	return T(distanceFromPointToLine);
}

template <typename T>
Vec2<T>* Line2D<T>::findIntersection(const Line2D<T>& otherLine) const
{
	Vec2<T> line2Point1 = otherLine.point1;
	Vec2<T> line2Point2 = otherLine.point2;

	T determinant = (line2Point2.x() - line2Point1.x()) * (point2.y() - point1.y()) - (line2Point2.y() - line2Point1.y()) * (point2.x() - point1.x());

	if (determinant == 0.0)
		return nullptr; // intersection not found

	double s = ((line2Point2.x() - line2Point1.x()) * (line2Point1.y() - point1.y()) - (line2Point2.y() - line2Point1.y()) * (line2Point1.x() - point1.x())) / determinant;
	//double t = ((point2.x - point1.x) * (line2Point1.y - point1.y) - (point2.y - point1.y) * (line2Point1.x - point1.x)) / determinant;

	Vec2<T>* intersection = new Vec2<T>(
		point1.x() + (point2.x() - point1.x())* T(s),
		point1.y() + (point2.y() - point1.y())* T(s)
		);

	if (!isOnTheLine(*intersection))
		return nullptr;  // intersection not found on this line

	if (!otherLine.isOnTheLine(*intersection))
		return nullptr;  // intersection not found on this line

	return intersection;
}

template <typename T>
Colision2DStatus Line2D<T>::hasIntersections(const Circle2D<T>& circle) const
{
	double distanceCenterToLine = ceil(getDistance(circle.center));
	double ray = ceil(circle.ray);

	if (distanceCenterToLine > ray)
		return Colision2DStatus::OUTSIDE;

	if (distanceCenterToLine < ray)
		return Colision2DStatus::INSIDE;

	return Colision2DStatus::INLINE;
}

template <typename T>
T Line2D<T>::deltaX() const
{
	return abs(point1.x() - point2.x());
}

template <typename T>
T Line2D<T>::deltaY() const
{
	return abs(point1.y() - point2.y());
}


namespace OpenML
{
	template class Line2D<int>;
	template class Line2D<float>;
	template class Line2D<double>;
}