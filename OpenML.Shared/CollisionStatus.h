#pragma once

namespace OpenML
{
	enum class CollisionStatus
	{
		OUTSIDE = -1,
		INLINE = 0,
		INSIDE = 1
	};

	template <typename T>
	class DetailedCollisionStatus 
	{
	public:

		DetailedCollisionStatus(CollisionStatus status) 
		{
			this->status = status;
		}

		DetailedCollisionStatus(CollisionStatus status, Vec3<T> point1)
		{
			this->status = status;

			points = ALLOC_ARRAY(Vec3<T>,1);
			points[0] = point1;

			pointsCount = 1;
		}

		DetailedCollisionStatus(CollisionStatus status, Vec3<T> point1, Vec3<T> point2)
		{
			this->status = status;

			points = ALLOC_ARRAY(Vec3<T>,2);
			points[0] = point1;
			points[1] = point2;

			pointsCount = 2;
		}

		DetailedCollisionStatus(CollisionStatus status, Vec3<T>* points, int pointsCount)
		{
			this->status = status;
			this->points = points;
			this->pointsCount = pointsCount;
		}

		CollisionStatus status;
		Vec3<T>* points = nullptr;
		int pointsCount = 0;
	};
}