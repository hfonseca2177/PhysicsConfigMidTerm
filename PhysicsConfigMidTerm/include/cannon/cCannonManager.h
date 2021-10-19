#pragma once
#include <physics/cParticle.h>
#include <config/sConfiguration.h>

namespace cannon
{
	enum eProjectileType
	{
		BULLET, LASER, BALL, ENERGY
	};
	//Manage Cannon and projectiles shooting
	class cCannonManager
	{
	private:
		eProjectileType projectileType = BULLET;
		config::sCannonConfiguration cannonConfig;
		config::sProjectileConfiguration projectileConfig;
	public:
		cCannonManager(config::sCannonConfiguration cannonConfig, config::sProjectileConfiguration projectileConfig);
		virtual ~cCannonManager();
		void Shoot(nPhysics::cParticle* particle);
		void ShootBullet(glm::mat3& axes, nPhysics::cParticle* particle);
		void ShootLaser(glm::mat3& axes, nPhysics::cParticle* particle);
		void ShootBall(glm::mat3& axes, nPhysics::cParticle* particle);
		void ShootEnergy(glm::mat3& axes, nPhysics::cParticle* particle);
		void SetProjectileType(eProjectileType  type);
		nPhysics::cParticle* SpawnProjectile();

	};
}