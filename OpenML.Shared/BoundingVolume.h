#ifndef BOUNDING_VOLUME
#define BOUNDING_VOLUME

#include "OpenML.h"
#include "Vec3.h"
#include "ParticleSystem.h"

namespace OpenML
{

	template <typename T>
	class BoundingVolume
	{
	public:

		ParticleSystem* particleSystem = NULL;
		
		API_INTERFACE virtual Vec3f centerOfBoundingVolume();

		API_INTERFACE virtual T* translate(float xAxis, float yAxis, float zAxis) = 0;
		API_INTERFACE virtual T* rotate(float angleInRadians, float xAxis, float yAxis, float zAxis) = 0;
		API_INTERFACE virtual T* scale(float xAxis, float yAxis, float zAxis) = 0;

		API_INTERFACE virtual Mat3f modelView() = 0;

	};

	typedef BoundingVolume<Sphere> BoundingVolumeSphere;
	typedef BoundingVolume<AABB> BoundingVolumeAABB;
	typedef BoundingVolume<OBB> BoundingVolumeOBB;

}

#endif // !BOUNDING_VOLUME