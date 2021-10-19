#pragma once
#include <physics/cParticle.h>
#include <config/sConfiguration.h>
#include <graphics/cGraphicsComponent.h>

namespace projectile
{
	//Projectile base implementation
	class cBaseProjectile 
	{
	private:
		config::sProjectilePreset preset;
	public:
		cBaseProjectile(){};
		virtual ~cBaseProjectile() {};
		virtual void SetPreset(config::sProjectilePreset& preset);
		virtual config::sProjectilePreset GetPreset();
		virtual bool ReachedTimeout(float& timeElapsed);
		virtual bool ReachedDistanceLimit(glm::vec3& initialPosition, glm::vec3& currentPosition);
		virtual void ApplyVisual(nGraphics::cGraphicsComponent& graphic);
	};
}
