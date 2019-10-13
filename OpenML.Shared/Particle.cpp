#include "Particle.h"

Particle::Particle(const Vec3f& position, const Vec3f& velocity, const float inverseMass)
{
	this->position = position;
	this->velocity = velocity;
	this->inverseMass = inverseMass;

	aceleration = Vec3f(0);
	force = Vec3f(0);
	lifeTime = FLT_MAX;
}

void Particle::addForce(const Vec3f& force) 
{
	this->force.add(force);
}

void Particle::update(long long elapsedTime) 
{
	assert(elapsedTime > 0);

	Vec3f newAceleration = force * inverseMass;

	Vec3f newVelocity = velocity + velocity + ((newAceleration - aceleration) / elapsedTime);

	Vec3f newPosition = position + ((velocity + newVelocity - velocity) / elapsedTime);

	aceleration = newAceleration;
	velocity = newVelocity;
	position = newPosition;

	force = 0.0f;
}