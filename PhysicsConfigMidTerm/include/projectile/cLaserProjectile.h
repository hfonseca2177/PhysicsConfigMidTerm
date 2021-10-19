#pragma once
#include <physics/cParticle.h>
#include <projectile/cBaseProjectile.h>


namespace projectile
{
	class cLaserProjectile : public projectile::cBaseProjectile, public nPhysics::cParticle
	{
 	public:
		cLaserProjectile(float mass, const glm::vec3& position) : nPhysics::cParticle(mass, position) {};
		virtual void Integrate(float deltaTime);
	};
}
