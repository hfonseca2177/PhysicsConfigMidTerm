#pragma once
#include <physics/cParticle.h>
#include <projectile/cBaseProjectile.h>

namespace projectile
{
	class cEnergyProjectile : public projectile::cBaseProjectile, public nPhysics::cParticle
	{
	public:
		cEnergyProjectile(float mass, const glm::vec3& position) : nPhysics::cParticle(mass, position) {};
		virtual void Integrate(float deltaTime);
	};
}
