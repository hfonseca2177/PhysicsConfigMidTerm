#pragma once
#include <physics/cParticle.h>

namespace projectile
{
	class cLaserProjectile : public nPhysics::cParticle
	{
 	public:
		cLaserProjectile(float mass, const glm::vec3& position) : nPhysics::cParticle(mass, position) {};
		virtual void Integrate(float deltaTime);
	};
}
