#include "BoundingVolume.h"

template <typename T>
Vec3f BoundingVolume<T>::centerOfBoundingVolume()
{
	return Vec3f(0.0f);
}

namespace OpenML
{
	template class BoundingVolume<Sphere>;
	template class BoundingVolume<AABB>;
	template class BoundingVolume<OBB>;
	template class BoundingVolume<DOP18>;
}
