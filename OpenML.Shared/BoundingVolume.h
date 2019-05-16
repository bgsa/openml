#pragma once

#include "Vec3.h"

namespace OpenML
{

	template <typename T>
	class BoundingVolume
	{
	public:
		
		API_INTERFACE virtual Vec3<T> centerOfBoundingVolume() const
		{
			return Vec3<T>();
		};

	};

}