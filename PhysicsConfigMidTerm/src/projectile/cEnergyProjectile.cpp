#include <projectile/cEnergyProjectile.h>
#include <iostream>
#include <physics/random_helpers.h>


void projectile::cEnergyProjectile::Integrate(float deltaTime)
{
	
	if (GetPosition().y < 14) {
		std::cout << "STAGE 2" << std::endl;
		SetAcceleration(nPhysics::getRandomVec3(5.0f));
	}
	cParticle::Integrate(deltaTime);
}
