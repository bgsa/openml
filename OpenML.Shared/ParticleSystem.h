#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#include "OpenML.h"
#include "Particle.h"
#include <vector>

namespace OpenML
{

	class ParticleSystem
	{
	private:
		std::vector<Vec3f> constantForces;

	public:
		Particle* particles;
		size_t particlesCount;

		API_INTERFACE ParticleSystem(size_t particlesCount);
		API_INTERFACE ParticleSystem(Particle* particles, size_t particlesCount);

		API_INTERFACE void addForce(const Vec3f& force);

		API_INTERFACE size_t addConstantForce(const Vec3f& constantForce);

		API_INTERFACE void update(long long elapsedTime);
	};

}

#endif // ! PARTICLE_SYSTEM