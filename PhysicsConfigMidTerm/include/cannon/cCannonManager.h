#pragma once
#include <physics/cParticle.h>
#include <config/sConfiguration.h>
#include <graphics/cGraphicsComponent.h>

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
		config::sProjectilePreset GetPreset(eProjectileType& projectileType);
	public:
		cCannonManager(config::sCannonConfiguration cannonConfig, config::sProjectileConfiguration projectileConfig);
		virtual ~cCannonManager();
		
		void ShootBullet(glm::mat3& axes, nPhysics::cParticle* particle);
		void ShootLaser(glm::mat3& axes, nPhysics::cParticle* particle);
		void ShootBall(glm::mat3& axes, nPhysics::cParticle* particle);
		void ShootEnergy(glm::mat3& axes, nPhysics::cParticle* particle);
		void SetProjectileType(eProjectileType  type);
		nPhysics::cParticle* SpawnProjectile();
		virtual bool ReachedTimeout(float& timeElapsed, nPhysics::cParticle* particle);
		virtual bool ReachedDistanceLimit(glm::vec3& initialPosition, glm::vec3& currentPosition, nPhysics::cParticle* particle);
		virtual void ApplyVisual(nGraphics::cGraphicsComponent* graphic);

	};
}