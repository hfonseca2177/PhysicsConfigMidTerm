#include <projectile/cBulletProjectile.h>
#include <iostream>
#include <physics/random_helpers.h>


void projectile::cBulletProjectile::Integrate(float deltaTime)
{
	//int  y = static_cast<int>(GetPosition().y);

	////stage 1
	//if (y > 10)
	//{
	//	if (y % 2 == 0)
	//	{
	//		std::cout << "STAGE 1" << std::endl;
	//		glm::vec3 newPos(GetPosition());
	//		newPos.z += nPhysics::getRandom();
	//		SetPosition(newPos);
	//	}
	//}
	////stage 2
	//else {
	//	std::cout << "STAGE 2" << std::endl;
	//	SetDamping(8.5);
	//	glm::vec3 randomAcc = nPhysics::getRandomVec3(5.0f);
	//	SetAcceleration(randomAcc);
	//}
	cParticle::Integrate(deltaTime);
}
