#pragma once

#include "CppUnitTest.h"
#include "TestHeader.h"
#include <Particle.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(ParticleTest)
	{
	public:

		TEST_METHOD(Particle_constructor_empty)
		{
			Particle particle = Particle();

			Assert::AreEqual(Vec3f(0), particle.position, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(Vec3f(0), particle.velocity, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(Vec3f(0), particle.acceleration, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(Vec3f(0), particle.force, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(0.8f, particle.inverseMass, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Particle_constructor_withParameters)
		{
			Particle particle = Particle(Vec3f(1), Vec3f(2), 2.5f);

			Assert::AreEqual(Vec3f(1), particle.position, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(Vec3f(2), particle.velocity, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(Vec3f(0), particle.acceleration, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(Vec3f(0), particle.force, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(2.5f, particle.inverseMass, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Particle_addForce)
		{
			Particle particle = Particle();

			Vec3f newForce = Vec3f(1.0f, 2.0f, 3.0f);

			particle.addForce(newForce);

			Assert::AreEqual(newForce, particle.force, L"Wrong value.", LINE_INFO());

			particle.addForce(newForce);

			Assert::AreEqual(Vec3f(2.0f, 4.0f, 6.0f), particle.force, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Particle_update)
		{
			Particle particle = Particle(0.0f, 0.0f, 0.8f);

			particle.addForce(Vec3f(0.0f, 2.0f, 0.0f));

			particle.update(33);
			
			Assert::AreEqual(Vec3f(0.0f, 1.6f, 0.0f), particle.acceleration, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(Vec3f(0.0f, 0.0484848507f, 0.0f), particle.velocity, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(Vec3f(0.0f, 0.00146923785f, 0.0f), particle.position, L"Wrong value.", LINE_INFO());
			Assert::AreEqual(Vec3f(0.0f, 0.0f, 0.0f), particle.previousPosition, L"Wrong value.", LINE_INFO());
			
			Assert::AreEqual(Vec3f(0), particle.force, L"Wrong value.", LINE_INFO());
		}
		
	};
}