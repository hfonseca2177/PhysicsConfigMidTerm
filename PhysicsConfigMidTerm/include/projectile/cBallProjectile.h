#pragma once
#include <physics/cParticle.h>

namespace projectile
{
	class cBallProjectile : public nPhysics::cParticle
	{
	public:
		cBallProjectile(float mass, const glm::vec3& position) : nPhysics::cParticle(mass, position) {};
		virtual void Integrate(float deltaTime);

	};
}
