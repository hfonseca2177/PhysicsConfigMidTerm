#pragma once
#include <physics/cParticle.h>

namespace projectile
{
	class cEnergyProjectile : public nPhysics::cParticle
	{
	public:
		cEnergyProjectile(float mass, const glm::vec3& position) : nPhysics::cParticle(mass, position) {};
		virtual void Integrate(float deltaTime);
	};
}
