#ifndef PARTICLE
#define PARTICLE

#include "OpenML.h"

namespace OpenML
{

	class Particle
	{
	public:

		Vec3f position;
		Vec3f previousPosition;
		Vec3f velocity;
		Vec3f previousVelocity;
		Vec3f acceleration;
		Vec3f force;

		/// <summary>
		/// The inverse mass of the particle. Ex.: Mass=8.0, so IM=1/8.0f
		/// </summary>
		float inverseMass;

		/// <summary>
		/// Define how long the particle will be alive
		/// </summary>
		float lifeTime;

		/// <summary>
		/// Change the velocity over the time
		/// </summary>
		float velocityDamping;

		/// <summary>
		/// Define the material when it collides
		/// </summary>
		float coeficientOfRestitution;

		/// <summary>
		/// Create a particle with optional arguments
		/// </summary>
		API_INTERFACE Particle(const Vec3f& position = Vec3f(0.0f), const Vec3f& velocity = Vec3f(0.0f), const float inverseMass = 0.8f, const float velocityDamping = 1.0f, const float coeficientOfRestitution = 0.9f);

		/// <summary>
		/// Add a force/impulse to a particle
		/// Constant force are not covered in this force. Use ConstantForce on ParticleSystem
		/// </summary>
		API_INTERFACE void addForce(const Vec3f& force);

		/// <summary>
		/// Update the status of particle (integration method)
		/// </summary>
		API_INTERFACE void update(long long elapsedTime);

		/// <summary>
		/// Define the direction (normalized) where the particle is going to
		/// </summary>
		API_INTERFACE Vec3f direction();

		/// <summary>
		/// Relative/differential velocity
		/// </summary>
		API_INTERFACE Vec3f relativeVelocity(const Particle& particle);

		/// <summary>
		/// Closing/approximation velocity
		/// </summary>
		API_INTERFACE float closingVelocity(const Particle& particle);
	};

}

#endif // ! PARTICLE