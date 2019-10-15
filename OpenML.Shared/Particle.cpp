#include "Particle.h"

Particle::Particle(const Vec3f& position, const Vec3f& velocity, const float inverseMass)
{
	this->position = position;
	this->velocity = velocity;
	this->inverseMass = inverseMass;

	acceleration = Vec3f(0.0f);
	force = Vec3f(0.0f);
	lifeTime = FLT_MAX;
}

void Particle::addForce(const Vec3f& force) 
{
	this->force.add(force);
}

void Particle::update(long long elapsedTime) 
{
	assert(elapsedTime > 0);

	Vec3f newAcceleration = force * inverseMass;

	Vec3f newVelocity = velocity + velocity + ((newAcceleration - acceleration) / elapsedTime);

	Vec3f newPosition = position + ((velocity + newVelocity - velocity) / elapsedTime);

	acceleration = newAcceleration;
	velocity = newVelocity;
	position = newPosition;

	force = 0.0f;
}