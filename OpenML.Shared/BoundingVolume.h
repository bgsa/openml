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

		API_INTERFACE virtual void translate(float xAxis, float yAxis, float zAxis) = 0;
		API_INTERFACE virtual void rotate(float angleInRadians, float xAxis, float yAxis, float zAxis) = 0;
		API_INTERFACE virtual void scale(float xAxis, float yAxis, float zAxis) = 0;

	};

}

#endif // !BOUNDING_VOLUME