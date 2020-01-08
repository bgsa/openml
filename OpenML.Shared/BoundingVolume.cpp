#include "BoundingVolume.h"

namespace OpenML
{
	template class BoundingVolume<Sphere>;
	template class BoundingVolume<AABB>;
	template class BoundingVolume<OBB>;
	template class BoundingVolume<DOP18>;
}
