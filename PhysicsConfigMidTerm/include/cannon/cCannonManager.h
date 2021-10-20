#pragma once
#include <physics/cParticle.h>
#include <config/sConfiguration.h>
#include <graphics/cGraphicsComponent.h>

namespace cannon
{
	//projetile types
	enum eProjectileType
	{
		BULLET, LASER, BALL, ENERGY
	};
	//Manage Cannon and projectiles shooting
	class cCannonManager
	{
	private:
		eProjectileType projectileType = BULLET;
		//cannon configuration
		config::sCannonConfiguration cannonConfig;
		//projectile configuration
		config::sProjectileConfiguration projectileConfig;
		//return the respective projectile config preset
		config::sProjectilePreset GetPreset(eProjectileType& projectileType);
	public:
		cCannonManager(config::sCannonConfiguration cannonConfig, config::sProjectileConfiguration projectileConfig);
		virtual ~cCannonManager();
		//Methods to fire the projectiles
		void ShootBullet(glm::mat3& axes, nPhysics::cParticle* particle, glm::vec4& cannonVector);
		void ShootLaser(glm::mat3& axes, nPhysics::cParticle* particle, glm::vec4& cannonVector);
		void ShootBall(glm::mat3& axes, nPhysics::cParticle* particle, glm::vec4& cannonVector);
		void ShootEnergy(glm::mat3& axes, nPhysics::cParticle* particle, glm::vec4& cannonVector);
		//Sets the current projectile type 
		void SetProjectileType(eProjectileType  type);
		//Spaws an instance of the current projectile
		nPhysics::cParticle* SpawnProjectile();
		//Tests if the projectile has reached the timeout
		virtual bool ReachedTimeout(float& timeElapsed, nPhysics::cParticle* particle);
		//tests if the projectile traveled the limit distance
		virtual bool ReachedDistanceLimit(glm::vec3& initialPosition, glm::vec3& currentPosition, nPhysics::cParticle* particle);
		//Apply visual modifications
		virtual void ApplyVisual(nGraphics::cGraphicsComponent* graphic);
		//Test projectile type
		bool IsEnergyBall();
		bool IsBullet();
		bool IsBall();
		bool IsLaser();

	};
}