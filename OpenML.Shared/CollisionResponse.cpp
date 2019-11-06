#include "CollisionResponse.h"


CollisionResponse::CollisionResponse() 
{
	;
}

CollisionResponse::CollisionResponse(const Vec3f& contactPoint)
{
	this->contactPoint = contactPoint;
}

void CollisionResponse::separeteSpheres(Sphere* sphere1, Sphere* sphere2)
{
	float factor = ((sphere1->ray + sphere2->ray) - sphere2->center.distance(sphere1->center)) * 0.5f;
	
	sphere1->center += sphere1->particleSystem->particles[0].direction() * -factor;
	sphere2->center += sphere2->particleSystem->particles[0].direction() * -factor;

	sphere1->particleSystem->particles[0].position = sphere1->center;
	sphere2->particleSystem->particles[0].position = sphere2->center;
}

CollisionResponse* CollisionResponse::handle(Sphere* sphere1, Sphere* sphere2)
{
	Particle particle1 = sphere1->particleSystem->particles[0];
	Particle particle2 = sphere2->particleSystem->particles[0];

	Vec3f movingTo1 = particle1.direction();
	Vec3f movingTo2 = particle2.direction();

	bool isGoingToCollide = movingTo1.dot(movingTo2) <= 0.0f;

	if (!isGoingToCollide)
		return NULL;
	
	CollisionResponse::separeteSpheres(sphere1, sphere2);
	
	Vec3f contactPoint = particle1.position + ((particle2.position - particle1.position) * 0.5f);
	
	Vec3f normalContact = (particle1.position - particle2.position).normalize();

	Vec3f relativeVelocity = particle1.relativeVelocity(particle2);

	float velocityNormal = relativeVelocity.dot(normalContact);

	if (velocityNormal > 0.0f)  // the spheres are getting away from each other
		return nullptr;

	CollisionResponse* response = ALLOC_NEW(CollisionResponse)(contactPoint);


	float denominator = (normalContact.dot(normalContact)) * (particle1.inverseMass + particle2.inverseMass);

	float j = (-(1.0f + particle1.coeficientOfRestitution) * (relativeVelocity.dot(normalContact))) / denominator;

	response->object1Impulse = (j * normalContact) * particle1.inverseMass;
	response->object2Impulse = -((j * normalContact) * particle2.inverseMass);

	return response;
}