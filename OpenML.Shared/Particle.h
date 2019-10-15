#ifndef PARTICLE
#define PARTICLE

#include "OpenML.h"

namespace OpenML
{

	class Particle
	{
	public:

		Vec3f position;
		Vec3f velocity;
		Vec3f acceleration;
		Vec3f force;
		float inverseMass;
		float lifeTime;

		Particle(const Vec3f& position = Vec3f(0.0f), const Vec3f& velocity = Vec3f(0.0f), const float inverseMass = 0.8f);

		API_INTERFACE void addForce(const Vec3f& force);

		API_INTERFACE void update(long long elapsedTime);
	};

}

#endif // ! PARTICLE