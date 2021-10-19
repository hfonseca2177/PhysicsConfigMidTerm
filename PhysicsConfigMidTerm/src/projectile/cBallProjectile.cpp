#include <projectile/cBallProjectile.h>
#include <iostream>
#include <physics/random_helpers.h>


void projectile::cBallProjectile::Integrate(float deltaTime)
{

	//stage 1
	if (GetPosition().y > 40)
	{
		std::cout << "STAGE 1" << std::endl;
		glm::vec3 newVel(GetVelocity());
		newVel.x *= nPhysics::getRandom(-2.0, 4.0f);
		SetVelocity(newVel);
	}
	//stage 2
	else if (GetPosition().y < 15) {
		std::cout << "STAGE 2" << std::endl;
		glm::vec3 newPos(GetPosition());
		newPos.z *= -1;
		SetPosition(newPos);
	}
	cParticle::Integrate(deltaTime);
}
