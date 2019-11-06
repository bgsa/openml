#ifndef COLLISION_RESPONSE
#define COLLISION_RESPONSE

#include "OpenML.h"
#include "Sphere.h"

namespace OpenML
{

	class CollisionResponse
	{
	private:
		CollisionResponse(const Vec3f& contactPoint);

	public:
		Vec3f object1Force;
		Vec3f object2Force;
		Vec3f contactPoint;

		CollisionResponse();

		API_INTERFACE static CollisionResponse* handle(Sphere* sphere1, Sphere* sphere2);

		API_INTERFACE static void separeteSpheres(Sphere* sphere1, Sphere* sphere2);

	};

}

#endif COLLISION_RESPONSE