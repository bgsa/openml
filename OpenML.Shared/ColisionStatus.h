#pragma once

namespace OpenML
{
	enum class ColisionStatus
	{
		OUTSIDE = -1,
		INLINE = 0,
		INSIDE = 1
	};

	template <typename T>
	class DetailedColisionStatus 
	{
	public:

		DetailedColisionStatus(ColisionStatus status) 
		{
			this->status = status;
		}

		DetailedColisionStatus(ColisionStatus status, Vec3<T> point1)
		{
			this->status = status;

			points = new Vec3<T>[1];
			points[0] = point1;

			pointsCount = 1;
		}

		DetailedColisionStatus(ColisionStatus status, Vec3<T> point1, Vec3<T> point2)
		{
			this->status = status;

			points = new Vec3<T>[2];
			points[0] = point1;
			points[1] = point2;

			pointsCount = 2;
		}

		DetailedColisionStatus(ColisionStatus status, Vec3<T>* points, int pointsCount)
		{
			this->status = status;
			this->points = points;
			this->pointsCount = pointsCount;
		}

		ColisionStatus status;
		Vec3<T>* points = nullptr;
		int pointsCount = 0;
	};
}