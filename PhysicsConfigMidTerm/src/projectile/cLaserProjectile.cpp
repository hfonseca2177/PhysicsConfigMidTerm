#include <projectile/cLaserProjectile.h>
#include <iostream>
#include <physics/random_helpers.h>


void projectile::cLaserProjectile::Integrate(float deltaTime)
{
	////stage 1
	//if (GetPosition().y > 20)
	//{
	//	std::cout << "STAGE 1" << std::endl;
	//	glm::vec3 newPos(GetPosition());
	//	newPos.x *= -1;
	//	SetPosition(newPos);
	//}
	////stage 2
	//else if (GetPosition().y < 8) {
	//	std::cout << "STAGE 2" << std::endl;
	//	SetAcceleration(nPhysics::getRandomVec3(5.0f));
	//}
	cParticle::Integrate(deltaTime);
}
