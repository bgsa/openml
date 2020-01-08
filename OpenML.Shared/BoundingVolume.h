#ifndef BOUNDING_VOLUME_HEADER
#define BOUNDING_VOLUME_HEADER

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
		
		API_INTERFACE virtual Vec3f centerOfBoundingVolume() const = 0;

		API_INTERFACE virtual T* translate(float xAxis, float yAxis, float zAxis) = 0;
		API_INTERFACE virtual T* rotate(float angleInRadians, float xAxis, float yAxis, float zAxis) = 0;
		API_INTERFACE virtual T* scale(float xAxis, float yAxis, float zAxis) = 0;

		API_INTERFACE virtual Mat3f modelView() = 0;

	};

	typedef BoundingVolume<Sphere> BoundingVolumeSphere;
	typedef BoundingVolume<AABB> BoundingVolumeAABB;
	typedef BoundingVolume<OBB> BoundingVolumeOBB;
	typedef BoundingVolume<DOP18> BoundingVolumeDOP18;

}

#endif // !BOUNDING_VOLUME_HEADER