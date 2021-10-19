#include <cannon/cCannonManager.h>
#include <physics/random_helpers.h>
#include <projectile/cBulletProjectile.h>
#include <projectile/cLaserProjectile.h>
#include <projectile/cBallProjectile.h>
#include <projectile/cEnergyProjectile.h>

#include <iostream>

cannon::cCannonManager::cCannonManager(config::sCannonConfiguration cannonConfig, config::sProjectileConfiguration projectileConfig)
{
	this->cannonConfig = cannonConfig;
	this->projectileConfig = projectileConfig;
}

cannon::cCannonManager::~cCannonManager()
{
}

void cannon::cCannonManager::Shoot(nPhysics::cParticle* particle)
{
	glm::vec3 position(0.0, 1.0, 0.0);
	particle->SetPosition(position);
	particle->SetVelocity(dynamic_cast<projectile::cBaseProjectile*>(particle)->GetPreset().muzzleVelocity);
	particle->SetDamping(dynamic_cast<projectile::cBaseProjectile*>(particle)->GetPreset().damping);
}

void cannon::cCannonManager::ShootBullet(glm::mat3& axes, nPhysics::cParticle* particle)
{
	axes = nPhysics::getRandomOrthonormalBasis();
	//start UP in the air
	glm::vec3 position(0.0, 1.0, 0.0);
	glm::vec3 velocity = (axes[0] * nPhysics::getRandom(-2.f, 2.f)) + (axes[1] * 5.f) + (axes[2] * nPhysics::getRandom(-2.f, 2.f));
	velocity = glm::normalize(velocity);
	//Relatively slow 
	velocity *= 20.f;
	particle->SetPosition(position);
	particle->SetVelocity(velocity);
	//Apply some razonable Damping
	particle->SetDamping(nPhysics::getRandom(5.0f, 10.0f));

}

void  cannon::cCannonManager::ShootLaser(glm::mat3& axes, nPhysics::cParticle* particle)
{
	axes = nPhysics::getRandomOrthonormalBasis();
	glm::vec3 position(1.0, 1.1f, 1.0);
	glm::vec3 velocity = (axes[0] * nPhysics::getRandom(-1.f, 5.f)) + (axes[1] * 5.f) + (axes[2] * nPhysics::getRandom(-2.f, 5.f));
	velocity = glm::normalize(velocity);
	//increased velocity
	velocity *= 30.f;
	//vertically launched
	velocity.x = 0;
	particle->SetPosition(position);
	particle->SetVelocity(velocity);
}

void  cannon::cCannonManager::ShootBall(glm::mat3& axes, nPhysics::cParticle* particle)
{
	axes = nPhysics::getRandomOrthonormalBasis();

	glm::vec3 position(0.0, 1.1f, 0.0);
	glm::vec3 velocity = (axes[0] * nPhysics::getRandom(-2.f, 2.f)) + (axes[1] * 5.f) + (axes[2] * nPhysics::getRandom(-2.f, 2.f));
	velocity = glm::normalize(velocity);
	velocity *= 40.f;
	particle->SetPosition(position);
	particle->SetVelocity(velocity);
	//Random accelarion causing shuffling
	glm::vec3 randomVel = nPhysics::getRandomVec3(10.0f);
	particle->SetAcceleration(randomVel);
}

void  cannon::cCannonManager::ShootEnergy(glm::mat3& axes, nPhysics::cParticle* particle)
{
	axes = nPhysics::getRandomOrthonormalBasis();

	glm::vec3 position(0.0, 1.1f, 0.0);
	glm::vec3 velocity = (axes[0] * nPhysics::getRandom(-2.f, 2.f)) + (axes[1] * 5.f) + (axes[2] * nPhysics::getRandom(-2.f, 2.f));
	velocity = glm::normalize(velocity);
	velocity *= 40.f;
	particle->SetPosition(position);
	particle->SetVelocity(velocity);
	//Random accelarion causing shuffling
	glm::vec3 randomVel = nPhysics::getRandomVec3(10.0f);
	particle->SetAcceleration(randomVel);
}

void cannon::cCannonManager::SetProjectileType(cannon::eProjectileType type)
{
	this->projectileType = type;
}

nPhysics::cParticle* cannon::cCannonManager::SpawnProjectile()
{
	switch (this->projectileType)
	{
	case ENERGY:
	{
		std::cout << "INSTANCE ENERGY BALL" << std::endl;
		nPhysics::cParticle* particle = new projectile::cEnergyProjectile(this->projectileConfig.energyBallPreset.mass, glm::vec3(0.f));
		dynamic_cast<projectile::cBaseProjectile*>(particle)->SetPreset(this->projectileConfig.energyBallPreset);
		return particle;
		break;
	}
	case LASER:
	{
		std::cout << "INSTANCE LASER" << std::endl;
		nPhysics::cParticle* particle = new projectile::cLaserProjectile(this->projectileConfig.laserPreset.mass, glm::vec3(0.f));
		dynamic_cast<projectile::cBaseProjectile*>(particle)->SetPreset(this->projectileConfig.laserPreset);
		return particle;
		break;
	}
	case BALL:
	{
		std::cout << "INSTANCE CANNON BALL" << std::endl;
		nPhysics::cParticle* particle = new projectile::cBallProjectile(this->projectileConfig.cannonBallPreset.mass, glm::vec3(0.f));
		dynamic_cast<projectile::cBaseProjectile*>(particle)->SetPreset(this->projectileConfig.cannonBallPreset);
		return particle;
		break;
	}
	default:
		std::cout << "INSTANCE BULLET" << std::endl;
		nPhysics::cParticle* particle = new projectile::cBulletProjectile(this->projectileConfig.bulletPreset.mass, glm::vec3(0.f));
		dynamic_cast<projectile::cBaseProjectile*>(particle)->SetPreset(this->projectileConfig.bulletPreset);
		return particle;
		break;
	}

}