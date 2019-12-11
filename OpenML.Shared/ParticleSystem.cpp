#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(size_t particlesCount)
{
	assert(particlesCount > 0);

	this->particles = ALLOC_NEW_ARRAY(Particle, particlesCount);
	this->particlesCount = particlesCount;
	this->orientation = Mat3f::identity();
	this->angularVelocity = Vec3f(0.0f);
}

ParticleSystem::ParticleSystem(Particle* particles, size_t particlesCount)
{
	assert(particlesCount > 0);

	this->particles = particles;
	this->particlesCount = particlesCount;
}

void ParticleSystem::addForce(const Vec3f& force)
{
	for (size_t i = 0; i < particlesCount; i++)
		this->particles[i].addForce(force);
}

size_t ParticleSystem::addConstantForce(const Vec3f& constantForce)
{
	constantForces.push_back(constantForce);

	return constantForces.size() - 1;
}

void ParticleSystem::update(long long elapsedTime)
{
	for (size_t i = 0; i < particlesCount; i++)
	{
		for (std::vector<Vec3f>::iterator contantForce = constantForces.begin(); contantForce != constantForces.end(); ++contantForce)
			this->particles[i].addForce(*contantForce);

		this->particles[i].update(elapsedTime);
	}
}