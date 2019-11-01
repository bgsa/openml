#ifndef BOUNDING_VOLUME
#define BOUNDING_VOLUME

#include "OpenML.h"
#include "Vec3.h"
#include "ParticleSystem.h"

namespace OpenML
{

	class BoundingVolume
	{
	public:

		ParticleSystem* particleSystem = NULL;
		
		API_INTERFACE virtual Vec3f centerOfBoundingVolume()
		{
			return Vec3f(0.0f);
		};

	};

}

#endif // !BOUNDING_VOLUME