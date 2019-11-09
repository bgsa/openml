#include "Particle.h"

Particle::Particle(const Vec3f& position, const Vec3f& velocity, const float inverseMass, const float velocityDamping, float coeficientOfRestitution)
{
	this->position = position;
	this->previousPosition = position;
	this->velocity = velocity;
	this->previousVelocity = velocity;
	this->inverseMass = inverseMass;
	this->velocityDamping = velocityDamping;
	this->coeficientOfRestitution = coeficientOfRestitution;

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

	Vec3f newVelocity = (velocity * velocityDamping) + ((newAcceleration - acceleration) / elapsedTime);

	Vec3f newPosition = position + (newVelocity / elapsedTime);

	acceleration = newAcceleration;

	previousVelocity = velocity;
	velocity = newVelocity;

	previousPosition = position;
	position = newPosition;

	force = 0.0f;
}

Vec3f Particle::direction() 
{
	return (position - previousPosition).normalize();
}

Vec3f Particle::relativeVelocity(const Particle& particle)
{
	return this->velocity - particle.velocity;
}

float Particle::closingVelocity(const Particle& particle)
{
	Vec3f direction = this->position - particle.position;

	return direction.dot(direction.normalize());
}